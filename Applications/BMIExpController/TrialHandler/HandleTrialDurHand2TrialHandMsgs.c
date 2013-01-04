#include "HandleTrialDurHand2TrialHandMsgs.h"


bool handle_trial_dur_handler_to_trial_handler_msg(TrialStatus *trial_status, TimeStamp current_time, TrialDurHand2TrialHandMsg *msgs_trial_dur_hand_2_trial_hand, TrialHand2TrialDurHandMsg *msgs_trial_hand_2_trial_dur_hand, TrialHand2ExpEnviHandMsg *msgs_trial_hand_2_exp_envi_hand, TrialHand2MovObjHandMsg *msgs_trial_hand_2_mov_obj_hand, TrialHand2NeuralNetMsg *msgs_trial_hand_2_neural_net, TrialHand2SpikeGenMsg *msgs_trial_hand_2_spike_gen, ClassifiedTrialHistory* classified_history, TrialHandParadigmRobotReach *paradigm)
{
	TrialDurHand2TrialHandMsgItem msg_item;
	char str_trial_dur_msg[TRIAL_DUR_HAND_2_TRIAL_HAND_MSG_STRING_LENGTH];
	char str_status[TRIAL_STATUS_MAX_STRING_LENGTH];
	TrialHand2NeuralNetMsgAdditional trial_hand_to_neural_net_msg_add;
	TrialHand2SpikeGenMsgAdditional trial_hand_to_spike_gen_msg_add;
	TrialHand2MovObjHandMsgAdditional  trial_hand_to_mov_obj_hand_msg_add;
	double reward;
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

						reward = -1.0;
						classified_history->all_trials->history[classified_history->all_trials->buff_write_idx].reward_magnitude = reward;
						classified_history->trial_types[paradigm->selected_robot_start_position_idx][paradigm->selected_robot_target_position_idx]->history[classified_history->trial_types[paradigm->selected_robot_start_position_idx][paradigm->selected_robot_target_position_idx]->buff_write_idx].reward_magnitude = reward;
						printf ("reward: %.8f\n", reward);
						classified_history->all_trials->history[classified_history->all_trials->buff_write_idx].trial_end_time = current_time;
						classified_history->trial_types[paradigm->selected_robot_start_position_idx][paradigm->selected_robot_target_position_idx]->history[classified_history->trial_types[paradigm->selected_robot_start_position_idx][paradigm->selected_robot_target_position_idx]->buff_write_idx].trial_end_time = current_time;

						reward = get_abs_mean_of_reward_of_previous_trials(classified_history->trial_types[paradigm->selected_robot_start_position_idx][paradigm->selected_robot_target_position_idx], 4);
						reward = ((reward * 4.0) + fabs(classified_history->all_trials->history[classified_history->all_trials->buff_write_idx].reward_magnitude))/5.0;   // get mean of last 5 trials including this trial
						trial_hand_to_neural_net_msg_add.reward = -reward;
						printf ("reward --- : %.8f\n", trial_hand_to_neural_net_msg_add.reward);
						if (!write_to_trial_hand_2_neural_net_msg_buffer(msgs_trial_hand_2_neural_net, current_time, TRIAL_HAND_2_NEURAL_NET_MSG_PUNISHMENT_GIVEN, trial_hand_to_neural_net_msg_add))  // to tell unsuccesful trial
							return print_message(ERROR_MSG ,"TrialHandler", "HandleMovObjHand2TrialHandMsgs", "handle_mov_obj_handler_to_trial_handler_msg", "write_to_trial_hand_2_neural_net_msg_buffer()");

						trial_hand_to_mov_obj_hand_msg_add.dummy = 0;
						if (!write_to_trial_hand_2_mov_obj_hand_msg_buffer(msgs_trial_hand_2_mov_obj_hand, current_time, TRIAL_HAND_2_MOV_OBJ_HAND_MSG_TRIAL_TIMEOUT, trial_hand_to_mov_obj_hand_msg_add))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleTrialDurHand2TrialHandMsgss", "handle_trial_dur_handler_to_trial_handler_msg", "write_to_trial_hand_2_mov_obj_hand_msg_buffer()");
						if (!write_to_trial_hand_2_exp_envi_hand_msg_buffer(msgs_trial_hand_2_exp_envi_hand, current_time, TRIAL_HAND_2_EXP_ENVI_HAND_MSG_RELEASE_PUNISHMENT, 0))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleMovObjHand2TrialHandMsgs", "handle_mov_obj_handler_to_trial_handler_msg", "write_to_trial_hand_2_exp_envi_hand_msg_buffer()");

						break;
					case TRIAL_STATUS_IN_REFRACTORY:
						*trial_status = TRIAL_STATUS_START_TRIAL_AVAILABLE;
						trial_hand_to_neural_net_msg_add.trial_status_change_msg_add.new_trial_status = TRIAL_STATUS_START_TRIAL_AVAILABLE;
						trial_hand_to_neural_net_msg_add.trial_status_change_msg_add.new_robot_target_position_idx = 0;
						if (!write_to_trial_hand_2_neural_net_msg_buffer(msgs_trial_hand_2_neural_net, current_time, TRIAL_HAND_2_NEURAL_NET_MSG_TRIAL_STATUS_CHANGED, trial_hand_to_neural_net_msg_add))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleTrialDurHand2TrialHandMsgss", "handle_trial_dur_handler_to_trial_handler_msg", "write_to_trial_hand_2_neural_net_msg_buffer()");
						trial_hand_to_spike_gen_msg_add.trial_status_change_msg_add.new_trial_status = TRIAL_STATUS_START_TRIAL_AVAILABLE;
						trial_hand_to_spike_gen_msg_add.trial_status_change_msg_add.new_robot_target_position_idx = 0;
						if (!write_to_trial_hand_2_spike_gen_msg_buffer(msgs_trial_hand_2_spike_gen, current_time, TRIAL_HAND_2_SPIKE_GEN_MSG_TRIAL_STATUS_CHANGED, trial_hand_to_spike_gen_msg_add))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleTrialDurHand2TrialHandMsgss", "handle_trial_dur_handler_to_trial_handler_msg", "write_to_trial_hand_2_neural_net_msg_buffer()");
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
