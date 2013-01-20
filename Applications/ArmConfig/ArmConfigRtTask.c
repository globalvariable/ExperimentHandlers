#include "ArmConfigRtTask.h"

static ThreeDofRobot *static_robot_arm = NULL;

static RtTasksData *static_rt_tasks_data = NULL;

static SEM *exp_envi_rx_buff_sem = NULL;
static SEM *exp_envi_tx_buff_sem = NULL;
static ExpEnviRxShm *exp_envi_rx_buff_shm = NULL;
static ExpEnviTxShm *exp_envi_tx_buff_shm = NULL;

static int servo_control_rt_thread = 0;
static bool rt_servo_control_stay_alive = 1;

static void *rt_servo_control(void *args);


bool create_servo_control_rt_thread(RtTasksData *rt_tasks_data, ThreeDofRobot *robot_arm)
{
	static_robot_arm = robot_arm;

	static_rt_tasks_data = rt_tasks_data;

	if (servo_control_rt_thread != 0)
		return print_message(BUG_MSG ,"ServoControl", "ServoControlRtTask", "create_servo_control_rt_thread", "CANNOT create rt_thread again.");	
	servo_control_rt_thread =  rt_thread_create(rt_servo_control, NULL, 10000);
	if (servo_control_rt_thread == 0)
		return print_message(BUG_MSG ,"ServoControl", "ServoControlRtTask", "create_servo_control_rt_thread", "Couldn' t create rt_thread.");	

	return TRUE;
}

static void *rt_servo_control(void *args)
{
	RT_TASK *handler;
        RTIME period;
	unsigned int prev_time, curr_time, i;
	TimeStamp curr_system_time;

	unsigned char rx_buffer[RX_BUFF_SIZE];
	unsigned char adc_tx_buffer[ADC_TX_BUFF_SIZE];
	unsigned char pw_tx_buffer[PW_TX_BUFF_SIZE];
	ExpEnviTxShm exp_envi_tx_buffer;
	unsigned char cmd_low_byte, cmd_high_byte;

	adc_tx_buffer[0] = 'A';
	adc_tx_buffer[ADC_TX_BUFF_SIZE-2] = 0xFF;
	adc_tx_buffer[ADC_TX_BUFF_SIZE-1] = 0xFF;

	pw_tx_buffer[0] = 'P';
	pw_tx_buffer[PW_TX_BUFF_SIZE-2] = 0xFF;
	pw_tx_buffer[PW_TX_BUFF_SIZE-1] = 0xFF;	

	if (! check_rt_task_specs_to_init(static_rt_tasks_data, 3, 0, 0,  10000000))  {
		print_message(ERROR_MSG ,"ServoControl", "ServoControlRtTask", "rt_servo_control", "! check_rt_task_specs_to_init()."); exit(1); }	
       if (! (handler = rt_task_init_schmod(nam2num("SERVOCON"), 10, 10000, 1000, SCHED_FIFO, 1 << ((3*MAX_NUM_OF_CPU_THREADS_PER_CPU)+0)))) {
		print_message(ERROR_MSG ,"ServoControl", "ServoControlRtTask", "rt_servo_control", "handler = rt_task_init_schmod()."); exit(1); }
	if (! write_rt_task_specs_to_rt_tasks_data(static_rt_tasks_data, 3, 0, 0, 10000000, 1000000, 1000000, "ServoControl"))  {
		print_message(ERROR_MSG ,"ServoControl", "ServoControlRtTask", "rt_servo_control", "! write_rt_task_specs_to_rt_tasks_data()."); exit(1); }	

	// SEMAPHORE should be init'd after rt_task_init_schmod
	if (! init_exp_envi_rx_buffer_semaphore(&exp_envi_rx_buff_sem))  {
		print_message(ERROR_MSG ,"ArmConfig", "ArmConfig", "main", "! init_exp_envi_rx_buffer_semaphore().");	exit(1); }	
	if (! init_exp_envi_tx_buffer_semaphore(&exp_envi_tx_buff_sem))  {
		print_message(ERROR_MSG ,"ArmConfig", "ArmConfig", "main", "! init_exp_envi_tx_buffer_semaphore().");	exit(1); }	
	if (! init_exp_envi_tx_buffer_shm(&exp_envi_tx_buff_shm, EXP_ENVI_CMD_MSG_LEN, static_rt_tasks_data->current_system_time) )  {
		print_message(ERROR_MSG ,"ArmConfig", "ArmConfig", "main", "! init_exp_envi_tx_buffer_shm().");	exit(1); }	
	if (! init_exp_envi_rx_buffer_shm(&exp_envi_rx_buff_shm, EXP_ENVI_STATUS_MSG_LEN) )  {
		print_message(ERROR_MSG ,"ArmConfig", "ArmConfig", "main", "! init_exp_envi_rx_buffer_shm().");	exit(1); }	


        period = nano2count(12500000);
        rt_task_make_periodic(handler, rt_get_time() + period, period);


        mlockall(MCL_CURRENT | MCL_FUTURE);
	rt_make_hard_real_time();		// do not forget this // check the task by nano /proc/rtai/scheduler (HD/SF) 

	curr_time = rt_get_cpu_time_ns();
	prev_time = curr_time;	
	curr_system_time = static_rt_tasks_data->current_system_time;
	if (! read_exp_envi_tx_buff_shm(&exp_envi_tx_buffer, exp_envi_tx_buff_shm, EXP_ENVI_CMD_MSG_LEN, exp_envi_tx_buff_sem)) {   //  Exp Envi Handler writes its command to static_exp_envi_tx_buff for delivery by this process
		print_message(ERROR_MSG ,"ServoControl", "ServoControlRtTask", "rt_servo_control", "! read_exp_envi_tx_buff_shm()."); exit(1); }	
	for (i = 0; i < EXP_ENVI_CMD_MSG_LEN; i++)
		adc_tx_buffer[EXP_ENVI_CMD_MSG_START_IDX+i] = exp_envi_tx_buffer.exp_envi_tx_buff[i];   // 'A' + EXP_ENVI_COMND (1 BYTE) + 0xFF + 0xFF	
	if (! write_to_rs232_com1(adc_tx_buffer, ADC_TX_BUFF_SIZE)) {
		print_message(ERROR_MSG ,"ServoControl", "ServoControlRtTask", "rt_servo_control", "! write_to_rs232_com1()."); exit(1); }	
        while (rt_servo_control_stay_alive) 
	{
        	rt_task_wait_period();
		curr_time = rt_get_cpu_time_ns();
		evaluate_and_save_jitter(static_rt_tasks_data, 3, 0, 0, prev_time, curr_time);
		prev_time = curr_time;
		curr_system_time = static_rt_tasks_data->current_system_time;
		// routines
		clear_rx_buffer(rx_buffer, RX_BUFF_SIZE) ;
		if (! read_from_rs232_com1(rx_buffer, RX_BUFF_SIZE)) {
			print_message(ERROR_MSG ,"ServoControl", "ServoControlRtTask", "rt_servo_control", "! read_from_rs232_com1()."); exit(1); }
		if ((rx_buffer[0] != 0xFF) || (rx_buffer[RX_BUFF_SIZE-2] != 0xFF) || (rx_buffer[RX_BUFF_SIZE-1] != 0xFF)) {
			print_message(ERROR_MSG ,"ServoControl", "ServoControlRtTask", "rt_servo_control", "Invalid rx message format."); exit(1); }
		if (! write_to_exp_envi_rx_buff_shm(&(rx_buffer[EXP_ENVI_STATUS_MSG_START_IDX]), exp_envi_rx_buff_shm, EXP_ENVI_STATUS_MSG_LEN, exp_envi_rx_buff_sem)) {
			print_message(ERROR_MSG ,"ServoControl", "ServoControlRtTask", "rt_servo_control", "! write_to_exp_envi_rx_buff_shm()."); exit(1); }
		for (i = 0; i <  ROBOT_POSITION_MSG_LEN; i+=2)
			write_servo_position_val(&(static_robot_arm->servos[(unsigned int) (i/2)]), rx_buffer[ROBOT_POSITION_MSG_START_IDX + i], rx_buffer[ROBOT_POSITION_MSG_START_IDX + i + 1]);

//		calculate_forward_kinematics(static_robot_arm);
		calculate_forward_kinematics_with_averaging(static_robot_arm);	
	
		for (i = 0; i < THREE_DOF_ROBOT_NUM_OF_SERVOS; i++)
			printf("%u\t", static_robot_arm->servos[i].position.position);
		printf("\n");

//		printf("%u\t%u\t%u\n", servos[0].position.position, servos[1].position.position, servos[2].position.position);

		// routines	

	       	rt_task_wait_period();
		curr_time = rt_get_cpu_time_ns();
		evaluate_and_save_jitter(static_rt_tasks_data, 3, 0, 0, prev_time, curr_time);
		prev_time = curr_time;
		curr_system_time = static_rt_tasks_data->current_system_time;
		// routines

		if (! read_exp_envi_tx_buff_shm(&exp_envi_tx_buffer, exp_envi_tx_buff_shm, EXP_ENVI_CMD_MSG_LEN, exp_envi_tx_buff_sem)) {
			print_message(ERROR_MSG ,"ServoControl", "ServoControlRtTask", "rt_servo_control", "! read_exp_envi_tx_buff_shm()."); exit(1); }
		
//		printf("%u\n", exp_envi_tx_buffer[0]);

		for (i = 0; i < EXP_ENVI_CMD_MSG_LEN; i++)
			pw_tx_buffer[EXP_ENVI_CMD_MSG_START_IDX+i] = exp_envi_tx_buffer.exp_envi_tx_buff[i];

		if ( check_three_dof_robot_security_limits(static_robot_arm))
		{
			evaluate_three_dof_robot_arm_pw_command(static_robot_arm);
			for (i = 0; i < ROBOT_PW_CMD_MSG_LEN; i+=2)
			{
				get_servo_pw_val_bytes(&(static_robot_arm->servos[(unsigned int) (i/2)]), &cmd_low_byte, &cmd_high_byte);
				pw_tx_buffer[ROBOT_PW_CMD_MSG_START_IDX + i] = cmd_low_byte;
 				pw_tx_buffer[ROBOT_PW_CMD_MSG_START_IDX + i +1] = cmd_high_byte;
			}
			if (! write_to_rs232_com1(pw_tx_buffer, PW_TX_BUFF_SIZE)) {
				print_message(ERROR_MSG ,"ServoControl", "ServoControlRtTask", "rt_servo_control", "! write_to_rs232_com1()."); exit(1); }	
		}
		else
		{
			print_message(ERROR_MSG ,"ServoControl", "ServoControlRtTask", "rt_servo_control", "! check_three_dof_robot_out_of_security_limits()."); exit(1);
		}

		evaluate_and_save_period_run_time(static_rt_tasks_data, 3,0,0, curr_time, rt_get_cpu_time_ns());		
		// routines	

        }
	rt_make_soft_real_time();
        rt_task_delete(handler);
	print_message(INFO_MSG ,"FirstBMICageInterfacer", "FirstBMICageInterfacerRtTask", "rt_cage_interfacer", "rt_task_delete().");	

        return 0; 
}
