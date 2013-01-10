#include "HandleMovObjHand2TrialHandMsgs.h"


#define PUNISHMENT_SCALER	20.0

bool handle_mov_obj_handler_to_trial_handler_msg(TrialStatus *trial_status, TimeStamp current_time, MovObjHand2TrialHandMsg *msgs_mov_obj_hand_2_trial_hand, TrialHand2TrialDurHandMsg *msgs_trial_hand_2_trial_dur_hand, TrialHand2ExpEnviHandMsg *msgs_trial_hand_2_exp_envi_hand, TrialHand2MovObjHandMsg *msgs_trial_hand_2_mov_obj_hand,TrialHand2NeuralNetMsg *msgs_trial_hand_2_neural_net, TrialHand2SpikeGenMsg *msgs_trial_hand_2_spike_gen, TrialHandParadigmRobotReach *paradigm, ClassifiedTrialHistory* classified_history)
{
	MovObjHand2TrialHandMsgItem msg_item;
	char str_mov_obj_msg[MOV_OBJ_HAND_2_TRIAL_HAND_MSG_STRING_LENGTH];
	char str_status[TRIAL_STATUS_MAX_STRING_LENGTH];
	TrialHand2NeuralNetMsgAdditional trial_hand_to_neural_net_msg_add;
	TrialHand2SpikeGenMsgAdditional trial_hand_to_spike_gen_msg_add;
	TrialHand2MovObjHandMsgAdditional trial_hand_2_mov_obj_hand_add;
	double reward;
	while (get_next_mov_obj_hand_2_trial_hand_msg_buffer_item(msgs_mov_obj_hand_2_trial_hand, &msg_item))
	{
		get_mov_obj_hand_2_trial_hand_msg_type_string(msg_item.msg_type, str_mov_obj_msg);
		print_message(INFO_MSG ,"TrialHandler", "HandleMovObjHand2TrialHandMsgs", "handle_mov_obj_handler_to_trial_handler_msg", str_mov_obj_msg);
		switch (msg_item.msg_type)
		{
			case MOV_OBJ_HAND_2_TRIAL_HAND_MSG_REWARD_REQUEST:	// Mov Obj send this out whether when it reaches target or threshold depending on its programming
				switch (*trial_status)
				{
					case TRIAL_STATUS_TRIALS_DISABLED:
						break;   // do nothing
					case TRIAL_STATUS_IN_TRIAL:
						if (current_time - classified_history->all_trials->history[classified_history->all_trials->buff_write_idx].trial_start_time < 1000000000)
							reward = 0;
						else
							reward = ((double)(current_time - classified_history->all_trials->history[classified_history->all_trials->buff_write_idx].trial_start_time-1000000000)) / ((double)paradigm->max_trial_length); 

						classified_history->all_trials->history[classified_history->all_trials->buff_write_idx].reward_magnitude = reward;
						classified_history->trial_types[paradigm->selected_robot_start_position_idx][paradigm->selected_robot_target_position_idx]->history[classified_history->trial_types[paradigm->selected_robot_start_position_idx][paradigm->selected_robot_target_position_idx]->buff_write_idx].reward_magnitude = reward;
						printf ("reward: %.8f\n", reward);
						classified_history->all_trials->history[classified_history->all_trials->buff_write_idx].trial_end_time = current_time;
						classified_history->trial_types[paradigm->selected_robot_start_position_idx][paradigm->selected_robot_target_position_idx]->history[classified_history->trial_types[paradigm->selected_robot_start_position_idx][paradigm->selected_robot_target_position_idx]->buff_write_idx].trial_end_time = current_time;

						reward = get_abs_mean_of_reward_of_previous_trials(classified_history->trial_types[paradigm->selected_robot_start_position_idx][paradigm->selected_robot_target_position_idx], 4);
						reward = ((reward * 4.0) + fabs(classified_history->all_trials->history[classified_history->all_trials->buff_write_idx].reward_magnitude))/5.0;   // get mean of last 5 trials including this trial
						trial_hand_to_neural_net_msg_add.reward = reward;
						printf ("reward --- : %.8f\n", trial_hand_to_neural_net_msg_add.reward);
						if (!write_to_trial_hand_2_neural_net_msg_buffer(msgs_trial_hand_2_neural_net, current_time, TRIAL_HAND_2_NEURAL_NET_MSG_PUNISHMENT_GIVEN, trial_hand_to_neural_net_msg_add))  // to tell unsuccesful trial
							return print_message(ERROR_MSG ,"TrialHandler", "HandleMovObjHand2TrialHandMsgs", "handle_mov_obj_handler_to_trial_handler_msg", "write_to_trial_hand_2_neural_net_msg_buffer()");

						
						if (!write_to_trial_hand_2_trial_dur_hand_msg_buffer(msgs_trial_hand_2_trial_dur_hand, current_time, TRIAL_HAND_2_TRIAL_DUR_HAND_MSG_DISABLE_DURATION_HANDLING, 0))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleMovObjHand2TrialHandMsgs", "handle_mov_obj_handler_to_trial_handler_msg", "write_to_trial_hand_2_trial_dur_hand_msg_buffer()");
						if (!write_to_trial_hand_2_exp_envi_hand_msg_buffer(msgs_trial_hand_2_exp_envi_hand, current_time, TRIAL_HAND_2_EXP_ENVI_HAND_MSG_RELEASE_REWARD, 0))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleMovObjHand2TrialHandMsgs", "handle_mov_obj_handler_to_trial_handler_msg", "write_to_trial_hand_2_exp_envi_hand_msg_buffer()");

						break;  
					case TRIAL_STATUS_IN_REFRACTORY:
						break;   // do nothing
					case TRIAL_STATUS_START_TRIAL_AVAILABLE:	
						break;	// do nothing
					default:
						print_message(BUG_MSG ,"TrialHandler", "HandleMovObjHand2TrialHandMsgs", "handle_mov_obj_handler_to_trial_handler_msg", str_mov_obj_msg);
						get_trial_status_type_string(*trial_status, str_status);   
						return print_message(BUG_MSG ,"TrialHandler", "HandleMovObjHand2TrialHandMsgs", "handle_mov_obj_handler_to_trial_handler_msg", str_status);
				}
				break;
			case MOV_OBJ_HAND_2_TRIAL_HAND_MSG_PUNISHMENT_REQUEST:	
				switch (*trial_status)
				{
					case TRIAL_STATUS_TRIALS_DISABLED:
						break;   // do nothing
					case TRIAL_STATUS_IN_TRIAL:

						reward = -(msg_item.additional_data / PUNISHMENT_SCALER);
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

						if (!write_to_trial_hand_2_trial_dur_hand_msg_buffer(msgs_trial_hand_2_trial_dur_hand, current_time, TRIAL_HAND_2_TRIAL_DUR_HAND_MSG_DISABLE_DURATION_HANDLING, 0))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleMovObjHand2TrialHandMsgs", "handle_mov_obj_handler_to_trial_handler_msg", "write_to_trial_hand_2_trial_dur_hand_msg_buffer()");

						if (!write_to_trial_hand_2_exp_envi_hand_msg_buffer(msgs_trial_hand_2_exp_envi_hand, current_time, TRIAL_HAND_2_EXP_ENVI_HAND_MSG_RELEASE_PUNISHMENT, 0))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleMovObjHand2TrialHandMsgs", "handle_mov_obj_handler_to_trial_handler_msg", "write_to_trial_hand_2_exp_envi_hand_msg_buffer()");

						break;  
					case TRIAL_STATUS_IN_REFRACTORY:
						break;   // do nothing
					case TRIAL_STATUS_START_TRIAL_AVAILABLE:	
						break;	// do nothing
					default:
						print_message(BUG_MSG ,"TrialHandler", "HandleMovObjHand2TrialHandMsgs", "handle_mov_obj_handler_to_trial_handler_msg", str_mov_obj_msg);
						get_trial_status_type_string(*trial_status, str_status);   
						return print_message(BUG_MSG ,"TrialHandler", "HandleMovObjHand2TrialHandMsgs", "handle_mov_obj_handler_to_trial_handler_msg", str_status);
				}
				break;
			case MOV_OBJ_HAND_2_TRIAL_HAND_MSG_END_TRIAL_REQUEST:     // mov obj handler sends this after it stayed at target enough	
				switch (*trial_status)
				{
					case TRIAL_STATUS_TRIALS_DISABLED:
						break;   // do nothing
					case TRIAL_STATUS_IN_TRIAL:
						*trial_status = TRIAL_STATUS_IN_REFRACTORY;

						if (classified_history->all_trials->buff_write_idx == classified_history->all_trials->buffer_size)
							classified_history->all_trials->buff_write_idx = 0;
						else
							classified_history->all_trials->buff_write_idx++;

						if (classified_history->trial_types[paradigm->selected_robot_start_position_idx][paradigm->selected_robot_target_position_idx]->buff_write_idx == classified_history->trial_types[paradigm->selected_robot_start_position_idx][paradigm->selected_robot_target_position_idx]->buffer_size)
							classified_history->trial_types[paradigm->selected_robot_start_position_idx][paradigm->selected_robot_target_position_idx]->buff_write_idx = 0;
						else
							classified_history->trial_types[paradigm->selected_robot_start_position_idx][paradigm->selected_robot_target_position_idx]->buff_write_idx++;

						paradigm->selected_robot_start_position_idx = (unsigned int)(paradigm->num_of_robot_start_positions * get_rand_number());   ///  Bunu trial bittiginde yap.
						
						if (!write_to_trial_hand_2_trial_dur_hand_msg_buffer(msgs_trial_hand_2_trial_dur_hand, current_time, TRIAL_HAND_2_TRIAL_DUR_HAND_MSG_DISABLE_DURATION_HANDLING, 0))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleTrialDurHand2TrialHandMsgss", "handle_trial_dur_handler_to_trial_handler_msg", "write_to_trial_hand_2_trial_dur_hand_msg_buffer()");
						if (!write_to_trial_hand_2_trial_dur_hand_msg_buffer(msgs_trial_hand_2_trial_dur_hand, current_time, TRIAL_HAND_2_TRIAL_DUR_HAND_MSG_ENABLE_DURATION_HANDLING, current_time + paradigm->trial_refractory))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleTrialDurHand2TrialHandMsgss", "handle_trial_dur_handler_to_trial_handler_msg", "write_to_trial_hand_2_trial_dur_hand_msg_buffer()");
						if (!write_to_trial_hand_2_exp_envi_hand_msg_buffer(msgs_trial_hand_2_exp_envi_hand, current_time, TRIAL_HAND_2_EXP_ENVI_HAND_MSG_END_TRIAL, 0))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleTrialDurHand2TrialHandMsgss", "handle_trial_dur_handler_to_trial_handler_msg", "write_to_trial_hand_2_exp_envi_hand_msg_buffer()");

						trial_hand_2_mov_obj_hand_add.robot_start_position_idx = paradigm->selected_robot_start_position_idx;
						if (!write_to_trial_hand_2_mov_obj_hand_msg_buffer(msgs_trial_hand_2_mov_obj_hand, current_time, TRIAL_HAND_2_MOV_OBJ_HAND_MSG_END_TRIAL, trial_hand_2_mov_obj_hand_add))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleTrialDurHand2TrialHandMsgss", "handle_trial_dur_handler_to_trial_handler_msg", "write_to_trial_hand_2_mov_obj_hand_msg_buffer()");
						trial_hand_to_neural_net_msg_add.trial_status_change_msg_add.new_trial_status = TRIAL_STATUS_IN_REFRACTORY;
						trial_hand_to_neural_net_msg_add.trial_status_change_msg_add.new_robot_start_position_idx = paradigm->selected_robot_start_position_idx;
						if (!write_to_trial_hand_2_neural_net_msg_buffer(msgs_trial_hand_2_neural_net, current_time, TRIAL_HAND_2_NEURAL_NET_MSG_TRIAL_STATUS_CHANGED, trial_hand_to_neural_net_msg_add))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleMovObjHand2TrialHandMsgs", "handle_mov_obj_handler_to_trial_handler_msg", "write_to_trial_hand_2_neural_net_msg_buffer()");
						trial_hand_to_spike_gen_msg_add.trial_status_change_msg_add.new_trial_status = TRIAL_STATUS_IN_REFRACTORY;
						trial_hand_to_spike_gen_msg_add.trial_status_change_msg_add.new_robot_start_position_idx = paradigm->selected_robot_start_position_idx;
						if (!write_to_trial_hand_2_spike_gen_msg_buffer(msgs_trial_hand_2_spike_gen, current_time, TRIAL_HAND_2_SPIKE_GEN_MSG_TRIAL_STATUS_CHANGED, trial_hand_to_spike_gen_msg_add))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleMovObjHand2TrialHandMsgs", "handle_mov_obj_handler_to_trial_handler_msg", "write_to_trial_hand_2_spike_gen_msg_buffer()");
						break;  
					case TRIAL_STATUS_IN_REFRACTORY:
						break;   // do nothing
					case TRIAL_STATUS_START_TRIAL_AVAILABLE:	
						break;	// do nothing
					default:
						print_message(BUG_MSG ,"TrialHandler", "HandleMovObjHand2TrialHandMsgs", "handle_mov_obj_handler_to_trial_handler_msg", str_mov_obj_msg);
						get_trial_status_type_string(*trial_status, str_status);   
						return print_message(BUG_MSG ,"TrialHandler", "HandleMovObjHand2TrialHandMsgs", "handle_mov_obj_handler_to_trial_handler_msg", str_status);
				}
				break;
			case MOV_OBJ_HAND_2_TRIAL_HAND_MSG_MOV_OBJ_CONTROL_ENABLED:     // mov obj handler sends this after it stayed at start point enough	
				switch (*trial_status)
				{
					case TRIAL_STATUS_TRIALS_DISABLED:
						break;   // do nothing
					case TRIAL_STATUS_IN_TRIAL:
						trial_hand_to_neural_net_msg_add.dummy = 0;
						if (!write_to_trial_hand_2_neural_net_msg_buffer(msgs_trial_hand_2_neural_net, current_time, TRIAL_HAND_2_NEURAL_NET_MSG_TRIAL_START, trial_hand_to_neural_net_msg_add))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleExpEnviHand2TrialHandMsgs", "handle_exp_envi_handler_to_trial_handler_msg", "write_to_trial_hand_2_neural_net_msg_buffer()");
						break;  
					case TRIAL_STATUS_IN_REFRACTORY:
						break;   // do nothing
					case TRIAL_STATUS_START_TRIAL_AVAILABLE:	
						break;	// do nothing
					default:
						print_message(BUG_MSG ,"TrialHandler", "HandleMovObjHand2TrialHandMsgs", "handle_mov_obj_handler_to_trial_handler_msg", str_mov_obj_msg);
						get_trial_status_type_string(*trial_status, str_status);   
						return print_message(BUG_MSG ,"TrialHandler", "HandleMovObjHand2TrialHandMsgs", "handle_mov_obj_handler_to_trial_handler_msg", str_status);
				}
				break;


			default:
				return print_message(BUG_MSG ,"TrialHandler", "HandleMovObjHand2TrialHandMsgs", "handle_mov_obj_handler_to_trial_handler_msg", str_mov_obj_msg);	
		}
	}
	return TRUE;
}
