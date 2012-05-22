#include "MovObjHandlerRtTask.h"

static MovObjStatus mov_obj_status = MOV_OBJ_STATUS_NULL;   // Only mov_obj handler can change status. 
static TrialType mov_obj_trial_type_status = TRIAL_TYPE_NULL;   // Only mov_obj handler can change trial type status. 

static int mov_obj_handler_rt_thread = 0;
static bool rt_mov_obj_handler_stay_alive = 1;

static void *rt_mov_obj_handler(void *args);

static MovObjData *static_mov_obj_data = NULL;

static Gui2MovObjHandMsg *static_msgs_gui_2_mov_obj_hand = NULL;

static MovObjInterf2MovObjHandMsg *msgs_mov_obj_interf_2_mov_obj_hand = NULL;
static MovObjHand2MovObjInterfMsg *msgs_mov_obj_hand_2_mov_obj_interf = NULL;

static TrialHand2MovObjHandMsg *msgs_trial_hand_2_mov_obj_hand = NULL;
static MovObjHand2TrialHandMsg *msgs_mov_obj_hand_2_trial_hand = NULL;

static MovObjDurHand2MovObjHandMsg *msgs_mov_obj_dur_hand_2_mov_obj_hand = NULL;
static MovObjHand2MovObjDurHandMsg *msgs_mov_obj_hand_2_mov_obj_dur_hand = NULL;   

static MovObjHand2NeuralNetMsg *msgs_mov_obj_hand_2_neural_net = NULL;
static NeuralNet2MovObjHandMsg *msgs_neural_net_2_mov_obj_hand = NULL;

static bool connect_to_trial_hand(void);
static bool connect_to_neural_net(void);
static bool connect_to_mov_obj_interf(void );

bool create_mov_obj_handler_rt_thread(MovObjData *mov_obj_data, Gui2MovObjHandMsg *msgs_gui_2_mov_obj_hand)
{
	mov_obj_status = MOV_OBJ_STATUS_OUT_OF_TRIAL;
	mov_obj_trial_type_status = TRIAL_TYPE_UNSPECIFIED;

	static_mov_obj_data = mov_obj_data;
	static_msgs_gui_2_mov_obj_hand = msgs_gui_2_mov_obj_hand;

	msgs_mov_obj_interf_2_mov_obj_hand = allocate_shm_server_mov_obj_interf_2_mov_obj_hand_msg_buffer(msgs_mov_obj_interf_2_mov_obj_hand);
	msgs_trial_hand_2_mov_obj_hand = allocate_shm_server_trial_hand_2_mov_obj_hand_msg_buffer(msgs_trial_hand_2_mov_obj_hand);

	if (! connect_to_mov_obj_interf())
		return print_message(ERROR_MSG ,"MovObjHandler", "MovObjHandlerRtTask", "create_mov_obj_handler_rt_thread", "connect_to_mov_obj_interf().");	

	if (!connect_to_neural_net())
		return print_message(ERROR_MSG ,"MovObjHandler", "MovObjHandlerRtTask", "create_mov_obj_handler_rt_thread", "connect_to_neural_net().");	

	if (! connect_to_trial_hand())
		return print_message(ERROR_MSG ,"MovObjHandler", "MovObjHandlerRtTask", "create_mov_obj_handler_rt_thread", "connect_to_trial_hand().");	

	msgs_mov_obj_dur_hand_2_mov_obj_hand = allocate_mov_obj_dur_hand_2_mov_obj_hand_msg_buffer(msgs_mov_obj_dur_hand_2_mov_obj_hand);
	msgs_mov_obj_hand_2_mov_obj_dur_hand = allocate_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer(msgs_mov_obj_hand_2_mov_obj_dur_hand);

	if(! create_mov_obj_duration_handler_rt_thread(msgs_mov_obj_dur_hand_2_mov_obj_hand, msgs_mov_obj_hand_2_mov_obj_dur_hand))
		return print_message(ERROR_MSG ,"MovObjHandler", "MovObjHandlerRtTask", "create_mov_obj_handler_rt_thread", "create_mov_obj_duration_handler_rt_thread().");	

	if (mov_obj_handler_rt_thread !=0)
		return print_message(BUG_MSG ,"MovObjHandler", "MovObjHandlerRtTask", "create_mov_obj_handler_rt_thread", "CANNOT create rt_thread again.");	
	mov_obj_handler_rt_thread =  rt_thread_create(rt_mov_obj_handler, NULL, 10000);
	if (mov_obj_handler_rt_thread ==0)
		return print_message(BUG_MSG ,"MovObjHandler", "MovObjHandlerRtTask", "create_mov_obj_handler_rt_thread", "Couldn' t create rt_thread.");	
	return TRUE;
}

bool kill_mov_obj_handler_rt_thread(void)
{
	return TRUE;
}

static void *rt_mov_obj_handler(void *args)
{
	RT_TASK *handler;
        RTIME period;
	unsigned int prev_time, curr_time;
	TimeStamp curr_system_time;
	if (! check_rt_task_specs_to_init(MOV_OBJ_HANDLER_CPU_ID, MOV_OBJ_HANDLER_CPU_THREAD_ID, MOV_OBJ_HANDLER_PERIOD))  {
		print_message(ERROR_MSG ,"MovObjHandler", "MovObjHandlerRtTask", "rt_mov_obj_handler", "! check_rt_task_specs_to_init()."); exit(1); }	
        if (! (handler = rt_task_init_schmod(MOV_OBJ_HANDLER_TASK_NAME, MOV_OBJ_HANDLER_TASK_PRIORITY, MOV_OBJ_HANDLER_STACK_SIZE, MOV_OBJ_HANDLER_MSG_SIZE,MOV_OBJ_HANDLER_POLICY, 1 << ((MOV_OBJ_HANDLER_CPU_ID*MAX_NUM_OF_THREADS_PER_CPU)+MOV_OBJ_HANDLER_CPU_THREAD_ID)))) {
		print_message(ERROR_MSG ,"MovObjHandler", "MovObjHandlerRtTask", "rt_mov_obj_handler", "handler = rt_task_init_schmod()."); exit(1); }
	if (! write_rt_task_specs_to_rt_tasks_data(MOV_OBJ_HANDLER_CPU_ID, MOV_OBJ_HANDLER_CPU_THREAD_ID, MOV_OBJ_HANDLER_PERIOD, MOV_OBJ_HANDLER_POSITIVE_JITTER_THRES, MOV_OBJ_HANDLER_NEGATIVE_JITTER_THRES))  {
		print_message(ERROR_MSG ,"MovObjHandler", "MovObjHandlerRtTask", "rt_mov_obj_handler", "! write_rt_task_specs_to_rt_tasks_data()."); exit(1); }	
        period = nano2count(MOV_OBJ_HANDLER_PERIOD);
        rt_task_make_periodic(handler, rt_get_time() + period, period);
	prev_time = rt_get_cpu_time_ns();	


        mlockall(MCL_CURRENT | MCL_FUTURE);
	rt_make_hard_real_time();		// do not forget this // check the task by nano /proc/rtai/scheduler (HD/SF) 

        while (rt_mov_obj_handler_stay_alive) 
	{
        	rt_task_wait_period();
		curr_time = rt_get_cpu_time_ns();
		evaluate_and_save_jitter(MOV_OBJ_HANDLER_CPU_ID, MOV_OBJ_HANDLER_CPU_THREAD_ID, prev_time, curr_time);
		prev_time = curr_time;
		curr_system_time = shared_memory->rt_tasks_data.current_system_time;
		// routines
		if (! handle_gui_to_mov_obj_handler_msg(static_mov_obj_data, &mov_obj_status, curr_system_time, static_msgs_gui_2_mov_obj_hand)) {
			print_message(ERROR_MSG ,"MovObjHandler", "MovObjHandlerRtTask", "rt_mov_obj_handler", "! handle_gui_to_mov_obj_handler_msg()."); break; }
		if (! handle_trial_handler_to_mov_obj_handler_msg(static_mov_obj_data, &mov_obj_status, &mov_obj_trial_type_status, curr_system_time, msgs_trial_hand_2_mov_obj_hand, msgs_mov_obj_hand_2_mov_obj_dur_hand))  {
			print_message(ERROR_MSG ,"MovObjHandler", "MovObjHandlerRtTask", "rt_mov_obj_handler", "! handle_trial_handler_to_mov_obj_handler_msg()."); break; }
		if (! handle_mov_obj_interf_to_mov_obj_handler_msg(static_mov_obj_data, &mov_obj_status, mov_obj_trial_type_status, curr_system_time, msgs_mov_obj_interf_2_mov_obj_hand, msgs_mov_obj_hand_2_mov_obj_dur_hand))  {
			print_message(ERROR_MSG ,"MovObjHandler", "MovObjHandlerRtTask", "rt_mov_obj_handler", "! handle_mov_obj_interf_to_mov_obj_handler_msg()."); break; }
		if (! handle_mov_obj_dur_handler_to_mov_obj_handler_msg(static_mov_obj_data, &mov_obj_status, curr_system_time, msgs_mov_obj_dur_hand_2_mov_obj_hand, msgs_mov_obj_hand_2_trial_hand))  {
			print_message(ERROR_MSG ,"MovObjHandler", "MovObjHandlerRtTask", "rt_mov_obj_handler", "! handle_mov_obj_dur_handler_to_mov_obj_handler_msg()."); break; }
		if (! handle_mov_obj_handler_status(mov_obj_status, mov_obj_trial_type_status, curr_system_time, msgs_mov_obj_hand_2_mov_obj_interf)) {
			print_message(ERROR_MSG ,"MovObjHandler", "MovObjHandlerRtTask", "rt_mov_obj_handler", "! handle_mov_obj_dur_handler_to_mov_obj_handler_msg()."); break; }
		// routines	
		evaluate_and_save_period_run_time(MOV_OBJ_HANDLER_CPU_ID, MOV_OBJ_HANDLER_CPU_THREAD_ID, curr_time, rt_get_cpu_time_ns());		
        }
	rt_make_soft_real_time();
        rt_task_delete(handler);
	print_message(INFO_MSG ,"MovObjHandler", "MovObjHandlerRtTask", "rt_mov_obj_handler", "rt_task_delete().");	

        return 0; 
}

static bool connect_to_mov_obj_interf(void )
{
	MovObjInterf2MovObjHandMsgItem *msg_item;
	char str_mov_obj_interf_2_mov_obj_hand_msg[MOV_OBJ_INTERF_2_MOV_OBJ_HAND_MSG_STRING_LENGTH];

	msgs_mov_obj_hand_2_mov_obj_interf = allocate_shm_client_mov_obj_hand_2_mov_obj_interf_msg_buffer(msgs_mov_obj_hand_2_mov_obj_interf);
	if (msgs_mov_obj_hand_2_mov_obj_interf == NULL)
		return print_message(ERROR_MSG ,"MovObjHandler", "MovObjHandlerRtTask", "connect_to_mov_obj_interf", "msgs_mov_obj_hand_2_mov_obj_interf == NULL.");
	if (!write_to_mov_obj_hand_2_mov_obj_interf_msg_buffer(msgs_mov_obj_hand_2_mov_obj_interf, shared_memory->rt_tasks_data.current_system_time, MOV_OBJ_HAND_2_MOV_OBJ_INTERF_MSG_ARE_YOU_ALIVE, MOV_OBJ_COMPONENT_NUM_NULL, MOV_OBJ_DIRECTION_NULL, MOV_OBJ_SPEED_NULL, MOV_OBJ_LOCATION_NULL))
		return print_message(ERROR_MSG ,"MovObjHandler", "MovObjHandlerRtTask", "connect_to_mov_obj_interf", "write_to_mov_obj_hand_2_mov_obj_interf_msg_buffer().");

	while (1) 
	{ 
		while (get_next_mov_obj_interf_2_mov_obj_hand_msg_buffer_item(msgs_mov_obj_interf_2_mov_obj_hand, &msg_item))
		{
			get_mov_obj_interf_2_mov_obj_hand_msg_type_string(msg_item->msg_type, str_mov_obj_interf_2_mov_obj_hand_msg);
			print_message(INFO_MSG ,"MovObjHandler", "MovObjHandlerRtTask", "connect_to_mov_obj_interf", str_mov_obj_interf_2_mov_obj_hand_msg);	
			switch (msg_item->msg_type)
			{
				case MOV_OBJ_INTERF_2_MOV_OBJ_HAND_MSG_I_AM_ALIVE:
					print_message(INFO_MSG ,"MovObjHandler", "MovObjHandlerRtTask", "connect_to_mov_obj_interf", "Connection to MOV_OBJ_INTERFACER is successful!!!");	
					return TRUE;			
				default:
					return print_message(BUG_MSG ,"MovObjHandler", "MovObjHandlerRtTask", "connect_to_mov_obj_interf", str_mov_obj_interf_2_mov_obj_hand_msg);	
			}
		}
		sleep(1); 
	}
	return print_message(BUG_MSG ,"MovObjHandler", "MovObjHandlerRtTask", "connect_to_mov_obj_interf", "Wrong hit in the code.");
}

static bool connect_to_neural_net(void)
{
	NeuralNet2MovObjHandMsgItem *msg_item;
	char str_neural_net_2_mov_obj_hand_msg[NEURAL_NET_2_MOV_OBJ_HAND_MSG_STRING_LENGTH];

	msgs_mov_obj_hand_2_neural_net = allocate_shm_client_mov_obj_hand_2_neural_net_msg_buffer(msgs_mov_obj_hand_2_neural_net);
	if (msgs_mov_obj_hand_2_neural_net == NULL)
		return print_message(ERROR_MSG ,"MovObjHandler", "MovObjHandlerRtTask", "connect_to_neural_net", "msgs_mov_obj_hand_2_neural_net == NULL.");
	if (!write_to_mov_obj_hand_2_neural_net_msg_buffer(msgs_mov_obj_hand_2_neural_net, shared_memory->rt_tasks_data.current_system_time, MOV_OBJ_HAND_2_NEURAL_NET_MSG_ARE_YOU_ALIVE, 0))
		return print_message(ERROR_MSG ,"MovObjHandler", "MovObjHandlerRtTask", "connect_to_neural_net", "write_to_mov_obj_hand_2_neural_net_msg_buffer().");

	while (1) 
	{ 
		while (get_next_neural_net_2_mov_obj_hand_msg_buffer_item(msgs_neural_net_2_mov_obj_hand, &msg_item))
		{
			get_neural_net_2_mov_obj_hand_msg_type_string(msg_item->msg_type, str_neural_net_2_mov_obj_hand_msg);
			print_message(INFO_MSG ,"MovObjHandler", "MovObjHandlerRtTask", "connect_to_neural_net", str_neural_net_2_mov_obj_hand_msg);	
			switch (msg_item->msg_type)
			{
				case NEURAL_NET_2_MOV_OBJ_HAND_MSG_I_AM_ALIVE:
					print_message(INFO_MSG ,"MovObjHandler", "MovObjHandlerRtTask", "connect_to_neural_net", "Connection to NEURAL_NET is successful!!!");	
					return TRUE;			
				default:
					return print_message(BUG_MSG ,"MovObjHandler", "MovObjHandlerRtTask", "connect_to_neural_net", str_neural_net_2_mov_obj_hand_msg);	
			}
		}
		sleep(1); 
	}
	return print_message(BUG_MSG ,"MovObjHandler", "MovObjHandlerRtTask", "connect_to_neural_net", "Wrong hit in the code.");
}

static bool connect_to_trial_hand(void )
{
	TrialHand2MovObjHandMsgItem *msg_item;
	char str_trial_hand_2_mov_obj_hand_msg[TRIAL_HAND_2_MOV_OBJ_HAND_MSG_STRING_LENGTH];

	while (1) 
	{ 
		while (get_next_trial_hand_2_mov_obj_hand_msg_buffer_item(msgs_trial_hand_2_mov_obj_hand, &msg_item))
		{
			get_trial_hand_2_mov_obj_hand_msg_type_string(msg_item->msg_type, str_trial_hand_2_mov_obj_hand_msg);
			print_message(INFO_MSG ,"MovObjHandler", "MovObjHandlerRtTask", "connect_to_trial_hand", str_trial_hand_2_mov_obj_hand_msg);	
			switch (msg_item->msg_type)
			{
				case TRIAL_HAND_2_MOV_OBJ_HAND_MSG_ARE_YOU_ALIVE:
					msgs_mov_obj_hand_2_trial_hand = allocate_shm_client_mov_obj_hand_2_trial_hand_msg_buffer(msgs_mov_obj_hand_2_trial_hand);
					sleep(1);
					if (msgs_mov_obj_hand_2_trial_hand == NULL)
						return print_message(ERROR_MSG ,"MovObjHandler", "MovObjHandlerRtTask", "connect_to_trial_hand", "msgs_mov_obj_hand_2_trial_hand == NULL.");	
					if (!write_to_mov_obj_hand_2_trial_hand_msg_buffer(msgs_mov_obj_hand_2_trial_hand, shared_memory->rt_tasks_data.current_system_time, MOV_OBJ_HAND_2_TRIAL_HAND_MSG_I_AM_ALIVE, 0))
						return print_message(ERROR_MSG ,"MovObjHandler", "MovObjHandlerRtTask", "connect_to_trial_hand", "write_to_mov_obj_hand_2_trial_hand_msg_buffer().");	
					print_message(INFO_MSG ,"MovObjHandler", "MovObjHandlerRtTask", "connect_to_trial_hand", "Connection to TRIAL_HANDLER is successful!!!");	
					return TRUE;		
				default:
					return print_message(BUG_MSG ,"MovObjHandler", "MovObjHandlerRtTask", "connect_to_trial_hand", str_trial_hand_2_mov_obj_hand_msg);	
			}
		}
		print_message(INFO_MSG ,"MovObjHandler", "MovObjHandlerRtTask", "connect_to_trial_hand", "Waiting for TRIAL_HANDLER to connect.");	
		sleep(1);
	}
	return print_message(BUG_MSG ,"MovObjHandler", "MovObjHandlerRtTask", "connect_to_trial_hand", "Wrong hit in the code.");
}
