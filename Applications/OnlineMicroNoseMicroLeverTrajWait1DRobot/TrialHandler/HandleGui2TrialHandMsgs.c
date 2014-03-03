#include "HandleGui2TrialHandMsgs.h"




bool handle_gui_to_trial_handler_msg(TrialStatus *trial_status, TimeStamp current_time, Gui2TrialHandMsg *msgs_gui_2_trial_hand, TrialHand2TrialDurHandMsg* msgs_trial_hand_2_trial_dur_hand, TrialHand2ExpEnviHandMsg *msgs_trial_hand_2_exp_envi_hand, TrialHand2MovObjHandMsg *msgs_trial_hand_2_mov_obj_hand, TrialHandParadigmRobotReach *paradigm, ClassifiedTrialHistory* classified_history, TrialHand2GuiMsg *msgs_trial_hand_2_gui, TrialStatusHistory *trial_status_history, TrialHand2NeuRecHandMsg *msgs_trial_hand_2_neu_rec_hand)
{
	Gui2TrialHandMsgItem msg_item;
	char str_gui_msg[GUI_2_TRIAL_HAND_MSG_STRING_LENGTH];
	char str_status[TRIAL_STATUS_MAX_STRING_LENGTH];
	TrialHand2MovObjHandMsgAdditional trial_hand_2_mov_obj_hand_add;
	unsigned int recording_number;	
	TimeStamp refractory, trial_length;
	TrialHand2MovObjHandMsgAdditional  trial_hand_to_mov_obj_hand_msg_add;

	while (get_next_gui_2_trial_hand_msg_buffer_item(msgs_gui_2_trial_hand, &msg_item))
	{
		get_gui_2_trial_hand_msg_type_string(msg_item.msg_type, str_gui_msg);
		print_message(INFO_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", str_gui_msg);
		switch (msg_item.msg_type)
		{
			case GUI_2_TRIAL_HAND_MSG_ENABLE_TRIAL_HANDLING:	
				switch (*trial_status)
				{
					case TRIAL_STATUS_TRIALS_DISABLED:
						*trial_status = TRIAL_STATUS_IN_REFRACTORY;
						if (!write_to_trial_hand_2_trial_dur_hand_msg_buffer(msgs_trial_hand_2_trial_dur_hand, current_time, TRIAL_HAND_2_TRIAL_DUR_HAND_MSG_ENABLE_DURATION_HANDLING, current_time + paradigm->min_trial_refractory))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", "write_to_trial_hand_2_trial_dur_hand_msg_buffer()");

						paradigm->current_trial_data.robot_start_position_idx = (unsigned int)(paradigm->num_of_robot_start_positions * get_rand_number());   ///  Bunu trial bittiginde yap.
						trial_hand_2_mov_obj_hand_add.robot_start_position_idx = paradigm->current_trial_data.robot_start_position_idx;
						if (!write_to_trial_hand_2_mov_obj_hand_msg_buffer(msgs_trial_hand_2_mov_obj_hand, current_time, TRIAL_HAND_2_MOV_OBJ_HAND_MSG_TRIALS_ENABLED, trial_hand_2_mov_obj_hand_add))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", "write_to_trial_hand_2_neural_net_msg_buffer()");
						if (!write_to_trial_hand_2_gui_msg_buffer(msgs_trial_hand_2_gui, current_time, TRIAL_HAND_2_GUI_MSG_TRIAL_STATUS_CHANGE, TRIAL_STATUS_IN_REFRACTORY))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", "write_to_trial_hand_2_gui_msg_buffer()");
						if (! write_to_trial_status_history(trial_status_history, current_time, TRIAL_STATUS_IN_REFRACTORY))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", "write_to_trial_status_history()");
						break;
					case TRIAL_STATUS_IN_TRIAL:
						print_message(BUG_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", str_gui_msg);
						get_trial_status_type_string(*trial_status, str_status);   
						return print_message(BUG_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", str_status);
					case TRIAL_STATUS_IN_REFRACTORY:
						print_message(BUG_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", str_gui_msg);
						get_trial_status_type_string(*trial_status, str_status);   
						return print_message(BUG_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", str_status);
					case TRIAL_STATUS_START_TRIAL_AVAILABLE:	
						print_message(BUG_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", str_gui_msg);
						get_trial_status_type_string(*trial_status, str_status);   
						return print_message(BUG_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", str_status);
					default:
						print_message(BUG_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", str_gui_msg);
						get_trial_status_type_string(*trial_status, str_status);   
						return print_message(BUG_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", str_status);
				}
				break;
			case GUI_2_TRIAL_HAND_MSG_DISABLE_TRIAL_HANDLING:	
				switch (*trial_status)
				{
					case TRIAL_STATUS_TRIALS_DISABLED:
						print_message(BUG_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", str_gui_msg);
						get_trial_status_type_string(*trial_status, str_status);   
						return print_message(BUG_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", str_status);
					case TRIAL_STATUS_IN_TRIAL:
						*trial_status = TRIAL_STATUS_TRIALS_DISABLED;
						if (!write_to_trial_hand_2_trial_dur_hand_msg_buffer(msgs_trial_hand_2_trial_dur_hand, current_time, TRIAL_HAND_2_TRIAL_DUR_HAND_MSG_DISABLE_DURATION_HANDLING, 0))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", "write_to_trial_hand_2_trial_dur_hand_msg_buffer()");
						if (!write_to_trial_hand_2_exp_envi_hand_msg_buffer(msgs_trial_hand_2_exp_envi_hand, current_time, TRIAL_HAND_2_EXP_ENVI_HAND_MSG_END_TRIAL, 0))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", "write_to_trial_hand_2_exp_envi_hand_msg_buffer()");

						if (!write_to_trial_hand_2_mov_obj_hand_msg_buffer(msgs_trial_hand_2_mov_obj_hand, current_time, TRIAL_HAND_2_MOV_OBJ_HAND_MSG_END_TRIAL, trial_hand_2_mov_obj_hand_add))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", "write_to_trial_hand_2_mov_obj_hand_msg_buffer()");
						if (!write_to_trial_hand_2_gui_msg_buffer(msgs_trial_hand_2_gui, current_time, TRIAL_HAND_2_GUI_MSG_TRIAL_STATUS_CHANGE, TRIAL_STATUS_TRIALS_DISABLED))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", "write_to_trial_hand_2_gui_msg_buffer()");
						if (! write_to_trial_status_history(trial_status_history, current_time, TRIAL_STATUS_TRIALS_DISABLED))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", "write_to_trial_status_history()");
						break;
					case TRIAL_STATUS_IN_REFRACTORY:
						*trial_status = TRIAL_STATUS_TRIALS_DISABLED;
						if (!write_to_trial_hand_2_trial_dur_hand_msg_buffer(msgs_trial_hand_2_trial_dur_hand, current_time, TRIAL_HAND_2_TRIAL_DUR_HAND_MSG_DISABLE_DURATION_HANDLING, 0))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", "write_to_trial_hand_2_trial_dur_hand_msg_buffer()");
						if (!write_to_trial_hand_2_exp_envi_hand_msg_buffer(msgs_trial_hand_2_exp_envi_hand, current_time, TRIAL_HAND_2_EXP_ENVI_HAND_MSG_END_TRIAL, 0))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", "write_to_trial_hand_2_exp_envi_hand_msg_buffer()");

						if (!write_to_trial_hand_2_mov_obj_hand_msg_buffer(msgs_trial_hand_2_mov_obj_hand, current_time, TRIAL_HAND_2_MOV_OBJ_HAND_MSG_END_TRIAL, trial_hand_2_mov_obj_hand_add))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", "write_to_trial_hand_2_mov_obj_hand_msg_buffer()");
						if (!write_to_trial_hand_2_gui_msg_buffer(msgs_trial_hand_2_gui, current_time, TRIAL_HAND_2_GUI_MSG_TRIAL_STATUS_CHANGE, TRIAL_STATUS_TRIALS_DISABLED))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", "write_to_trial_hand_2_gui_msg_buffer()");
						if (! write_to_trial_status_history(trial_status_history, current_time, TRIAL_STATUS_TRIALS_DISABLED))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", "write_to_trial_status_history()");
						break;
					case TRIAL_STATUS_START_TRIAL_AVAILABLE:	
						*trial_status = TRIAL_STATUS_TRIALS_DISABLED;
						if (!write_to_trial_hand_2_trial_dur_hand_msg_buffer(msgs_trial_hand_2_trial_dur_hand, current_time, TRIAL_HAND_2_TRIAL_DUR_HAND_MSG_DISABLE_DURATION_HANDLING, 0))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", "write_to_trial_hand_2_trial_dur_hand_msg_buffer()");
						if (!write_to_trial_hand_2_exp_envi_hand_msg_buffer(msgs_trial_hand_2_exp_envi_hand, current_time, TRIAL_HAND_2_EXP_ENVI_HAND_MSG_END_TRIAL, 0))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", "write_to_trial_hand_2_exp_envi_hand_msg_buffer()");

						if (!write_to_trial_hand_2_mov_obj_hand_msg_buffer(msgs_trial_hand_2_mov_obj_hand, current_time, TRIAL_HAND_2_MOV_OBJ_HAND_MSG_END_TRIAL, trial_hand_2_mov_obj_hand_add))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", "write_to_trial_hand_2_mov_obj_hand_msg_buffer()");
						if (!write_to_trial_hand_2_gui_msg_buffer(msgs_trial_hand_2_gui, current_time, TRIAL_HAND_2_GUI_MSG_TRIAL_STATUS_CHANGE, TRIAL_STATUS_TRIALS_DISABLED))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", "write_to_trial_hand_2_gui_msg_buffer()");
						if (! write_to_trial_status_history(trial_status_history, current_time, TRIAL_STATUS_TRIALS_DISABLED))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", "write_to_trial_status_history()");
						break;
					default:
						print_message(BUG_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", str_gui_msg);
						get_trial_status_type_string(*trial_status, str_status);   
						return print_message(BUG_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", str_status);
				}
				break;
			case GUI_2_TRIAL_HAND_MSG_QUIT:	
				switch (*trial_status)
				{
					case TRIAL_STATUS_TRIALS_DISABLED:
						break;
					case TRIAL_STATUS_IN_TRIAL:
						break;
					case TRIAL_STATUS_IN_REFRACTORY:
						break;
					case TRIAL_STATUS_START_TRIAL_AVAILABLE:	
						break;
					default:
						print_message(BUG_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", str_gui_msg);
						get_trial_status_type_string(*trial_status, str_status);   
						return print_message(BUG_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", str_status);
				}
				break;
			case GUI_2_TRIAL_HAND_MSG_SELECT_TARGET:
				switch (*trial_status)
				{
					case TRIAL_STATUS_TRIALS_DISABLED:
						paradigm->current_trial_data.gui_selected_target_position_idx = msg_item.additional_data;
						break;
					case TRIAL_STATUS_IN_TRIAL:
						paradigm->current_trial_data.gui_selected_target_position_idx = msg_item.additional_data;
						break;
					case TRIAL_STATUS_IN_REFRACTORY:
						paradigm->current_trial_data.gui_selected_target_position_idx = msg_item.additional_data;
						break;
					case TRIAL_STATUS_START_TRIAL_AVAILABLE:	
						paradigm->current_trial_data.gui_selected_target_position_idx = msg_item.additional_data;
						break;
					case TRIAL_STATUS_GET_READY_TO_START:	
						paradigm->current_trial_data.gui_selected_target_position_idx = msg_item.additional_data;
						break;
					default:
						print_message(BUG_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", str_gui_msg);
						get_trial_status_type_string(*trial_status, str_status);   
						return print_message(BUG_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", str_status);
				}
				break;
			case GUI_2_TRIAL_HAND_MSG_AUTO_TARGET_SELECTION_OFF:
				switch (*trial_status)
				{
					case TRIAL_STATUS_TRIALS_DISABLED:
						paradigm->current_trial_data.auto_target_select_mode_on = FALSE;
						break;
					case TRIAL_STATUS_IN_TRIAL:
						paradigm->current_trial_data.auto_target_select_mode_on = FALSE;
						break;
					case TRIAL_STATUS_IN_REFRACTORY:
						paradigm->current_trial_data.auto_target_select_mode_on = FALSE;
						break;
					case TRIAL_STATUS_START_TRIAL_AVAILABLE:	
						paradigm->current_trial_data.auto_target_select_mode_on = FALSE;
						break;
					case TRIAL_STATUS_GET_READY_TO_START:	
						paradigm->current_trial_data.auto_target_select_mode_on = FALSE;
						break;
					default:
						print_message(BUG_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", str_gui_msg);
						get_trial_status_type_string(*trial_status, str_status);   
						return print_message(BUG_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", str_status);
				}
				break;
			case GUI_2_TRIAL_HAND_MSG_AUTO_TARGET_SELECTION_ON:
				switch (*trial_status)
				{
					case TRIAL_STATUS_TRIALS_DISABLED:
						paradigm->current_trial_data.auto_target_select_mode_on = TRUE;
						break;
					case TRIAL_STATUS_IN_TRIAL:
						paradigm->current_trial_data.auto_target_select_mode_on = TRUE;
						break;
					case TRIAL_STATUS_IN_REFRACTORY:
						paradigm->current_trial_data.auto_target_select_mode_on = TRUE;
						break;
					case TRIAL_STATUS_START_TRIAL_AVAILABLE:	
						paradigm->current_trial_data.auto_target_select_mode_on = TRUE;
						break;
					case TRIAL_STATUS_GET_READY_TO_START:	
						paradigm->current_trial_data.auto_target_select_mode_on = TRUE;
						break;
					default:
						print_message(BUG_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", str_gui_msg);
						get_trial_status_type_string(*trial_status, str_status);   
						return print_message(BUG_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", str_status);
				}
				break;
			case GUI_2_TRIAL_HAND_MSG_CATCH_TRIAL_MODE_OFF:
				switch (*trial_status)
				{
					case TRIAL_STATUS_TRIALS_DISABLED:
						paradigm->current_trial_data.catch_trial_mode_on = FALSE;
						break;
					case TRIAL_STATUS_IN_TRIAL:
						paradigm->current_trial_data.catch_trial_mode_on = FALSE;
						break;
					case TRIAL_STATUS_IN_REFRACTORY:
						paradigm->current_trial_data.catch_trial_mode_on = FALSE;
						break;
					case TRIAL_STATUS_START_TRIAL_AVAILABLE:	
						paradigm->current_trial_data.catch_trial_mode_on = FALSE;
						break;
					case TRIAL_STATUS_GET_READY_TO_START:	
						paradigm->current_trial_data.catch_trial_mode_on = FALSE;
						break;
					default:
						print_message(BUG_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", str_gui_msg);
						get_trial_status_type_string(*trial_status, str_status);   
						return print_message(BUG_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", str_status);
				}
				break;
			case GUI_2_TRIAL_HAND_MSG_CATCH_TRIAL_MODE_ON:
				switch (*trial_status)
				{
					case TRIAL_STATUS_TRIALS_DISABLED:
						paradigm->current_trial_data.catch_trial_mode_on = TRUE;
						break;
					case TRIAL_STATUS_IN_TRIAL:
						paradigm->current_trial_data.catch_trial_mode_on = TRUE;
						break;
					case TRIAL_STATUS_IN_REFRACTORY:
						paradigm->current_trial_data.catch_trial_mode_on = TRUE;
						break;
					case TRIAL_STATUS_START_TRIAL_AVAILABLE:	
						paradigm->current_trial_data.catch_trial_mode_on = TRUE;
						break;
					case TRIAL_STATUS_GET_READY_TO_START:	
						paradigm->current_trial_data.catch_trial_mode_on = TRUE;
						break;
					default:
						print_message(BUG_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", str_gui_msg);
						get_trial_status_type_string(*trial_status, str_status);   
						return print_message(BUG_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", str_status);
				}
				break;
			case GUI_2_TRIAL_HAND_MSG_BROADCAST_START_RECORDING:
				switch (*trial_status)
				{
					case TRIAL_STATUS_TRIALS_DISABLED:
						print_message(ERROR_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", "Cannot start recording when TRIAL_STATUS_TRIALS_DISABLED");
						break;
					case TRIAL_STATUS_IN_TRIAL:
						print_message(ERROR_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", "Cannot start recording when TRIAL_STATUS_IN_TRIAL");
						break;
					case TRIAL_STATUS_IN_REFRACTORY:
						recording_number = classified_history->all_trials->buff_write_idx;  // delete previous 
						if (!write_to_trial_hand_2_exp_envi_hand_msg_buffer(msgs_trial_hand_2_exp_envi_hand, current_time, TRIAL_HAND_2_EXP_ENVI_HAND_MSG_START_RECORDING, recording_number))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", "write_to_trial_hand_2_exp_envi_hand_msg_buffer()");
						trial_hand_2_mov_obj_hand_add.recording_number = recording_number;
						if (! write_to_trial_hand_2_mov_obj_hand_msg_buffer(msgs_trial_hand_2_mov_obj_hand, current_time, TRIAL_HAND_2_MOV_OBJ_HAND_MSG_START_RECORDING, trial_hand_2_mov_obj_hand_add))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", "write_to_trial_hand_2_exp_envi_hand_msg_buffer()");
						if (! write_to_trial_hand_2_neu_rec_hand_msg_buffer(msgs_trial_hand_2_neu_rec_hand, current_time, TRIAL_HAND_2_NEU_REC_HAND_MSG_START_RECORDING, recording_number))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", "write_to_trial_hand_2_neu_rec_hand_msg_buffer()");
						if (! write_to_trial_hand_2_gui_msg_buffer(msgs_trial_hand_2_gui, current_time, TRIAL_HAND_2_GUI_MSG_BROADCAST_START_RECORDING_MSG_ACK, recording_number))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", "write_to_trial_hand_2_gui_msg_buffer()");
						break;
					case TRIAL_STATUS_START_TRIAL_AVAILABLE:	
						recording_number = classified_history->all_trials->buff_write_idx; 
						if (!write_to_trial_hand_2_exp_envi_hand_msg_buffer(msgs_trial_hand_2_exp_envi_hand, current_time, TRIAL_HAND_2_EXP_ENVI_HAND_MSG_START_RECORDING, recording_number))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", "write_to_trial_hand_2_exp_envi_hand_msg_buffer()");
						trial_hand_2_mov_obj_hand_add.recording_number = recording_number;
						if (! write_to_trial_hand_2_mov_obj_hand_msg_buffer(msgs_trial_hand_2_mov_obj_hand, current_time, TRIAL_HAND_2_MOV_OBJ_HAND_MSG_START_RECORDING, trial_hand_2_mov_obj_hand_add))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", "write_to_trial_hand_2_exp_envi_hand_msg_buffer()");
						if (! write_to_trial_hand_2_neu_rec_hand_msg_buffer(msgs_trial_hand_2_neu_rec_hand, current_time, TRIAL_HAND_2_NEU_REC_HAND_MSG_START_RECORDING, recording_number))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", "write_to_trial_hand_2_neu_rec_hand_msg_buffer()");
						if (! write_to_trial_hand_2_gui_msg_buffer(msgs_trial_hand_2_gui, current_time, TRIAL_HAND_2_GUI_MSG_BROADCAST_START_RECORDING_MSG_ACK, recording_number))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", "write_to_trial_hand_2_gui_msg_buffer()");
						break;
					case TRIAL_STATUS_GET_READY_TO_START:	
						print_message(ERROR_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", "Cannot start recording when TRIAL_STATUS_GET_READY_TO_START");
						break;
					default:
						print_message(BUG_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", str_gui_msg);
						get_trial_status_type_string(*trial_status, str_status);   
						return print_message(BUG_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", str_status);
				}
				break;
			case GUI_2_TRIAL_HAND_MSG_BROADCAST_STOP_RECORDING:		
				switch (*trial_status)
				{
					case TRIAL_STATUS_TRIALS_DISABLED:
						print_message(ERROR_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", "Cannot stop recording when TRIAL_STATUS_TRIALS_DISABLED");
						break;
					case TRIAL_STATUS_IN_TRIAL:
						print_message(ERROR_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", "Cannot stop recording when TRIAL_STATUS_IN_TRIAL");
						break;
					case TRIAL_STATUS_IN_REFRACTORY:
						if (classified_history->all_trials->buff_write_idx == 0)
						{
							print_message(ERROR_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", "No trial finished to be saved");
							break;
						}
						recording_number = classified_history->all_trials->buff_write_idx-1;  // delete previous 
						if (!write_to_trial_hand_2_exp_envi_hand_msg_buffer(msgs_trial_hand_2_exp_envi_hand, current_time, TRIAL_HAND_2_EXP_ENVI_HAND_MSG_STOP_RECORDING, recording_number))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", "write_to_trial_hand_2_exp_envi_hand_msg_buffer()");
						trial_hand_2_mov_obj_hand_add.recording_number = recording_number;
						if (! write_to_trial_hand_2_mov_obj_hand_msg_buffer(msgs_trial_hand_2_mov_obj_hand, current_time, TRIAL_HAND_2_MOV_OBJ_HAND_MSG_STOP_RECORDING, trial_hand_2_mov_obj_hand_add))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", "write_to_trial_hand_2_exp_envi_hand_msg_buffer()");
						if (! write_to_trial_hand_2_neu_rec_hand_msg_buffer(msgs_trial_hand_2_neu_rec_hand, current_time, TRIAL_HAND_2_NEU_REC_HAND_MSG_STOP_RECORDING, recording_number))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", "write_to_trial_hand_2_neu_rec_hand_msg_buffer()");
						if (! write_to_trial_hand_2_gui_msg_buffer(msgs_trial_hand_2_gui, current_time, TRIAL_HAND_2_GUI_MSG_BROADCAST_STOP_RECORDING_MSG_ACK, recording_number))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", "write_to_trial_hand_2_gui_msg_buffer()");
						break;				
					case TRIAL_STATUS_START_TRIAL_AVAILABLE:	
						if (classified_history->all_trials->buff_write_idx == 0)
						{
							print_message(ERROR_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", "No trial finished to be saved");
							break;
						}
						recording_number = classified_history->all_trials->buff_write_idx-1;  // delete previous 
						if (!write_to_trial_hand_2_exp_envi_hand_msg_buffer(msgs_trial_hand_2_exp_envi_hand, current_time, TRIAL_HAND_2_EXP_ENVI_HAND_MSG_STOP_RECORDING, recording_number))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", "write_to_trial_hand_2_exp_envi_hand_msg_buffer()");
						trial_hand_2_mov_obj_hand_add.recording_number = recording_number;
						if (! write_to_trial_hand_2_mov_obj_hand_msg_buffer(msgs_trial_hand_2_mov_obj_hand, current_time, TRIAL_HAND_2_MOV_OBJ_HAND_MSG_STOP_RECORDING, trial_hand_2_mov_obj_hand_add))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", "write_to_trial_hand_2_exp_envi_hand_msg_buffer()");
						if (! write_to_trial_hand_2_neu_rec_hand_msg_buffer(msgs_trial_hand_2_neu_rec_hand, current_time, TRIAL_HAND_2_NEU_REC_HAND_MSG_STOP_RECORDING, recording_number))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", "write_to_trial_hand_2_neu_rec_hand_msg_buffer()");
						if (! write_to_trial_hand_2_gui_msg_buffer(msgs_trial_hand_2_gui, current_time, TRIAL_HAND_2_GUI_MSG_BROADCAST_STOP_RECORDING_MSG_ACK, recording_number))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", "write_to_trial_hand_2_gui_msg_buffer()");
						break;		
					case TRIAL_STATUS_GET_READY_TO_START:	
						print_message(ERROR_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", "Cannot stop recording when TRIAL_STATUS_GET_READY_TO_START");
						break;	
					default:
						print_message(BUG_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", str_gui_msg);
						get_trial_status_type_string(*trial_status, str_status);   
						return print_message(BUG_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", str_status);
				}
				break;
			case GUI_2_TRIAL_HAND_MSG_BROADCAST_CANCEL_RECORDING:
				switch (*trial_status)
				{
					case TRIAL_STATUS_TRIALS_DISABLED:
						print_message(ERROR_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", "Cannot stop recording when TRIAL_STATUS_TRIALS_DISABLED");
						break;
					case TRIAL_STATUS_IN_TRIAL:
						print_message(ERROR_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", "Cannot stop recording when TRIAL_STATUS_IN_TRIAL");
						break;
					case TRIAL_STATUS_IN_REFRACTORY:
						recording_number = classified_history->all_trials->buff_write_idx;  // delete the recording for current trial   //  history buffer write idx is inceremented when trial ends by TrialHandler rt thread funcitons.
						if (!write_to_trial_hand_2_exp_envi_hand_msg_buffer(msgs_trial_hand_2_exp_envi_hand, current_time, TRIAL_HAND_2_EXP_ENVI_HAND_MSG_CANCEL_RECORDING, recording_number))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", "write_to_trial_hand_2_exp_envi_hand_msg_buffer()");
						trial_hand_2_mov_obj_hand_add.recording_number = recording_number;
						if (! write_to_trial_hand_2_mov_obj_hand_msg_buffer(msgs_trial_hand_2_mov_obj_hand, current_time, TRIAL_HAND_2_MOV_OBJ_HAND_MSG_CANCEL_RECORDING, trial_hand_2_mov_obj_hand_add))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", "write_to_trial_hand_2_exp_envi_hand_msg_buffer()");
						if (! write_to_trial_hand_2_neu_rec_hand_msg_buffer(msgs_trial_hand_2_neu_rec_hand, current_time, TRIAL_HAND_2_NEU_REC_HAND_MSG_CANCEL_RECORDING, recording_number))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", "write_to_trial_hand_2_neu_rec_hand_msg_buffer()");
						if (! write_to_trial_hand_2_gui_msg_buffer(msgs_trial_hand_2_gui, current_time, TRIAL_HAND_2_GUI_MSG_BROADCAST_CANCEL_RECORDING_MSG_ACK, recording_number))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", "write_to_trial_hand_2_gui_msg_buffer()");
						break;				
					case TRIAL_STATUS_START_TRIAL_AVAILABLE:	
						recording_number = classified_history->all_trials->buff_write_idx;  // delete the recording for current trial   //  history buffer write idx is inceremented when trial ends by TrialHandler rt thread funcitons.
						if (!write_to_trial_hand_2_exp_envi_hand_msg_buffer(msgs_trial_hand_2_exp_envi_hand, current_time, TRIAL_HAND_2_EXP_ENVI_HAND_MSG_CANCEL_RECORDING, recording_number))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", "write_to_trial_hand_2_exp_envi_hand_msg_buffer()");
						trial_hand_2_mov_obj_hand_add.recording_number = recording_number;
						if (! write_to_trial_hand_2_mov_obj_hand_msg_buffer(msgs_trial_hand_2_mov_obj_hand, current_time, TRIAL_HAND_2_MOV_OBJ_HAND_MSG_CANCEL_RECORDING, trial_hand_2_mov_obj_hand_add))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", "write_to_trial_hand_2_exp_envi_hand_msg_buffer()");
						if (! write_to_trial_hand_2_neu_rec_hand_msg_buffer(msgs_trial_hand_2_neu_rec_hand, current_time, TRIAL_HAND_2_NEU_REC_HAND_MSG_CANCEL_RECORDING, recording_number))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", "write_to_trial_hand_2_neu_rec_hand_msg_buffer()");
						if (! write_to_trial_hand_2_gui_msg_buffer(msgs_trial_hand_2_gui, current_time, TRIAL_HAND_2_GUI_MSG_BROADCAST_CANCEL_RECORDING_MSG_ACK, recording_number))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", "write_to_trial_hand_2_gui_msg_buffer()");
						break;	
					case TRIAL_STATUS_GET_READY_TO_START:	
						print_message(ERROR_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", "Cannot stop recording when TRIAL_STATUS_GET_READY_TO_START");
						break;			
					default:
						print_message(BUG_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", str_gui_msg);
						get_trial_status_type_string(*trial_status, str_status);   
						return print_message(BUG_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", str_status);
				}
				break;
			case GUI_2_TRIAL_HAND_MSG_RELEASE_REWARD:
				if (!write_to_trial_hand_2_exp_envi_hand_msg_buffer(msgs_trial_hand_2_exp_envi_hand, current_time, TRIAL_HAND_2_EXP_ENVI_HAND_MSG_RELEASE_REWARD, 0))
					return print_message(ERROR_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", "write_to_trial_hand_2_exp_envi_hand_msg_buffer()");
				break;
			case GUI_2_TRIAL_HAND_MSG_TURN_LEVER_PRESS_MODE_ON:
				switch (*trial_status)
				{
					case TRIAL_STATUS_TRIALS_DISABLED:
						paradigm->current_trial_data.lever_press_mode_on = TRUE;
						break;
					case TRIAL_STATUS_IN_TRIAL:
						print_message(ERROR_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", "TURN_LEVER_PRESS_MODE_ON cannot be done during TRIAL_STATUS_IN_TRIAL");
						break;
					case TRIAL_STATUS_IN_REFRACTORY:
						paradigm->current_trial_data.lever_press_mode_on = TRUE;
						break;
					case TRIAL_STATUS_START_TRIAL_AVAILABLE:	
						paradigm->current_trial_data.lever_press_mode_on = TRUE;
						break;
					case TRIAL_STATUS_WAIT_FOR_LEVER_PRESS:
						print_message(ERROR_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", "TURN_LEVER_PRESS_MODE_ON cannot be done during TRIAL_STATUS_WAIT_FOR_LEVER_PRESS");
						break;
					case TRIAL_STATUS_GET_READY_TO_START:	
						print_message(ERROR_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", "TURN_LEVER_PRESS_MODE_ON cannot be done during TRIAL_STATUS_GET_READY_TO_START");
						break;	
					default:
						print_message(BUG_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", str_gui_msg);
						get_trial_status_type_string(*trial_status, str_status);   
						return print_message(BUG_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", str_status);
				}
				break;
			case GUI_2_TRIAL_HAND_MSG_TURN_LEVER_PRESS_MODE_OFF:
				switch (*trial_status)
				{
					case TRIAL_STATUS_TRIALS_DISABLED:
						paradigm->current_trial_data.lever_press_mode_on = FALSE;
						break;
					case TRIAL_STATUS_IN_TRIAL:
						print_message(ERROR_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", "TURN_LEVER_PRESS_MODE_OFF cannot be done during TRIAL_STATUS_IN_TRIAL");
						break;
					case TRIAL_STATUS_IN_REFRACTORY:
						paradigm->current_trial_data.lever_press_mode_on = FALSE;
						break;
					case TRIAL_STATUS_START_TRIAL_AVAILABLE:	
						paradigm->current_trial_data.lever_press_mode_on = FALSE;
						break;
					case TRIAL_STATUS_WAIT_FOR_LEVER_PRESS:
						print_message(ERROR_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", "TURN_LEVER_PRESS_MODE_OFF cannot be done during TRIAL_STATUS_WAIT_FOR_LEVER_PRESS");
						break;
					case TRIAL_STATUS_GET_READY_TO_START:	
						print_message(ERROR_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", "TURN_LEVER_PRESS_MODE_OFF cannot be done during TRIAL_STATUS_GET_READY_TO_START");
						break;	
					default:
						print_message(BUG_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", str_gui_msg);
						get_trial_status_type_string(*trial_status, str_status);   
						return print_message(BUG_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", str_status);
				}
				break;
			case GUI_2_TRIAL_HAND_MSG_END_TRIAL:
				switch (*trial_status)
				{
					case TRIAL_STATUS_TRIALS_DISABLED:
						break;
					case TRIAL_STATUS_IN_TRIAL:
						*trial_status = TRIAL_STATUS_IN_REFRACTORY;

						trial_length = current_time - paradigm->current_trial_data.trial_start_time;
						paradigm->current_trial_data.trial_end_time = current_time;
						paradigm->current_trial_data.trial_length = trial_length;
						paradigm->current_trial_data.binary_reward = FALSE;
						paradigm->current_trial_data.trial_incomplete = TRUE;

						if (! write_trial_data_to_classified_trial_history(classified_history, &(paradigm->current_trial_data)))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleExpEnviHand2TrialHandMsgs", "handle_exp_envi_handler_to_trial_handler_msg", "write_trial_data_to_classified_trial_history()");

						paradigm->current_trial_data.trial_start_time = 0;
						paradigm->current_trial_data.trial_end_time = 0;
						paradigm->current_trial_data.trial_length = 0;

						paradigm->current_trial_data.robot_start_position_idx = (unsigned int)(paradigm->num_of_robot_start_positions * get_rand_number());   ///  Bunu trial bittiginde yap.
						
						if (!write_to_trial_hand_2_trial_dur_hand_msg_buffer(msgs_trial_hand_2_trial_dur_hand, current_time, TRIAL_HAND_2_TRIAL_DUR_HAND_MSG_DISABLE_DURATION_HANDLING, 0))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleTrialDurHand2TrialHandMsgs", "handle_trial_dur_handler_to_trial_handler_msg", "write_to_trial_hand_2_trial_dur_hand_msg_buffer()");

						refractory = current_time + paradigm->min_trial_refractory + ((TimeStamp)(get_rand_number() * (double)paradigm->max_extra_trial_refractory));
						if (!write_to_trial_hand_2_trial_dur_hand_msg_buffer(msgs_trial_hand_2_trial_dur_hand, current_time, TRIAL_HAND_2_TRIAL_DUR_HAND_MSG_ENABLE_DURATION_HANDLING, refractory))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleTrialDurHand2TrialHandMsgs", "handle_trial_dur_handler_to_trial_handler_msg", "write_to_trial_hand_2_trial_dur_hand_msg_buffer()");

/*						if (!write_to_trial_hand_2_exp_envi_hand_msg_buffer(msgs_trial_hand_2_exp_envi_hand, current_time, TRIAL_HAND_2_EXP_ENVI_HAND_MSG_RELEASE_PUNISHMENT, 0))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleTrialDurHand2TrialHandMsgs", "handle_trial_dur_handler_to_trial_handler_msg", "write_to_trial_hand_2_exp_envi_hand_msg_buffer()");  */
						if (!write_to_trial_hand_2_exp_envi_hand_msg_buffer(msgs_trial_hand_2_exp_envi_hand, current_time, TRIAL_HAND_2_EXP_ENVI_HAND_MSG_END_TRIAL, 0))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleTrialDurHand2TrialHandMsgss", "handle_trial_dur_handler_to_trial_handler_msg", "write_to_trial_hand_2_exp_envi_hand_msg_buffer()");
						trial_hand_to_mov_obj_hand_msg_add.robot_start_position_idx = paradigm->current_trial_data.robot_start_position_idx;
						if (!write_to_trial_hand_2_mov_obj_hand_msg_buffer(msgs_trial_hand_2_mov_obj_hand, current_time, TRIAL_HAND_2_MOV_OBJ_HAND_MSG_END_TRIAL, trial_hand_to_mov_obj_hand_msg_add))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleTrialDurHand2TrialHandMsgss", "handle_trial_dur_handler_to_trial_handler_msg", "write_to_trial_hand_2_mov_obj_hand_msg_buffer()");
						if (!write_to_trial_hand_2_gui_msg_buffer(msgs_trial_hand_2_gui, current_time, TRIAL_HAND_2_GUI_MSG_TRIAL_STATUS_CHANGE, TRIAL_STATUS_IN_REFRACTORY))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleTrialDurHand2TrialHandMsgs", "handle_trial_dur_handler_to_trial_handler_msg", "write_to_trial_hand_2_gui_msg_buffer(()");
						if (! write_to_trial_status_history(trial_status_history, current_time, TRIAL_STATUS_IN_REFRACTORY))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleTrialDurHand2TrialHandMsgs", "handle_trial_dur_handler_to_trial_handler_msg", "write_to_trial_status_history()");
						break;
					case TRIAL_STATUS_IN_REFRACTORY:
						break;
					case TRIAL_STATUS_START_TRIAL_AVAILABLE:	
						break;
					case TRIAL_STATUS_WAIT_FOR_LEVER_PRESS:
						break;
					case TRIAL_STATUS_GET_READY_TO_START:
						print_message(ERROR_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", "GUI_2_TRIAL_HAND_MSG_END_TRIAL is not supported during TRIAL_STATUS_GET_READY_TO_START");
						break;	
					default:
						print_message(BUG_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", str_gui_msg);
						get_trial_status_type_string(*trial_status, str_status);   
						return print_message(BUG_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", str_status);
				}
				break;
			default:
				return print_message(BUG_MSG ,"TrialHandler", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", str_gui_msg);	
		}
	}
	return TRUE;
}
