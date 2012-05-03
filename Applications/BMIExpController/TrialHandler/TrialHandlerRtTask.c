#include "TrialHandlerRtTask.h"

static TrialStatus trial_status = TRIAL_STATUS_NULL;   // Only trial handler can change trial status. 

static TrialTypesData *static_trial_types_data;	
static TrialStatsData *static_trial_stats_data; 
static TrialsHistory *static_trials_history;   

static Gui2TrialHandMsg *static_msgs_gui_2_trial_hand;    

static TrialDurHand2TrialHandMsg *static_msgs_trial_dur_hand_2_trial_hand = NULL;    // Trial Handler only read it, cannot write
static TrialHand2TrialDurHandMsg *static_msgs_trial_hand_2_trial_dur_hand = NULL;     // Trial Handler can write here, cannot read it, trial duration handler will read it

static ExpEnviHand2TrialHandMsg *static_msgs_exp_envi_hand_2_trial_hand = NULL;
static MovObjHand2TrialHandMsg *static_msgs_mov_obj_hand_2_trial_hand = NULL;

static TrialHand2ExpEnviHandMsg *static_msgs_trial_hand_2_exp_envi_hand = NULL;
static TrialHand2MovObjHandMsg *static_msgs_trial_hand_2_mov_obj_hand = NULL;

static int trial_handler_rt_thread = 0;
static bool rt_trial_handler_stay_alive = 1;

static void *rt_trial_handler(void *args);

bool create_trial_handler_rt_thread(TrialTypesData *trial_types_data, TrialStatsData *trial_stats, TrialsHistory *trials_history, Gui2TrialHandMsg *msgs_gui_2_trial_hand, ExpEnviHand2TrialHandMsg *msgs_exp_envi_hand_2_trial_hand, MovObjHand2TrialHandMsg *msgs_mov_obj_hand_2_trial_hand)
{
	trial_status = TRIAL_STATUS_TRIALS_DISABLED;

	static_trial_types_data = trial_types_data;
	static_trial_stats_data = trial_stats;
	static_trials_history = trials_history;
	static_msgs_gui_2_trial_hand = msgs_gui_2_trial_hand;	

	static_msgs_trial_dur_hand_2_trial_hand = allocate_trial_dur_hand_2_trial_hand_msg_buffer(static_msgs_trial_dur_hand_2_trial_hand);

	if(! create_trial_duration_handler_rt_thread(static_msgs_trial_dur_hand_2_trial_hand, &static_msgs_trial_hand_2_trial_dur_hand))
		return print_message(ERROR_MSG ,"BMIExpController", "TrialHandlerRtTask", "create_trial_handler_rt_thread", "create_trial_handler_rt_thread().");	



	if (trial_handler_rt_thread !=0)
		return print_message(BUG_MSG ,"BMIExpController", "TrialHandlerRtTask", "create_trial_handler_rt_thread", "CANNOT create rt_thread again.");	
	trial_handler_rt_thread =  rt_thread_create(rt_trial_handler, NULL, 10000);
	if (trial_handler_rt_thread ==0)
		return print_message(BUG_MSG ,"BMIExpController", "TrialHandlerRtTask", "create_trial_handler_rt_thread", "Couldn' t create rt_thread.");	
	return TRUE;
}

bool kill_trial_handler_rt_thread(void)
{
	return TRUE;
}

static void *rt_trial_handler(void *args)
{
	RT_TASK *handler;
        RTIME period;
	unsigned int prev_time, curr_time;

	if (! check_rt_task_specs_to_init(TRIAL_HANDLER_CPU_ID, TRIAL_HANDLER_CPU_THREAD_ID, TRIAL_HANDLER_PERIOD))  {
		print_message(ERROR_MSG ,"BMIExpController", "TrialHandlerRtTask", "rt_trial_handler", "! check_rt_task_specs_to_init()."); exit(1); }	
        if (! (handler = rt_task_init_schmod(TRIAL_HANDLER_TASK_NAME, TRIAL_HANDLER_TASK_PRIORITY, TRIAL_HANDLER_STACK_SIZE, TRIAL_HANDLER_MSG_SIZE,TRIAL_HANDLER_POLICY, 1 << ((TRIAL_HANDLER_CPU_ID*MAX_NUM_OF_THREADS_PER_CPU)+TRIAL_HANDLER_CPU_THREAD_ID)))) {
		print_message(ERROR_MSG ,"BMIExpController", "TrialHandlerRtTask", "rt_trial_handler", "handler = rt_task_init_schmod()."); exit(1); }
	if (! write_rt_task_specs_to_rt_tasks_data(TRIAL_HANDLER_CPU_ID, TRIAL_HANDLER_CPU_THREAD_ID, TRIAL_HANDLER_PERIOD, TRIAL_HANDLER_POSITIVE_JITTER_THRES, TRIAL_HANDLER_NEGATIVE_JITTER_THRES))  {
		print_message(ERROR_MSG ,"BMIExpController", "TrialHandlerRtTask", "rt_trial_handler", "! write_rt_task_specs_to_rt_tasks_data()."); exit(1); }	
        period = nano2count(TRIAL_HANDLER_PERIOD);
        rt_task_make_periodic(handler, rt_get_time() + period, period);
	prev_time = rt_get_cpu_time_ns();	


        mlockall(MCL_CURRENT | MCL_FUTURE);
	rt_make_hard_real_time();		// do not forget this // check the task by nano /proc/rtai/scheduler (HD/SF) 

        while (rt_trial_handler_stay_alive) 
	{
        	rt_task_wait_period();
		curr_time = rt_get_cpu_time_ns();
		evaluate_and_save_jitter(TRIAL_HANDLER_CPU_ID, TRIAL_HANDLER_CPU_THREAD_ID, prev_time, curr_time);
		prev_time = curr_time;
		// routines
		if (!handle_gui_to_trial_handler_msg(&trial_status, shared_memory->rt_tasks_data.current_system_time, static_msgs_gui_2_trial_hand)) {
			print_message(ERROR_MSG ,"BMIExpController", "TrialHandlerRtTask", "rt_trial_handler", "! handle_gui_to_trial_handler_msg()."); break; }
		if (!handle_trial_dur_handler_to_trial_handler_msg(&trial_status, shared_memory->rt_tasks_data.current_system_time, static_msgs_trial_dur_hand_2_trial_hand))  {
			print_message(ERROR_MSG ,"BMIExpController", "TrialDurationHandlerRtTask", "rt_trial_handler", "! handle_trial_dur_handler_to_trial_handler_msg()."); break; }
		if (!handle_exp_envi_handler_to_trial_handler_msg(&trial_status, shared_memory->rt_tasks_data.current_system_time, static_msgs_exp_envi_hand_2_trial_hand))  {
			print_message(ERROR_MSG ,"BMIExpController", "TrialDurationHandlerRtTask", "rt_trial_handler", "! handle_exp_envi_handler_to_trial_handler_msg()."); break; }
		if (!handle_mov_obj_handler_to_trial_handler_msg(&trial_status, shared_memory->rt_tasks_data.current_system_time, static_msgs_mov_obj_hand_2_trial_hand))  {
			print_message(ERROR_MSG ,"BMIExpController", "TrialDurationHandlerRtTask", "rt_trial_handler", "! handle_mov_obj_handler_to_trial_handler_msg()."); break; }
/*		handle_trial_duration_to_trial_handler_msg
		handle_exp_envi_to_trial_handler_msg
		handle_mov_obj_to_trial_handler_msg
		handle_neural_net_to_trial_handler_msg

*/		// routines	
		evaluate_and_save_period_run_time(TRIAL_HANDLER_CPU_ID, TRIAL_HANDLER_CPU_THREAD_ID, curr_time, rt_get_cpu_time_ns());		
        }
	rt_make_soft_real_time();
        rt_task_delete(handler);
	print_message(INFO_MSG ,"BMIExpController", "TrialHandlerRtTask", "rt_trial_handler", "rt_task_delete().");	

        return 0; 
}
