#include "HandleExpEnviHand2TrialHandMsgs.h"


bool handle_exp_envi_handler_to_trial_handler_msg(TrialStatus *trial_status, TimeStamp current_time, ExpEnviHand2TrialHandMsg *msgs_exp_envi_hand_2_trial_hand, TrialHand2TrialDurHandMsg *msgs_trial_hand_2_trial_dur_hand, TrialHand2ExpEnviHandMsg *msgs_trial_hand_2_exp_envi_hand, TrialHand2MovObjHandMsg *msgs_trial_hand_2_mov_obj_hand, TrialHand2NeuralNetMsg *msgs_trial_hand_2_neural_net, TrialHand2SpikeGenMsg *msgs_trial_hand_2_spike_gen, TrialHandParadigmRobotReach *paradigm, ClassifiedTrialHistory* classified_history)
{
	ExpEnviHand2TrialHandMsgItem msg_item;
	char str_exp_envi_msg[EXP_ENVI_HAND_2_TRIAL_HAND_MSG_STRING_LENGTH];
	char str_status[TRIAL_STATUS_MAX_STRING_LENGTH];
	TrialHand2NeuralNetMsgAdditional trial_hand_to_neural_net_msg_add;
	TrialHand2SpikeGenMsgAdditional trial_hand_to_spike_gen_msg_add;
	TrialHand2MovObjHandMsgAdditional trial_hand_to_mov_obj_hand_msg_add;
	while (get_next_exp_envi_hand_2_trial_hand_msg_buffer_item(msgs_exp_envi_hand_2_trial_hand, &msg_item))
	{
		get_exp_envi_hand_2_trial_hand_msg_type_string(msg_item.msg_type, str_exp_envi_msg);
		print_message(INFO_MSG ,"TrialHandler", "HandleExpEnviHand2TrialHandMsgs", "handle_exp_envi_handler_to_trial_handler_msg", str_exp_envi_msg);
		switch (msg_item.msg_type)
		{
			case EXP_ENVI_HAND_2_TRIAL_HAND_MSG_START_TRIAL_REQUEST:	
				switch (*trial_status)
				{
					case TRIAL_STATUS_TRIALS_DISABLED:
						break;   // do nothing
					case TRIAL_STATUS_IN_TRIAL:
						break;   // do nothing
					case TRIAL_STATUS_IN_REFRACTORY:
						break;   // do nothing
					case TRIAL_STATUS_START_TRIAL_AVAILABLE:	
						*trial_status = TRIAL_STATUS_IN_TRIAL;
						paradigm->selected_robot_target_position_idx = (unsigned int)(paradigm->num_of_robot_target_positions * get_rand_number());   ///  Bunu trial bittiginde yap.
						paradigm->selected_target_led_component_list_idx = paradigm->selected_robot_target_position_idx;
					
						classified_history->all_trials->history[classified_history->all_trials->buff_write_idx].trial_start_time = current_time;   
						classified_history->all_trials->history[classified_history->all_trials->buff_write_idx].target_led_component_list_idx = paradigm->selected_target_led_component_list_idx;
						classified_history->all_trials->history[classified_history->all_trials->buff_write_idx].robot_start_position_idx = paradigm->selected_robot_start_position_idx;
						classified_history->all_trials->history[classified_history->all_trials->buff_write_idx].robot_target_position_idx = paradigm->selected_robot_target_position_idx;
						classified_history->all_trials->history[classified_history->all_trials->buff_write_idx].rewarding_threshold = paradigm->selected_target_reach_threshold;

						classified_history->trial_types[paradigm->selected_robot_start_position_idx][paradigm->selected_robot_target_position_idx]->history[classified_history->trial_types[paradigm->selected_robot_start_position_idx][paradigm->selected_robot_target_position_idx]->buff_write_idx].trial_start_time = current_time;   
						classified_history->trial_types[paradigm->selected_robot_start_position_idx][paradigm->selected_robot_target_position_idx]->history[classified_history->trial_types[paradigm->selected_robot_start_position_idx][paradigm->selected_robot_target_position_idx]->buff_write_idx].target_led_component_list_idx = paradigm->selected_target_led_component_list_idx;
						classified_history->trial_types[paradigm->selected_robot_start_position_idx][paradigm->selected_robot_target_position_idx]->history[classified_history->trial_types[paradigm->selected_robot_start_position_idx][paradigm->selected_robot_target_position_idx]->buff_write_idx].robot_start_position_idx = paradigm->selected_robot_start_position_idx;
						classified_history->trial_types[paradigm->selected_robot_start_position_idx][paradigm->selected_robot_target_position_idx]->history[classified_history->trial_types[paradigm->selected_robot_start_position_idx][paradigm->selected_robot_target_position_idx]->buff_write_idx].robot_target_position_idx = paradigm->selected_robot_target_position_idx;
						classified_history->trial_types[paradigm->selected_robot_start_position_idx][paradigm->selected_robot_target_position_idx]->history[classified_history->trial_types[paradigm->selected_robot_start_position_idx][paradigm->selected_robot_target_position_idx]->buff_write_idx].rewarding_threshold = paradigm->selected_target_reach_threshold;


						if (!write_to_trial_hand_2_trial_dur_hand_msg_buffer(msgs_trial_hand_2_trial_dur_hand, current_time, TRIAL_HAND_2_TRIAL_DUR_HAND_MSG_ENABLE_DURATION_HANDLING, current_time + paradigm->max_trial_length))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleExpEnviHand2TrialHandMsgs", "handle_exp_envi_handler_to_trial_handler_msg", "write_to_trial_hand_2_trial_dur_hand_msg_buffer()");
						if (!write_to_trial_hand_2_exp_envi_hand_msg_buffer(msgs_trial_hand_2_exp_envi_hand, current_time, TRIAL_HAND_2_EXP_ENVI_HAND_MSG_START_TRIAL, paradigm->selected_target_led_component_list_idx))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleExpEnviHand2TrialHandMsgs", "handle_exp_envi_handler_to_trial_handler_msg", "write_to_trial_hand_2_exp_envi_hand_msg_buffer()");
						trial_hand_to_mov_obj_hand_msg_add.threshold = paradigm->selected_target_reach_threshold;
						if (!write_to_trial_hand_2_mov_obj_hand_msg_buffer(msgs_trial_hand_2_mov_obj_hand, current_time, TRIAL_HAND_2_MOV_OBJ_HAND_MSG_ELLIPSOID_THRESHOLD, trial_hand_to_mov_obj_hand_msg_add))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleExpEnviHand2TrialHandMsgs", "handle_exp_envi_handler_to_trial_handler_msg", "write_to_trial_hand_2_mov_obj_hand_msg_buffer()");
						trial_hand_to_mov_obj_hand_msg_add.robot_target_position_idx = paradigm->selected_robot_target_position_idx;
						if (!write_to_trial_hand_2_mov_obj_hand_msg_buffer(msgs_trial_hand_2_mov_obj_hand, current_time, TRIAL_HAND_2_MOV_OBJ_HAND_MSG_START_TRIAL, trial_hand_to_mov_obj_hand_msg_add))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleExpEnviHand2TrialHandMsgs", "handle_exp_envi_handler_to_trial_handler_msg", "write_to_trial_hand_2_mov_obj_hand_msg_buffer()");
						trial_hand_to_neural_net_msg_add.trial_status_change_msg_add.new_trial_status = TRIAL_STATUS_IN_TRIAL;
						trial_hand_to_neural_net_msg_add.trial_status_change_msg_add.new_robot_target_position_idx = paradigm->selected_robot_target_position_idx;
						if (!write_to_trial_hand_2_neural_net_msg_buffer(msgs_trial_hand_2_neural_net, current_time, TRIAL_HAND_2_NEURAL_NET_MSG_TRIAL_STATUS_CHANGED, trial_hand_to_neural_net_msg_add))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleExpEnviHand2TrialHandMsgs", "handle_exp_envi_handler_to_trial_handler_msg", "write_to_trial_hand_2_neural_net_msg_buffer()");
						// DO NOT SEND TRIAL START MSG NOW. SEND IT WHEN THE ROBOT CONTROL IS AVAILABLE AFTER STAY_AT_START_DURATION ENDS.
//						trial_hand_to_neural_net_msg_add.dummy = 0;
//						if (!write_to_trial_hand_2_neural_net_msg_buffer(msgs_trial_hand_2_neural_net, current_time, TRIAL_HAND_2_NEURAL_NET_MSG_TRIAL_START, trial_hand_to_neural_net_msg_add))
//							return print_message(ERROR_MSG ,"TrialHandler", "HandleExpEnviHand2TrialHandMsgs", "handle_exp_envi_handler_to_trial_handler_msg", "write_to_trial_hand_2_neural_net_msg_buffer()");
						trial_hand_to_spike_gen_msg_add.trial_status_change_msg_add.new_trial_status = TRIAL_STATUS_IN_TRIAL;
						trial_hand_to_spike_gen_msg_add.trial_status_change_msg_add.new_robot_target_position_idx = paradigm->selected_robot_target_position_idx;
						if (!write_to_trial_hand_2_spike_gen_msg_buffer(msgs_trial_hand_2_spike_gen, current_time, TRIAL_HAND_2_SPIKE_GEN_MSG_TRIAL_STATUS_CHANGED, trial_hand_to_spike_gen_msg_add))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleExpEnviHand2TrialHandMsgs", "handle_exp_envi_handler_to_trial_handler_msg", "write_to_trial_hand_2_neural_net_msg_buffer()");
						break;
					default:
						print_message(BUG_MSG ,"TrialHandler", "HandleExpEnviHand2TrialHandMsgs", "handle_exp_envi_handler_to_trial_handler_msg", str_exp_envi_msg);
						get_trial_status_type_string(*trial_status, str_status);   
						return print_message(BUG_MSG ,"TrialHandler", "HandleExpEnviHand2TrialHandMsgs", "handle_exp_envi_handler_to_trial_handler_msg", str_status);
				}
				break;
			default:
				return print_message(BUG_MSG ,"TrialHandler", "HandleExpEnviHand2TrialHandMsgs", "handle_exp_envi_handler_to_trial_handler_msg", str_exp_envi_msg);	
		}
	}
	return TRUE;
}
