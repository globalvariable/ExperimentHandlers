#include "MovObjHandlerRtTask.h"

static int mov_obj_handler_rt_thread = 0;
static bool rt_mov_obj_handler_stay_alive = 1;

static void *rt_mov_obj_handler(void *args);

static MovObjDurHand2MovObjHandMsg *msgs_mov_obj_dur_hand_2_mov_obj_hand = NULL;
static MovObjHand2MovObjDurHandMsg *msgs_mov_obj_hand_2_mov_obj_dur_hand = NULL;    
static TrialHand2MovObjHandMsg *msgs_trial_hand_2_mov_obj_hand = NULL;
static bool connected_to_trial_hand = FALSE;
static pthread_t connect_to_trial_hand_thread;
static void *connect_to_trial_hand_thread_function( void *ptr );

bool create_mov_obj_handler_rt_thread(Gui2MovObjHandMsg *msgs_gui_2_mov_obj_hand)
{

	msgs_trial_hand_2_mov_obj_hand = allocate_shm_server_trial_hand_2_mov_obj_hand_msg_buffer(msgs_trial_hand_2_mov_obj_hand);

	pthread_create( &connect_to_trial_hand_thread, NULL, connect_to_trial_hand_thread_function, NULL);
	while (!connected_to_trial_hand) { sleep(1); }
	msgs_mov_obj_dur_hand_2_mov_obj_hand = allocate_mov_obj_dur_hand_2_mov_obj_hand_msg_buffer(msgs_mov_obj_dur_hand_2_mov_obj_hand);

	if(! create_mov_obj_duration_handler_rt_thread(msgs_mov_obj_dur_hand_2_mov_obj_hand, &msgs_mov_obj_hand_2_mov_obj_dur_hand))
		return print_message(ERROR_MSG ,"BMIExpController", "MovObjHandlerRtTask", "create_mov_obj_handler_rt_thread", "create_mov_obj_handler_rt_thread().");

	if (mov_obj_handler_rt_thread !=0)
		return print_message(BUG_MSG ,"BMIExpController", "MovObjHandlerRtTask", "create_mov_obj_handler_rt_thread", "CANNOT create rt_thread again.");	
	mov_obj_handler_rt_thread =  rt_thread_create(rt_mov_obj_handler, NULL, 10000);
	if (mov_obj_handler_rt_thread ==0)
		return print_message(BUG_MSG ,"BMIExpController", "MovObjHandlerRtTask", "create_mov_obj_handler_rt_thread", "Couldn' t create rt_thread.");	
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

	if (! check_rt_task_specs_to_init(MOV_OBJ_HANDLER_CPU_ID, MOV_OBJ_HANDLER_CPU_THREAD_ID, MOV_OBJ_HANDLER_PERIOD))  {
		print_message(ERROR_MSG ,"BMIExpController", "MovObjHandlerRtTask", "rt_mov_obj_handler", "! check_rt_task_specs_to_init()."); exit(1); }	
        if (! (handler = rt_task_init_schmod(MOV_OBJ_HANDLER_TASK_NAME, MOV_OBJ_HANDLER_TASK_PRIORITY, MOV_OBJ_HANDLER_STACK_SIZE, MOV_OBJ_HANDLER_MSG_SIZE,MOV_OBJ_HANDLER_POLICY, 1 << ((MOV_OBJ_HANDLER_CPU_ID*MAX_NUM_OF_THREADS_PER_CPU)+MOV_OBJ_HANDLER_CPU_THREAD_ID)))) {
		print_message(ERROR_MSG ,"BMIExpController", "MovObjHandlerRtTask", "rt_mov_obj_handler", "handler = rt_task_init_schmod()."); exit(1); }
	if (! write_rt_task_specs_to_rt_tasks_data(MOV_OBJ_HANDLER_CPU_ID, MOV_OBJ_HANDLER_CPU_THREAD_ID, MOV_OBJ_HANDLER_PERIOD, MOV_OBJ_HANDLER_POSITIVE_JITTER_THRES, MOV_OBJ_HANDLER_NEGATIVE_JITTER_THRES))  {
		print_message(ERROR_MSG ,"BMIExpController", "MovObjHandlerRtTask", "rt_mov_obj_handler", "! write_rt_task_specs_to_rt_tasks_data()."); exit(1); }	
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
		// routines


		// routines	
		evaluate_and_save_period_run_time(MOV_OBJ_HANDLER_CPU_ID, MOV_OBJ_HANDLER_CPU_THREAD_ID, curr_time, rt_get_cpu_time_ns());		
        }
	rt_make_soft_real_time();
        rt_task_delete(handler);
	print_message(INFO_MSG ,"BMIExpController", "MovObjHandlerRtTask", "rt_mov_obj_handler", "rt_task_delete().");	

        return 0; 
}

static void *connect_to_trial_hand_thread_function( void *ptr )
{
	TrialHand2MovObjHandMsgItem *msg_item;
	char str_trial_hand_2_mov_obj_hand_msg[TRIAL_HAND_2_MOV_OBJ_HAND_MSG_STRING_LENGTH];

	while (get_next_trial_hand_2_mov_obj_hand_msg_buffer_item(msgs_trial_hand_2_mov_obj_hand, &msg_item))
	{
		get_trial_hand_2_mov_obj_hand_msg_type_string(msg_item->msg_type, str_trial_hand_2_mov_obj_hand_msg);
		print_message(INFO_MSG ,"FirstBMICageManager", "FirstBMICageInterfacerRtTask", "connect_to_trial_hand_thread_function", str_trial_hand_2_mov_obj_hand_msg);	
		switch (msg_item->msg_type)
		{
			case TRIAL_HAND_2_MOV_OBJ_HAND_MSG_ARE_YOU_ALIVE:
				connected_to_trial_hand = TRUE;
				return 0;			
			default:
				print_message(BUG_MSG ,"FirstBMICageManager", "FirstBMICageInterfacerRtTask", "connect_to_trial_hand_thread_function", str_trial_hand_2_mov_obj_hand_msg);	
				return (void*)print_message(BUG_MSG ,"FirstBMICageManager", "FirstBMICageInterfacerRtTask", "connect_to_trial_hand_thread_function", "default - switch.");
		}
		sleep(1);
	}
	return 0;
}
