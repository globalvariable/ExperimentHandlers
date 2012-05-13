#include "ExpEnviHandlerRtTask.h"

static int exp_envi_handler_rt_thread = 0;
static bool rt_exp_envi_handler_stay_alive = 1;

static void *rt_exp_envi_handler(void *args);

static ExpEnviInterf2ExpEnviHandMsg *msgs_exp_envi_interf_2_exp_envi_hand = NULL;
static ExpEnviHand2ExpEnviInterfMsg *msgs_exp_envi_hand_2_exp_envi_interf = NULL;

static TrialHand2ExpEnviHandMsg *msgs_trial_hand_2_exp_envi_hand = NULL;
static ExpEnviHand2TrialHandMsg *msgs_exp_envi_hand_2_trial_hand = NULL;

static ExpEnviDurHand2ExpEnviHandMsg *msgs_exp_envi_dur_hand_2_exp_envi_hand = NULL;
static ExpEnviHand2ExpEnviDurHandMsg *msgs_exp_envi_hand_2_exp_envi_dur_hand = NULL;   

static bool connect_to_trial_hand(void);
static bool connect_to_exp_envi_interf(void );

bool create_exp_envi_handler_rt_thread(Gui2ExpEnviHandMsg *msgs_gui_2_exp_envi_hand)
{
	msgs_exp_envi_interf_2_exp_envi_hand = allocate_shm_server_exp_envi_interf_2_exp_envi_hand_msg_buffer(msgs_exp_envi_interf_2_exp_envi_hand);
	msgs_trial_hand_2_exp_envi_hand = allocate_shm_server_trial_hand_2_exp_envi_hand_msg_buffer(msgs_trial_hand_2_exp_envi_hand);

	if (! connect_to_exp_envi_interf())
		return print_message(ERROR_MSG ,"BMIExpController", "ExpEnviHandlerRtTask", "create_exp_envi_handler_rt_thread", "connect_to_exp_envi_interf().");	

	if (! connect_to_trial_hand())
		return print_message(ERROR_MSG ,"BMIExpController", "ExpEnviHandlerRtTask", "create_exp_envi_handler_rt_thread", "connect_to_trial_hand().");	

	msgs_exp_envi_dur_hand_2_exp_envi_hand = allocate_exp_envi_dur_hand_2_exp_envi_hand_msg_buffer(msgs_exp_envi_dur_hand_2_exp_envi_hand);
	msgs_exp_envi_hand_2_exp_envi_dur_hand = allocate_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer(msgs_exp_envi_hand_2_exp_envi_dur_hand);

	if(! create_exp_envi_duration_handler_rt_thread(msgs_exp_envi_dur_hand_2_exp_envi_hand, msgs_exp_envi_hand_2_exp_envi_dur_hand))
		return print_message(ERROR_MSG ,"BMIExpController", "ExpEnviHandlerRtTask", "create_exp_envi_handler_rt_thread", "create_exp_envi_duration_handler_rt_thread().");	

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

static bool connect_to_exp_envi_interf(void )
{
	ExpEnviInterf2ExpEnviHandMsgItem *msg_item;
	char str_exp_envi_interf_2_exp_envi_hand_msg[EXP_ENVI_INTERF_2_EXP_ENVI_HAND_MSG_STRING_LENGTH];

	msgs_exp_envi_hand_2_exp_envi_interf = allocate_shm_client_exp_envi_hand_2_exp_envi_interf_msg_buffer(msgs_exp_envi_hand_2_exp_envi_interf);
	if (msgs_exp_envi_hand_2_exp_envi_interf == NULL)
		return print_message(ERROR_MSG ,"BMIExpController", "ExpEnviHandlerRtTask", "connect_to_exp_envi_interf", "msgs_exp_envi_hand_2_exp_envi_interf == NULL.");
	if (!write_to_exp_envi_hand_2_exp_envi_interf_msg_buffer(msgs_exp_envi_hand_2_exp_envi_interf, shared_memory->rt_tasks_data.current_system_time, EXP_ENVI_HAND_2_EXP_ENVI_INTERF_MSG_ARE_YOU_ALIVE, 0))
		return print_message(ERROR_MSG ,"BMIExpController", "ExpEnviHandlerRtTask", "connect_to_exp_envi_interf", "write_to_exp_envi_hand_2_exp_envi_interf_msg_buffer().");

	while (1) 
	{ 
		while (get_next_exp_envi_interf_2_exp_envi_hand_msg_buffer_item(msgs_exp_envi_interf_2_exp_envi_hand, &msg_item))
		{
			get_exp_envi_interf_2_exp_envi_hand_msg_type_string(msg_item->msg_type, str_exp_envi_interf_2_exp_envi_hand_msg);
			print_message(INFO_MSG ,"ExpEnviHandler", "ExpEnviHandlerRtTask", "connect_to_exp_envi_interf", str_exp_envi_interf_2_exp_envi_hand_msg);	
			switch (msg_item->msg_type)
			{
				case EXP_ENVI_INTERF_2_EXP_ENVI_HAND_MSG_I_AM_ALIVE:
					print_message(INFO_MSG ,"ExpEnviHandler", "ExpEnviHandlerRtTask", "connect_to_exp_envi_interf", "Connection to EXP_ENVI_INTERFACER is successful!!!");	
					return TRUE;			
				default:
					print_message(BUG_MSG ,"ExpEnviHandler", "ExpEnviHandlerRtTask", "connect_to_exp_envi_interf", str_exp_envi_interf_2_exp_envi_hand_msg);	
					return print_message(BUG_MSG ,"ExpEnviHandler", "ExpEnviHandlerRtTask", "connect_to_exp_envi_interf", "default - switch.");
			}
		}
		sleep(1); 
	}
	return print_message(BUG_MSG ,"ExpEnviHandler", "ExpEnviHandlerRtTask", "connect_to_exp_envi_interf", "Wrong hit in the code.");
}

static bool connect_to_trial_hand(void )
{
	TrialHand2ExpEnviHandMsgItem *msg_item;
	char str_trial_hand_2_exp_envi_hand_msg[TRIAL_HAND_2_EXP_ENVI_HAND_MSG_STRING_LENGTH];

	while (1) 
	{ 
		while (get_next_trial_hand_2_exp_envi_hand_msg_buffer_item(msgs_trial_hand_2_exp_envi_hand, &msg_item))
		{
			get_trial_hand_2_exp_envi_hand_msg_type_string(msg_item->msg_type, str_trial_hand_2_exp_envi_hand_msg);
			print_message(INFO_MSG ,"ExpEnviHandler", "ExpEnviHandlerRtTask", "connect_to_trial_hand", str_trial_hand_2_exp_envi_hand_msg);	
			switch (msg_item->msg_type)
			{
				case TRIAL_HAND_2_EXP_ENVI_HAND_MSG_ARE_YOU_ALIVE:
					msgs_exp_envi_hand_2_trial_hand = allocate_shm_client_exp_envi_hand_2_trial_hand_msg_buffer(msgs_exp_envi_hand_2_trial_hand);
					if (msgs_exp_envi_hand_2_trial_hand == NULL)
						return print_message(ERROR_MSG ,"ExpEnviHandler", "ExpEnviHandlerRtTask", "connect_to_trial_hand", "msgs_exp_envi_hand_2_trial_hand == NULL.");	
					if (!write_to_exp_envi_hand_2_trial_hand_msg_buffer(msgs_exp_envi_hand_2_trial_hand, shared_memory->rt_tasks_data.current_system_time, EXP_ENVI_HAND_2_TRIAL_HAND_MSG_I_AM_ALIVE, 0))
						return print_message(ERROR_MSG ,"ExpEnviHandler", "ExpEnviHandlerRtTask", "connect_to_trial_hand", "write_to_exp_envi_hand_2_trial_hand_msg_buffer().");	
					print_message(INFO_MSG ,"ExpEnviHandler", "ExpEnviHandlerRtTask", "connect_to_trial_hand", "Connection to TRIAL_HANDLER is successful!!!");	
					return TRUE;		
				default:
					print_message(BUG_MSG ,"ExpEnviHandler", "ExpEnviHandlerRtTask", "connect_to_trial_hand", str_trial_hand_2_exp_envi_hand_msg);	
					return print_message(BUG_MSG ,"ExpEnviHandler", "ExpEnviHandlerRtTask", "connect_to_trial_hand", "default - switch.");
			}
		}
		print_message(INFO_MSG ,"ExpEnviHandler", "ExpEnviHandlerRtTask", "connect_to_trial_hand", "Waiting for TRIAL_HANDLER to connect.");	
		sleep(1);
	}
	return print_message(BUG_MSG ,"ExpEnviHandler", "ExpEnviHandlerRtTask", "connect_to_exp_envi_interf", "Wrong hit in the code.");
}
