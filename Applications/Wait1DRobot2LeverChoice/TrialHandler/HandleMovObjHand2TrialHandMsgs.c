#include "HandleMovObjHand2TrialHandMsgs.h"

#define AVERAGING_WINDOW 5
#define ALPHA 20.0
#define BETA 0.5

bool handle_mov_obj_handler_to_trial_handler_msg(TrialStatus *trial_status, TimeStamp current_time, MovObjHand2TrialHandMsg *msgs_mov_obj_hand_2_trial_hand, TrialHand2TrialDurHandMsg *msgs_trial_hand_2_trial_dur_hand, TrialHand2ExpEnviHandMsg *msgs_trial_hand_2_exp_envi_hand, TrialHand2MovObjHandMsg *msgs_trial_hand_2_mov_obj_hand, TrialHandParadigmRobotReach *paradigm, ClassifiedTrialHistory* classified_history, TrialHand2GuiMsg *msgs_trial_hand_2_gui, TrialStatusHistory *trial_status_history)
{
	MovObjHand2TrialHandMsgItem msg_item;
	char str_mov_obj_msg[MOV_OBJ_HAND_2_TRIAL_HAND_MSG_STRING_LENGTH];
	char str_status[TRIAL_STATUS_MAX_STRING_LENGTH];
	while (get_next_mov_obj_hand_2_trial_hand_msg_buffer_item(msgs_mov_obj_hand_2_trial_hand, &msg_item))
	{
		get_mov_obj_hand_2_trial_hand_msg_type_string(msg_item.msg_type, str_mov_obj_msg);
		print_message(INFO_MSG ,"TrialHandler", "HandleMovObjHand2TrialHandMsgs", "handle_mov_obj_handler_to_trial_handler_msg", str_mov_obj_msg);
		switch (msg_item.msg_type)
		{
			case MOV_OBJ_HAND_2_TRIAL_HAND_MSG_REACHED_2_TARGET:     // mov obj handler sends this when it receives a trial start msg from trial hand			
				switch (*trial_status)
				{
					case TRIAL_STATUS_TRIALS_DISABLED:
						return print_message(BUG_MSG ,"TrialHandler", "HandleMovObjHand2TrialHandMsgs", "handle_mov_obj_handler_to_trial_handler_msg", str_status);
					case TRIAL_STATUS_IN_TRIAL:
						if (! paradigm->current_trial_data.catch_trial_mode_on)
						{
							if (!write_to_trial_hand_2_exp_envi_hand_msg_buffer(msgs_trial_hand_2_exp_envi_hand, current_time, TRIAL_HAND_2_EXP_ENVI_HAND_MSG_ENABLE_INP_COMPS_W_NO_STATUS_RESET, 0))
								return print_message(ERROR_MSG ,"TrialHandler", "HandleMovObjHand2TrialHandMsgss", "handle_mov_obj_handler_to_trial_handler_msg", "write_to_trial_hand_2_exp_envi_hand_msg_buffer()");
						}
						else
						{
							if (paradigm->current_trial_data.target_led_component_list_idx == paradigm->current_trial_data.robot_target_position_idx)
							{
								if (!write_to_trial_hand_2_exp_envi_hand_msg_buffer(msgs_trial_hand_2_exp_envi_hand, current_time, TRIAL_HAND_2_EXP_ENVI_HAND_MSG_ENABLE_INP_COMPS_W_NO_STATUS_RESET, 0))
									return print_message(ERROR_MSG ,"TrialHandler", "HandleMovObjHand2TrialHandMsgss", "handle_mov_obj_handler_to_trial_handler_msg", "write_to_trial_hand_2_exp_envi_hand_msg_buffer()");						
							}
						}
						if (!write_to_trial_hand_2_trial_dur_hand_msg_buffer(msgs_trial_hand_2_trial_dur_hand, current_time, TRIAL_HAND_2_TRIAL_DUR_HAND_MSG_DISABLE_DURATION_HANDLING, 0))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleTrialDurHand2TrialHandMsgs", "handle_trial_dur_handler_to_trial_handler_msg", "write_to_trial_hand_2_trial_dur_hand_msg_buffer()");
						if (!write_to_trial_hand_2_trial_dur_hand_msg_buffer(msgs_trial_hand_2_trial_dur_hand, current_time, TRIAL_HAND_2_TRIAL_DUR_HAND_MSG_ENABLE_DURATION_HANDLING, current_time + paradigm->max_lever_press_interval))
							return print_message(ERROR_MSG ,"TrialHandler", "HandleTrialDurHand2TrialHandMsgs", "handle_trial_dur_handler_to_trial_handler_msg", "write_to_trial_hand_2_trial_dur_hand_msg_buffer()");
						break;  
					case TRIAL_STATUS_IN_REFRACTORY:
						get_trial_status_type_string(*trial_status, str_status);   
						return print_message(BUG_MSG ,"TrialHandler", "HandleMovObjHand2TrialHandMsgs", "handle_mov_obj_handler_to_trial_handler_msg", str_status);
					case TRIAL_STATUS_START_TRIAL_AVAILABLE:	
						get_trial_status_type_string(*trial_status, str_status);   
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
