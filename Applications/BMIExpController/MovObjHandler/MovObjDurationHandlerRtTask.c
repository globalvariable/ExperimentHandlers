#include "MovObjDurationHandlerRtTask.h"

static MovObjDurationStatus mov_obj_duration_status = MOV_OBJ_DUR_STATUS_NULL;   // Only mov obj duration handler can change mov obj status. 

static MovObjHand2MovObjDurHandMsg *static_msgs_mov_obj_hand_2_mov_obj_dur_hand;    
static MovObjDurHand2MovObjHandMsg *static_msgs_mov_obj_dur_hand_2_mov_obj_hand;    

static int mov_obj_duration_handler_rt_thread = 0;
static bool rt_mov_obj_duration_handler_stay_alive = 1;


static void *rt_mov_obj_duration_handler(void *args);

bool create_mov_obj_duration_handler_rt_thread(MovObjDurHand2MovObjHandMsg *msgs_mov_obj_dur_hand_2_mov_obj_hand, MovObjHand2MovObjDurHandMsg **msgs_mov_obj_hand_2_mov_obj_dur_hand)
{
	static_msgs_mov_obj_dur_hand_2_mov_obj_hand = msgs_mov_obj_dur_hand_2_mov_obj_hand;
	*msgs_mov_obj_hand_2_mov_obj_dur_hand = allocate_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer(*msgs_mov_obj_hand_2_mov_obj_dur_hand);
	static_msgs_mov_obj_hand_2_mov_obj_dur_hand = *msgs_mov_obj_hand_2_mov_obj_dur_hand;
//	mov_obj_duration_status = MOV_OBJ_DUR_STATUS_OUTSIDE_MOV_OBJ_PHASE;
	if (mov_obj_duration_handler_rt_thread !=0)
		return print_message(BUG_MSG ,"MovObjHandler", "MovObjHandlerRtTask", "create_mov_obj_duration_handler_rt_thread", "CANNOT create rt_thread again.");	
	mov_obj_duration_handler_rt_thread =  rt_thread_create(rt_mov_obj_duration_handler, NULL, 10000);
	if (mov_obj_duration_handler_rt_thread ==0)
		return print_message(BUG_MSG ,"MovObjHandler", "MovObjHandlerRtTask", "create_mov_obj_duration_handler_rt_thread", "Couldn' t create rt_thread.");	
	return TRUE;
}

bool kill_mov_obj_duration_handler_rt_thread(void)
{
	return TRUE;
}

static void *rt_mov_obj_duration_handler(void *args)
{
	RT_TASK *handler;
        RTIME period;
	unsigned int prev_time, curr_time;

	if (! check_rt_task_specs_to_init(MOV_OBJ_DURATION_HANDLER_CPU_ID, MOV_OBJ_DURATION_HANDLER_CPU_THREAD_ID, MOV_OBJ_DURATION_HANDLER_PERIOD))  {
		print_message(ERROR_MSG ,"MovObjHandler", "MovObjDurationHandlerRtTask", "rt_mov_obj_duration_handler", "! check_rt_task_specs_to_init()."); exit(1); }	
        if (! (handler = rt_task_init_schmod(MOV_OBJ_DURATION_HANDLER_TASK_NAME, MOV_OBJ_DURATION_HANDLER_TASK_PRIORITY, MOV_OBJ_DURATION_HANDLER_STACK_SIZE, MOV_OBJ_DURATION_HANDLER_MSG_SIZE,MOV_OBJ_DURATION_HANDLER_POLICY, 1 << ((MOV_OBJ_DURATION_HANDLER_CPU_ID*MAX_NUM_OF_THREADS_PER_CPU)+MOV_OBJ_DURATION_HANDLER_CPU_THREAD_ID)))) {
		print_message(ERROR_MSG ,"MovObjHandler", "MovObjDurationHandlerRtTask", "rt_mov_obj_duration_handler", "handler = rt_task_init_schmod()."); exit(1); }
	if (! write_rt_task_specs_to_rt_tasks_data(MOV_OBJ_DURATION_HANDLER_CPU_ID, MOV_OBJ_DURATION_HANDLER_CPU_THREAD_ID, MOV_OBJ_DURATION_HANDLER_PERIOD, MOV_OBJ_DURATION_HANDLER_POSITIVE_JITTER_THRES, MOV_OBJ_DURATION_HANDLER_NEGATIVE_JITTER_THRES))  {
		print_message(ERROR_MSG ,"MovObjHandler", "MovObjDurationHandlerRtTask", "rt_mov_obj_duration_handler", "! write_rt_task_specs_to_rt_tasks_data()."); exit(1); }	
        period = nano2count(MOV_OBJ_HANDLER_PERIOD);
        rt_task_make_periodic(handler, rt_get_time() + period, period);
	prev_time = rt_get_cpu_time_ns();	


        mlockall(MCL_CURRENT | MCL_FUTURE);
	rt_make_hard_real_time();		// do not forget this // check the task by nano /proc/rtai/scheduler (HD/SF) 

        while (rt_mov_obj_duration_handler_stay_alive) 
	{
        	rt_task_wait_period();
		curr_time = rt_get_cpu_time_ns();
		evaluate_and_save_jitter(MOV_OBJ_DURATION_HANDLER_CPU_ID, MOV_OBJ_DURATION_HANDLER_CPU_THREAD_ID, prev_time, curr_time);
		prev_time = curr_time;
		// routines
		if (!handle_mov_obj_handler_to_mov_obj_dur_handler_msg(&mov_obj_duration_status, shared_memory->rt_tasks_data.current_system_time, static_msgs_mov_obj_hand_2_mov_obj_dur_hand)) {
			print_message(ERROR_MSG ,"MovObjHandler", "MovObjDurationHandlerRtTask", "rt_mov_obj_duration_handler", "! handle_mov_obj_handler_to_mov_obj_duration_handler_msg()."); break; }
		// routines	
		evaluate_and_save_period_run_time(MOV_OBJ_DURATION_HANDLER_CPU_ID, MOV_OBJ_DURATION_HANDLER_CPU_THREAD_ID, curr_time, rt_get_cpu_time_ns());		
        }
	rt_make_soft_real_time();
        rt_task_delete(handler);
	print_message(INFO_MSG ,"MovObjHandler", "MovObjDurationHandlerRtTask", "rt_mov_obj_duration_handler", "rt_task_delete().");	

        return 0; 
}
