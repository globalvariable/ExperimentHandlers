#include "FirstBMICageInterfacerRtTask.h"

static RtTasksData *static_rt_tasks_data = NULL;
static RS232Data *static_rs_232_data = NULL;

static int cage_interfacer_rt_thread = 0;
static bool rt_cage_interfacer_stay_alive = 1;

static void *rt_cage_interfacer(void *args);

static ExpEnviHand2ExpEnviInterfMsg *msgs_exp_envi_hand_2_exp_envi_interf = NULL;
static ExpEnviInterf2ExpEnviHandMsg *msgs_exp_envi_interf_2_exp_envi_hand = NULL;

static MovObjHand2MovObjInterfMsg *msgs_mov_obj_hand_2_mov_obj_interf = NULL;
static MovObjInterf2MovObjHandMsg *msgs_mov_obj_interf_2_mov_obj_hand = NULL;

static RS232Hand2RS232DurHandMsg *msgs_rs232_hand_2_rs232_dur_hand = NULL;
static RS232DurHand2RS232HandMsg *msgs_rs232_dur_hand_2_rs232_hand = NULL;

static bool connect_to_exp_envi_hand(void);
static bool connect_to_mov_obj_hand(void);

bool create_cage_interfacer_rt_thread(RtTasksData *rt_tasks_data, RS232Data *rs_232_data)
{
	static_rt_tasks_data = rt_tasks_data;
	static_rs_232_data = rs_232_data;

	msgs_exp_envi_hand_2_exp_envi_interf = allocate_shm_server_exp_envi_hand_2_exp_envi_interf_msg_buffer(msgs_exp_envi_hand_2_exp_envi_interf);
	msgs_mov_obj_hand_2_mov_obj_interf = allocate_shm_server_mov_obj_hand_2_mov_obj_interf_msg_buffer(msgs_mov_obj_hand_2_mov_obj_interf);

	msgs_rs232_hand_2_rs232_dur_hand = allocate_rs232_hand_2_rs232_dur_hand_msg_buffer(msgs_rs232_hand_2_rs232_dur_hand);
	msgs_rs232_dur_hand_2_rs232_hand = allocate_rs232_dur_hand_2_rs232_hand_msg_buffer(msgs_rs232_dur_hand_2_rs232_hand);


	if (! create_rs232_duration_handler_data(rs_232_data->num_of_comps))
		return print_message(ERROR_MSG ,"FirstBMICageInterfacer", "FirstBMICageInterfacerRtTask", "create_cage_interfacer_rt_thread", "! create_rs232_duration_handler_data().");	

	if (! connect_to_exp_envi_hand())
		return print_message(ERROR_MSG ,"FirstBMICageInterfacer", "FirstBMICageInterfacerRtTask", "create_cage_interfacer_rt_thread", "! connect_to_exp_envi_hand().");	
	if (! connect_to_mov_obj_hand())
		return print_message(ERROR_MSG ,"FirstBMICageInterfacer", "FirstBMICageInterfacerRtTask", "create_cage_interfacer_rt_thread", "! connect_to_exp_envi_hand().");	

	if (cage_interfacer_rt_thread != 0)
		return print_message(BUG_MSG ,"FirstBMICageInterfacer", "FirstBMICageInterfacerRtTask", "create_cage_interfacer_rt_thread", "CANNOT create rt_thread again.");	
	cage_interfacer_rt_thread =  rt_thread_create(rt_cage_interfacer, NULL, 10000);
	if (cage_interfacer_rt_thread == 0)
		return print_message(BUG_MSG ,"FirstBMICageInterfacer", "FirstBMICageInterfacerRtTask", "create_cage_interfacer_rt_thread", "Couldn' t create rt_thread.");	
	return TRUE;
}

bool kill_cage_interfacer_rt_thread(void)
{
	return TRUE;
}

static void *rt_cage_interfacer(void *args)
{
	RT_TASK *handler;
        RTIME period;
	unsigned int prev_time, curr_time;
	TimeStamp curr_system_time;

	if (! check_rt_task_specs_to_init(static_rt_tasks_data, FIRST_BMI_CAGE_INTERF_CPU_ID, FIRST_BMI_CAGE_INTERF_CPU_THREAD_ID, FIRST_BMI_CAGE_INTERF_CPU_THREAD_TASK_ID,  FIRST_BMI_CAGE_INTERF_PERIOD))  {
		print_message(ERROR_MSG ,"FirstBMICageInterfacer", "FirstBMICageInterfacerRtTask", "rt_cage_interfacer", "! check_rt_task_specs_to_init()."); exit(1); }	
        if (! (handler = rt_task_init_schmod(FIRST_BMI_CAGE_INTERF_TASK_NAME, FIRST_BMI_CAGE_INTERF_TASK_PRIORITY, FIRST_BMI_CAGE_INTERF_STACK_SIZE, FIRST_BMI_CAGE_INTERF_MSG_SIZE,FIRST_BMI_CAGE_INTERF_POLICY, 1 << ((FIRST_BMI_CAGE_INTERF_CPU_ID*MAX_NUM_OF_CPU_THREADS_PER_CPU)+FIRST_BMI_CAGE_INTERF_CPU_THREAD_ID)))) {
		print_message(ERROR_MSG ,"FirstBMICageInterfacer", "FirstBMICageInterfacerRtTask", "rt_cage_interfacer", "handler = rt_task_init_schmod()."); exit(1); }
	if (! write_rt_task_specs_to_rt_tasks_data(static_rt_tasks_data, FIRST_BMI_CAGE_INTERF_CPU_ID, FIRST_BMI_CAGE_INTERF_CPU_THREAD_ID, FIRST_BMI_CAGE_INTERF_CPU_THREAD_TASK_ID, FIRST_BMI_CAGE_INTERF_PERIOD, FIRST_BMI_CAGE_INTERF_POSITIVE_JITTER_THRES, FIRST_BMI_CAGE_INTERF_NEGATIVE_JITTER_THRES, "FirstBMICageInterfacer"))  {
		print_message(ERROR_MSG ,"FirstBMICageInterfacer", "FirstBMICageInterfacerRtTask", "rt_cage_interfacer", "! write_rt_task_specs_to_rt_tasks_data()."); exit(1); }	
        period = nano2count(FIRST_BMI_CAGE_INTERF_PERIOD);
        rt_task_make_periodic(handler, rt_get_time() + period, period);


        mlockall(MCL_CURRENT | MCL_FUTURE);
	rt_make_hard_real_time();		// do not forget this // check the task by nano /proc/rtai/scheduler (HD/SF) 

	curr_time = rt_get_cpu_time_ns();
	prev_time = curr_time;	
	curr_system_time = static_rt_tasks_data->current_system_time;

	msgs_exp_envi_hand_2_exp_envi_interf->buff_read_idx = msgs_exp_envi_hand_2_exp_envi_interf->buff_write_idx; // to reset message buffer. previously written messages and reading of them now might lead to inconvenience.,
	msgs_mov_obj_hand_2_mov_obj_interf->buff_read_idx = msgs_mov_obj_hand_2_mov_obj_interf->buff_write_idx; // to reset message buffer. previously written messages and reading of them now might lead to inconvenience.,
	msgs_rs232_hand_2_rs232_dur_hand->buff_read_idx = msgs_rs232_hand_2_rs232_dur_hand->buff_write_idx;
	msgs_rs232_dur_hand_2_rs232_hand->buff_read_idx = msgs_rs232_dur_hand_2_rs232_hand->buff_write_idx;

	if (!write_to_rs232_hand_2_rs232_dur_hand_msg_buffer(msgs_rs232_hand_2_rs232_dur_hand, curr_system_time, RS232_HAND_2_RS232_DUR_HAND_MSG_ENABLE_TX_TIMER, 0, static_rs_232_data->comp_data[0].tx_period+curr_system_time))  {
		print_message(ERROR_MSG ,"FirstBMICageInterfacer", "HandleRS232DurHand2RS232HandMsgs", "handle_rs232_dur_handler_to_rs232_handler_msgs", "! write_to_rs232_hand_2_rs232_dur_hand_msg_buffer().");exit(1); }	

        while (rt_cage_interfacer_stay_alive) 
	{
        	rt_task_wait_period();
		curr_time = rt_get_cpu_time_ns();
		evaluate_and_save_jitter(static_rt_tasks_data, FIRST_BMI_CAGE_INTERF_CPU_ID, FIRST_BMI_CAGE_INTERF_CPU_THREAD_ID, FIRST_BMI_CAGE_INTERF_CPU_THREAD_TASK_ID, prev_time, curr_time);
		prev_time = curr_time;
		curr_system_time = static_rt_tasks_data->current_system_time;
		// routines
		if (! handle_rs232_duration_handler(curr_system_time, msgs_rs232_dur_hand_2_rs232_hand)) {
			print_message(ERROR_MSG ,"FirstBMICageInterfacer", "FirstBMICageInterfacerRtTask", "rt_cage_interfacer", "! handle_rs232_handler_duration()."); break; }	
		if (! handle_rs232_handler_to_rs232_dur_handler_msgs(static_rs_232_data, curr_system_time, msgs_rs232_dur_hand_2_rs232_hand, msgs_rs232_hand_2_rs232_dur_hand)) {
			print_message(ERROR_MSG ,"FirstBMICageInterfacer", "FirstBMICageInterfacerRtTask", "rt_cage_interfacer", "! handle_rs232_handler_to_rs232_dur_handler_msgs()."); break; }	
		if (! handle_rs232_dur_hand_to_rs232_hand_msgs(static_rs_232_data, curr_system_time, msgs_exp_envi_hand_2_exp_envi_interf, msgs_exp_envi_interf_2_exp_envi_hand, msgs_mov_obj_hand_2_mov_obj_interf, msgs_mov_obj_interf_2_mov_obj_hand, msgs_rs232_dur_hand_2_rs232_hand, msgs_rs232_hand_2_rs232_dur_hand)) {
			print_message(ERROR_MSG ,"FirstBMICageInterfacer", "FirstBMICageInterfacerRtTask", "rt_cage_interfacer", "! handle_rs232_dur_handler_to_rs232_handler_msgs()."); break; }	
		evaluate_and_save_period_run_time(static_rt_tasks_data, FIRST_BMI_CAGE_INTERF_CPU_ID, FIRST_BMI_CAGE_INTERF_CPU_THREAD_ID, FIRST_BMI_CAGE_INTERF_CPU_THREAD_TASK_ID, curr_time, rt_get_cpu_time_ns());		
		// routines	
        }
	rt_make_soft_real_time();
        rt_task_delete(handler);
	print_message(INFO_MSG ,"FirstBMICageInterfacer", "FirstBMICageInterfacerRtTask", "rt_cage_interfacer", "rt_task_delete().");	

        return 0; 
}

static bool connect_to_exp_envi_hand(void )
{
	ExpEnviHand2ExpEnviInterfMsgItem msg_item;
	char str_exp_envi_hand_2_exp_envi_interf_msg[EXP_ENVI_HAND_2_EXP_ENVI_INTERF_MSG_STRING_LENGTH];

	while (1) 
	{ 
		while (get_next_exp_envi_hand_2_exp_envi_interf_msg_buffer_item(msgs_exp_envi_hand_2_exp_envi_interf, &msg_item))
		{
			get_exp_envi_hand_2_exp_envi_interf_msg_type_string(msg_item.msg_type, str_exp_envi_hand_2_exp_envi_interf_msg);
			print_message(INFO_MSG ,"FirstBMICageInterfacer", "FirstBMICageInterfacerRtTask", "connect_to_exp_envi_hand", str_exp_envi_hand_2_exp_envi_interf_msg);	
			switch (msg_item.msg_type)
			{
				case EXP_ENVI_HAND_2_EXP_ENVI_INTERF_MSG_ARE_YOU_ALIVE:
					msgs_exp_envi_interf_2_exp_envi_hand = allocate_shm_client_exp_envi_interf_2_exp_envi_hand_msg_buffer(msgs_exp_envi_interf_2_exp_envi_hand);
					if (msgs_exp_envi_interf_2_exp_envi_hand == NULL)
						return print_message(ERROR_MSG ,"FirstBMICageInterfacer", "FirstBMICageInterfacerRtTask", "connect_to_exp_envi_hand", "msgs_exp_envi_interf_2_exp_envi_hand == NULL.");	
					if (!write_to_exp_envi_interf_2_exp_envi_hand_msg_buffer(msgs_exp_envi_interf_2_exp_envi_hand, static_rt_tasks_data->current_system_time, EXP_ENVI_INTERF_2_EXP_ENVI_HAND_MSG_I_AM_ALIVE, EXP_ENVI_COMP_NUM_NULL, 0))
						return print_message(ERROR_MSG ,"FirstBMICageInterfacer", "FirstBMICageInterfacerRtTask", "connect_to_exp_envi_hand", "write_to_exp_envi_interf_2_exp_envi_hand_msg_buffer().");	
					print_message(INFO_MSG ,"FirstBMICageInterfacer", "FirstBMICageInterfacerRtTask", "connect_to_exp_envi_hand", "Connection to EXP_ENVI_HANDLER is successful!!!");	
					return TRUE;		
				default:
					print_message(BUG_MSG ,"FirstBMICageInterfacer", "FirstBMICageInterfacerRtTask", "connect_to_exp_envi_hand", str_exp_envi_hand_2_exp_envi_interf_msg);	
					return (void*)print_message(BUG_MSG ,"FirstBMICageInterfacer", "FirstBMICageInterfacerRtTask", "connect_to_exp_envi_hand", "default - switch.");
			}
		}
		sleep(1);
	}
	return print_message(BUG_MSG ,"FirstBMICageInterfacer", "FirstBMICageInterfacerRtTask", "connect_to_exp_envi_interf", "Wrong hit in the code.");
}

static bool connect_to_mov_obj_hand(void )
{
	MovObjHand2MovObjInterfMsgItem msg_item;
	char str_mov_obj_hand_2_mov_obj_interf_msg[MOV_OBJ_HAND_2_MOV_OBJ_INTERF_MSG_STRING_LENGTH];

	while (1) 
	{ 
		while (get_next_mov_obj_hand_2_mov_obj_interf_msg_buffer_item(msgs_mov_obj_hand_2_mov_obj_interf, &msg_item))
		{
			get_mov_obj_hand_2_mov_obj_interf_msg_type_string(msg_item.msg_type, str_mov_obj_hand_2_mov_obj_interf_msg);
			print_message(INFO_MSG ,"FirstBMICageInterfacer", "FirstBMICageInterfacerRtTask", "connect_to_mov_obj_hand", str_mov_obj_hand_2_mov_obj_interf_msg);	
			switch (msg_item.msg_type)
			{
				case MOV_OBJ_HAND_2_MOV_OBJ_INTERF_MSG_ARE_YOU_ALIVE:
					msgs_mov_obj_interf_2_mov_obj_hand = allocate_shm_client_mov_obj_interf_2_mov_obj_hand_msg_buffer(msgs_mov_obj_interf_2_mov_obj_hand);
					if (msgs_mov_obj_interf_2_mov_obj_hand == NULL)
						return print_message(ERROR_MSG ,"FirstBMICageInterfacer", "FirstBMICageInterfacerRtTask", "connect_to_mov_obj_hand", "msgs_mov_obj_interf_2_mov_obj_hand == NULL.");	
					if (!write_to_mov_obj_interf_2_mov_obj_hand_msg_buffer(msgs_mov_obj_interf_2_mov_obj_hand, static_rt_tasks_data->current_system_time, MOV_OBJ_INTERF_2_MOV_OBJ_HAND_MSG_I_AM_ALIVE, MOV_OBJ_COMPONENT_NUM_NULL,MOV_OBJ_DIRECTION_NULL,MOV_OBJ_SPEED_NULL, MOV_OBJ_LOCATION_NULL))
						return print_message(ERROR_MSG ,"FirstBMICageInterfacer", "FirstBMICageInterfacerRtTask", "connect_to_mov_obj_hand", "write_to_mov_obj_interf_2_mov_obj_hand_msg_buffer().");	
					print_message(INFO_MSG ,"FirstBMICageInterfacer", "FirstBMICageInterfacerRtTask", "connect_to_mov_obj_hand", "Connection to MOV_OBJ_HANDLER is successful!!!");	
					return TRUE;		
				default:
					print_message(BUG_MSG ,"FirstBMICageInterfacer", "FirstBMICageInterfacerRtTask", "connect_to_mov_obj_hand", str_mov_obj_hand_2_mov_obj_interf_msg);	
					return (void*)print_message(BUG_MSG ,"FirstBMICageInterfacer", "FirstBMICageInterfacerRtTask", "connect_to_mov_obj_hand", "default - switch.");
			}
		}
		sleep(1);
	}
	return print_message(BUG_MSG ,"FirstBMICageInterfacer", "FirstBMICageInterfacerRtTask", "connect_to_mov_obj_interf", "Wrong hit in the code.");
}
