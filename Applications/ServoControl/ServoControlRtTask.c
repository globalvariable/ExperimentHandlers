#include "ServoControlRtTask.h"

static RtTasksData *static_rt_tasks_data = NULL;

static int servo_control_rt_thread = 0;
static bool rt_servo_control_stay_alive = 1;

static void *rt_servo_control(void *args);


bool create_servo_control_rt_thread(RtTasksData *rt_tasks_data)
{
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

	if (! check_rt_task_specs_to_init(static_rt_tasks_data, 3, 0, 0,  10000000))  {
		print_message(ERROR_MSG ,"ServoControl", "ServoControlRtTask", "rt_servo_control", "! check_rt_task_specs_to_init()."); exit(1); }	
        if (! (handler = rt_task_init_schmod(nam2num("SERVOCON"), 10, 10000, 1000, SCHED_FIFO, 1 << ((3*MAX_NUM_OF_CPU_THREADS_PER_CPU)+0)))) {
		print_message(ERROR_MSG ,"ServoControl", "ServoControlRtTask", "rt_servo_control", "handler = rt_task_init_schmod()."); exit(1); }
	if (! write_rt_task_specs_to_rt_tasks_data(static_rt_tasks_data, 3, 0, 0, 10000000, 1000000, 1000000, "ServoControl"))  {
		print_message(ERROR_MSG ,"ServoControl", "ServoControlRtTask", "rt_servo_control", "! write_rt_task_specs_to_rt_tasks_data()."); exit(1); }	
        period = nano2count(10000000);
        rt_task_make_periodic(handler, rt_get_time() + period, period);

        mlockall(MCL_CURRENT | MCL_FUTURE);
	rt_make_hard_real_time();		// do not forget this // check the task by nano /proc/rtai/scheduler (HD/SF) 

	curr_time = rt_get_cpu_time_ns();
	prev_time = curr_time;	
	curr_system_time = static_rt_tasks_data->current_system_time;

        while (rt_servo_control_stay_alive) 
	{
        	rt_task_wait_period();
		curr_time = rt_get_cpu_time_ns();
		evaluate_and_save_jitter(static_rt_tasks_data, 3, 0, 0, prev_time, curr_time);
		prev_time = curr_time;
		curr_system_time = static_rt_tasks_data->current_system_time;
		// routines
		tx_buffer[0] = 'P';
		tx_buffer[1] = 2;
		tx_buffer[2] = 3;

		for (i = 3; i <  tx_pw_command_len; i+=2)
		{
			tx_buffer[i] = servos[(i-3)/2].pulse_command.byte[0]; 
			tx_buffer[i+1] = servos[(i-3)/2].pulse_command.byte[1]; 
		}

		if (! write_to_rs232_com1(tx_buffer, tx_pw_command_len))
			return (void*)print_message(ERROR_MSG ,"ServoControl", "ServoControlRtTask", "rt_servo_control", "! write_to_rs232_com1().");

		evaluate_and_save_period_run_time(static_rt_tasks_data, 3,0,0, curr_time, rt_get_cpu_time_ns());	
	
		// routines	
	       	rt_task_wait_period();
		curr_time = rt_get_cpu_time_ns();
		evaluate_and_save_jitter(static_rt_tasks_data, 3, 0, 0, prev_time, curr_time);
		prev_time = curr_time;
		curr_system_time = static_rt_tasks_data->current_system_time;
		// routines
		if (! read_from_rs232_com1(rx_buffer, rx_position_len))
			return (void*)print_message(ERROR_MSG ,"ServoControl", "ServoControlRtTask", "rt_servo_control", "! read_from_rs232_com1().");

		if ( (rx_buffer[0] != 0x00) || (rx_buffer[1] != 0x00) ) 
			return (void*)print_message(ERROR_MSG ,"ServoControl", "ServoControlRtTask", "rt_servo_control", "! Invalid message from MCU().");

		for (i = 2; i <  rx_position_len; i+=2)
		{
			servos[(i-2)/2].position.byte[0] = rx_buffer[i];
			servos[(i-2)/2].position.byte[1] = rx_buffer[i+1];
		}
/*		for (i = 0; i < NUM_OF_SERVOS; i++)
			printf("%u\t", servos[i].position.position);
		printf("\n");
*/


		evaluate_and_save_period_run_time(static_rt_tasks_data, 3,0,0, curr_time, rt_get_cpu_time_ns());		
		// routines	

        }
	rt_make_soft_real_time();
        rt_task_delete(handler);
	print_message(INFO_MSG ,"FirstBMICageInterfacer", "FirstBMICageInterfacerRtTask", "rt_cage_interfacer", "rt_task_delete().");	

        return 0; 
}
