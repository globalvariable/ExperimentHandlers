#include "ExpEnviHandlerRtTask.h"

static int exp_envi_handler_rt_thread = 0;
static bool rt_exp_envi_handler_stay_alive = 1;

static void *rt_exp_envi_handler(void *args);

bool create_exp_envi_handler_rt_thread(Gui2ExpEnviHandMsg *msgs_gui_2_exp_envi_hand)
{

/*	static_msgs_trial_dur_hand_2_trial_hand = allocate_trial_dur_hand_2_trial_hand_msg_buffer(static_msgs_trial_dur_hand_2_trial_hand);

	if(! create_trial_duration_handler_rt_thread(static_msgs_trial_dur_hand_2_trial_hand, &static_msgs_trial_hand_2_trial_dur_hand))
		return print_message(ERROR_MSG ,"BMIExpController", "TrialHandlerRtTask", "create_trial_handler_rt_thread", "create_trial_handler_rt_thread().");	
*/

	if (exp_envi_handler_rt_thread !=0)
		return print_message(BUG_MSG ,"BMIExpController", "ExpEnviHandlerRtTask", "create_exp_envi_handler_rt_thread", "CANNOT create rt_thread again.");	
	exp_envi_handler_rt_thread =  rt_thread_create(rt_exp_envi_handler, NULL, 10000);
	if (exp_envi_handler_rt_thread ==0)
		return print_message(BUG_MSG ,"BMIExpController", "ExpEnviHandlerRtTask", "create_exp_envi_handler_rt_thread", "Couldn' t create rt_thread.");	
	return TRUE;
}

bool kill_exp_envi_handler_rt_thread(void)
{
	return TRUE;
}

static void *rt_exp_envi_handler(void *args)
{
	RT_TASK *handler;
        RTIME period;
	unsigned int prev_time, curr_time;

	if (! check_rt_task_specs_to_init(EXP_ENVI_HANDLER_CPU_ID, EXP_ENVI_HANDLER_CPU_THREAD_ID, EXP_ENVI_HANDLER_PERIOD))  {
		print_message(ERROR_MSG ,"BMIExpController", "ExpEnviHandlerRtTask", "rt_exp_envi_handler", "! check_rt_task_specs_to_init()."); exit(1); }	
        if (! (handler = rt_task_init_schmod(EXP_ENVI_HANDLER_TASK_NAME, EXP_ENVI_HANDLER_TASK_PRIORITY, EXP_ENVI_HANDLER_STACK_SIZE, EXP_ENVI_HANDLER_MSG_SIZE,EXP_ENVI_HANDLER_POLICY, 1 << ((EXP_ENVI_HANDLER_CPU_ID*MAX_NUM_OF_THREADS_PER_CPU)+EXP_ENVI_HANDLER_CPU_THREAD_ID)))) {
		print_message(ERROR_MSG ,"BMIExpController", "ExpEnviHandlerRtTask", "rt_exp_envi_handler", "handler = rt_task_init_schmod()."); exit(1); }
	if (! write_rt_task_specs_to_rt_tasks_data(EXP_ENVI_HANDLER_CPU_ID, EXP_ENVI_HANDLER_CPU_THREAD_ID, EXP_ENVI_HANDLER_PERIOD, EXP_ENVI_HANDLER_POSITIVE_JITTER_THRES, EXP_ENVI_HANDLER_NEGATIVE_JITTER_THRES))  {
		print_message(ERROR_MSG ,"BMIExpController", "ExpEnviHandlerRtTask", "rt_exp_envi_handler", "! write_rt_task_specs_to_rt_tasks_data()."); exit(1); }	
        period = nano2count(EXP_ENVI_HANDLER_PERIOD);
        rt_task_make_periodic(handler, rt_get_time() + period, period);
	prev_time = rt_get_cpu_time_ns();	


        mlockall(MCL_CURRENT | MCL_FUTURE);
	rt_make_hard_real_time();		// do not forget this // check the task by nano /proc/rtai/scheduler (HD/SF) 

        while (rt_exp_envi_handler_stay_alive) 
	{
        	rt_task_wait_period();
		curr_time = rt_get_cpu_time_ns();
		evaluate_and_save_jitter(EXP_ENVI_HANDLER_CPU_ID, EXP_ENVI_HANDLER_CPU_THREAD_ID, prev_time, curr_time);
		prev_time = curr_time;
		// routines


		// routines	
		evaluate_and_save_period_run_time(EXP_ENVI_HANDLER_CPU_ID, EXP_ENVI_HANDLER_CPU_THREAD_ID, curr_time, rt_get_cpu_time_ns());		
        }
	rt_make_soft_real_time();
        rt_task_delete(handler);
	print_message(INFO_MSG ,"BMIExpController", "ExpEnviHandlerRtTask", "rt_exp_envi_handler", "rt_task_delete().");	

        return 0; 
}
