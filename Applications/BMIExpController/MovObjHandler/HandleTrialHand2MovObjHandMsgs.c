#include "HandleTrialHand2MovObjHandMsgs.h"



bool handle_trial_handler_to_mov_obj_handler_msg(MovObjData *mov_obj_data, MovObjStatus *mov_obj_status, TrialType *mov_obj_trial_type_status, TimeStamp current_time, TrialHand2MovObjHandMsg *msgs_trial_hand_2_mov_obj_hand, MovObjHand2MovObjDurHandMsg *msgs_mov_obj_hand_2_mov_obj_dur_hand)
{
	TrialHand2MovObjHandMsgItem *msg_item;
	char str_trial_hand_msg[TRIAL_HAND_2_MOV_OBJ_HAND_MSG_STRING_LENGTH];
	char str_mov_obj_status[MOV_OBJ_STATUS_MAX_STRING_LENGTH];

	while (get_next_trial_hand_2_mov_obj_hand_msg_buffer_item(msgs_trial_hand_2_mov_obj_hand, &msg_item))
	{
		get_trial_hand_2_mov_obj_hand_msg_type_string(msg_item->msg_type, str_trial_hand_msg);
		print_message(INFO_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_handler_to_mov_obj_handler_msg", str_trial_hand_msg);
		switch (msg_item->msg_type)
		{
			case TRIAL_HAND_2_MOV_OBJ_HAND_MSG_START_TRIAL:	
				switch (*mov_obj_status)
				{
					case MOV_OBJ_STATUS_OUT_OF_TRIAL:
						*mov_obj_trial_type_status = msg_item->additional_data;
						switch (*mov_obj_trial_type_status)
						{
							case TRIAL_TYPE_IN_VIVO_BMI_LEFT_TARGET:	
								*mov_obj_status = MOV_OBJ_STATUS_STAYING_AT_START_POINT;
								if (! write_to_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer(msgs_mov_obj_hand_2_mov_obj_dur_hand, current_time,  MOV_OBJ_HAND_2_MOV_OBJ_DUR_HAND_MSG_START_TIMER, mov_obj_data->glo_constraints.stay_at_start_duration + current_time))
									return print_message(BUG_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_hand_to_mov_obj_handler_msg", "write_to_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer().");	
								break;
							case TRIAL_TYPE_IN_VIVO_BMI_RIGHT_TARGET:
								*mov_obj_status = MOV_OBJ_STATUS_STAYING_AT_START_POINT;
								if (! write_to_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer(msgs_mov_obj_hand_2_mov_obj_dur_hand, current_time,  MOV_OBJ_HAND_2_MOV_OBJ_DUR_HAND_MSG_START_TIMER, mov_obj_data->glo_constraints.stay_at_start_duration + current_time))
									return print_message(BUG_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_hand_to_mov_obj_handler_msg", "write_to_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer().");
								break;
							default:
								print_message(BUG_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_handler_to_mov_obj_handler_msg", str_trial_hand_msg);	
								get_mov_obj_status_type_string(*mov_obj_status, str_mov_obj_status);   
								return print_message(BUG_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_handler_to_mov_obj_handler_msg", str_mov_obj_status);	
						}
						break;
					case MOV_OBJ_STATUS_STAYING_AT_START_POINT:
						print_message(BUG_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_handler_to_mov_obj_handler_msg", str_trial_hand_msg);	
						get_mov_obj_status_type_string(*mov_obj_status, str_mov_obj_status);   
						return print_message(BUG_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_handler_to_mov_obj_handler_msg", str_mov_obj_status);	
					case MOV_OBJ_STATUS_AVAILABLE_TO_CONTROL:
						print_message(BUG_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_handler_to_mov_obj_handler_msg", str_trial_hand_msg);	
						get_mov_obj_status_type_string(*mov_obj_status, str_mov_obj_status);   
						return print_message(BUG_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_handler_to_mov_obj_handler_msg", str_mov_obj_status);	
					case MOV_OBJ_STATUS_RESETTING_TO_TARGET_POINT_W_FAIL:
						print_message(BUG_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_handler_to_mov_obj_handler_msg", str_trial_hand_msg);	
						get_mov_obj_status_type_string(*mov_obj_status, str_mov_obj_status);   
						return print_message(BUG_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_handler_to_mov_obj_handler_msg", str_mov_obj_status);
					case MOV_OBJ_STATUS_RESETTING_TO_TARGET_POINT_W_SUCCESS:
						print_message(BUG_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_handler_to_mov_obj_handler_msg", str_trial_hand_msg);	
						get_mov_obj_status_type_string(*mov_obj_status, str_mov_obj_status);   
						return print_message(BUG_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_handler_to_mov_obj_handler_msg", str_mov_obj_status);
					case MOV_OBJ_STATUS_REACHED_TARGET_POINT_W_FAIL:
						print_message(BUG_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_handler_to_mov_obj_handler_msg", str_trial_hand_msg);	
						get_mov_obj_status_type_string(*mov_obj_status, str_mov_obj_status);   
						return print_message(BUG_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_handler_to_mov_obj_handler_msg", str_mov_obj_status);
					case MOV_OBJ_STATUS_REACHED_TARGET_POINT_W_SUCCESS:
						print_message(BUG_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_handler_to_mov_obj_handler_msg", str_trial_hand_msg);	
						get_mov_obj_status_type_string(*mov_obj_status, str_mov_obj_status);   
						return print_message(BUG_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_handler_to_mov_obj_handler_msg", str_mov_obj_status);
					case MOV_OBJ_STATUS_RESETTING_TO_START_POINT:
						print_message(BUG_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_handler_to_mov_obj_handler_msg", str_trial_hand_msg);	
						get_mov_obj_status_type_string(*mov_obj_status, str_mov_obj_status);   
						return print_message(BUG_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_handler_to_mov_obj_handler_msg", str_mov_obj_status);
					default:
						print_message(BUG_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_handler_to_mov_obj_handler_msg", str_trial_hand_msg);
						get_mov_obj_status_type_string(*mov_obj_status, str_mov_obj_status);   
						return print_message(BUG_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_handler_to_mov_obj_handler_msg", str_mov_obj_status);
				}
				break;
			case TRIAL_HAND_2_MOV_OBJ_HAND_MSG_TRIAL_TIMEOUT:
				switch (*mov_obj_status)
				{
					case MOV_OBJ_STATUS_OUT_OF_TRIAL:
						print_message(BUG_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_handler_to_mov_obj_handler_msg", str_trial_hand_msg);	
						get_mov_obj_status_type_string(*mov_obj_status, str_mov_obj_status);   
						return print_message(BUG_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_handler_to_mov_obj_handler_msg", str_mov_obj_status);	
					case MOV_OBJ_STATUS_STAYING_AT_START_POINT:
						print_message(ERROR_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_handler_to_mov_obj_handler_msg", str_trial_hand_msg);	
						get_mov_obj_status_type_string(*mov_obj_status, str_mov_obj_status);   
						return print_message(ERROR_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_handler_to_mov_obj_handler_msg", str_mov_obj_status);	
					case MOV_OBJ_STATUS_AVAILABLE_TO_CONTROL:
						*mov_obj_status = MOV_OBJ_STATUS_RESETTING_TO_TARGET_POINT_W_FAIL;	  // handle_mov_obj_handler_status handles robot to convenient target. 
						break;
					case MOV_OBJ_STATUS_RESETTING_TO_TARGET_POINT_W_FAIL:
						print_message(BUG_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_handler_to_mov_obj_handler_msg", str_trial_hand_msg);	
						get_mov_obj_status_type_string(*mov_obj_status, str_mov_obj_status);   
						return print_message(BUG_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_handler_to_mov_obj_handler_msg", str_mov_obj_status);
					case MOV_OBJ_STATUS_RESETTING_TO_TARGET_POINT_W_SUCCESS:	
						break;	// ignore message. reached threshold before trial time out
					case MOV_OBJ_STATUS_REACHED_TARGET_POINT_W_FAIL:
						print_message(BUG_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_handler_to_mov_obj_handler_msg", str_trial_hand_msg);	
						get_mov_obj_status_type_string(*mov_obj_status, str_mov_obj_status);   
						return print_message(BUG_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_handler_to_mov_obj_handler_msg", str_mov_obj_status);
					case MOV_OBJ_STATUS_REACHED_TARGET_POINT_W_SUCCESS:
						break;	// ignore message. reached target before trial time out
					case MOV_OBJ_STATUS_RESETTING_TO_START_POINT:
						print_message(BUG_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_handler_to_mov_obj_handler_msg", str_trial_hand_msg);	
						get_mov_obj_status_type_string(*mov_obj_status, str_mov_obj_status);   
						return print_message(BUG_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_handler_to_mov_obj_handler_msg", str_mov_obj_status);
					default:
						print_message(BUG_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_handler_to_mov_obj_handler_msg", str_trial_hand_msg);
						get_mov_obj_status_type_string(*mov_obj_status, str_mov_obj_status);   
						return print_message(BUG_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_handler_to_mov_obj_handler_msg", str_mov_obj_status);
				}
				break;
			case TRIAL_HAND_2_MOV_OBJ_HAND_MSG_END_TRIAL:	
				switch (*mov_obj_status)
				{
					case MOV_OBJ_STATUS_OUT_OF_TRIAL:
						print_message(BUG_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_handler_to_mov_obj_handler_msg", str_trial_hand_msg);	
						get_mov_obj_status_type_string(*mov_obj_status, str_mov_obj_status);   
						return print_message(BUG_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_handler_to_mov_obj_handler_msg", str_mov_obj_status);	
					case MOV_OBJ_STATUS_STAYING_AT_START_POINT:  // should have gone to target already to receive such message
						print_message(BUG_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_handler_to_mov_obj_handler_msg", str_trial_hand_msg);	
						get_mov_obj_status_type_string(*mov_obj_status, str_mov_obj_status);   
						return print_message(BUG_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_handler_to_mov_obj_handler_msg", str_mov_obj_status);
					case MOV_OBJ_STATUS_AVAILABLE_TO_CONTROL: // should have gone to target already to receive such message
						print_message(BUG_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_handler_to_mov_obj_handler_msg", str_trial_hand_msg);	
						get_mov_obj_status_type_string(*mov_obj_status, str_mov_obj_status);   
						return print_message(BUG_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_handler_to_mov_obj_handler_msg", str_mov_obj_status);
					case MOV_OBJ_STATUS_RESETTING_TO_TARGET_POINT_W_FAIL: // should have gone to target already to receive such message
						print_message(BUG_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_handler_to_mov_obj_handler_msg", str_trial_hand_msg);	
						get_mov_obj_status_type_string(*mov_obj_status, str_mov_obj_status);   
						return print_message(BUG_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_handler_to_mov_obj_handler_msg", str_mov_obj_status);
					case MOV_OBJ_STATUS_RESETTING_TO_TARGET_POINT_W_SUCCESS: // should have gone to target already to receive such message
						print_message(BUG_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_handler_to_mov_obj_handler_msg", str_trial_hand_msg);	
						get_mov_obj_status_type_string(*mov_obj_status, str_mov_obj_status);   
						return print_message(BUG_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_handler_to_mov_obj_handler_msg", str_mov_obj_status);
					case MOV_OBJ_STATUS_REACHED_TARGET_POINT_W_FAIL:
						*mov_obj_status = MOV_OBJ_STATUS_RESETTING_TO_START_POINT;
						*mov_obj_trial_type_status = TRIAL_TYPE_UNSPECIFIED;
						// end trial message also goes exp envi which resets exp envi and mov obj
						break;   // do nothing
					case MOV_OBJ_STATUS_REACHED_TARGET_POINT_W_SUCCESS:
						*mov_obj_status = MOV_OBJ_STATUS_RESETTING_TO_START_POINT;
						*mov_obj_trial_type_status = TRIAL_TYPE_UNSPECIFIED;
						// end trial message also goes exp envi which resets exp envi and mov obj
						break;   // do nothing
					case MOV_OBJ_STATUS_RESETTING_TO_START_POINT:
						print_message(BUG_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_handler_to_mov_obj_handler_msg", str_trial_hand_msg);	
						get_mov_obj_status_type_string(*mov_obj_status, str_mov_obj_status);   
						return print_message(BUG_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_handler_to_mov_obj_handler_msg", str_mov_obj_status);
					default:
						print_message(BUG_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_handler_to_mov_obj_handler_msg", str_trial_hand_msg);
						get_mov_obj_status_type_string(*mov_obj_status, str_mov_obj_status);   
						return print_message(BUG_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_handler_to_mov_obj_handler_msg", str_mov_obj_status);
				}
				break;
			default:
				return print_message(BUG_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_handler_to_mov_obj_handler_msg", str_trial_hand_msg);
		}
	}
	return TRUE;
}
