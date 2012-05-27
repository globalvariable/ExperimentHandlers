#include "TrialHandlerRtTask.h"

static RtTasksData *static_rt_tasks_data = NULL;

static TrialStatus trial_status = TRIAL_STATUS_NULL;   // Only trial handler can change trial status. 

static TrialTypesData *static_trial_types_data = NULL;	
static TrialStatsData *static_trial_stats_data = NULL; 
static TrialsHistory *static_trials_history = NULL;   

static Gui2TrialHandMsg *static_msgs_gui_2_trial_hand = NULL;    

static ExpEnviHand2TrialHandMsg *msgs_exp_envi_hand_2_trial_hand = NULL;
static MovObjHand2TrialHandMsg *msgs_mov_obj_hand_2_trial_hand = NULL;

static TrialHand2ExpEnviHandMsg *msgs_trial_hand_2_exp_envi_hand = NULL;
static TrialHand2MovObjHandMsg *msgs_trial_hand_2_mov_obj_hand = NULL;

static TrialDurHand2TrialHandMsg *msgs_trial_dur_hand_2_trial_hand = NULL;    // Trial Handler only read it, cannot write
static TrialHand2TrialDurHandMsg *msgs_trial_hand_2_trial_dur_hand = NULL;     // Trial Handler can write here, cannot read it, trial duration handler will read it

static TrialHand2NeuralNetMsg *msgs_trial_hand_2_neural_net = NULL;
static NeuralNet2TrialHandMsg *msgs_neural_net_2_trial_hand = NULL;

static TrialHand2SpikeGenMsg *msgs_trial_hand_2_spike_gen = NULL;
static SpikeGen2TrialHandMsg *msgs_spike_gen_2_trial_hand = NULL;

static int trial_handler_rt_thread = 0;
static bool rt_trial_handler_stay_alive = 1;

static void *rt_trial_handler(void *args);

static bool connect_to_exp_envi_hand(void);
static bool connect_to_mov_obj_hand(void);
static bool connect_to_neural_net(void);
static bool connect_to_spike_gen(void);

bool create_trial_handler_rt_thread(RtTasksData *rt_tasks_data, TrialTypesData *trial_types_data, TrialStatsData *trial_stats, TrialsHistory *trials_history, Gui2TrialHandMsg *msgs_gui_2_trial_hand)
{
	static_rt_tasks_data = rt_tasks_data;

	trial_status = TRIAL_STATUS_TRIALS_DISABLED;

	static_trial_types_data = trial_types_data;
	static_trial_stats_data = trial_stats;
	static_trials_history = trials_history;
	static_msgs_gui_2_trial_hand = msgs_gui_2_trial_hand;	

	msgs_exp_envi_hand_2_trial_hand = allocate_shm_server_exp_envi_hand_2_trial_hand_msg_buffer(msgs_exp_envi_hand_2_trial_hand);
	msgs_mov_obj_hand_2_trial_hand = allocate_shm_server_mov_obj_hand_2_trial_hand_msg_buffer(msgs_mov_obj_hand_2_trial_hand);
	msgs_neural_net_2_trial_hand = allocate_shm_server_neural_net_2_trial_hand_msg_buffer(msgs_neural_net_2_trial_hand);
	msgs_spike_gen_2_trial_hand = allocate_shm_server_spike_gen_2_trial_hand_msg_buffer(msgs_spike_gen_2_trial_hand);

	if (!connect_to_neural_net())
		return print_message(ERROR_MSG ,"TrialHandler", "TrialHandlerRtTask", "create_trial_handler_rt_thread", "connect_to_neural_net().");	
	if (!connect_to_spike_gen())
		return print_message(ERROR_MSG ,"TrialHandler", "TrialHandlerRtTask", "create_trial_handler_rt_thread", "connect_to_spike_gen().");	
	if (! connect_to_exp_envi_hand())
		return print_message(ERROR_MSG ,"TrialHandler", "TrialHandlerRtTask", "create_trial_handler_rt_thread", "connect_to_exp_envi_hand().");	
	if (! connect_to_mov_obj_hand())
		return print_message(ERROR_MSG ,"TrialHandler", "TrialHandlerRtTask", "create_trial_handler_rt_thread", "connect_to_exp_envi_hand().");	

	msgs_trial_dur_hand_2_trial_hand = allocate_trial_dur_hand_2_trial_hand_msg_buffer(msgs_trial_dur_hand_2_trial_hand);
	msgs_trial_hand_2_trial_dur_hand = allocate_trial_hand_2_trial_dur_hand_msg_buffer(msgs_trial_hand_2_trial_dur_hand);

	if(! create_trial_duration_handler_rt_thread(rt_tasks_data, msgs_trial_dur_hand_2_trial_hand, msgs_trial_hand_2_trial_dur_hand))
		return print_message(ERROR_MSG ,"TrialHandler", "TrialHandlerRtTask", "create_trial_handler_rt_thread", "create_trial_handler_rt_thread().");	

	if (trial_handler_rt_thread !=0)
		return print_message(BUG_MSG ,"TrialHandler", "TrialHandlerRtTask", "create_trial_handler_rt_thread", "CANNOT create rt_thread again.");	
	trial_handler_rt_thread =  rt_thread_create(rt_trial_handler, NULL, 10000);
	if (trial_handler_rt_thread ==0)
		return print_message(BUG_MSG ,"TrialHandler", "TrialHandlerRtTask", "create_trial_handler_rt_thread", "Couldn' t create rt_thread.");	
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
	TimeStamp curr_system_time;
	if (! check_rt_task_specs_to_init(static_rt_tasks_data, TRIAL_HANDLER_CPU_ID, TRIAL_HANDLER_CPU_THREAD_ID, TRIAL_HANDLER_PERIOD))  {
		print_message(ERROR_MSG ,"TrialHandler", "TrialHandlerRtTask", "rt_trial_handler", "! check_rt_task_specs_to_init()."); exit(1); }	
        if (! (handler = rt_task_init_schmod(TRIAL_HANDLER_TASK_NAME, TRIAL_HANDLER_TASK_PRIORITY, TRIAL_HANDLER_STACK_SIZE, TRIAL_HANDLER_MSG_SIZE,TRIAL_HANDLER_POLICY, 1 << ((TRIAL_HANDLER_CPU_ID*MAX_NUM_OF_THREADS_PER_CPU)+TRIAL_HANDLER_CPU_THREAD_ID)))) {
		print_message(ERROR_MSG ,"TrialHandler", "TrialHandlerRtTask", "rt_trial_handler", "handler = rt_task_init_schmod()."); exit(1); }
	if (! write_rt_task_specs_to_rt_tasks_data(static_rt_tasks_data, TRIAL_HANDLER_CPU_ID, TRIAL_HANDLER_CPU_THREAD_ID, TRIAL_HANDLER_PERIOD, TRIAL_HANDLER_POSITIVE_JITTER_THRES, TRIAL_HANDLER_NEGATIVE_JITTER_THRES))  {
		print_message(ERROR_MSG ,"TrialHandler", "TrialHandlerRtTask", "rt_trial_handler", "! write_rt_task_specs_to_rt_tasks_data()."); exit(1); }	
        period = nano2count(TRIAL_HANDLER_PERIOD);
        rt_task_make_periodic(handler, rt_get_time() + period, period);
	prev_time = rt_get_cpu_time_ns();	


        mlockall(MCL_CURRENT | MCL_FUTURE);
	rt_make_hard_real_time();		// do not forget this // check the task by nano /proc/rtai/scheduler (HD/SF) 

        while (rt_trial_handler_stay_alive) 
	{
        	rt_task_wait_period();
		curr_time = rt_get_cpu_time_ns();
		evaluate_and_save_jitter(static_rt_tasks_data, TRIAL_HANDLER_CPU_ID, TRIAL_HANDLER_CPU_THREAD_ID, prev_time, curr_time);
		prev_time = curr_time;
		curr_system_time = static_rt_tasks_data->current_system_time;
		// routines
		if (!handle_gui_to_trial_handler_msg(static_trial_types_data, &trial_status, curr_system_time, static_msgs_gui_2_trial_hand, msgs_trial_hand_2_trial_dur_hand, msgs_trial_hand_2_exp_envi_hand, msgs_trial_hand_2_mov_obj_hand, msgs_trial_hand_2_neural_net, msgs_trial_hand_2_spike_gen)) {
			print_message(ERROR_MSG ,"TrialHandler", "TrialHandlerRtTask", "rt_trial_handler", "! handle_gui_to_trial_handler_msg()."); break; }
		if (!handle_trial_dur_handler_to_trial_handler_msg(static_trial_types_data, static_trials_history, &trial_status, curr_system_time, msgs_trial_dur_hand_2_trial_hand, msgs_trial_hand_2_trial_dur_hand, msgs_trial_hand_2_exp_envi_hand, msgs_trial_hand_2_mov_obj_hand, msgs_trial_hand_2_neural_net, msgs_trial_hand_2_spike_gen))  {
			print_message(ERROR_MSG ,"TrialHandler", "TrialDurationHandlerRtTask", "rt_trial_handler", "! handle_trial_dur_handler_to_trial_handler_msg()."); break; }
		if (!handle_exp_envi_handler_to_trial_handler_msg(static_trial_types_data, static_trials_history, &trial_status, curr_system_time, msgs_exp_envi_hand_2_trial_hand, msgs_trial_hand_2_trial_dur_hand, msgs_trial_hand_2_exp_envi_hand, msgs_trial_hand_2_mov_obj_hand, msgs_trial_hand_2_neural_net, msgs_trial_hand_2_spike_gen))  {
			print_message(ERROR_MSG ,"TrialHandler", "TrialDurationHandlerRtTask", "rt_trial_handler", "! handle_exp_envi_handler_to_trial_handler_msg()."); break; }
		if (!handle_mov_obj_handler_to_trial_handler_msg(static_trial_types_data, static_trials_history, static_trial_stats_data, &trial_status, curr_system_time, msgs_mov_obj_hand_2_trial_hand, msgs_trial_hand_2_trial_dur_hand, msgs_trial_hand_2_exp_envi_hand, msgs_trial_hand_2_mov_obj_hand, msgs_trial_hand_2_neural_net, msgs_trial_hand_2_spike_gen))  {
			print_message(ERROR_MSG ,"TrialHandler", "TrialDurationHandlerRtTask", "rt_trial_handler", "! handle_mov_obj_handler_to_trial_handler_msg()."); break; }
		// routines	
		evaluate_and_save_period_run_time(static_rt_tasks_data, TRIAL_HANDLER_CPU_ID, TRIAL_HANDLER_CPU_THREAD_ID, curr_time, rt_get_cpu_time_ns());		
        }
	rt_make_soft_real_time();
        rt_task_delete(handler);
	print_message(INFO_MSG ,"TrialHandler", "TrialHandlerRtTask", "rt_trial_handler", "rt_task_delete().");	

        return 0; 
}


static bool connect_to_exp_envi_hand(void)
{
	ExpEnviHand2TrialHandMsgItem *msg_item;
	char str_exp_envi_hand_2_trial_hand_msg[EXP_ENVI_HAND_2_TRIAL_HAND_MSG_STRING_LENGTH];

	msgs_trial_hand_2_exp_envi_hand = allocate_shm_client_trial_hand_2_exp_envi_hand_msg_buffer(msgs_trial_hand_2_exp_envi_hand);	
	if (msgs_trial_hand_2_exp_envi_hand == NULL)
		return print_message(ERROR_MSG ,"TrialHandler", "TrialHandlerRtTask", "connect_to_exp_envi_hand", "msgs_trial_hand_2_exp_envi_hand == NULL.");
	sleep(1);	
	if (!write_to_trial_hand_2_exp_envi_hand_msg_buffer(msgs_trial_hand_2_exp_envi_hand, static_rt_tasks_data->current_system_time, TRIAL_HAND_2_EXP_ENVI_HAND_MSG_ARE_YOU_ALIVE, 0))
		return print_message(ERROR_MSG ,"TrialHandler", "TrialHandlerRtTask", "connect_to_exp_envi_hand", "write_to_trial_hand_2_exp_envi_hand_msg_bufferr().");

	while(1)
	{
		while (get_next_exp_envi_hand_2_trial_hand_msg_buffer_item(msgs_exp_envi_hand_2_trial_hand, &msg_item))
		{
			get_exp_envi_hand_2_trial_hand_msg_type_string(msg_item->msg_type, str_exp_envi_hand_2_trial_hand_msg);
			print_message(INFO_MSG ,"TrialHandler", "TrialHandlerRtTask", "connect_to_exp_envi_hand", str_exp_envi_hand_2_trial_hand_msg);	
			switch (msg_item->msg_type)
			{
				case EXP_ENVI_HAND_2_TRIAL_HAND_MSG_I_AM_ALIVE:
					print_message(INFO_MSG ,"TrialHandler", "TrialHandlerRtTask", "connect_to_exp_envi_hand", "Connection to EXP_ENVI_HANDLER is successful!!!");	
					sleep(1);	
					return TRUE;			
				default:
					print_message(BUG_MSG ,"TrialHandler", "TrialHandlerRtTask", "connect_to_exp_envi_hand", str_exp_envi_hand_2_trial_hand_msg);	
					return (void*)print_message(BUG_MSG ,"TrialHandler", "TrialHandlerRtTask", "connect_to_exp_envi_hand", "default - switch.");
			}
		}
		sleep(1);
	}
	return print_message(BUG_MSG ,"TrialHandler", "TrialHandlerRtTask", "connect_to_exp_envi_hand", "Wrong hit in the code.");
}

static bool connect_to_mov_obj_hand(void)
{
	MovObjHand2TrialHandMsgItem *msg_item;
	char str_mov_obj_hand_2_trial_hand_msg[MOV_OBJ_HAND_2_TRIAL_HAND_MSG_STRING_LENGTH];

	msgs_trial_hand_2_mov_obj_hand = allocate_shm_client_trial_hand_2_mov_obj_hand_msg_buffer(msgs_trial_hand_2_mov_obj_hand);	
	if (msgs_trial_hand_2_mov_obj_hand == NULL)
		return print_message(ERROR_MSG ,"TrialHandler", "TrialHandlerRtTask", "connect_to_mov_obj_hand", "msgs_trial_hand_2_mov_obj_hand == NULL.");
	sleep(1);	
	if (!write_to_trial_hand_2_mov_obj_hand_msg_buffer(msgs_trial_hand_2_mov_obj_hand, static_rt_tasks_data->current_system_time, TRIAL_HAND_2_MOV_OBJ_HAND_MSG_ARE_YOU_ALIVE, 0))
		return print_message(ERROR_MSG ,"TrialHandler", "TrialHandlerRtTask", "connect_to_mov_obj_hand", "write_to_trial_hand_2_mov_obj_hand_msg_bufferr().");

	while(1)
	{
		while (get_next_mov_obj_hand_2_trial_hand_msg_buffer_item(msgs_mov_obj_hand_2_trial_hand, &msg_item))
		{
			get_mov_obj_hand_2_trial_hand_msg_type_string(msg_item->msg_type, str_mov_obj_hand_2_trial_hand_msg);
			print_message(INFO_MSG ,"TrialHandler", "TrialHandlerRtTask", "connect_to_mov_obj_hand", str_mov_obj_hand_2_trial_hand_msg);	
			switch (msg_item->msg_type)
			{
				case MOV_OBJ_HAND_2_TRIAL_HAND_MSG_I_AM_ALIVE:
					print_message(INFO_MSG ,"TrialHandler", "TrialHandlerRtTask", "connect_to_mov_obj_hand", "Connection to MOV_OBJ_HANDLER is successful!!!");
					sleep(1);		
					return TRUE;			
				default:
					print_message(BUG_MSG ,"TrialHandler", "TrialHandlerRtTask", "connect_to_mov_obj_hand", str_mov_obj_hand_2_trial_hand_msg);	
					return (void*)print_message(BUG_MSG ,"TrialHandler", "TrialHandlerRtTask", "connect_to_mov_obj_hand", "default - switch.");
			}
		}
		sleep(1);
	}
	return print_message(BUG_MSG ,"TrialHandler", "TrialHandlerRtTask", "connect_to_mov_obj_hand", "Wrong hit in the code.");
}

static bool connect_to_neural_net(void)
{
	NeuralNet2TrialHandMsgItem *msg_item;
	char str_neural_net_2_trial_hand_msg[NEURAL_NET_2_TRIAL_HAND_MSG_STRING_LENGTH];

	msgs_trial_hand_2_neural_net = allocate_shm_client_trial_hand_2_neural_net_msg_buffer(msgs_trial_hand_2_neural_net);
	if (msgs_trial_hand_2_neural_net == NULL)
		return print_message(ERROR_MSG ,"TrialHandler", "TrialHandlerRtTask", "connect_to_neural_net", "msgs_trial_hand_2_neural_net == NULL.");
	if (!write_to_trial_hand_2_neural_net_msg_buffer(msgs_trial_hand_2_neural_net, static_rt_tasks_data->current_system_time, TRIAL_HAND_2_NEURAL_NET_MSG_ARE_YOU_ALIVE, TRIAL_STATUS_NULL, TRIAL_TYPE_NULL))
		return print_message(ERROR_MSG ,"TrialHandler", "TrialHandlerRtTask", "connect_to_neural_net", "write_to_trial_hand_2_neural_net_msg_buffer().");

	while (1) 
	{ 
		while (get_next_neural_net_2_trial_hand_msg_buffer_item(msgs_neural_net_2_trial_hand, &msg_item))
		{
			get_neural_net_2_trial_hand_msg_type_string(msg_item->msg_type, str_neural_net_2_trial_hand_msg);
			print_message(INFO_MSG ,"TrialHandler", "TrialHandlerRtTask", "connect_to_neural_net", str_neural_net_2_trial_hand_msg);	
			switch (msg_item->msg_type)
			{
				case NEURAL_NET_2_TRIAL_HAND_MSG_I_AM_ALIVE:
					print_message(INFO_MSG ,"TrialHandler", "TrialHandlerRtTask", "connect_to_neural_net", "Connection to NEURAL_NET is successful!!!");
					if (!write_to_trial_hand_2_neural_net_msg_buffer(msgs_trial_hand_2_neural_net, static_rt_tasks_data->current_system_time, TRIAL_HAND_2_SPIKE_GEN_MSG_TRIAL_STATUS_CHANGED, TRIAL_STATUS_TRIALS_DISABLED, TRIAL_TYPE_NULL))
						return print_message(ERROR_MSG ,"TrialHandler", "TrialHandlerRtTask", "connect_to_neural_net", "write_to_trial_hand_2_neural_net_msg_buffer().");	
					return TRUE;			
				default:
					return print_message(BUG_MSG ,"TrialHandler", "TrialHandlerRtTask", "connect_to_neural_net", str_neural_net_2_trial_hand_msg);	
			}
		}
		sleep(1); 
	}
	return print_message(BUG_MSG ,"TrialHandler", "MovObjHandlerRtTask", "connect_to_neural_net", "Wrong hit in the code.");
}

static bool connect_to_spike_gen(void)
{
	SpikeGen2TrialHandMsgItem *msg_item;
	char str_spike_gen_2_trial_hand_msg[SPIKE_GEN_2_TRIAL_HAND_MSG_STRING_LENGTH];

	msgs_trial_hand_2_spike_gen = allocate_shm_client_trial_hand_2_spike_gen_msg_buffer(msgs_trial_hand_2_spike_gen);
	if (msgs_trial_hand_2_spike_gen == NULL)
		return print_message(ERROR_MSG ,"TrialHandler", "TrialHandlerRtTask", "connect_to_spike_gen", "msgs_trial_hand_2_spike_gen == NULL.");
	if (!write_to_trial_hand_2_spike_gen_msg_buffer(msgs_trial_hand_2_spike_gen, static_rt_tasks_data->current_system_time, TRIAL_HAND_2_SPIKE_GEN_MSG_ARE_YOU_ALIVE, TRIAL_STATUS_NULL, TRIAL_TYPE_NULL))
		return print_message(ERROR_MSG ,"TrialHandler", "TrialHandlerRtTask", "connect_to_spike_gen", "write_to_trial_hand_2_spike_gen_msg_buffer().");

	while (1) 
	{ 
		while (get_next_spike_gen_2_trial_hand_msg_buffer_item(msgs_spike_gen_2_trial_hand, &msg_item))
		{
			get_spike_gen_2_trial_hand_msg_type_string(msg_item->msg_type, str_spike_gen_2_trial_hand_msg);
			print_message(INFO_MSG ,"TrialHandler", "TrialHandlerRtTask", "connect_to_spike_gen", str_spike_gen_2_trial_hand_msg);	
			switch (msg_item->msg_type)
			{
				case SPIKE_GEN_2_TRIAL_HAND_MSG_I_AM_ALIVE:
					print_message(INFO_MSG ,"TrialHandler", "TrialHandlerRtTask", "connect_to_spike_gen", "Connection to SPIKE_GEN is successful!!!");	
					if (!write_to_trial_hand_2_spike_gen_msg_buffer(msgs_trial_hand_2_spike_gen, static_rt_tasks_data->current_system_time, TRIAL_HAND_2_SPIKE_GEN_MSG_TRIAL_STATUS_CHANGED, TRIAL_STATUS_TRIALS_DISABLED, TRIAL_TYPE_NULL))
						return print_message(ERROR_MSG ,"TrialHandler", "TrialHandlerRtTask", "connect_to_spike_gen", "write_to_trial_hand_2_spike_gen_msg_buffer().");
					return TRUE;			
				default:
					return print_message(BUG_MSG ,"TrialHandler", "TrialHandlerRtTask", "connect_to_spike_gen", str_spike_gen_2_trial_hand_msg);	
			}
		}
		sleep(1); 
	}
	return print_message(BUG_MSG ,"TrialHandler", "MovObjHandlerRtTask", "connect_to_spike_gen", "Wrong hit in the code.");
}
