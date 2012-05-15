#include "ExpEnviDurationHandlerRtTask.h"

static ExpEnviInputsDurationStatus *exp_envi_inputs_duration_status = NULL;   // Only exp envi duration handler can change exp envi duration status. 
static TimeStamp *inputs_handling_end_time = NULL;
static unsigned int num_of_input_components = 0;
///  Define the guys above for outputs as well when necessary. 

static ExpEnviHand2ExpEnviDurHandMsg *static_msgs_exp_envi_hand_2_exp_envi_dur_hand = NULL;    
static ExpEnviDurHand2ExpEnviHandMsg *static_msgs_exp_envi_dur_hand_2_exp_envi_hand = NULL;    

static int exp_envi_duration_handler_rt_thread = 0;
static bool rt_exp_envi_duration_handler_stay_alive = 1;


static void *rt_exp_envi_duration_handler(void *args);

bool create_exp_envi_duration_handler_rt_thread(ExpEnviDurHand2ExpEnviHandMsg *msgs_exp_envi_dur_hand_2_exp_envi_hand, ExpEnviHand2ExpEnviDurHandMsg *msgs_exp_envi_hand_2_exp_envi_dur_hand, unsigned int num_of_inp_comps)
{
	static_msgs_exp_envi_dur_hand_2_exp_envi_hand = msgs_exp_envi_dur_hand_2_exp_envi_hand;
	static_msgs_exp_envi_hand_2_exp_envi_dur_hand = msgs_exp_envi_hand_2_exp_envi_dur_hand;
	num_of_input_components = num_of_inp_comps;
	exp_envi_inputs_duration_status = g_new0(ExpEnviInputsDurationStatus, num_of_inp_comps);
	inputs_handling_end_time = g_new0(TimeStamp, num_of_inp_comps);
//	exp_envi_duration_status = EXP_ENVI_DUR_STATUS_OUTSIDE_EXP_ENVI_PHASE;
	if (exp_envi_duration_handler_rt_thread !=0)
		return print_message(BUG_MSG ,"BMIExpController", "ExpEnviHandlerRtTask", "create_exp_envi_duration_handler_rt_thread", "CANNOT create rt_thread again.");	
	exp_envi_duration_handler_rt_thread =  rt_thread_create(rt_exp_envi_duration_handler, NULL, 10000);
	if (exp_envi_duration_handler_rt_thread ==0)
		return print_message(BUG_MSG ,"BMIExpController", "ExpEnviHandlerRtTask", "create_exp_envi_duration_handler_rt_thread", "Couldn' t create rt_thread.");	
	return TRUE;
}

bool kill_exp_envi_duration_handler_rt_thread(void)
{
	return TRUE;
}

static void *rt_exp_envi_duration_handler(void *args)
{
	RT_TASK *handler;
        RTIME period;
	unsigned int prev_time, curr_time;
	TimeStamp curr_system_time;

	if (! check_rt_task_specs_to_init(EXP_ENVI_DURATION_HANDLER_CPU_ID, EXP_ENVI_DURATION_HANDLER_CPU_THREAD_ID, EXP_ENVI_DURATION_HANDLER_PERIOD))  {
		print_message(ERROR_MSG ,"BMIExpController", "ExpEnviDurationHandlerRtTask", "rt_exp_envi_duration_handler", "! check_rt_task_specs_to_init()."); exit(1); }	
        if (! (handler = rt_task_init_schmod(EXP_ENVI_DURATION_HANDLER_TASK_NAME, EXP_ENVI_DURATION_HANDLER_TASK_PRIORITY, EXP_ENVI_DURATION_HANDLER_STACK_SIZE, EXP_ENVI_DURATION_HANDLER_MSG_SIZE,EXP_ENVI_DURATION_HANDLER_POLICY, 1 << ((EXP_ENVI_DURATION_HANDLER_CPU_ID*MAX_NUM_OF_THREADS_PER_CPU)+EXP_ENVI_DURATION_HANDLER_CPU_THREAD_ID)))) {
		print_message(ERROR_MSG ,"BMIExpController", "ExpEnviDurationHandlerRtTask", "rt_exp_envi_duration_handler", "handler = rt_task_init_schmod()."); exit(1); }
	if (! write_rt_task_specs_to_rt_tasks_data(EXP_ENVI_DURATION_HANDLER_CPU_ID, EXP_ENVI_DURATION_HANDLER_CPU_THREAD_ID, EXP_ENVI_DURATION_HANDLER_PERIOD, EXP_ENVI_DURATION_HANDLER_POSITIVE_JITTER_THRES, EXP_ENVI_DURATION_HANDLER_NEGATIVE_JITTER_THRES))  {
		print_message(ERROR_MSG ,"BMIExpController", "ExpEnviDurationHandlerRtTask", "rt_exp_envi_duration_handler", "! write_rt_task_specs_to_rt_tasks_data()."); exit(1); }	
        period = nano2count(EXP_ENVI_HANDLER_PERIOD);
        rt_task_make_periodic(handler, rt_get_time() + period, period);
	prev_time = rt_get_cpu_time_ns();	


        mlockall(MCL_CURRENT | MCL_FUTURE);
	rt_make_hard_real_time();		// do not forget this // check the task by nano /proc/rtai/scheduler (HD/SF) 

        while (rt_exp_envi_duration_handler_stay_alive) 
	{
        	rt_task_wait_period();
		curr_time = rt_get_cpu_time_ns();
		evaluate_and_save_jitter(EXP_ENVI_DURATION_HANDLER_CPU_ID, EXP_ENVI_DURATION_HANDLER_CPU_THREAD_ID, prev_time, curr_time);
		prev_time = curr_time;
		curr_system_time = shared_memory->rt_tasks_data.current_system_time;
		// routines
		if (! handle_exp_envi_handler_to_exp_envi_dur_handler_msg(exp_envi_inputs_duration_status, curr_system_time, static_msgs_exp_envi_hand_2_exp_envi_dur_hand, inputs_handling_end_time)) {
			print_message(ERROR_MSG ,"BMIExpController", "ExpEnviDurationHandlerRtTask", "rt_exp_envi_duration_handler", "! handle_exp_envi_handler_to_exp_envi_dur_handler_msg()."); break; }
		if (! handle_exp_envi_handler_duration(exp_envi_inputs_duration_status, curr_system_time, inputs_handling_end_time, num_of_input_components, static_msgs_exp_envi_dur_hand_2_exp_envi_hand))  {
			print_message(ERROR_MSG ,"BMIExpController", "ExpEnviDurationHandlerRtTask", "rt_exp_envi_duration_handler", "! handle_exp_envi_handler_duration()."); break; }
		// routines	
		evaluate_and_save_period_run_time(EXP_ENVI_DURATION_HANDLER_CPU_ID, EXP_ENVI_DURATION_HANDLER_CPU_THREAD_ID, curr_time, rt_get_cpu_time_ns());		
        }
	rt_make_soft_real_time();
        rt_task_delete(handler);
	print_message(INFO_MSG ,"BMIExpController", "ExpEnviDurationHandlerRtTask", "rt_exp_envi_duration_handler", "rt_task_delete().");	

        return 0; 
}
