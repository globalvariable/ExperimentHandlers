#include "HandleMovObjDurHand2MovObjHandMsgs.h"


#define NEURONS_MOTOR_OUTPUT_MOTOR_SPEED 4.0

bool handle_mov_obj_dur_handler_to_mov_obj_handler_msg(MovObjData *mov_obj_data, MovObjStatus *mov_obj_status, TimeStamp current_time, MovObjDurHand2MovObjHandMsg *msgs_mov_obj_dur_hand_2_mov_obj_hand, MovObjHand2TrialHandMsg *msgs_mov_obj_hand_2_trial_hand, MovObjHand2MovObjDurHandMsg *msgs_mov_obj_hand_2_mov_obj_dur_hand, unsigned int *left_layer_spike_counter, unsigned int *right_layer_spike_counter, MovObjHand2MovObjInterfMsg *msgs_mov_obj_hand_2_mov_obj_interf)
{
	MovObjDurHand2MovObjHandMsgItem *msg_item;
	char str_mov_obj_dur_msg[MOV_OBJ_DUR_HAND_2_MOV_OBJ_HAND_MSG_STRING_LENGTH];
	char str_mov_obj_status[MOV_OBJ_STATUS_MAX_STRING_LENGTH];
	while (get_next_mov_obj_dur_hand_2_mov_obj_hand_msg_buffer_item(msgs_mov_obj_dur_hand_2_mov_obj_hand, &msg_item))
	{
		get_mov_obj_dur_hand_2_mov_obj_hand_msg_type_string(msg_item->msg_type, str_mov_obj_dur_msg);
		print_message(INFO_MSG ,"MovObjHandler", "HandleMovObjDurHand2MovObjHandMsgs", "handle_mov_obj_dur_handler_to_mov_obj_handler_msg", str_mov_obj_dur_msg);
		switch (msg_item->msg_type)
		{
			case MOV_OBJ_DUR_HAND_2_MOV_OBJ_HAND_MSG_TIMEOUT:	
				switch (*mov_obj_status)
				{
					case MOV_OBJ_STATUS_OUT_OF_TRIAL:
						print_message(BUG_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_dur_handler_to_mov_obj_handler_msg", str_mov_obj_dur_msg);	
						get_mov_obj_status_type_string(*mov_obj_status, str_mov_obj_status);   
						return print_message(BUG_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_dur_handler_to_mov_obj_handler_msg", str_mov_obj_status);	
					case MOV_OBJ_STATUS_STAYING_AT_START_POINT:
						*mov_obj_status = MOV_OBJ_STATUS_AVAILABLE_TO_CONTROL;
						if (! write_to_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer(msgs_mov_obj_hand_2_mov_obj_dur_hand, current_time,  MOV_OBJ_HAND_2_MOV_OBJ_DUR_HAND_MSG_START_TIMER, mov_obj_data->glo_constraints.motor_command_delivery_interval + current_time))
							return print_message(BUG_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_dur_handler_to_mov_obj_handler_msg", "write_to_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer().");	
						break;
					case MOV_OBJ_STATUS_AVAILABLE_TO_CONTROL:	// binning timeout
						if (! write_to_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer(msgs_mov_obj_hand_2_mov_obj_dur_hand, current_time,  MOV_OBJ_HAND_2_MOV_OBJ_DUR_HAND_MSG_START_TIMER, mov_obj_data->glo_constraints.motor_command_delivery_interval + current_time))
							return print_message(BUG_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_dur_handler_to_mov_obj_handler_msg", "write_to_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer().");
						if ((*left_layer_spike_counter) > (*right_layer_spike_counter))
						{
							*left_layer_spike_counter = 0;
							*right_layer_spike_counter = 0;
							if (! write_to_mov_obj_hand_2_mov_obj_interf_msg_buffer(msgs_mov_obj_hand_2_mov_obj_interf, current_time, MOV_OBJ_HAND_2_MOV_OBJ_INTERF_SET_DIRECTION_SPEED_LOCATION,  0, MOV_OBJ_DIRECTION_LEFT, NEURONS_MOTOR_OUTPUT_MOTOR_SPEED, MOV_OBJ_LOCATION_NULL))
								print_message(ERROR_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_dur_handler_to_mov_obj_handler_msg","! write_to_mov_obj_hand_2_mov_obj_interf_msg_buffer()."); 
						}
						else if  ((*left_layer_spike_counter) < (*right_layer_spike_counter))
						{
							*left_layer_spike_counter = 0;
							*right_layer_spike_counter = 0;
							if (! write_to_mov_obj_hand_2_mov_obj_interf_msg_buffer(msgs_mov_obj_hand_2_mov_obj_interf, current_time, MOV_OBJ_HAND_2_MOV_OBJ_INTERF_SET_DIRECTION_SPEED_LOCATION,  0, MOV_OBJ_DIRECTION_RIGHT, NEURONS_MOTOR_OUTPUT_MOTOR_SPEED, MOV_OBJ_LOCATION_NULL))
								print_message(ERROR_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_dur_handler_to_mov_obj_handler_msg","! write_to_mov_obj_hand_2_mov_obj_interf_msg_buffer()."); 
						}
						else
						{
							*left_layer_spike_counter = 0;
							*right_layer_spike_counter = 0;
							if (! write_to_mov_obj_hand_2_mov_obj_interf_msg_buffer(msgs_mov_obj_hand_2_mov_obj_interf, current_time, MOV_OBJ_HAND_2_MOV_OBJ_INTERF_SET_DIRECTION_SPEED_LOCATION,  0, MOV_OBJ_DIRECTION_STATIONARY, MOV_OBJ_SPEED_NULL, MOV_OBJ_LOCATION_NULL))
								print_message(ERROR_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_dur_handler_to_mov_obj_handler_msg","! write_to_mov_obj_hand_2_mov_obj_interf_msg_buffer()."); 
						}
						break;
					case MOV_OBJ_STATUS_RESETTING_TO_TARGET_POINT_W_FAIL:
						print_message(BUG_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_interfler_to_mov_obj_handler_msg", str_mov_obj_dur_msg);	
						get_mov_obj_status_type_string(*mov_obj_status, str_mov_obj_status);   
						return print_message(BUG_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_interfler_to_mov_obj_handler_msg", str_mov_obj_status);	
					case MOV_OBJ_STATUS_RESETTING_TO_TARGET_POINT_W_SUCCESS:
						print_message(BUG_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_interfler_to_mov_obj_handler_msg", str_mov_obj_dur_msg);	
						get_mov_obj_status_type_string(*mov_obj_status, str_mov_obj_status);   
						return print_message(BUG_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_interfler_to_mov_obj_handler_msg", str_mov_obj_status);	
					case MOV_OBJ_STATUS_REACHED_TARGET_POINT_W_FAIL:
					//	*mov_obj_status = MOV_OBJ_STATUS_RESETTING_TO_START_POINT;   // TRIAL_HAND_2_MOV_OBJ_HAND_MSG_END_TRIAL changes status this way in trialhand2movobj handler
						if (! write_to_mov_obj_hand_2_trial_hand_msg_buffer(msgs_mov_obj_hand_2_trial_hand, current_time,  MOV_OBJ_HAND_2_TRIAL_HAND_MSG_PUNISHMENT_REQUEST, 0))
							return print_message(BUG_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_interfler_to_mov_obj_handler_msg", "write_to_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer().");	
						if (! write_to_mov_obj_hand_2_trial_hand_msg_buffer(msgs_mov_obj_hand_2_trial_hand, current_time,  MOV_OBJ_HAND_2_TRIAL_HAND_MSG_END_TRIAL_REQUEST, 0))
							return print_message(BUG_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_interfler_to_mov_obj_handler_msg", "write_to_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer().");	
						break;
					case MOV_OBJ_STATUS_REACHED_TARGET_POINT_W_SUCCESS:
					//	*mov_obj_status = MOV_OBJ_STATUS_RESETTING_TO_START_POINT;   // TRIAL_HAND_2_MOV_OBJ_HAND_MSG_END_TRIAL changes status this way in trialhand2movobj handler
						if (! write_to_mov_obj_hand_2_trial_hand_msg_buffer(msgs_mov_obj_hand_2_trial_hand, current_time,  MOV_OBJ_HAND_2_TRIAL_HAND_MSG_REWARD_REQUEST, 0))
							return print_message(BUG_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_interfler_to_mov_obj_handler_msg", "write_to_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer().");	
						if (! write_to_mov_obj_hand_2_trial_hand_msg_buffer(msgs_mov_obj_hand_2_trial_hand, current_time,  MOV_OBJ_HAND_2_TRIAL_HAND_MSG_END_TRIAL_REQUEST, 0))
							return print_message(BUG_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_interfler_to_mov_obj_handler_msg", "write_to_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer().");	
						break;
					case MOV_OBJ_STATUS_RESETTING_TO_START_POINT:
						print_message(BUG_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_interfler_to_mov_obj_handler_msg", str_mov_obj_dur_msg);	
						get_mov_obj_status_type_string(*mov_obj_status, str_mov_obj_status);   
						return print_message(BUG_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_interfler_to_mov_obj_handler_msg", str_mov_obj_status);	
					default:
						print_message(BUG_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_interfler_to_mov_obj_handler_msg", str_mov_obj_dur_msg);
						get_mov_obj_status_type_string(*mov_obj_status, str_mov_obj_status);   
						return print_message(BUG_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_interfler_to_mov_obj_handler_msg", str_mov_obj_status);
				}
				break;
			default:
				return print_message(BUG_MSG ,"MovObjHandler", "HandleMovObjDurHand2MovObjHandMsgs", "handle_mov_obj_dur_handler_to_mov_obj_handler_msg", str_mov_obj_dur_msg);
		}
	}

	return TRUE;
}
