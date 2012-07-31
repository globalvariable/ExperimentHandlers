#include "HandleMovObjDurHand2MovObjHandMsgs.h"


bool handle_mov_obj_dur_handler_to_mov_obj_handler_msg(MovObjData *mov_obj_data, MovObjStatus *mov_obj_status, TrialType mov_obj_trial_type_status, TimeStamp current_time, MovObjDurHand2MovObjHandMsg *msgs_mov_obj_dur_hand_2_mov_obj_hand, MovObjHand2TrialHandMsg *msgs_mov_obj_hand_2_trial_hand, MovObjHand2MovObjDurHandMsg *msgs_mov_obj_hand_2_mov_obj_dur_hand, MovObjHand2MovObjInterfMsg *msgs_mov_obj_hand_2_mov_obj_interf, MovObjHand2NeuralNetMsgMultiThread *msgs_mov_obj_hand_2_neural_net_multi_thread, SpikeData *scheduled_spike_data, MovObjLocationType current_location)
{
	MovObjDurHand2MovObjHandMsgItem msg_item;
	char str_mov_obj_dur_msg[MOV_OBJ_DUR_HAND_2_MOV_OBJ_HAND_MSG_STRING_LENGTH];
	char str_mov_obj_status[MOV_OBJ_STATUS_MAX_STRING_LENGTH];
	while (get_next_mov_obj_dur_hand_2_mov_obj_hand_msg_buffer_item(msgs_mov_obj_dur_hand_2_mov_obj_hand, &msg_item))
	{
		get_mov_obj_dur_hand_2_mov_obj_hand_msg_type_string(msg_item.msg_type, str_mov_obj_dur_msg);
		print_message(INFO_MSG ,"MovObjHandler", "HandleMovObjDurHand2MovObjHandMsgs", "handle_mov_obj_dur_handler_to_mov_obj_handler_msg", str_mov_obj_dur_msg);
		switch (msg_item.msg_type)
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
							return print_message(ERROR_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_dur_handler_to_mov_obj_handler_msg", "write_to_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer().");	
						if (! write_to_mov_obj_hand_2_neural_net_msg_buffer((*msgs_mov_obj_hand_2_neural_net_multi_thread)[0], current_time, MOV_OBJ_HAND_2_NEURAL_NET_MSG_LOCATION, 0))			
							return print_message(ERROR_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_dur_handler_to_mov_obj_handler_msg", "write_to_mov_obj_hand_2_neural_net_msg_buffer().");	
						break;
					case MOV_OBJ_STATUS_AVAILABLE_TO_CONTROL:	// binning timeout
						if (! write_to_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer(msgs_mov_obj_hand_2_mov_obj_dur_hand, current_time,  MOV_OBJ_HAND_2_MOV_OBJ_DUR_HAND_MSG_START_TIMER, mov_obj_data->glo_constraints.motor_command_delivery_interval + current_time))
							return print_message(ERROR_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_dur_handler_to_mov_obj_handler_msg", "write_to_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer().");
						if (! handle_spike_data_buff_for_bin(mov_obj_data, scheduled_spike_data, current_time, msgs_mov_obj_hand_2_mov_obj_interf, mov_obj_trial_type_status, current_location))
							return print_message(ERROR_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_dur_handler_to_mov_obj_handler_msg", "handle_spike_data_buff_for_bin().");
						break;
					case MOV_OBJ_STATUS_RESETTING_TO_TARGET_POINT_W_FAIL:
						switch (mov_obj_trial_type_status)
						{
							case TRIAL_TYPE_IN_VIVO_BMI_LEFT_TARGET:	// left locations are below zero
								if (! write_to_mov_obj_hand_2_mov_obj_interf_msg_buffer(msgs_mov_obj_hand_2_mov_obj_interf, current_time, MOV_OBJ_HAND_2_MOV_OBJ_INTERF_SET_DIRECTION_SPEED_LOCATION, ONE_D_ACTUATOR, MOV_OBJ_DIRECTION_LEFT, MOV_OBJ_RESETING_SPEED, MOV_OBJ_LOCATION_NULL))
									return print_message(ERROR_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_dur_handler_to_mov_obj_handler_msg","! write_to_mov_obj_hand_2_mov_obj_interf_msg_buffer().");	
								if (! write_to_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer(msgs_mov_obj_hand_2_mov_obj_dur_hand, current_time,  MOV_OBJ_HAND_2_MOV_OBJ_DUR_HAND_MSG_START_TIMER, mov_obj_data->glo_constraints.motor_command_delivery_interval + current_time))
									return print_message(ERROR_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_dur_handler_to_mov_obj_handler_msg", "write_to_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer().");
								break;
							case TRIAL_TYPE_IN_VIVO_BMI_RIGHT_TARGET:  // right locations are above zero
								if (! write_to_mov_obj_hand_2_mov_obj_interf_msg_buffer(msgs_mov_obj_hand_2_mov_obj_interf, current_time, MOV_OBJ_HAND_2_MOV_OBJ_INTERF_SET_DIRECTION_SPEED_LOCATION, ONE_D_ACTUATOR, MOV_OBJ_DIRECTION_RIGHT, MOV_OBJ_RESETING_SPEED, MOV_OBJ_LOCATION_NULL))
									return print_message(ERROR_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_dur_handler_to_mov_obj_handler_msg","! write_to_mov_obj_hand_2_mov_obj_interf_msg_buffer().");
								if (! write_to_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer(msgs_mov_obj_hand_2_mov_obj_dur_hand, current_time,  MOV_OBJ_HAND_2_MOV_OBJ_DUR_HAND_MSG_START_TIMER, mov_obj_data->glo_constraints.motor_command_delivery_interval + current_time))
									return print_message(ERROR_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_dur_handler_to_mov_obj_handler_msg", "write_to_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer().");	
								break;
							default:
								get_mov_obj_status_type_string(*mov_obj_status, str_mov_obj_status);   
								return print_message(BUG_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_dur_handler_to_mov_obj_handler_msg", str_mov_obj_status);	
						}
						break;		// do not send any movement command now. handle_mov_obj_handler_status will handle this status
					case MOV_OBJ_STATUS_RESETTING_TO_TARGET_POINT_W_SUCCESS:
						switch (mov_obj_trial_type_status)
						{
							case TRIAL_TYPE_IN_VIVO_BMI_LEFT_TARGET:	// left locations are below zero
								if (! write_to_mov_obj_hand_2_mov_obj_interf_msg_buffer(msgs_mov_obj_hand_2_mov_obj_interf, current_time, MOV_OBJ_HAND_2_MOV_OBJ_INTERF_SET_DIRECTION_SPEED_LOCATION, ONE_D_ACTUATOR, MOV_OBJ_DIRECTION_LEFT, MOV_OBJ_RESETING_SPEED, MOV_OBJ_LOCATION_NULL))
									return print_message(ERROR_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_dur_handler_to_mov_obj_handler_msg","! write_to_mov_obj_hand_2_mov_obj_interf_msg_buffer().");	
								if (! write_to_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer(msgs_mov_obj_hand_2_mov_obj_dur_hand, current_time,  MOV_OBJ_HAND_2_MOV_OBJ_DUR_HAND_MSG_START_TIMER, mov_obj_data->glo_constraints.motor_command_delivery_interval + current_time))
									return print_message(ERROR_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_dur_handler_to_mov_obj_handler_msg", "write_to_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer().");
								break;
							case TRIAL_TYPE_IN_VIVO_BMI_RIGHT_TARGET:  // right locations are above zero
								if (! write_to_mov_obj_hand_2_mov_obj_interf_msg_buffer(msgs_mov_obj_hand_2_mov_obj_interf, current_time, MOV_OBJ_HAND_2_MOV_OBJ_INTERF_SET_DIRECTION_SPEED_LOCATION, ONE_D_ACTUATOR, MOV_OBJ_DIRECTION_RIGHT, MOV_OBJ_RESETING_SPEED, MOV_OBJ_LOCATION_NULL))
									return print_message(ERROR_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_dur_handler_to_mov_obj_handler_msg","! write_to_mov_obj_hand_2_mov_obj_interf_msg_buffer().");
								if (! write_to_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer(msgs_mov_obj_hand_2_mov_obj_dur_hand, current_time,  MOV_OBJ_HAND_2_MOV_OBJ_DUR_HAND_MSG_START_TIMER, mov_obj_data->glo_constraints.motor_command_delivery_interval + current_time))
									return print_message(ERROR_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_dur_handler_to_mov_obj_handler_msg", "write_to_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer().");	
								break;
							default:
								get_mov_obj_status_type_string(*mov_obj_status, str_mov_obj_status);   
								return print_message(BUG_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_dur_handler_to_mov_obj_handler_msg", str_mov_obj_status);	
						}
						break;		// do not send any movement command now.
					case MOV_OBJ_STATUS_REACHED_TARGET_POINT_W_FAIL:
					//	*mov_obj_status = MOV_OBJ_STATUS_RESETTING_TO_START_POINT;   // TRIAL_HAND_2_MOV_OBJ_HAND_MSG_END_TRIAL changes status this way in trialhand2movobj handler
						if (! write_to_mov_obj_hand_2_trial_hand_msg_buffer(msgs_mov_obj_hand_2_trial_hand, current_time,  MOV_OBJ_HAND_2_TRIAL_HAND_MSG_PUNISHMENT_REQUEST, 0))
							return print_message(ERROR_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_interfler_to_mov_obj_handler_msg", "write_to_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer().");	
						if (! write_to_mov_obj_hand_2_trial_hand_msg_buffer(msgs_mov_obj_hand_2_trial_hand, current_time,  MOV_OBJ_HAND_2_TRIAL_HAND_MSG_END_TRIAL_REQUEST, 0))
							return print_message(ERROR_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_interfler_to_mov_obj_handler_msg", "write_to_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer().");	
						break;
					case MOV_OBJ_STATUS_REACHED_TARGET_POINT_W_SUCCESS:
					//	*mov_obj_status = MOV_OBJ_STATUS_RESETTING_TO_START_POINT;   // TRIAL_HAND_2_MOV_OBJ_HAND_MSG_END_TRIAL changes status this way in trialhand2movobj handler,
						if (! write_to_mov_obj_hand_2_trial_hand_msg_buffer(msgs_mov_obj_hand_2_trial_hand, current_time,  MOV_OBJ_HAND_2_TRIAL_HAND_MSG_REWARD_REQUEST, 0))
							return print_message(ERROR_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_interfler_to_mov_obj_handler_msg", "write_to_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer().");	
						if (! write_to_mov_obj_hand_2_trial_hand_msg_buffer(msgs_mov_obj_hand_2_trial_hand, current_time,  MOV_OBJ_HAND_2_TRIAL_HAND_MSG_END_TRIAL_REQUEST, 0))
							return print_message(ERROR_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_interfler_to_mov_obj_handler_msg", "write_to_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer().");	
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
