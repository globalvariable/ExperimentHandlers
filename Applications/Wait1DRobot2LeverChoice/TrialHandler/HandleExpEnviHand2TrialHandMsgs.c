#include "HandleExpEnviHand2TrialHandMsgs.h"


bool handle_exp_envi_handler_to_trial_handler_msg(TrialStatus *trial_status, TimeStamp current_time, ExpEnviHand2TrialHandMsg *msgs_exp_envi_hand_2_trial_hand, TrialHand2TrialDurHandMsg *msgs_trial_hand_2_trial_dur_hand, TrialHand2ExpEnviHandMsg *msgs_trial_hand_2_exp_envi_hand, TrialHand2MovObjHandMsg *msgs_trial_hand_2_mov_obj_hand, TrialHandParadigmRobotReach *paradigm, ClassifiedTrialHistory* classified_history, TrialHand2GuiMsg *msgs_trial_hand_2_gui, TrialStatusHistory *trial_status_history)
{
	ExpEnviHand2TrialHandMsgItem msg_item;
	char str_exp_envi_msg[EXP_ENVI_HAND_2_TRIAL_HAND_MSG_STRING_LENGTH];
	char str_status[TRIAL_STATUS_MAX_STRING_LENGTH];
	TrialHand2MovObjHandMsgAdditional trial_hand_to_mov_obj_hand_msg_add;
	TimeStamp trial_length, refractory, get_ready_duration;
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
					case TRIAL_STATUS_GET_READY_TO_START:	
						break;   // do nothing
					case TRIAL_STATUS_START_TRIAL_AVAILABLE:	
						*trial_status = TRIAL_STATUS_GET_READY_TO_START;
						paradigm->current_trial_data.trial_start_time = current_time;
						if (paradigm->current_trial_data.auto_target_select_mode_on)
							paradigm->current_trial_data.robot_target_position_idx = (unsigned int)(paradigm->num_of_robot_target_positions * get_rand_number());   ///  Bunu trial bittiginde yap.
						else
							paradigm->current_trial_data.robot_target_position_idx = paradigm->current_trial_data.gui_selected_target_position_idx;

						paradigm->current_trial_data.target_led_component_list_idx = paradigm->current_trial_data.robot_target_position_idx;

						get_ready_duration = current_time + paradigm->min_get_ready_to_trial_start_length + ((TimeStamp)(get_rand_number() * (double)paradigm->max_extra_get_ready_to_trial_start_length));
						if (!write_to_trial_hand_2_trial_dur_hand_msg_buffer(msgs_trial_hand_2_trial_dur_hand, current_time, TRIAL_HAND_2_TRIAL_DUR_HAND_MSG_ENABLE_DURATION_HANDLING, get_ready_duration))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleExpEnviHand2TrialHandMsgs", "handle_exp_envi_handler_to_trial_handler_msg", "write_to_trial_hand_2_trial_dur_hand_msg_buffer()");
						if (!write_to_trial_hand_2_exp_envi_hand_msg_buffer(msgs_trial_hand_2_exp_envi_hand, current_time, TRIAL_HAND_2_EXP_ENVI_HAND_MSG_GET_READY_TO_TRIAL_START, 0))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleExpEnviHand2TrialHandMsgs", "handle_exp_envi_handler_to_trial_handler_msg", "write_to_trial_hand_2_exp_envi_hand_msg_buffer()");
						if (!write_to_trial_hand_2_gui_msg_buffer(msgs_trial_hand_2_gui, current_time, TRIAL_HAND_2_GUI_MSG_TRIAL_STATUS_CHANGE, TRIAL_STATUS_GET_READY_TO_START))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", "write_to_trial_hand_2_gui_msg_buffer()");
						if (! write_to_trial_status_history(trial_status_history, current_time, TRIAL_STATUS_GET_READY_TO_START))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", "write_to_trial_status_history()");
						break;
					default:
						print_message(BUG_MSG ,"TrialHandler", "HandleExpEnviHand2TrialHandMsgs", "handle_exp_envi_handler_to_trial_handler_msg", str_exp_envi_msg);
						get_trial_status_type_string(*trial_status, str_status);   
						return print_message(BUG_MSG ,"TrialHandler", "HandleExpEnviHand2TrialHandMsgs", "handle_exp_envi_handler_to_trial_handler_msg", str_status);
				}
				break;
			case EXP_ENVI_HAND_2_TRIAL_HAND_MSG_REWARD_REQUEST:	
				switch (*trial_status)
				{
					case TRIAL_STATUS_TRIALS_DISABLED:
						break;   // do nothing
					case TRIAL_STATUS_IN_TRIAL:
						*trial_status = TRIAL_STATUS_IN_REFRACTORY;

						trial_length = current_time - paradigm->current_trial_data.trial_start_time;
						paradigm->current_trial_data.trial_end_time = current_time;
						paradigm->current_trial_data.trial_length = trial_length;
						paradigm->current_trial_data.binary_reward = TRUE;
						paradigm->current_trial_data.trial_incomplete = FALSE;

						if (! write_trial_data_to_classified_trial_history(classified_history, &(paradigm->current_trial_data)))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleExpEnviHand2TrialHandMsgs", "handle_exp_envi_handler_to_trial_handler_msg", "write_trial_data_to_classified_trial_history()");

						paradigm->current_trial_data.trial_start_time = 0;
						paradigm->current_trial_data.trial_end_time = 0;
						paradigm->current_trial_data.trial_length = 0;

						paradigm->current_trial_data.robot_start_position_idx = (unsigned int)(paradigm->num_of_robot_start_positions * get_rand_number());   ///  Bunu trial bittiginde yap.
						
						if (!write_to_trial_hand_2_trial_dur_hand_msg_buffer(msgs_trial_hand_2_trial_dur_hand, current_time, TRIAL_HAND_2_TRIAL_DUR_HAND_MSG_DISABLE_DURATION_HANDLING, 0))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleExpEnviHand2TrialHandMsgss", "handle_exp_envi_handler_to_trial_handler_msg", "write_to_trial_hand_2_trial_dur_hand_msg_buffer()");
						refractory = current_time + paradigm->min_trial_refractory + ((TimeStamp)(get_rand_number() * (double)paradigm->max_extra_trial_refractory));
						if (!write_to_trial_hand_2_trial_dur_hand_msg_buffer(msgs_trial_hand_2_trial_dur_hand, current_time, TRIAL_HAND_2_TRIAL_DUR_HAND_MSG_ENABLE_DURATION_HANDLING, refractory))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleExpEnviHand2TrialHandMsgss", "handle_exp_envi_handler_to_trial_handler_msg", "write_to_trial_hand_2_trial_dur_hand_msg_buffer()");
						if (!write_to_trial_hand_2_exp_envi_hand_msg_buffer(msgs_trial_hand_2_exp_envi_hand, current_time, TRIAL_HAND_2_EXP_ENVI_HAND_MSG_RELEASE_REWARD, 0))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleExpEnviHand2TrialHandMsgs", "handle_exp_envi_handler_to_trial_handler_msg", "write_to_trial_hand_2_exp_envi_hand_msg_buffer()");
						if (!write_to_trial_hand_2_exp_envi_hand_msg_buffer(msgs_trial_hand_2_exp_envi_hand, current_time, TRIAL_HAND_2_EXP_ENVI_HAND_MSG_END_TRIAL, 0))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleExpEnviHand2TrialHandMsgss", "handle_exp_envi_handler_to_trial_handler_msg", "write_to_trial_hand_2_exp_envi_hand_msg_buffer()");
						trial_hand_to_mov_obj_hand_msg_add.robot_start_position_idx = paradigm->current_trial_data.robot_start_position_idx;
						if (!write_to_trial_hand_2_mov_obj_hand_msg_buffer(msgs_trial_hand_2_mov_obj_hand, current_time, TRIAL_HAND_2_MOV_OBJ_HAND_MSG_END_TRIAL, trial_hand_to_mov_obj_hand_msg_add))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleTrialDurHand2TrialHandMsgss", "handle_trial_dur_handler_to_trial_handler_msg", "write_to_trial_hand_2_mov_obj_hand_msg_buffer()");
						if (!write_to_trial_hand_2_gui_msg_buffer(msgs_trial_hand_2_gui, current_time, TRIAL_HAND_2_GUI_MSG_TRIAL_STATUS_CHANGE, TRIAL_STATUS_IN_REFRACTORY))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleExpEnviHand2TrialHandMsgs", "handle_exp_envi_handler_to_trial_handler_msg", "write_to_trial_hand_2_spike_gen_msg_buffer()");
						if (! write_to_trial_status_history(trial_status_history, current_time, TRIAL_STATUS_IN_REFRACTORY))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleExpEnviHand2TrialHandMsgs", "handle_exp_envi_handler_to_trial_handler_msg", "write_to_trial_status_history()");
						break;  
					case TRIAL_STATUS_IN_REFRACTORY:
						break;   // do nothing
					case TRIAL_STATUS_START_TRIAL_AVAILABLE:	
						break;   // do nothing
					default:
						print_message(BUG_MSG ,"TrialHandler", "HandleExpEnviHand2TrialHandMsgs", "handle_exp_envi_handler_to_trial_handler_msg", str_exp_envi_msg);
						get_trial_status_type_string(*trial_status, str_status);   
						return print_message(BUG_MSG ,"TrialHandler", "HandleExpEnviHand2TrialHandMsgs", "handle_exp_envi_handler_to_trial_handler_msg", str_status);
				}
				break;
			case EXP_ENVI_HAND_2_TRIAL_HAND_MSG_PUNISHMENT_REQUEST:	
				switch (*trial_status)
				{
					case TRIAL_STATUS_TRIALS_DISABLED:
						break;   // do nothing
					case TRIAL_STATUS_IN_TRIAL:
						*trial_status = TRIAL_STATUS_IN_REFRACTORY;

						trial_length = current_time - paradigm->current_trial_data.trial_start_time;
						paradigm->current_trial_data.trial_end_time = current_time;
						paradigm->current_trial_data.trial_length = trial_length;
						paradigm->current_trial_data.binary_reward = FALSE;
						paradigm->current_trial_data.trial_incomplete = FALSE;

						if (! write_trial_data_to_classified_trial_history(classified_history, &(paradigm->current_trial_data)))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleExpEnviHand2TrialHandMsgs", "handle_exp_envi_handler_to_trial_handler_msg", "write_trial_data_to_classified_trial_history()");

						paradigm->current_trial_data.trial_start_time = 0;
						paradigm->current_trial_data.trial_end_time = 0;
						paradigm->current_trial_data.trial_length = 0;

						paradigm->current_trial_data.robot_start_position_idx = (unsigned int)(paradigm->num_of_robot_start_positions * get_rand_number());   ///  Bunu trial bittiginde yap.
						
						if (!write_to_trial_hand_2_trial_dur_hand_msg_buffer(msgs_trial_hand_2_trial_dur_hand, current_time, TRIAL_HAND_2_TRIAL_DUR_HAND_MSG_DISABLE_DURATION_HANDLING, 0))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleExpEnviHand2TrialHandMsgs", "handle_exp_envi_handler_to_trial_handler_msg", "write_to_trial_hand_2_trial_dur_hand_msg_buffer()");
						refractory = current_time + paradigm->min_trial_refractory + ((TimeStamp)(get_rand_number() * (double)paradigm->max_extra_trial_refractory));
						if (!write_to_trial_hand_2_trial_dur_hand_msg_buffer(msgs_trial_hand_2_trial_dur_hand, current_time, TRIAL_HAND_2_TRIAL_DUR_HAND_MSG_ENABLE_DURATION_HANDLING, refractory))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleExpEnviHand2TrialHandMsgs", "handle_exp_envi_handler_to_trial_handler_msg", "write_to_trial_hand_2_trial_dur_hand_msg_buffer()");
						if (!write_to_trial_hand_2_exp_envi_hand_msg_buffer(msgs_trial_hand_2_exp_envi_hand, current_time, TRIAL_HAND_2_EXP_ENVI_HAND_MSG_RELEASE_PUNISHMENT, 0))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleExpEnviHand2TrialHandMsgs", "handle_exp_envi_handler_to_trial_handler_msg", "write_to_trial_hand_2_exp_envi_hand_msg_buffer()");
						if (!write_to_trial_hand_2_exp_envi_hand_msg_buffer(msgs_trial_hand_2_exp_envi_hand, current_time, TRIAL_HAND_2_EXP_ENVI_HAND_MSG_END_TRIAL, 0))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleExpEnviHand2TrialHandMsgss", "handle_exp_envi_handler_to_trial_handler_msg", "write_to_trial_hand_2_exp_envi_hand_msg_buffer()");
						trial_hand_to_mov_obj_hand_msg_add.robot_start_position_idx = paradigm->current_trial_data.robot_start_position_idx;
						if (!write_to_trial_hand_2_mov_obj_hand_msg_buffer(msgs_trial_hand_2_mov_obj_hand, current_time, TRIAL_HAND_2_MOV_OBJ_HAND_MSG_END_TRIAL, trial_hand_to_mov_obj_hand_msg_add))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleTrialDurHand2TrialHandMsgss", "handle_trial_dur_handler_to_trial_handler_msg", "write_to_trial_hand_2_mov_obj_hand_msg_buffer()");
						if (!write_to_trial_hand_2_gui_msg_buffer(msgs_trial_hand_2_gui, current_time, TRIAL_HAND_2_GUI_MSG_TRIAL_STATUS_CHANGE, TRIAL_STATUS_IN_REFRACTORY))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleExpEnviHand2TrialHandMsgs", "handle_exp_envi_handler_to_trial_handler_msg", "write_to_trial_hand_2_spike_gen_msg_buffer()");
						if (! write_to_trial_status_history(trial_status_history, current_time, TRIAL_STATUS_IN_REFRACTORY))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleExpEnviHand2TrialHandMsgs", "handle_exp_envi_handler_to_trial_handler_msg", "write_to_trial_status_history()");
						break;  
					case TRIAL_STATUS_IN_REFRACTORY:
						break;   // do nothing
					case TRIAL_STATUS_START_TRIAL_AVAILABLE:	
						break;   // do nothing
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
