#include "HandleTrialDurHand2TrialHandMsgs.h"


bool handle_trial_dur_handler_to_trial_handler_msg(TrialStatus *trial_status, TimeStamp current_time, TrialDurHand2TrialHandMsg *msgs_trial_dur_hand_2_trial_hand, TrialHand2TrialDurHandMsg *msgs_trial_hand_2_trial_dur_hand, TrialHand2ExpEnviHandMsg *msgs_trial_hand_2_exp_envi_hand, TrialHand2MovObjHandMsg *msgs_trial_hand_2_mov_obj_hand, ClassifiedTrialHistory* classified_history, TrialHandParadigmRobotReach *paradigm, TrialHand2GuiMsg *msgs_trial_hand_2_gui, TrialStatusHistory *trial_status_history)
{
	TrialDurHand2TrialHandMsgItem msg_item;
	char str_trial_dur_msg[TRIAL_DUR_HAND_2_TRIAL_HAND_MSG_STRING_LENGTH];
	char str_status[TRIAL_STATUS_MAX_STRING_LENGTH];
	TrialHand2MovObjHandMsgAdditional  trial_hand_to_mov_obj_hand_msg_add;
	TimeStamp refractory;
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
						*trial_status = TRIAL_STATUS_IN_REFRACTORY;
						if (! write_trial_data_to_classified_trial_history(classified_history, &(paradigm->current_trial_data)))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleMovObjHand2TrialHandMsgs", "handle_mov_obj_handler_to_trial_handler_msg", "write_trial_data_to_classified_trial_history()");
				
						paradigm->current_trial_data.trial_start_time = 0;
						paradigm->current_trial_data.trial_end_time = 0;
						paradigm->current_trial_data.trial_length = 0;

						paradigm->current_trial_data.robot_start_position_idx = (unsigned int)(paradigm->num_of_robot_start_positions * get_rand_number()); /// Bunu trial bittiginde yap.

						if (!write_to_trial_hand_2_trial_dur_hand_msg_buffer(msgs_trial_hand_2_trial_dur_hand, current_time, TRIAL_HAND_2_TRIAL_DUR_HAND_MSG_DISABLE_DURATION_HANDLING, 0))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleTrialDurHand2TrialHandMsgss", "handle_trial_dur_handler_to_trial_handler_msg", "write_to_trial_hand_2_trial_dur_hand_msg_buffer()");
						refractory = current_time + paradigm->min_trial_refractory + ((TimeStamp)(get_rand_number() * (double)paradigm->max_extra_trial_refractory));
						if (!write_to_trial_hand_2_trial_dur_hand_msg_buffer(msgs_trial_hand_2_trial_dur_hand, current_time, TRIAL_HAND_2_TRIAL_DUR_HAND_MSG_ENABLE_DURATION_HANDLING, refractory))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleTrialDurHand2TrialHandMsgss", "handle_trial_dur_handler_to_trial_handler_msg", "write_to_trial_hand_2_trial_dur_hand_msg_buffer()");

						if (!write_to_trial_hand_2_exp_envi_hand_msg_buffer(msgs_trial_hand_2_exp_envi_hand, current_time, TRIAL_HAND_2_EXP_ENVI_HAND_MSG_END_TRIAL, 0))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleTrialDurHand2TrialHandMsgss", "handle_trial_dur_handler_to_trial_handler_msg", "write_to_trial_hand_2_exp_envi_hand_msg_buffer()");
						trial_hand_to_mov_obj_hand_msg_add.robot_start_position_idx = paradigm->current_trial_data.robot_start_position_idx;
						if (!write_to_trial_hand_2_mov_obj_hand_msg_buffer(msgs_trial_hand_2_mov_obj_hand, current_time, TRIAL_HAND_2_MOV_OBJ_HAND_MSG_END_TRIAL, trial_hand_to_mov_obj_hand_msg_add))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleTrialDurHand2TrialHandMsgss", "handle_trial_dur_handler_to_trial_handler_msg", "write_to_trial_hand_2_mov_obj_hand_msg_buffer()");

						if (!write_to_trial_hand_2_gui_msg_buffer(msgs_trial_hand_2_gui, current_time, TRIAL_HAND_2_GUI_MSG_TRIAL_STATUS_CHANGE,  TRIAL_STATUS_IN_REFRACTORY))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleTrialDurHand2TrialHandMsgss", "handle_trial_dur_handler_to_trial_handler_msg", "write_to_trial_hand_2_gui_msg_buffer()");

						break;
					case TRIAL_STATUS_IN_REFRACTORY:
						*trial_status = TRIAL_STATUS_START_TRIAL_AVAILABLE;
						if (!write_to_trial_hand_2_gui_msg_buffer(msgs_trial_hand_2_gui, current_time, TRIAL_HAND_2_GUI_MSG_TRIAL_STATUS_CHANGE, TRIAL_STATUS_START_TRIAL_AVAILABLE))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleTrialDurHand2TrialHandMsgss", "handle_trial_dur_handler_to_trial_handler_msg", "write_to_trial_hand_2_gui_msg_buffer()");
						if (! write_to_trial_status_history(trial_status_history, current_time, TRIAL_STATUS_START_TRIAL_AVAILABLE))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleTrialDurHand2TrialHandMsgss", "handle_trial_dur_handler_to_trial_handler_msg", "write_to_trial_status_history()");
						if (!write_to_trial_hand_2_exp_envi_hand_msg_buffer(msgs_trial_hand_2_exp_envi_hand, current_time, TRIAL_HAND_2_EXP_ENVI_HAND_MSG_ENABLE_INP_COMPS_W_STATUS_RESET, 0))
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
