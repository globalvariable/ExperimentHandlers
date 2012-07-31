#include "HandleMovObjInterf2MovObjHandMsgs.h"




bool handle_mov_obj_interf_to_mov_obj_handler_msg(MovObjData *mov_obj_data, MovObjStatus *mov_obj_status, TrialType mov_obj_trial_type_status, TimeStamp current_time, MovObjInterf2MovObjHandMsg *msgs_mov_obj_interf_2_mov_obj_hand, MovObjHand2MovObjDurHandMsg *msgs_mov_obj_hand_2_mov_obj_dur_hand, MovObjHand2MovObjInterfMsg *msgs_mov_obj_hand_2_mov_obj_interf, MovObjHand2TrialHandMsg *msgs_mov_obj_hand_2_trial_hand, MovObjHand2NeuralNetMsgMultiThread *msgs_mov_obj_hand_2_neural_net_multi_thread, MovObjLocationType *current_location)
{
	MovObjInterf2MovObjHandMsgItem msg_item;
	char str_mov_obj_interf_msg[MOV_OBJ_INTERF_2_MOV_OBJ_HAND_MSG_STRING_LENGTH];
	char str_mov_obj_status[MOV_OBJ_STATUS_MAX_STRING_LENGTH];
	MovObjLocationType location;
	while (get_next_mov_obj_interf_2_mov_obj_hand_msg_buffer_item(msgs_mov_obj_interf_2_mov_obj_hand, &msg_item))
	{
		get_mov_obj_interf_2_mov_obj_hand_msg_type_string(msg_item.msg_type, str_mov_obj_interf_msg);
		print_message(INFO_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_interf_to_mov_obj_handler_msg", str_mov_obj_interf_msg);
		switch (msg_item.msg_type)
		{
			case MOV_OBJ_INTERF_2_MOV_OBJ_HAND_MSG_DIRECTION_SPEED_LOCATION:	
				location = msg_item.location;
				*current_location = location;
				printf("Location: %f\n", location);
				if (! write_to_mov_obj_hand_2_neural_net_msg_buffer((*msgs_mov_obj_hand_2_neural_net_multi_thread)[0], current_time, MOV_OBJ_HAND_2_NEURAL_NET_MSG_LOCATION, location))			
					return print_message(BUG_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_interf_to_mov_obj_handler_msg", "! write_to_mov_obj_hand_2_neural_net_msg_buffer()");	
				switch (*mov_obj_status)
				{
					case MOV_OBJ_STATUS_OUT_OF_TRIAL:
						print_message(BUG_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_interf_to_mov_obj_handler_msg", str_mov_obj_interf_msg);	
						get_mov_obj_status_type_string(*mov_obj_status, str_mov_obj_status);   
						return print_message(BUG_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_interf_to_mov_obj_handler_msg", str_mov_obj_status);	
					case MOV_OBJ_STATUS_STAYING_AT_START_POINT:
						print_message(BUG_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_interf_to_mov_obj_handler_msg", str_mov_obj_interf_msg);	
						get_mov_obj_status_type_string(*mov_obj_status, str_mov_obj_status);   
						return print_message(BUG_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_interf_to_mov_obj_handler_msg", str_mov_obj_status);	
					case MOV_OBJ_STATUS_AVAILABLE_TO_CONTROL:
						switch (mov_obj_trial_type_status)
						{
							case TRIAL_TYPE_IN_VIVO_BMI_LEFT_TARGET:	// left locations are above zero
								if (location >= (+mov_obj_data->glo_constraints.current_threshold))
								{
									*mov_obj_status = MOV_OBJ_STATUS_RESETTING_TO_TARGET_POINT_W_SUCCESS;  // handle_mov_obj_handler_status handles robot to convenient target. 
									// cancel binning timer for sending commands to interfacer
									if (! write_to_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer(msgs_mov_obj_hand_2_mov_obj_dur_hand, current_time,  MOV_OBJ_HAND_2_MOV_OBJ_DUR_HAND_MSG_CANCEL_TIMER, mov_obj_data->glo_constraints.stay_at_target_duration + current_time))
										return print_message(BUG_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_interf_to_mov_obj_handler_msg", "write_to_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer().");	
									if (! write_to_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer(msgs_mov_obj_hand_2_mov_obj_dur_hand, current_time,  MOV_OBJ_HAND_2_MOV_OBJ_DUR_HAND_MSG_START_TIMER, mov_obj_data->glo_constraints.motor_command_delivery_interval + current_time))
										return print_message(BUG_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_interf_to_mov_obj_handler_msg", "write_to_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer().");	
									if (! write_to_mov_obj_hand_2_mov_obj_interf_msg_buffer(msgs_mov_obj_hand_2_mov_obj_interf, current_time, MOV_OBJ_HAND_2_MOV_OBJ_INTERF_SET_DIRECTION_SPEED_LOCATION, ONE_D_ACTUATOR, MOV_OBJ_DIRECTION_LEFT, NEURONS_MOTOR_OUTPUT_MOTOR_SPEED, MOV_OBJ_LOCATION_NULL))
										return print_message(BUG_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_interf_to_mov_obj_handler_msg", "write_to_mov_obj_hand_2_mov_obj_interf_msg_buffer().");	
									mov_obj_data->main_stats.trajectory_success_ratio = mov_obj_data->main_stats.trajectory_success/mov_obj_data->main_stats.num_of_actions;
									if (! write_to_mov_obj_hand_2_trial_hand_msg_buffer(msgs_mov_obj_hand_2_trial_hand, current_time,  MOV_OBJ_HAND_2_TRIAL_HAND_TRAJECTORY_SUCCESS_RATIO, mov_obj_data->main_stats.trajectory_success_ratio))  // sending it before trial ends for being used to update synaptic weights..  send it before MOV_OBJ_HAND_2_TRIAL_HAND_THRESHOLD_REACHED
										return print_message(BUG_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_interf_to_mov_obj_handler_msg", "write_to_mov_obj_hand_2_trial_hand_msg_buffer().");
									if (! write_to_mov_obj_hand_2_trial_hand_msg_buffer(msgs_mov_obj_hand_2_trial_hand, current_time, MOV_OBJ_HAND_2_TRIAL_HAND_THRESHOLD_REACHED, 0))
										return print_message(BUG_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_interf_to_mov_obj_handler_msg", "write_to_mov_obj_hand_2_trial_hand_msg_buffer().");

								}	
								break;
							case TRIAL_TYPE_IN_VIVO_BMI_RIGHT_TARGET:  // right locations are below zero
								if (location <= (-mov_obj_data->glo_constraints.current_threshold))
								{
									*mov_obj_status = MOV_OBJ_STATUS_RESETTING_TO_TARGET_POINT_W_SUCCESS; // handle_mov_obj_handler_status handles robot to convenient target. 
									// cancel binning timer for sending commands to interfacer
									if (! write_to_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer(msgs_mov_obj_hand_2_mov_obj_dur_hand, current_time,  MOV_OBJ_HAND_2_MOV_OBJ_DUR_HAND_MSG_CANCEL_TIMER, 0))
										return print_message(BUG_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_interf_to_mov_obj_handler_msg", "write_to_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer().");	
									if (! write_to_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer(msgs_mov_obj_hand_2_mov_obj_dur_hand, current_time,  MOV_OBJ_HAND_2_MOV_OBJ_DUR_HAND_MSG_START_TIMER, mov_obj_data->glo_constraints.motor_command_delivery_interval + current_time))
										return print_message(BUG_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_interf_to_mov_obj_handler_msg", "write_to_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer().");	// set interval to reset position to target
									if (! write_to_mov_obj_hand_2_mov_obj_interf_msg_buffer(msgs_mov_obj_hand_2_mov_obj_interf, current_time, MOV_OBJ_HAND_2_MOV_OBJ_INTERF_SET_DIRECTION_SPEED_LOCATION, ONE_D_ACTUATOR, MOV_OBJ_DIRECTION_RIGHT, NEURONS_MOTOR_OUTPUT_MOTOR_SPEED, MOV_OBJ_LOCATION_NULL))
										return print_message(BUG_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_interf_to_mov_obj_handler_msg", "write_to_mov_obj_hand_2_mov_obj_interf_msg_buffer().");	
									mov_obj_data->main_stats.trajectory_success_ratio = mov_obj_data->main_stats.trajectory_success/mov_obj_data->main_stats.num_of_actions;
									if (! write_to_mov_obj_hand_2_trial_hand_msg_buffer(msgs_mov_obj_hand_2_trial_hand, current_time,  MOV_OBJ_HAND_2_TRIAL_HAND_TRAJECTORY_SUCCESS_RATIO, mov_obj_data->main_stats.trajectory_success_ratio))  // sending it before trial ends for being used to update synaptic weights.. send it before MOV_OBJ_HAND_2_TRIAL_HAND_THRESHOLD_REACHED
										return print_message(BUG_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_interf_to_mov_obj_handler_msg", "write_to_mov_obj_hand_2_trial_hand_msg_buffer().");
									if (! write_to_mov_obj_hand_2_trial_hand_msg_buffer(msgs_mov_obj_hand_2_trial_hand, current_time, MOV_OBJ_HAND_2_TRIAL_HAND_THRESHOLD_REACHED, 0))
										return print_message(BUG_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_interf_to_mov_obj_handler_msg", "write_to_mov_obj_hand_2_trial_hand_msg_buffer().");

								}	
								break;
							default:
								print_message(BUG_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_interf_to_mov_obj_handler_msg", str_mov_obj_interf_msg);	
								get_mov_obj_status_type_string(*mov_obj_status, str_mov_obj_status);   
								print_message(BUG_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_interf_to_mov_obj_handler_msg", str_mov_obj_status);	
								return print_message(BUG_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_interf_to_mov_obj_handler_msg", "switch (mov_obj_trial_type_status)");	
						}
						break;
					case MOV_OBJ_STATUS_RESETTING_TO_TARGET_POINT_W_FAIL:
						if (( (MovObjLocationType) (fabs(location)) ) == mov_obj_data->glo_constraints.target_location)
						{
							*mov_obj_status = MOV_OBJ_STATUS_REACHED_TARGET_POINT_W_FAIL;
							if (! write_to_mov_obj_hand_2_mov_obj_interf_msg_buffer(msgs_mov_obj_hand_2_mov_obj_interf, current_time, MOV_OBJ_HAND_2_MOV_OBJ_INTERF_SET_DIRECTION_SPEED_LOCATION, ONE_D_ACTUATOR, MOV_OBJ_DIRECTION_STATIONARY, MOV_OBJ_SPEED_NULL, MOV_OBJ_LOCATION_NULL))
								return print_message(BUG_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_interf_to_mov_obj_handler_msg", "write_to_mov_obj_hand_2_mov_obj_interf_msg_buffer().");	//////   TO CLEAR THE MOVEMENT COMMAND PREVIOUSLY SENT BY HandleMovObjHandStatus module, FirstBMICageManager keep previous command in mind. 
							if (! write_to_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer(msgs_mov_obj_hand_2_mov_obj_dur_hand, current_time,  MOV_OBJ_HAND_2_MOV_OBJ_DUR_HAND_MSG_CANCEL_TIMER, 0))
								return print_message(BUG_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_interf_to_mov_obj_handler_msg", "write_to_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer().");	
							if (! write_to_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer(msgs_mov_obj_hand_2_mov_obj_dur_hand, current_time, MOV_OBJ_HAND_2_MOV_OBJ_DUR_HAND_MSG_START_TIMER, mov_obj_data->glo_constraints.stay_at_target_duration + current_time))
								return print_message(BUG_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_interf_to_mov_obj_handler_msg", "write_to_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer().");
						} 
						break;
					case MOV_OBJ_STATUS_RESETTING_TO_TARGET_POINT_W_SUCCESS:
						if (( (MovObjLocationType) (fabs(location)) ) == mov_obj_data->glo_constraints.target_location)
						{
							*mov_obj_status = MOV_OBJ_STATUS_REACHED_TARGET_POINT_W_SUCCESS;
							if (! write_to_mov_obj_hand_2_mov_obj_interf_msg_buffer(msgs_mov_obj_hand_2_mov_obj_interf, current_time, MOV_OBJ_HAND_2_MOV_OBJ_INTERF_SET_DIRECTION_SPEED_LOCATION, ONE_D_ACTUATOR, MOV_OBJ_DIRECTION_STATIONARY, MOV_OBJ_SPEED_NULL, MOV_OBJ_LOCATION_NULL))
								return print_message(BUG_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_interf_to_mov_obj_handler_msg", "write_to_mov_obj_hand_2_mov_obj_interf_msg_buffer().");	//////   TO CLEAR THE MOVEMENT COMMAND PREVIOUSLY SENT BY HandleMovObjHandStatus module, FirstBMICageManager keep previous command in mind. 
							if (! write_to_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer(msgs_mov_obj_hand_2_mov_obj_dur_hand, current_time,  MOV_OBJ_HAND_2_MOV_OBJ_DUR_HAND_MSG_CANCEL_TIMER, 0))
								return print_message(BUG_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_interf_to_mov_obj_handler_msg", "write_to_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer().");	
							if (! write_to_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer(msgs_mov_obj_hand_2_mov_obj_dur_hand, current_time, MOV_OBJ_HAND_2_MOV_OBJ_DUR_HAND_MSG_START_TIMER, mov_obj_data->glo_constraints.stay_at_target_duration + current_time))
								return print_message(BUG_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_interf_to_mov_obj_handler_msg", "write_to_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer().");
						} 
						break;
					case MOV_OBJ_STATUS_REACHED_TARGET_POINT_W_FAIL:
						print_message(BUG_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_interf_to_mov_obj_handler_msg", str_mov_obj_interf_msg);	
						get_mov_obj_status_type_string(*mov_obj_status, str_mov_obj_status);   
						return print_message(BUG_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_interf_to_mov_obj_handler_msg", str_mov_obj_status);
					case MOV_OBJ_STATUS_REACHED_TARGET_POINT_W_SUCCESS:
						print_message(BUG_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_interf_to_mov_obj_handler_msg", str_mov_obj_interf_msg);	
						get_mov_obj_status_type_string(*mov_obj_status, str_mov_obj_status);   
						return print_message(BUG_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_interf_to_mov_obj_handler_msg", str_mov_obj_status);
					case MOV_OBJ_STATUS_RESETTING_TO_START_POINT:
						if (location == 0)
						{
							*mov_obj_status = MOV_OBJ_STATUS_OUT_OF_TRIAL;
						} 
						break;
					default:
						print_message(BUG_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_interf_to_mov_obj_handler_msg", str_mov_obj_interf_msg);
						get_mov_obj_status_type_string(*mov_obj_status, str_mov_obj_status);   
						return print_message(BUG_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_interf_to_mov_obj_handler_msg", str_mov_obj_status);
				}
				break;
			default:
				return print_message(BUG_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_interf_to_mov_obj_handler_msg", str_mov_obj_interf_msg);
		}
	}

	return TRUE;
}
