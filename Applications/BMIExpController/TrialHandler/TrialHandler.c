#include "TrialHandler.h"



int main( int argc, char *argv[])
{
	RtTasksData *rt_tasks_data = NULL;
	Gui2TrialHandMsg *msgs_gui_2_trial_hand = NULL;    
	TrialHandParadigmRobotReach *paradigm = NULL;

   	rt_tasks_data = rtai_malloc(SHM_NUM_RT_TASKS_DATA, 0);
	if (rt_tasks_data == NULL) 
		return print_message(ERROR_MSG ,"BMIExpController", "TrialHandler", "main", "rt_tasks_data == NULL.");

	paradigm = g_new0(TrialHandParadigmRobotReach, 1);
	paradigm->max_trial_length = 5000000000;
	paradigm->trial_refractory = 4000000000;
	paradigm->num_of_robot_start_positions = 1;
	paradigm->num_of_robot_target_positions = 2;
	paradigm->num_of_target_led_components = 2;
	paradigm->target_led_component_indexes_list = g_new0(unsigned int, 2);
	paradigm->target_led_component_indexes_list[0] = LEFT_LED_IDX_IN_EXP_ENVI_DATA;   // get this number from ExpEnviHandler/ConfigExpEnviComponentNums.h
	paradigm->target_led_component_indexes_list[1] = RIGHT_LED_IDX_IN_EXP_ENVI_DATA;

	msgs_gui_2_trial_hand = allocate_gui_2_trial_hand_msg_buffer(msgs_gui_2_trial_hand);

	if (! create_trial_handler_rt_thread(rt_tasks_data, msgs_gui_2_trial_hand, paradigm))
		return print_message(ERROR_MSG ,"BMIExpController", "TrialHandler", "main", "create_trial_handler_rt_thread().");

	gtk_init(&argc, &argv);
	create_gui_handler(rt_tasks_data, msgs_gui_2_trial_hand);
	gtk_main();
	return 0;
}	



