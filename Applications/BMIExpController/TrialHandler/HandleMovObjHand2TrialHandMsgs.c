#include "HandleMovObjHand2TrialHandMsgs.h"


bool handle_mov_obj_handler_to_trial_handler_msg(TrialStatus *trial_status, TimeStamp current_time, MovObjHand2TrialHandMsg *msgs_mov_obj_hand_2_trial_hand, TrialHand2TrialDurHandMsg *msgs_trial_hand_2_trial_dur_hand, TrialHand2ExpEnviHandMsg *msgs_trial_hand_2_exp_envi_hand, TrialHand2MovObjHandMsg *msgs_trial_hand_2_mov_obj_hand,TrialHand2NeuralNetMsg *msgs_trial_hand_2_neural_net, TrialHand2SpikeGenMsg *msgs_trial_hand_2_spike_gen, TrialHandParadigmRobotReach *paradigm, ClassifiedTrialHistory* classified_history)
{
	MovObjHand2TrialHandMsgItem msg_item;
	char str_mov_obj_msg[MOV_OBJ_HAND_2_TRIAL_HAND_MSG_STRING_LENGTH];
	char str_status[TRIAL_STATUS_MAX_STRING_LENGTH];
	TrialHand2NeuralNetMsgAdditional trial_hand_to_neural_net_msg_add;
	TrialHand2SpikeGenMsgAdditional trial_hand_to_spike_gen_msg_add;
	TrialHand2MovObjHandMsgAdditional trial_hand_2_mov_obj_hand_add;
	double reward;
	TimeStamp prev_trial_length;
	double prev_remained_distance_to_target, remained_distance_to_target, travel_distance;
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
						remained_distance_to_target = msg_item.additional_data;
						classified_history->all_trials->history[classified_history->all_trials->buff_write_idx].trial_end_time = current_time;
						classified_history->all_trials->history[classified_history->all_trials->buff_write_idx].trial_length = current_time - classified_history->all_trials->history[classified_history->all_trials->buff_write_idx].trial_start_time ;
						classified_history->all_trials->history[classified_history->all_trials->buff_write_idx].remained_distance_to_target = remained_distance_to_target;

						classified_history->trial_types[paradigm->selected_robot_start_position_idx][paradigm->selected_robot_target_position_idx]->history[classified_history->trial_types[paradigm->selected_robot_start_position_idx][paradigm->selected_robot_target_position_idx]->buff_write_idx].trial_end_time = current_time;
						classified_history->trial_types[paradigm->selected_robot_start_position_idx][paradigm->selected_robot_target_position_idx]->history[classified_history->trial_types[paradigm->selected_robot_start_position_idx][paradigm->selected_robot_target_position_idx]->buff_write_idx].trial_length = current_time - classified_history->trial_types[paradigm->selected_robot_start_position_idx][paradigm->selected_robot_target_position_idx]->history[classified_history->trial_types[paradigm->selected_robot_start_position_idx][paradigm->selected_robot_target_position_idx]->buff_write_idx].trial_start_time;
						classified_history->trial_types[paradigm->selected_robot_start_position_idx][paradigm->selected_robot_target_position_idx]->history[classified_history->trial_types[paradigm->selected_robot_start_position_idx][paradigm->selected_robot_target_position_idx]->buff_write_idx].remained_distance_to_target = remained_distance_to_target;

						prev_remained_distance_to_target = get_previous_trial_type_remained_distance_to_target(classified_history, paradigm->selected_robot_start_position_idx, paradigm->selected_robot_target_position_idx);
						prev_trial_length = get_previous_trial_type_trial_length(classified_history, paradigm->selected_robot_start_position_idx, paradigm->selected_robot_target_position_idx);

						// always punish for the first trial
						if (prev_trial_length < 1000000000)
						{
							if (classified_history->trial_types[paradigm->selected_robot_start_position_idx][paradigm->selected_robot_target_position_idx]->history[classified_history->trial_types[paradigm->selected_robot_start_position_idx][paradigm->selected_robot_target_position_idx]->buff_write_idx].trial_length < 1000000000)
								reward = 0;
							else
								reward = (((double)1000000000 - (double)classified_history->trial_types[paradigm->selected_robot_start_position_idx][paradigm->selected_robot_target_position_idx]->history[classified_history->trial_types[paradigm->selected_robot_start_position_idx][paradigm->selected_robot_target_position_idx]->buff_write_idx].trial_length) / 1000000000.0) /20.0;   // scale by 1 second						
						}
						else
						{
							reward = (((double)prev_trial_length - (double)classified_history->trial_types[paradigm->selected_robot_start_position_idx][paradigm->selected_robot_target_position_idx]->history[classified_history->trial_types[paradigm->selected_robot_start_position_idx][paradigm->selected_robot_target_position_idx]->buff_write_idx].trial_length) / 1000000000.0) / 20.0;   // scale by 1 second
						}

						classified_history->all_trials->history[classified_history->all_trials->buff_write_idx].reward_magnitude = reward;
						classified_history->trial_types[paradigm->selected_robot_start_position_idx][paradigm->selected_robot_target_position_idx]->history[classified_history->trial_types[paradigm->selected_robot_start_position_idx][paradigm->selected_robot_target_position_idx]->buff_write_idx].reward_magnitude = reward;


						printf ("reward --- : %.8f\n", reward);
						printf ("prev_trial_length --- : %.8f seconds\n", prev_trial_length/1000000000.0);
						printf ("trial_length --- : %.8f seconds\n", classified_history->trial_types[paradigm->selected_robot_start_position_idx][paradigm->selected_robot_target_position_idx]->history[classified_history->trial_types[paradigm->selected_robot_start_position_idx][paradigm->selected_robot_target_position_idx]->buff_write_idx].trial_length/1000000000.0);
						printf ("prev distance to target --- : %.8f\n", prev_remained_distance_to_target);
						printf ("distance to target --- : %.8f\n", classified_history->trial_types[paradigm->selected_robot_start_position_idx][paradigm->selected_robot_target_position_idx]->history[classified_history->trial_types[paradigm->selected_robot_start_position_idx][paradigm->selected_robot_target_position_idx]->buff_write_idx].remained_distance_to_target);
						printf ("initial distance to target --- : %.8f\n", classified_history->trial_types[paradigm->selected_robot_start_position_idx][paradigm->selected_robot_target_position_idx]->history[classified_history->trial_types[paradigm->selected_robot_start_position_idx][paradigm->selected_robot_target_position_idx]->buff_write_idx].initial_distance_to_target);

						trial_hand_to_neural_net_msg_add.reward = reward;
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
						remained_distance_to_target = msg_item.additional_data;
						classified_history->all_trials->history[classified_history->all_trials->buff_write_idx].trial_end_time = current_time;
						classified_history->all_trials->history[classified_history->all_trials->buff_write_idx].trial_length = current_time - classified_history->all_trials->history[classified_history->all_trials->buff_write_idx].trial_start_time ;
						classified_history->all_trials->history[classified_history->all_trials->buff_write_idx].remained_distance_to_target = remained_distance_to_target;

						classified_history->trial_types[paradigm->selected_robot_start_position_idx][paradigm->selected_robot_target_position_idx]->history[classified_history->trial_types[paradigm->selected_robot_start_position_idx][paradigm->selected_robot_target_position_idx]->buff_write_idx].trial_end_time = current_time;
						classified_history->trial_types[paradigm->selected_robot_start_position_idx][paradigm->selected_robot_target_position_idx]->history[classified_history->trial_types[paradigm->selected_robot_start_position_idx][paradigm->selected_robot_target_position_idx]->buff_write_idx].trial_length = current_time - classified_history->trial_types[paradigm->selected_robot_start_position_idx][paradigm->selected_robot_target_position_idx]->history[classified_history->trial_types[paradigm->selected_robot_start_position_idx][paradigm->selected_robot_target_position_idx]->buff_write_idx].trial_start_time;
						classified_history->trial_types[paradigm->selected_robot_start_position_idx][paradigm->selected_robot_target_position_idx]->history[classified_history->trial_types[paradigm->selected_robot_start_position_idx][paradigm->selected_robot_target_position_idx]->buff_write_idx].remained_distance_to_target = remained_distance_to_target;

						prev_remained_distance_to_target = get_previous_trial_type_remained_distance_to_target(classified_history, paradigm->selected_robot_start_position_idx, paradigm->selected_robot_target_position_idx);
						prev_trial_length = get_previous_trial_type_trial_length(classified_history, paradigm->selected_robot_start_position_idx, paradigm->selected_robot_target_position_idx);

						travel_distance = (classified_history->trial_types[paradigm->selected_robot_start_position_idx][paradigm->selected_robot_target_position_idx]->history[classified_history->trial_types[paradigm->selected_robot_start_position_idx][paradigm->selected_robot_target_position_idx]->buff_write_idx].initial_distance_to_target - remained_distance_to_target);  
						if (fabs(travel_distance) < 0.5)
							travel_distance = -0.5;
						reward = travel_distance / 10.0; // scale by 10 cm
						classified_history->all_trials->history[classified_history->all_trials->buff_write_idx].reward_magnitude = reward;
						classified_history->trial_types[paradigm->selected_robot_start_position_idx][paradigm->selected_robot_target_position_idx]->history[classified_history->trial_types[paradigm->selected_robot_start_position_idx][paradigm->selected_robot_target_position_idx]->buff_write_idx].reward_magnitude = reward;

						printf ("reward --- : %.8f\n", reward);
						printf ("prev_trial_length --- : %.8f seconds\n", prev_trial_length/1000000000.0);
						printf ("trial_length --- : %.8f seconds\n", classified_history->trial_types[paradigm->selected_robot_start_position_idx][paradigm->selected_robot_target_position_idx]->history[classified_history->trial_types[paradigm->selected_robot_start_position_idx][paradigm->selected_robot_target_position_idx]->buff_write_idx].trial_length/1000000000.0);
						printf ("prev distance to target --- : %.8f\n", prev_remained_distance_to_target);
						printf ("distance to target --- : %.8f\n", classified_history->trial_types[paradigm->selected_robot_start_position_idx][paradigm->selected_robot_target_position_idx]->history[classified_history->trial_types[paradigm->selected_robot_start_position_idx][paradigm->selected_robot_target_position_idx]->buff_write_idx].remained_distance_to_target);
						printf ("initial distance to target --- : %.8f\n", classified_history->trial_types[paradigm->selected_robot_start_position_idx][paradigm->selected_robot_target_position_idx]->history[classified_history->trial_types[paradigm->selected_robot_start_position_idx][paradigm->selected_robot_target_position_idx]->buff_write_idx].initial_distance_to_target);

						trial_hand_to_neural_net_msg_add.reward = reward;
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
						return print_message(BUG_MSG ,"TrialHandler", "HandleMovObjHand2TrialHandMsgs", "handle_mov_obj_handler_to_trial_handler_msg", str_status);
					case TRIAL_STATUS_IN_TRIAL:
						trial_hand_to_neural_net_msg_add.dummy = 0;
						if (!write_to_trial_hand_2_neural_net_msg_buffer(msgs_trial_hand_2_neural_net, current_time, TRIAL_HAND_2_NEURAL_NET_MSG_TRIAL_START, trial_hand_to_neural_net_msg_add))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleExpEnviHand2TrialHandMsgs", "handle_exp_envi_handler_to_trial_handler_msg", "write_to_trial_hand_2_neural_net_msg_buffer()");
						break;  
					case TRIAL_STATUS_IN_REFRACTORY:
						return print_message(BUG_MSG ,"TrialHandler", "HandleMovObjHand2TrialHandMsgs", "handle_mov_obj_handler_to_trial_handler_msg", str_status);
					case TRIAL_STATUS_START_TRIAL_AVAILABLE:	
						return print_message(BUG_MSG ,"TrialHandler", "HandleMovObjHand2TrialHandMsgs", "handle_mov_obj_handler_to_trial_handler_msg", str_status);
					default:
						print_message(BUG_MSG ,"TrialHandler", "HandleMovObjHand2TrialHandMsgs", "handle_mov_obj_handler_to_trial_handler_msg", str_mov_obj_msg);
						get_trial_status_type_string(*trial_status, str_status);   
						return print_message(BUG_MSG ,"TrialHandler", "HandleMovObjHand2TrialHandMsgs", "handle_mov_obj_handler_to_trial_handler_msg", str_status);
				}
				break;
			case MOV_OBJ_HAND_2_TRIAL_HAND_MSG_MOV_OBJ_INITIAL_DIST_2_TARGET:     // mov obj handler sends this when it receives a trial start msg from trial hand
				switch (*trial_status)
				{
					case TRIAL_STATUS_TRIALS_DISABLED:
						return print_message(BUG_MSG ,"TrialHandler", "HandleMovObjHand2TrialHandMsgs", "handle_mov_obj_handler_to_trial_handler_msg", str_status);
					case TRIAL_STATUS_IN_TRIAL:
						classified_history->all_trials->history[classified_history->all_trials->buff_write_idx].initial_distance_to_target = msg_item.additional_data;
						classified_history->trial_types[paradigm->selected_robot_start_position_idx][paradigm->selected_robot_target_position_idx]->history[classified_history->trial_types[paradigm->selected_robot_start_position_idx][paradigm->selected_robot_target_position_idx]->buff_write_idx].initial_distance_to_target = msg_item.additional_data;
						break;  
					case TRIAL_STATUS_IN_REFRACTORY:
						return print_message(BUG_MSG ,"TrialHandler", "HandleMovObjHand2TrialHandMsgs", "handle_mov_obj_handler_to_trial_handler_msg", str_status);
					case TRIAL_STATUS_START_TRIAL_AVAILABLE:	
						return print_message(BUG_MSG ,"TrialHandler", "HandleMovObjHand2TrialHandMsgs", "handle_mov_obj_handler_to_trial_handler_msg", str_status);
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
