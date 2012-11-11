#include "ExpEnviControlRtTask.h"

static RtTasksData *static_rt_tasks_data = NULL;
static SEM *static_exp_envi_rx_buff_sem = NULL;
static SEM *static_exp_envi_tx_buff_sem = NULL;
static unsigned char *static_exp_envi_rx_buff = NULL;
static unsigned char *static_exp_envi_tx_buff = NULL;

static int exp_envi_control_rt_thread = 0;
static bool rt_exp_envi_control_stay_alive = 1;

static void *rt_exp_envi_control(void *args);


bool create_exp_envi_control_rt_thread(RtTasksData *rt_tasks_data, SEM* exp_envi_rx_buff_sem, SEM *exp_envi_tx_buff_sem, unsigned char *exp_envi_rx_buff, unsigned char *exp_envi_tx_buff)
{
	static_rt_tasks_data = rt_tasks_data;
	static_exp_envi_rx_buff_sem = exp_envi_rx_buff_sem;
	static_exp_envi_tx_buff_sem = exp_envi_tx_buff_sem; 
	static_exp_envi_rx_buff = exp_envi_rx_buff;
	static_exp_envi_tx_buff = exp_envi_tx_buff;

	if (exp_envi_control_rt_thread != 0)
		return print_message(BUG_MSG ,"ExpEnviControl", "ExpEnviControlRtTask", "create_exp_envi_control_rt_thread", "CANNOT create rt_thread again.");	

	exp_envi_control_rt_thread =  rt_thread_create(rt_exp_envi_control, NULL, 10000);
	if (exp_envi_control_rt_thread == 0)
		return print_message(BUG_MSG ,"ExpEnviControl", "ExpEnviControlRtTask", "create_exp_envi_control_rt_thread", "Couldn' t create rt_thread.");	

	return TRUE;
}

static void *rt_exp_envi_control(void *args)
{
	RT_TASK *handler;
        RTIME period;
	unsigned int prev_time, curr_time;
	unsigned int cntr = 0;
	TimeStamp curr_system_time;
	unsigned char exp_envi_tx_buffer[EXP_ENVI_CMD_MSG_LEN];
	unsigned char exp_envi_rx_buffer[EXP_ENVI_STATUS_MSG_LEN];

	if (! check_rt_task_specs_to_init(static_rt_tasks_data, 2, 0, 1,  10000000))  {
		print_message(ERROR_MSG ,"ExpEnviControl", "ExpEnviControlRtTask", "rt_exp_envi_control", "! check_rt_task_specs_to_init()."); exit(1); }	
       if (! (handler = rt_task_init_schmod(nam2num("EXPENCON"), 10, 10000, 1000, SCHED_FIFO, 1 << ((2*MAX_NUM_OF_CPU_THREADS_PER_CPU)+0)))) {
		print_message(ERROR_MSG ,"ExpEnviControl", "ExpEnviControlRtTask", "rt_exp_envi_control", "handler = rt_task_init_schmod()."); exit(1); }
	if (! write_rt_task_specs_to_rt_tasks_data(static_rt_tasks_data, 2, 0, 1, 10000000, 1000000, 1000000, "ExpEnviControl"))  {
		print_message(ERROR_MSG ,"ExpEnviControl", "ExpEnviControlRtTask", "rt_exp_envi_control", "! write_rt_task_specs_to_rt_tasks_data()."); exit(1); }	

        period = nano2count(12500000);
        rt_task_make_periodic(handler, rt_get_time() + period, period);

        mlockall(MCL_CURRENT | MCL_FUTURE);
	rt_make_hard_real_time();		// do not forget this // check the task by nano /proc/rtai/scheduler (HD/SF) 

	curr_time = rt_get_cpu_time_ns();
	prev_time = curr_time;	
	curr_system_time = static_rt_tasks_data->current_system_time;

	exp_envi_cmd.all_cmd = 0;
	exp_envi_tx_buffer[0] = exp_envi_cmd.all_cmd;
	if (! write_to_exp_envi_tx_buff_shm(exp_envi_tx_buffer, static_exp_envi_tx_buff, EXP_ENVI_CMD_MSG_LEN, static_exp_envi_tx_buff_sem)) {   //  Exp Envi Handler writes its command to static_exp_envi_tx_buff for delivery by this process
		print_message(ERROR_MSG ,"ServoControl", "ServoControlRtTask", "rt_servo_control", "! read_exp_envi_tx_buff_shm()."); exit(1); }	

        while (rt_exp_envi_control_stay_alive) 
	{
        	rt_task_wait_period();
		curr_time = rt_get_cpu_time_ns();
		evaluate_and_save_jitter(static_rt_tasks_data, 2, 0, 1, prev_time, curr_time);
		prev_time = curr_time;
		curr_system_time = static_rt_tasks_data->current_system_time;
		// routines
		if (! read_exp_envi_rx_buff_shm(exp_envi_rx_buffer, static_exp_envi_rx_buff, EXP_ENVI_STATUS_MSG_LEN, static_exp_envi_rx_buff_sem)) {  
			print_message(ERROR_MSG ,"ServoControl", "ServoControlRtTask", "rt_servo_control", "! read_exp_envi_tx_buff_shm()."); exit(1); }	
		exp_envi_status.all_status = exp_envi_rx_buffer[0];
		printf("%u\t%u\t%u\n", exp_envi_status.ir_beam, exp_envi_status.left_lever, exp_envi_status.right_lever);
		evaluate_and_save_period_run_time(static_rt_tasks_data, 2,0,1, curr_time, rt_get_cpu_time_ns());	
	
		// routines	
	       	rt_task_wait_period();
		curr_time = rt_get_cpu_time_ns();
		evaluate_and_save_jitter(static_rt_tasks_data, 2, 0, 1, prev_time, curr_time);
		prev_time = curr_time;
		curr_system_time = static_rt_tasks_data->current_system_time;
		// routines
		exp_envi_cmd.all_cmd = 0;
		exp_envi_cmd.guide_led = 1;
		exp_envi_cmd.left_led = 1;
		exp_envi_cmd.right_led = 0;
		cntr ++;
		if (cntr == 16)
		{
			cntr = 0;
			if (exp_envi_cmd.levers_avaiable)
				exp_envi_cmd.levers_avaiable = 0;
			else
				exp_envi_cmd.levers_avaiable = 1;
			if (exp_envi_cmd.valve)
				exp_envi_cmd.valve = 0;
			else
				exp_envi_cmd.valve = 1;
		}
		exp_envi_tx_buffer[0] = exp_envi_cmd.all_cmd;
		if (! write_to_exp_envi_tx_buff_shm(exp_envi_tx_buffer, static_exp_envi_tx_buff, EXP_ENVI_CMD_MSG_LEN, static_exp_envi_tx_buff_sem)) {   //  Exp Envi Handler writes its command to static_exp_envi_tx_buff for delivery by this process
			print_message(ERROR_MSG ,"ServoControl", "ServoControlRtTask", "rt_servo_control", "! read_exp_envi_tx_buff_shm()."); exit(1); }	

		evaluate_and_save_period_run_time(static_rt_tasks_data, 2,0,1, curr_time, rt_get_cpu_time_ns());		
		// routines	
        }
	rt_make_soft_real_time();
        rt_task_delete(handler);
	print_message(INFO_MSG ,"FirstBMICageInterfacer", "FirstBMICageInterfacerRtTask", "rt_cage_interfacer", "rt_task_delete().");	

        return 0; 
}
