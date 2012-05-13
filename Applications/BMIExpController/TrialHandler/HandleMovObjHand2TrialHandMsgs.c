#include "HandleMovObjHand2TrialHandMsgs.h"


bool handle_mov_obj_handler_to_trial_handler_msg(TrialTypesData *trial_types_data, TrialsHistory *trials_history, TrialStatsData *trial_stats_data, TrialStatus *trial_status, TimeStamp current_time, MovObjHand2TrialHandMsg *msgs_mov_obj_hand_2_trial_hand, TrialHand2TrialDurHandMsg *msgs_trial_hand_2_trial_dur_hand, TrialHand2ExpEnviHandMsg *msgs_trial_hand_2_exp_envi_hand, TrialHand2MovObjHandMsg *msgs_trial_hand_2_mov_obj_hand)
{
	MovObjHand2TrialHandMsgItem *msg_item;
	char str_mov_obj_msg[MOV_OBJ_HAND_2_TRIAL_HAND_MSG_STRING_LENGTH];
	char str_status[TRIAL_STATUS_MAX_STRING_LENGTH];
	TrialType trial_type;
	unsigned int trial_type_idx;
	while (get_next_mov_obj_hand_2_trial_hand_msg_buffer_item(msgs_mov_obj_hand_2_trial_hand, &msg_item))
	{
		get_mov_obj_hand_2_trial_hand_msg_type_string(msg_item->msg_type, str_mov_obj_msg);
		print_message(INFO_MSG ,"TrialHandler", "HandleMovObjHand2TrialHandMsgs", "handle_mov_obj_handler_to_trial_handler_msg", str_mov_obj_msg);
		switch (msg_item->msg_type)
		{
			case MOV_OBJ_HAND_2_TRIAL_HAND_MSG_REWARD_REQUEST:	
				switch (*trial_status)
				{
					case TRIAL_STATUS_TRIALS_DISABLED:
						break;   // do nothing
					case TRIAL_STATUS_IN_TRIAL:
						if (!write_to_trial_hand_2_trial_dur_hand_msg_buffer(msgs_trial_hand_2_trial_dur_hand, current_time, TRIAL_HAND_2_TRIAL_DUR_HAND_MSG_DISABLE_DURATION_HANDLING, 0))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleMovObjHand2TrialHandMsgs", "handle_mov_obj_handler_to_trial_handler_msg", "write_to_trial_hand_2_trial_dur_hand_msg_buffer()");
						if (!write_to_trial_hand_2_exp_envi_hand_msg_buffer(msgs_trial_hand_2_exp_envi_hand, current_time, TRIAL_HAND_2_EXP_ENVI_HAND_MSG_RELEASE_REWARD, 0))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleMovObjHand2TrialHandMsgs", "handle_mov_obj_handler_to_trial_handler_msg", "write_to_trial_hand_2_exp_envi_hand_msg_buffer()");
						trial_type = trials_history->history[trials_history->buff_write_idx].trial_type;
						if (! get_trial_type_idx_in_trial_types_data(trial_types_data, trial_type, &trial_type_idx))
							return print_message(BUG_MSG ,"TrialHandler", "HandleMovObjHand2TrialHandMsgs", "handle_mov_obj_handler_to_trial_handler_msg", "get_trial_type_idx_in_trial_types_data()");
						trial_stats_data->trial_type_stats[trial_type_idx].num_of_rewarded_trials++;
						trial_stats_data->num_of_rewarded_trials++;
						trials_history->history[trials_history->buff_write_idx].rewarded = TRUE;
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
			case MOV_OBJ_HAND_2_TRIAL_HAND_MSG_END_TRIAL_REQUEST:     	
				switch (*trial_status)
				{
					case TRIAL_STATUS_TRIALS_DISABLED:
						break;   // do nothing
					case TRIAL_STATUS_IN_TRIAL:
						*trial_status = TRIAL_STATUS_IN_REFRACTORY;
						trial_type = trials_history->history[trials_history->buff_write_idx].trial_type;
						if (! get_trial_type_idx_in_trial_types_data(trial_types_data, trial_type, &trial_type_idx))
							return print_message(BUG_MSG ,"TrialHandler", "HandleMovObjHand2TrialHandMsgs", "handle_mov_obj_handler_to_trial_handler_msg", "get_trial_type_idx_in_trial_types_data()");
						if (!write_to_trial_hand_2_trial_dur_hand_msg_buffer(msgs_trial_hand_2_trial_dur_hand, current_time, TRIAL_HAND_2_TRIAL_DUR_HAND_MSG_ENABLE_DURATION_HANDLING, current_time + trial_types_data->types[trial_type_idx].constraints.trial_refractory))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleTrialDurHand2TrialHandMsgss", "handle_trial_dur_handler_to_trial_handler_msg", "write_to_trial_hand_2_trial_dur_hand_msg_buffer()");
						if (!write_to_trial_hand_2_exp_envi_hand_msg_buffer(msgs_trial_hand_2_exp_envi_hand, current_time, TRIAL_HAND_2_EXP_ENVI_HAND_MSG_END_TRIAL, 0))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleTrialDurHand2TrialHandMsgss", "handle_trial_dur_handler_to_trial_handler_msg", "write_to_trial_hand_2_exp_envi_hand_msg_buffer()");
						if (!write_to_trial_hand_2_mov_obj_hand_msg_buffer(msgs_trial_hand_2_mov_obj_hand, current_time, TRIAL_HAND_2_MOV_OBJ_HAND_MSG_END_TRIAL, 0))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleTrialDurHand2TrialHandMsgss", "handle_trial_dur_handler_to_trial_handler_msg", "write_to_trial_hand_2_mov_obj_hand_msg_buffer()");
						trials_history->history[trials_history->buff_write_idx].trial_end_time = current_time;
						increment_trials_history_write_idx(trials_history);
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
