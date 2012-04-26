#include "TrialHandlerRtTask.h"

static TrialStatus trial_status = TRIAL_STATUS_NULL;   // Only trial handler can change trial status. 

static TrialTypesData *static_trial_types_data;	
static TrialStatsData *static_trial_stats_data; 
static TrialsHistory *static_trials_history;   

static Gui2TrialHandMsg *static_msgs_gui_2_trial_hand;    

static TrialDurHand2TrialHandMsg *msgs_trial_dur_hand_2_trial_hand;    
static TrialHand2TrialDurHandMsg *msgs_trial_hand_2_trial_dur_hand;    

static int trial_handler_rt_thread = 0;

static void *rt_trial_handler(void *args);

bool create_trial_handler_rt_thread(TrialTypesData *trial_types_data, TrialStatsData *trial_stats, TrialsHistory *trials_history, Gui2TrialHandMsg *msgs_gui_2_trial_hand)
{
   	shared_memory = (SharedMemStruct*)rtai_malloc(nam2num(SHARED_MEM_NAME), SHARED_MEM_SIZE);
	if (shared_memory == NULL) {
		return print_message(ERROR_MSG ,"BMISimulationTrialController", "BMISimulationTrialController", "main", "shared_memory == NULL.");	return -1; }

	trial_status = TRIAL_STATUS_TRIALS_DISABLED;

	static_trial_types_data = trial_types_data;
	static_trial_stats_data = trial_stats;
	static_trials_history = trials_history;
	static_msgs_gui_2_trial_hand = msgs_gui_2_trial_hand;	

//	msgs_trial_dur_hand_2_trial_hand = allocate

	if(! create_trial_duration_handler_rt_thread(msgs_trial_dur_hand_2_trial_hand, &msgs_trial_hand_2_trial_dur_hand))
		return print_message(ERROR_MSG ,"BMISimulationTrialController", "BMISimulationTrialController", "main", "create_trial_handler_rt_thread().");	

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
/*	RT_TASK *handler;
        RTIME period;
	unsigned int prev_time, curr_time;

	if (! check_rt_task_specs_to_init(IZ_PS_NETWORK_SIM_CPU_ID, IZ_PS_NETWORK_SIM_CPU_THREAD_ID, IZ_PS_NETWORK_SIM_PERIOD))  {
		print_message(ERROR_MSG ,"HybridNetRLBMI", "HybridNetRLBMIRtTask", "hybrid_net_rl_bmi_internal_network_handler", "! check_rt_task_specs_to_init()."); exit(1); }	
        if (! (handler = rt_task_init_schmod(IZ_PS_NETWORK_SIM_PERIOD_SIM_TASK_NAME, IZ_PS_NETWORK_SIM_PERIOD_SIM_TASK_PRIORITY, IZ_PS_NETWORK_SIM_STACK_SIZE, IZ_PS_NETWORK_SIM_MSG_SIZE, IZ_PS_NETWORK_SIM_POLICY, 1 << ((IZ_PS_NETWORK_SIM_CPU_ID*MAX_NUM_OF_THREADS_PER_CPU)+IZ_PS_NETWORK_SIM_CPU_THREAD_ID)))) {
		print_message(ERROR_MSG ,"HybridNetRLBMI", "HybridNetRLBMIRtTask", "hybrid_net_rl_bmi_internal_network_handler", "handler = rt_task_init_schmod()."); exit(1); }
	if (! write_rt_task_specs_to_rt_tasks_data(IZ_PS_NETWORK_SIM_CPU_ID, IZ_PS_NETWORK_SIM_CPU_THREAD_ID, IZ_PS_NETWORK_SIM_PERIOD, IZ_PS_NETWORK_SIM_POSITIVE_JITTER_THRES, IZ_PS_NETWORK_SIM_NEGATIVE_JITTER_THRES))  {
		print_message(ERROR_MSG ,"HybridNetRLBMI", "HybridNetRLBMIRtTask", "hybrid_net_rl_bmi_internal_network_handler", "! write_rt_task_specs_to_rt_tasks_data()."); exit(1); }	
        period = nano2count(IZ_PS_NETWORK_SIM_PERIOD);
        rt_task_make_periodic(handler, rt_get_time() + period, period);
	prev_time = rt_get_cpu_time_ns();	


        mlockall(MCL_CURRENT | MCL_FUTURE);
	rt_make_hard_real_time();		// do not forget this // check the task by nano /proc/rtai/scheduler (HD/SF) 

        while (rt_trial_handler_stay_alive) 
	{
        	rt_task_wait_period();
		curr_time = rt_get_cpu_time_ns();
		evaluate_and_save_jitter(IZ_PS_NETWORK_SIM_CPU_ID, IZ_PS_NETWORK_SIM_CPU_THREAD_ID, prev_time, curr_time);
		prev_time = curr_time;
		// routines
		handle_trial_duration_to_trial_handler_msg
		handle_exp_envi_to_trial_handler_msg
		handle_mov_obj_to_trial_handler_msg
		handle_neural_net_to_trial_handler_msg
		handle_gui_to_trial_handler_msg
		// routines	
		evaluate_and_save_period_run_time(IZ_PS_NETWORK_SIM_CPU_ID, IZ_PS_NETWORK_SIM_CPU_THREAD_ID, curr_time, rt_get_cpu_time_ns());		
        }
	rt_make_soft_real_time();
        rt_task_delete(handler);
	print_message(INFO_MSG ,"HybridNetRLBMI", "HybridNetRLBMIRtTask", "hybrid_net_rl_bmi_internal_network_handler", "rt_task_delete().");	
*/
        return 0; 
}
