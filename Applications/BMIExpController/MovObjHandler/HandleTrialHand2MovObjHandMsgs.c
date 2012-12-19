#include "HandleTrialHand2MovObjHandMsgs.h"



bool handle_trial_handler_to_mov_obj_handler_msg(ThreeDofRobot *robot_arm, MovObjStatus *mov_obj_status, TimeStamp current_time, TrialHand2MovObjHandMsg *msgs_trial_hand_2_mov_obj_hand, MovObjHand2MovObjDurHandMsg *msgs_mov_obj_hand_2_mov_obj_dur_hand, MovObjHand2TrialHandMsg *msgs_mov_obj_hand_2_trial_hand, MovObjHandParadigmRobotReach *mov_obj_paradigm, MessageLogBuffer *message_log)
{
	TrialHand2MovObjHandMsgItem msg_item;
	char str_trial_hand_msg[TRIAL_HAND_2_MOV_OBJ_HAND_MSG_STRING_LENGTH];
	char str_mov_obj_status[MOV_OBJ_STATUS_MAX_STRING_LENGTH];
	MovObjHand2MovObjDurHandMsgAdditional mov_obj_hand_2_mov_obj_dur_hand_additional_data;
	while (get_next_trial_hand_2_mov_obj_hand_msg_buffer_item(msgs_trial_hand_2_mov_obj_hand, &msg_item))
	{
		get_trial_hand_2_mov_obj_hand_msg_type_string(msg_item.msg_type, str_trial_hand_msg);
		if (! write_to_message_log_buffer(message_log, INFO_MSG, current_time, "MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_handler_to_mov_obj_handler_msg", str_trial_hand_msg))
			print_message(ERROR_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_handler_to_mov_obj_handler_msg", "! write_to_message_log_buffer()");
		switch (msg_item.msg_type)
		{
			case TRIAL_HAND_2_MOV_OBJ_HAND_MSG_START_TRIAL:	
				switch (*mov_obj_status)
				{
					case MOV_OBJ_STATUS_OUT_OF_TRIAL:
						mov_obj_paradigm->move_to_target_position_pulse.pulse[0] = msg_item.additional_data.move_to_target_position_pulse.pulse[0];
						mov_obj_paradigm->move_to_target_position_pulse.pulse[1] = msg_item.additional_data.move_to_target_position_pulse.pulse[1];
						mov_obj_paradigm->move_to_target_position_pulse.pulse[2] = msg_item.additional_data.move_to_target_position_pulse.pulse[2];

						*mov_obj_status = MOV_OBJ_STATUS_STAYING_AT_START_POINT;
						mov_obj_hand_2_mov_obj_dur_hand_additional_data.schedule.schedule = current_time + mov_obj_paradigm->stay_at_start_duration;
						mov_obj_hand_2_mov_obj_dur_hand_additional_data.schedule.item_idx = MOV_OBJ_DUR_STATUS_ITEM_STAY_AT_CURRENT_POSITION;
						if (! write_to_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer(msgs_mov_obj_hand_2_mov_obj_dur_hand, current_time,  MOV_OBJ_HAND_2_MOV_OBJ_DUR_HAND_MSG_SET_SCHEDULE, mov_obj_hand_2_mov_obj_dur_hand_additional_data))
							return print_message(BUG_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_hand_to_mov_obj_handler_msg", "write_to_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer().");	
						break;
					case MOV_OBJ_STATUS_STAYING_AT_START_POINT:
						print_message(BUG_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_handler_to_mov_obj_handler_msg", str_trial_hand_msg);	
						get_mov_obj_status_type_string(*mov_obj_status, str_mov_obj_status);   
						return print_message(BUG_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_handler_to_mov_obj_handler_msg", str_mov_obj_status);	
					case MOV_OBJ_STATUS_AVAILABLE_TO_CONTROL:
						print_message(BUG_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_handler_to_mov_obj_handler_msg", str_trial_hand_msg);	
						get_mov_obj_status_type_string(*mov_obj_status, str_mov_obj_status);   
						return print_message(BUG_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_handler_to_mov_obj_handler_msg", str_mov_obj_status);	
					case MOV_OBJ_STATUS_RESETTING_TO_TARGET_POINT:
						print_message(BUG_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_handler_to_mov_obj_handler_msg", str_trial_hand_msg);	
						get_mov_obj_status_type_string(*mov_obj_status, str_mov_obj_status);   
						return print_message(BUG_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_handler_to_mov_obj_handler_msg", str_mov_obj_status);
					case MOV_OBJ_STATUS_REACHED_TARGET_POINT:
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
						*mov_obj_status = MOV_OBJ_STATUS_RESETTING_TO_TARGET_POINT; 
						break;
					case MOV_OBJ_STATUS_RESETTING_TO_TARGET_POINT:
						print_message(BUG_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_handler_to_mov_obj_handler_msg", str_trial_hand_msg);	
						get_mov_obj_status_type_string(*mov_obj_status, str_mov_obj_status);   
						return print_message(BUG_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_handler_to_mov_obj_handler_msg", str_mov_obj_status);
					case MOV_OBJ_STATUS_REACHED_TARGET_POINT:
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
					case MOV_OBJ_STATUS_RESETTING_TO_TARGET_POINT: // should have gone to target already to receive such message
						print_message(BUG_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_handler_to_mov_obj_handler_msg", str_trial_hand_msg);	
						get_mov_obj_status_type_string(*mov_obj_status, str_mov_obj_status);   
						return print_message(BUG_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_handler_to_mov_obj_handler_msg", str_mov_obj_status);
					case MOV_OBJ_STATUS_REACHED_TARGET_POINT:
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
