#include "TrialHandler.h"



int main( int argc, char *argv[])
{
	RtTasksData *rt_tasks_data = NULL;
	Gui2TrialHandMsg *msgs_gui_2_trial_hand = NULL;    
	TrialHand2GuiMsg *msgs_trial_hand_2_gui = NULL;    
	TrialHandParadigmRobotReach *paradigm = NULL;
	ClassifiedTrialHistory* classified_history = NULL; 
	TrialStatusHistory *trial_status_history = NULL;

   	rt_tasks_data = rtai_malloc(SHM_NUM_RT_TASKS_DATA, 0);
	if (rt_tasks_data == NULL) 
		return print_message(ERROR_MSG ,"BMIExpController", "TrialHandler", "main", "rt_tasks_data == NULL.");

	paradigm = g_new0(TrialHandParadigmRobotReach, 1);
	paradigm->max_trial_length = 10000000000;
	paradigm->min_trial_refractory = 2500000000;
	paradigm->max_extra_trial_refractory = 1500000000;
//	paradigm->min_get_ready_to_trial_start_length = 300000000;
	paradigm->min_get_ready_to_trial_start_length = 0;
	paradigm->max_extra_get_ready_to_trial_start_length = 200000000;
	paradigm->max_nose_retract_interval = 1500000000;
	paradigm->cue_led_status_duration = 300000000;

	paradigm->num_of_robot_start_positions = 1;
	paradigm->num_of_robot_target_positions = 2;
	paradigm->num_of_target_led_components = 2;

	paradigm->target_led_component_indexes_list = g_new0(unsigned int, paradigm->num_of_target_led_components);
	paradigm->target_led_component_indexes_list[0] = LEFT_LED_IDX_IN_EXP_ENVI_DATA;   // get this number from ExpEnviHandler/ConfigExpEnviComponentNums.h
	paradigm->target_led_component_indexes_list[1] = RIGHT_LED_IDX_IN_EXP_ENVI_DATA;

	paradigm->min_target_reach_threshold.r_x = 1;  //height
	paradigm->min_target_reach_threshold.r_y = 1; // depth
	paradigm->min_target_reach_threshold.r_z = 1; // lateral

	paradigm->max_target_reach_threshold.r_x = 8;  //height   //  heigh be laterali non overlapping seç. aksi takdirde sıçan her iki target için ödül alabilir. dolayısıyla targetlara dikkat etmeden sadece trial başlatır ve guide led ve target led leri izlemez. 
	paradigm->max_target_reach_threshold.r_y = 10; // depth    
	paradigm->max_target_reach_threshold.r_z = 8; // lateral
	paradigm->max_num_of_sessions = 1;  

	paradigm->current_trial_data.session_idx = 0;
	paradigm->current_trial_data.rewarding_threshold.r_x = paradigm->max_target_reach_threshold.r_x - (((paradigm->max_target_reach_threshold.r_x - paradigm->min_target_reach_threshold.r_x) / paradigm->max_num_of_sessions) * (paradigm->current_trial_data.session_idx + 1)); // if max_num_of_sessions is 10, then the 9th threshold (array indexes in C starts from 0) should be equal to minimum threshold. 
	paradigm->current_trial_data.rewarding_threshold.r_y = paradigm->max_target_reach_threshold.r_y - (((paradigm->max_target_reach_threshold.r_y - paradigm->min_target_reach_threshold.r_y) / paradigm->max_num_of_sessions) * (paradigm->current_trial_data.session_idx + 1));  // if max_num_of_sessions is 10, then the 9th threshold (array indexes in C starts from 0) should be equal to minimum threshold.
	paradigm->current_trial_data.rewarding_threshold.r_z = paradigm->max_target_reach_threshold.r_z - (((paradigm->max_target_reach_threshold.r_z - paradigm->min_target_reach_threshold.r_z) / paradigm->max_num_of_sessions) * (paradigm->current_trial_data.session_idx + 1)); // if max_num_of_sessions is 10, then the 9th threshold (array indexes in C starts from 0) should be equal to minimum threshold.

	paradigm->current_trial_data.auto_target_select_mode_on = TRUE; 

	paradigm->current_trial_data.nose_retract_mode_on = FALSE; 

	paradigm->current_trial_data.cue_led_mode_on = FALSE; 

	classified_history = allocate_classified_trial_history(classified_history, 1000, paradigm->num_of_robot_start_positions, paradigm->num_of_robot_target_positions, paradigm->max_num_of_sessions); 

	msgs_gui_2_trial_hand = allocate_gui_2_trial_hand_msg_buffer(msgs_gui_2_trial_hand);
	msgs_trial_hand_2_gui = allocate_trial_hand_2_gui_msg_buffer(msgs_trial_hand_2_gui);

	trial_status_history = allocate_trial_status_history(trial_status_history, 20);

	if (! create_trial_handler_rt_thread(rt_tasks_data, msgs_gui_2_trial_hand, paradigm, classified_history, msgs_trial_hand_2_gui, trial_status_history))
		return print_message(ERROR_MSG ,"BMIExpController", "TrialHandler", "main", "create_trial_handler_rt_thread().");


	initialize_data_read_write_handlers();

	gtk_init(&argc, &argv);
	create_gui_handler(rt_tasks_data, msgs_gui_2_trial_hand, paradigm, classified_history, msgs_trial_hand_2_gui, trial_status_history);
	gtk_main();
	return 0;
}	



