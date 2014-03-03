#include "HandleTrialDurHand2TrialHandMsgs.h"


static TrialStatus *trial_status = NULL;
static TrialDurHand2TrialHandMsg *msgs_trial_dur_hand_2_trial_hand = NULL;
static TrialHand2TrialDurHandMsg *msgs_trial_hand_2_trial_dur_hand = NULL;
static TrialHand2ExpEnviHandMsg *msgs_trial_hand_2_exp_envi_hand = NULL;
static TrialHand2MovObjHandMsg *msgs_trial_hand_2_mov_obj_hand = NULL;
static TrialHand2NeuralNetMsg *msgs_trial_hand_2_neural_net = NULL;
#ifdef	SIMULATION_MODE
static TrialHand2SpikeGenMsg *msgs_trial_hand_2_spike_gen = NULL;
#endif
static ClassifiedTrialHistory *classified_history = NULL;
static TrialHandParadigmRobotReach *paradigm = NULL;
static TrialHand2GuiMsg *msgs_trial_hand_2_gui = NULL;
static TrialStatusHistory *trial_status_history = NULL;


bool handle_trial_dur_handler_to_trial_handler_msg(TimeStamp current_time)
{
	TrialDurHand2TrialHandMsgItem msg_item;
	char str_trial_dur_msg[TRIAL_DUR_HAND_2_TRIAL_HAND_MSG_STRING_LENGTH];
	char str_status[TRIAL_STATUS_MAX_STRING_LENGTH];
	TrialHand2NeuralNetMsgAdditional trial_hand_to_neural_net_msg_add;
#ifdef	SIMULATION_MODE
	TrialHand2SpikeGenMsgAdditional trial_hand_to_spike_gen_msg_add;
#endif
	TrialHand2MovObjHandMsgAdditional  trial_hand_2_mov_obj_hand_add;
	double remained_distance_to_target;
	double reward, R_n;
	double remained_distance_to_target_windowed_average;
	TimeStamp trial_length, refractory;


	while (get_next_trial_dur_hand_2_trial_hand_msg_buffer_item(msgs_trial_dur_hand_2_trial_hand, &msg_item))
	{
		get_trial_dur_hand_2_trial_hand_msg_type_string(msg_item.msg_type, str_trial_dur_msg);
		print_message(INFO_MSG ,"TrialHandler", "HandleTrialDurHand2TrialHandMsgss", "handle_trial_dur_handler_to_trial_handler_msg", str_trial_dur_msg);
		switch (msg_item.msg_type)
		{
			case TRIAL_DUR_HAND_2_TRIAL_HAND_MSG_TIMEOUT:	
				switch (*trial_status)
				{
					case TRIAL_STATUS_TRIALS_DISABLED:
						break;   // do nothing
					case TRIAL_STATUS_IN_TRIAL:

						remained_distance_to_target = msg_item.additional_data;
						trial_length = current_time - paradigm->current_trial_data.trial_start_time;
						paradigm->current_trial_data.trial_end_time = current_time;
						paradigm->current_trial_data.trial_length = trial_length;
						paradigm->current_trial_data.remained_distance_to_target = (remained_distance_to_target/ paradigm->current_trial_data.initial_distance_to_target) - 1.0;  // here is -1.0 due to the averaging by  calculate_and_get_remained_distance_to_target_windowed_average(). for the first trial paradigm->current_trial_data.remained_distance_to_target will be zero. NORMALIZATION AROUND ZERO

						remained_distance_to_target_windowed_average = calculate_and_get_remained_distance_to_target_windowed_average(classified_history, &(paradigm->current_trial_data), DISTANCE_AVERAGING_WINDOW);

						paradigm->current_trial_data.binary_reward = FALSE;
						R_n = calculate_and_get_windowed_binary_reward_average(classified_history, &(paradigm->current_trial_data), REWARD_AVERAGING_WINDOW);	
					//	reward = 1 - R_n;
						reward = -0.5* (1 - R_n);
						paradigm->current_trial_data.reward_magnitude = reward;

						printf ("reward --- : %.8f\n", reward);
						printf ("distance to target --- : %.8f\n", remained_distance_to_target);
						printf ("initial distance to target --- : %.8f\n", paradigm->current_trial_data.initial_distance_to_target);
						printf ("paradigm->current_trial_data.remained_distance_to_target --- : %.8f\n", paradigm->current_trial_data.remained_distance_to_target);
						printf ("remained_distance_to_target_windowed_average --- : %.8f\n", remained_distance_to_target_windowed_average);

						trial_hand_to_neural_net_msg_add.reward = reward;
						if (!write_to_trial_hand_2_neural_net_msg_buffer(msgs_trial_hand_2_neural_net, current_time, TRIAL_HAND_2_NEURAL_NET_MSG_PUNISHMENT_GIVEN, trial_hand_to_neural_net_msg_add))  // to tell unsuccesful trial
							return print_message(ERROR_MSG ,"TrialHandler", "HandleMovObjHand2TrialHandMsgs", "handle_mov_obj_handler_to_trial_handler_msg", "write_to_trial_hand_2_neural_net_msg_buffer()");

						if (!write_to_trial_hand_2_trial_dur_hand_msg_buffer(msgs_trial_hand_2_trial_dur_hand, current_time, TRIAL_HAND_2_TRIAL_DUR_HAND_MSG_DISABLE_DURATION_HANDLING, 0))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleMovObjHand2TrialHandMsgs", "handle_mov_obj_handler_to_trial_handler_msg", "write_to_trial_hand_2_trial_dur_hand_msg_buffer()");
						*trial_status = TRIAL_STATUS_IN_REFRACTORY;

						if (! write_trial_data_to_classified_trial_history(classified_history, &(paradigm->current_trial_data)))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleMovObjHand2TrialHandMsgs", "handle_mov_obj_handler_to_trial_handler_msg", "write_trial_data_to_classified_trial_history()");

						paradigm->current_trial_data.trial_start_time = 0;
						paradigm->current_trial_data.trial_end_time = 0;
						paradigm->current_trial_data.trial_length = 0;

	// BELOW LINE IS SET BY THE USER.
	//						paradigm->current_trial_data.robot_start_position_idx = (unsigned int)(paradigm->num_of_robot_start_positions * get_rand_number());   ///  Bunu trial bittiginde yap.

						if (paradigm->current_trial_data.auto_target_select_mode_on)
							paradigm->current_trial_data.robot_target_position_idx = (unsigned int)(paradigm->num_of_robot_target_positions * get_rand_number());   ///  Bunu trial bittiginde yap.
						else
							paradigm->current_trial_data.robot_target_position_idx = paradigm->current_trial_data.gui_selected_target_position_idx;

						paradigm->current_trial_data.target_led_component_list_idx = paradigm->current_trial_data.robot_target_position_idx;

						
						if (!write_to_trial_hand_2_trial_dur_hand_msg_buffer(msgs_trial_hand_2_trial_dur_hand, current_time, TRIAL_HAND_2_TRIAL_DUR_HAND_MSG_DISABLE_DURATION_HANDLING, 0))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleTrialDurHand2TrialHandMsgss", "handle_trial_dur_handler_to_trial_handler_msg", "write_to_trial_hand_2_trial_dur_hand_msg_buffer()");
						refractory = current_time + paradigm->min_trial_refractory + ((TimeStamp)(get_rand_number() * (double)paradigm->max_extra_trial_refractory));
						if (!write_to_trial_hand_2_trial_dur_hand_msg_buffer(msgs_trial_hand_2_trial_dur_hand, current_time, TRIAL_HAND_2_TRIAL_DUR_HAND_MSG_ENABLE_DURATION_HANDLING, refractory))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleTrialDurHand2TrialHandMsgss", "handle_trial_dur_handler_to_trial_handler_msg", "write_to_trial_hand_2_trial_dur_hand_msg_buffer()");
						trial_hand_2_mov_obj_hand_add.dummy = 0;	// send this message before TRIAL_HAND_2_MOV_OBJ_HAND_MSG_END_TRIAL since mov obj handler handles this msg according to target idx
						if (!write_to_trial_hand_2_mov_obj_hand_msg_buffer(msgs_trial_hand_2_mov_obj_hand, current_time, TRIAL_HAND_2_MOV_OBJ_HAND_MSG_TRIAL_TIMEOUT, trial_hand_2_mov_obj_hand_add))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleTrialDurHand2TrialHandMsgss", "handle_trial_dur_handler_to_trial_handler_msg", "write_to_trial_hand_2_mov_obj_hand_msg_buffer()");

						if ((paradigm->current_trial_data.robot_target_position_idx) == 0)   /// LEFT TARGET
						{
							trial_hand_2_mov_obj_hand_add.robot_start_position_idx = paradigm->current_trial_data.robot_start_position_idx; 
						}
						else		// RIGHT TARGET
						{
							trial_hand_2_mov_obj_hand_add.robot_start_position_idx = paradigm->num_of_robot_start_positions - 1 - paradigm->current_trial_data.robot_start_position_idx;
						}
		
						if (!write_to_trial_hand_2_mov_obj_hand_msg_buffer(msgs_trial_hand_2_mov_obj_hand, current_time, TRIAL_HAND_2_MOV_OBJ_HAND_MSG_END_TRIAL, trial_hand_2_mov_obj_hand_add))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleTrialDurHand2TrialHandMsgss", "handle_trial_dur_handler_to_trial_handler_msg", "write_to_trial_hand_2_mov_obj_hand_msg_buffer()");

						if (!write_to_trial_hand_2_exp_envi_hand_msg_buffer(msgs_trial_hand_2_exp_envi_hand, current_time, TRIAL_HAND_2_EXP_ENVI_HAND_MSG_END_TRIAL, 0))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleTrialDurHand2TrialHandMsgss", "handle_mov_obj_handler_to_trial_handler_msg", "write_to_trial_hand_2_exp_envi_hand_msg_buffer()");
/*						if (!write_to_trial_hand_2_exp_envi_hand_msg_buffer(msgs_trial_hand_2_exp_envi_hand, current_time, TRIAL_HAND_2_EXP_ENVI_HAND_MSG_RELEASE_PUNISHMENT, 0))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleMovObjHand2TrialHandMsgs", "handle_mov_obj_handler_to_trial_handler_msg", "write_to_trial_hand_2_exp_envi_hand_msg_buffer()");  */

#ifdef	SIMULATION_MODE
						trial_hand_to_spike_gen_msg_add.trial_status_change_msg_add.new_trial_status = TRIAL_STATUS_IN_REFRACTORY;
						trial_hand_to_spike_gen_msg_add.trial_status_change_msg_add.new_robot_start_position_idx = paradigm->current_trial_data.robot_start_position_idx;
						if (!write_to_trial_hand_2_spike_gen_msg_buffer(msgs_trial_hand_2_spike_gen, current_time, TRIAL_HAND_2_SPIKE_GEN_MSG_TRIAL_STATUS_CHANGED, trial_hand_to_spike_gen_msg_add))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleMovObjHand2TrialHandMsgs", "handle_mov_obj_handler_to_trial_handler_msg", "write_to_trial_hand_2_spike_gen_msg_buffer()");
#endif	
						if (!write_to_trial_hand_2_gui_msg_buffer(msgs_trial_hand_2_gui, current_time, TRIAL_HAND_2_GUI_MSG_TRIAL_STATUS_CHANGE, TRIAL_STATUS_IN_REFRACTORY))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleMovObjHand2TrialHandMsgs", "handle_mov_obj_handler_to_trial_handler_msg", "write_to_trial_hand_2_spike_gen_msg_buffer()");
						if (! write_to_trial_status_history(trial_status_history, current_time, TRIAL_STATUS_IN_REFRACTORY))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleMovObjHand2TrialHandMsgs", "handle_mov_obj_handler_to_trial_handler_msg", "write_to_trial_status_history()");

						trial_hand_to_neural_net_msg_add.trial_status_change_msg_add.new_trial_status = TRIAL_STATUS_IN_REFRACTORY;
						trial_hand_to_neural_net_msg_add.trial_status_change_msg_add.new_robot_start_position_idx = paradigm->current_trial_data.robot_start_position_idx;
						if (!write_to_trial_hand_2_neural_net_msg_buffer(msgs_trial_hand_2_neural_net, current_time, TRIAL_HAND_2_NEURAL_NET_MSG_TRIAL_STATUS_CHANGED, trial_hand_to_neural_net_msg_add))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleMovObjHand2TrialHandMsgs", "handle_mov_obj_handler_to_trial_handler_msg", "write_to_trial_hand_2_neural_net_msg_buffer()");
						break;  
					case TRIAL_STATUS_IN_REFRACTORY:
						*trial_status = TRIAL_STATUS_START_TRIAL_AVAILABLE;
						trial_hand_to_neural_net_msg_add.trial_status_change_msg_add.new_trial_status = TRIAL_STATUS_START_TRIAL_AVAILABLE;
						trial_hand_to_neural_net_msg_add.trial_status_change_msg_add.new_robot_target_position_idx = 0;
						if (!write_to_trial_hand_2_neural_net_msg_buffer(msgs_trial_hand_2_neural_net, current_time, TRIAL_HAND_2_NEURAL_NET_MSG_TRIAL_STATUS_CHANGED, trial_hand_to_neural_net_msg_add))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleTrialDurHand2TrialHandMsgss", "handle_trial_dur_handler_to_trial_handler_msg", "write_to_trial_hand_2_neural_net_msg_buffer()");
#ifdef	SIMULATION_MODE
						trial_hand_to_spike_gen_msg_add.trial_status_change_msg_add.new_trial_status = TRIAL_STATUS_START_TRIAL_AVAILABLE;
						trial_hand_to_spike_gen_msg_add.trial_status_change_msg_add.new_robot_target_position_idx = 0;
						if (!write_to_trial_hand_2_spike_gen_msg_buffer(msgs_trial_hand_2_spike_gen, current_time, TRIAL_HAND_2_SPIKE_GEN_MSG_TRIAL_STATUS_CHANGED, trial_hand_to_spike_gen_msg_add))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleTrialDurHand2TrialHandMsgss", "handle_trial_dur_handler_to_trial_handler_msg", "write_to_trial_hand_2_neural_net_msg_buffer()");
#endif
						if (!write_to_trial_hand_2_gui_msg_buffer(msgs_trial_hand_2_gui, current_time, TRIAL_HAND_2_GUI_MSG_TRIAL_STATUS_CHANGE, TRIAL_STATUS_START_TRIAL_AVAILABLE))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleTrialDurHand2TrialHandMsgss", "handle_trial_dur_handler_to_trial_handler_msg", "write_to_trial_hand_2_gui_msg_buffer()");
						if (! write_to_trial_status_history(trial_status_history, current_time, TRIAL_STATUS_START_TRIAL_AVAILABLE))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleTrialDurHand2TrialHandMsgss", "handle_trial_dur_handler_to_trial_handler_msg", "write_to_trial_status_history()");
						if (!write_to_trial_hand_2_exp_envi_hand_msg_buffer(msgs_trial_hand_2_exp_envi_hand, current_time, TRIAL_HAND_2_EXP_ENVI_HAND_MSG_START_TRIAL_AVAILABLE, 0))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleTrialDurHand2TrialHandMsgss", "handle_trial_dur_handler_to_trial_handler_msg", "write_to_trial_hand_2_exp_envi_hand_msg_buffer()");
						break;
					case TRIAL_STATUS_START_TRIAL_AVAILABLE:	
						print_message(BUG_MSG ,"TrialHandler", "HandleTrialDurHand2TrialHandMsgss", "handle_trial_dur_handler_to_trial_handler_msg", str_trial_dur_msg);
						get_trial_status_type_string(*trial_status, str_status);   
						return print_message(BUG_MSG ,"TrialHandler", "HandleTrialDurHand2TrialHandMsgss", "handle_trial_dur_handler_to_trial_handler_msg", str_status);
					default:
						print_message(BUG_MSG ,"TrialHandler", "HandleTrialDurHand2TrialHandMsgss", "handle_trial_dur_handler_to_trial_handler_msg", str_trial_dur_msg);
						get_trial_status_type_string(*trial_status, str_status);   
						return print_message(BUG_MSG ,"TrialHandler", "HandleTrialDurHand2TrialHandMsgss", "handle_trial_dur_handler_to_trial_handler_msg", str_status);
				}
				break;
			default:
				return print_message(BUG_MSG ,"TrialHandler", "HandleTrialDurHand2TrialHandMsgss", "handle_trial_dur_handler_to_trial_handler_msg", str_trial_dur_msg);	
		}
	}
	return TRUE;
}


#ifdef	SIMULATION_MODE
void initialize_trial_dur_handler_to_trial_handler_msg_params(TrialStatus *arg_trial_status, TrialDurHand2TrialHandMsg *arg_msgs_trial_dur_hand_2_trial_hand, TrialHand2TrialDurHandMsg *arg_msgs_trial_hand_2_trial_dur_hand, TrialHand2ExpEnviHandMsg *arg_msgs_trial_hand_2_exp_envi_hand, TrialHand2MovObjHandMsg *arg_msgs_trial_hand_2_mov_obj_hand, TrialHand2NeuralNetMsg *arg_msgs_trial_hand_2_neural_net, TrialHand2SpikeGenMsg *arg_msgs_trial_hand_2_spike_gen, ClassifiedTrialHistory *arg_classified_history, TrialHandParadigmRobotReach *arg_paradigm, TrialHand2GuiMsg *arg_msgs_trial_hand_2_gui, TrialStatusHistory *arg_trial_status_history)
#endif
#ifdef	IN_VIVO_MODE
void initialize_trial_dur_handler_to_trial_handler_msg_params(TrialStatus *arg_trial_status, TrialDurHand2TrialHandMsg *arg_msgs_trial_dur_hand_2_trial_hand, TrialHand2TrialDurHandMsg *arg_msgs_trial_hand_2_trial_dur_hand, TrialHand2ExpEnviHandMsg *arg_msgs_trial_hand_2_exp_envi_hand, TrialHand2MovObjHandMsg *arg_msgs_trial_hand_2_mov_obj_hand, TrialHand2NeuralNetMsg *arg_msgs_trial_hand_2_neural_net, ClassifiedTrialHistory *arg_classified_history, TrialHandParadigmRobotReach *arg_paradigm, TrialHand2GuiMsg *arg_msgs_trial_hand_2_gui, TrialStatusHistory *arg_trial_status_history)
#endif
{
	trial_status = arg_trial_status;
	msgs_trial_dur_hand_2_trial_hand = arg_msgs_trial_dur_hand_2_trial_hand;
	msgs_trial_hand_2_trial_dur_hand = arg_msgs_trial_hand_2_trial_dur_hand;
	msgs_trial_hand_2_exp_envi_hand = arg_msgs_trial_hand_2_exp_envi_hand;
	msgs_trial_hand_2_mov_obj_hand = arg_msgs_trial_hand_2_mov_obj_hand;
	msgs_trial_hand_2_neural_net = arg_msgs_trial_hand_2_neural_net;
#ifdef	SIMULATION_MODE
	msgs_trial_hand_2_spike_gen = arg_msgs_trial_hand_2_spike_gen;
#endif
	classified_history = arg_classified_history; 
	paradigm = arg_paradigm;
	msgs_trial_hand_2_gui = arg_msgs_trial_hand_2_gui;
	trial_status_history = arg_trial_status_history;
}


