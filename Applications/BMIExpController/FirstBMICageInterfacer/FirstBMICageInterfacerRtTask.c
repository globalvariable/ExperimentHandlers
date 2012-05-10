#include "FirstBMICageInterfacerRtTask.h"

#define RX_BUFF_LEN		3
#define TX_BUFF_LEN		2

static int cage_interfacer_rt_thread = 0;
static bool rt_cage_interfacer_stay_alive = 1;

static void *rt_cage_interfacer(void *args);

static ExpEnviHand2ExpEnviInterfMsg *msgs_exp_envi_hand_2_exp_envi_interf = NULL;
static MovObjHand2MovObjInterfMsg *msgs_mov_obj_hand_2_mov_obj_interf = NULL;
static Gui2ExpEnviInterfMsg *static_msgs_gui_2_exp_envi_interf = NULL;    
static Gui2MovObjInterfMsg *static_msgs_gui_2_mov_obj_interf = NULL;    


bool create_cage_interfacer_rt_thread(Gui2ExpEnviInterfMsg *msgs_gui_2_exp_envi_interf, Gui2MovObjInterfMsg *msgs_gui_2_mov_obj_interf)
{
	static_msgs_gui_2_exp_envi_interf = msgs_gui_2_exp_envi_interf;
	static_msgs_gui_2_mov_obj_interf = msgs_gui_2_mov_obj_interf;
	msgs_exp_envi_hand_2_exp_envi_interf = allocate_shm_server_exp_envi_hand_2_exp_envi_interf_msg_buffer(msgs_exp_envi_hand_2_exp_envi_interf);
	msgs_mov_obj_hand_2_mov_obj_interf = allocate_shm_server_mov_obj_hand_2_mov_obj_interf_msg_buffer(msgs_mov_obj_hand_2_mov_obj_interf);

	if (cage_interfacer_rt_thread != 0)
		return print_message(BUG_MSG ,"BMIExpController", "FirstBMICageInterfacerRtTask", "create_cage_interfacer_rt_thread", "CANNOT create rt_thread again.");	
	cage_interfacer_rt_thread =  rt_thread_create(rt_cage_interfacer, NULL, 10000);
	if (cage_interfacer_rt_thread == 0)
		return print_message(BUG_MSG ,"BMIExpController", "FirstBMICageInterfacerRtTask", "create_cage_interfacer_rt_thread", "Couldn' t create rt_thread.");	
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
	char rx_buff[RX_BUFF_LEN];
	char tx_buff[TX_BUFF_LEN];	

	if (! check_rt_task_specs_to_init(FIRST_BMI_CAGE_INTERF_CPU_ID, FIRST_BMI_CAGE_INTERF_CPU_THREAD_ID, FIRST_BMI_CAGE_INTERF_PERIOD))  {
		print_message(ERROR_MSG ,"BMIExpController", "FirstBMICageInterfacerRtTask", "rt_cage_interfacer", "! check_rt_task_specs_to_init()."); exit(1); }	
        if (! (handler = rt_task_init_schmod(FIRST_BMI_CAGE_INTERF_TASK_NAME, FIRST_BMI_CAGE_INTERF_TASK_PRIORITY, FIRST_BMI_CAGE_INTERF_STACK_SIZE, FIRST_BMI_CAGE_INTERF_MSG_SIZE,FIRST_BMI_CAGE_INTERF_POLICY, 1 << ((FIRST_BMI_CAGE_INTERF_CPU_ID*MAX_NUM_OF_THREADS_PER_CPU)+FIRST_BMI_CAGE_INTERF_CPU_THREAD_ID)))) {
		print_message(ERROR_MSG ,"BMIExpController", "FirstBMICageInterfacerRtTask", "rt_cage_interfacer", "handler = rt_task_init_schmod()."); exit(1); }
	if (! write_rt_task_specs_to_rt_tasks_data(FIRST_BMI_CAGE_INTERF_CPU_ID, FIRST_BMI_CAGE_INTERF_CPU_THREAD_ID, FIRST_BMI_CAGE_INTERF_PERIOD, FIRST_BMI_CAGE_INTERF_POSITIVE_JITTER_THRES, FIRST_BMI_CAGE_INTERF_NEGATIVE_JITTER_THRES))  {
		print_message(ERROR_MSG ,"BMIExpController", "FirstBMICageInterfacerRtTask", "rt_cage_interfacer", "! write_rt_task_specs_to_rt_tasks_data()."); exit(1); }	
        period = nano2count(FIRST_BMI_CAGE_INTERF_PERIOD);
        rt_task_make_periodic(handler, rt_get_time() + period, period);


        mlockall(MCL_CURRENT | MCL_FUTURE);
	rt_make_hard_real_time();		// do not forget this // check the task by nano /proc/rtai/scheduler (HD/SF) 

	curr_time = rt_get_cpu_time_ns();
	prev_time = curr_time;	
        while (rt_cage_interfacer_stay_alive) 
	{
		// routines
		if (! handle_gui_2_exp_envi_interf_msgs(static_msgs_gui_2_exp_envi_interf, tx_buff)) {
			print_message(ERROR_MSG ,"BMIExpController", "FirstBMICageInterfacerRtTask", "rt_cage_interfacer", "! handle_gui_2_exp_envi_interf_msgs()."); break; }	
		if (! handle_gui_2_mov_obj_interf_msgs(static_msgs_gui_2_mov_obj_interf, tx_buff)) {
			print_message(ERROR_MSG ,"BMIExpController", "FirstBMICageInterfacerRtTask", "rt_cage_interfacer", "! handle_gui_2_mov_obj_interf_msgs()."); break; }	
		if (! handle_exp_envi_hand_2_exp_envi_interf_msgs(msgs_exp_envi_hand_2_exp_envi_interf, tx_buff)) {
			print_message(ERROR_MSG ,"BMIExpController", "FirstBMICageInterfacerRtTask", "rt_cage_interfacer", "! handle_exp_envi_hand_2_exp_envi_interf_msgs()."); break; }	
		if (! handle_mov_obj_hand_2_mov_obj_interf_msgs(msgs_mov_obj_hand_2_mov_obj_interf, tx_buff)) {
			print_message(ERROR_MSG ,"BMIExpController", "FirstBMICageInterfacerRtTask", "rt_cage_interfacer", "! handle_mov_obj_hand_2_mov_obj_interf_msgs()."); break; }	
		if (! write_to_rs232_com1(tx_buff, TX_BUFF_LEN)) {
			print_message(ERROR_MSG ,"BMIExpController", "FirstBMICageInterfacerRtTask", "rt_cage_interfacer", "! write_to_rs232_com1()."); break; }	
		evaluate_and_save_period_run_time(FIRST_BMI_CAGE_INTERF_CPU_ID, FIRST_BMI_CAGE_INTERF_CPU_THREAD_ID, curr_time, rt_get_cpu_time_ns());		
        	rt_task_wait_period();
		curr_time = rt_get_cpu_time_ns();
		evaluate_and_save_jitter(FIRST_BMI_CAGE_INTERF_CPU_ID, FIRST_BMI_CAGE_INTERF_CPU_THREAD_ID, prev_time, curr_time);
		prev_time = curr_time;
		if (! read_from_rs232_com1(rx_buff, RX_BUFF_LEN))  {
			print_message(ERROR_MSG ,"BMIExpController", "FirstBMICageInterfacerRtTask", "rt_cage_interfacer", "! read_from_rs232_com1().");  break; }	
		if (! handle_exp_envi_interf_2_exp_envi_hand_msgs(rx_buff)) {
			print_message(ERROR_MSG ,"BMIExpController", "FirstBMICageInterfacerRtTask", "rt_cage_interfacer", "! handle_exp_envi_interf_2_exp_envi_hand_msgs()."); break; }	
		if (! handle_mov_obj_interf_2_mov_obj_hand_msgs(rx_buff)) {
			print_message(ERROR_MSG ,"BMIExpController", "FirstBMICageInterfacerRtTask", "rt_cage_interfacer", "! handle_mov_obj_interf_2_mov_obj_hand_msgs()."); break; }	
		// routines	

        }
	rt_make_soft_real_time();
        rt_task_delete(handler);
	print_message(INFO_MSG ,"BMIExpController", "FirstBMICageInterfacerRtTask", "rt_cage_interfacer", "rt_task_delete().");	

        return 0; 
}
