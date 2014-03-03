#include "HandleTrialHand2MovObjHandMsgs.h"



bool handle_trial_handler_to_mov_obj_handler_msg(ThreeDofRobot *robot_arm, MovObjStatus *mov_obj_status, TimeStamp current_time, TrialHand2MovObjHandMsg *msgs_trial_hand_2_mov_obj_hand, MovObjHand2MovObjDurHandMsg *msgs_mov_obj_hand_2_mov_obj_dur_hand, MovObjHand2TrialHandMsg *msgs_mov_obj_hand_2_trial_hand, MovObjHandParadigmRobotReach *mov_obj_paradigm, MessageLogBuffer *message_log, MovObjStatusHistory* mov_obj_status_history, MovObjHand2GuiMsg *msgs_mov_obj_hand_2_gui)
{
	TrialHand2MovObjHandMsgItem msg_item;
	char str_trial_hand_msg[TRIAL_HAND_2_MOV_OBJ_HAND_MSG_STRING_LENGTH];
	char str_mov_obj_status[MOV_OBJ_STATUS_MAX_STRING_LENGTH];
	double speed;
	unsigned int recording_number;

	CartesianCoordinates	*target_coordinates;
	CartesianCoordinates	*start_coordinates;
	ThreeDofRobotPosition	*tip_position;

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
						*mov_obj_status = MOV_OBJ_STATUS_RESETTING_TO_TARGET_POINT;
						mov_obj_paradigm->target_info.selected_position_idx = msg_item.additional_data.robot_target_position_idx;  
						speed = ((mov_obj_paradigm->servo_pw_change_rate_for_position_reset_max - mov_obj_paradigm->servo_pw_change_rate_for_position_reset_min)* get_rand_number()) + mov_obj_paradigm->servo_pw_change_rate_for_position_reset_min;
						submit_servo_target(&(robot_arm->servos[BASE_SERVO]), mov_obj_paradigm->target_info.robot_pulse_widths[mov_obj_paradigm->target_info.selected_position_idx].pulse[BASE_SERVO], speed);
						speed = ((mov_obj_paradigm->servo_pw_change_rate_for_position_reset_max - mov_obj_paradigm->servo_pw_change_rate_for_position_reset_min)* get_rand_number()) + mov_obj_paradigm->servo_pw_change_rate_for_position_reset_min;
						submit_servo_target(&(robot_arm->servos[SHOULDER_SERVO]), mov_obj_paradigm->target_info.robot_pulse_widths[mov_obj_paradigm->target_info.selected_position_idx].pulse[SHOULDER_SERVO], speed);
						speed = ((mov_obj_paradigm->servo_pw_change_rate_for_position_reset_max - mov_obj_paradigm->servo_pw_change_rate_for_position_reset_min)* get_rand_number()) + mov_obj_paradigm->servo_pw_change_rate_for_position_reset_min;
						submit_servo_target(&(robot_arm->servos[ELBOW_SERVO]), mov_obj_paradigm->target_info.robot_pulse_widths[mov_obj_paradigm->target_info.selected_position_idx].pulse[ELBOW_SERVO], speed);	
						if (! write_to_mov_obj_status_history(mov_obj_status_history, current_time, MOV_OBJ_STATUS_RESETTING_TO_TARGET_POINT))
							return print_message(ERROR_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_hand_to_mov_obj_handler_msg", "! write_to_mov_obj_status_history()");			
						if (! write_to_mov_obj_status_history(mov_obj_status_history, current_time, MOV_OBJ_STATUS_RESETTING_TO_TARGET_POINT))
							return print_message(ERROR_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_hand_to_mov_obj_handler_msg", "! write_to_mov_obj_status_history()");	
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
						*mov_obj_status = MOV_OBJ_STATUS_OUT_OF_TRIAL;
						mov_obj_paradigm->start_info.selected_position_idx = msg_item.additional_data.robot_start_position_idx;  
						submit_servo_target(&(robot_arm->servos[BASE_SERVO]), mov_obj_paradigm->start_info.robot_pulse_widths[mov_obj_paradigm->start_info.selected_position_idx].pulse[BASE_SERVO], MOV_OBJ_RESET_SPEED_RATIO);
						submit_servo_target(&(robot_arm->servos[SHOULDER_SERVO]), mov_obj_paradigm->start_info.robot_pulse_widths[mov_obj_paradigm->start_info.selected_position_idx].pulse[SHOULDER_SERVO], MOV_OBJ_RESET_SPEED_RATIO);
						submit_servo_target(&(robot_arm->servos[ELBOW_SERVO]), mov_obj_paradigm->start_info.robot_pulse_widths[mov_obj_paradigm->start_info.selected_position_idx].pulse[ELBOW_SERVO], MOV_OBJ_RESET_SPEED_RATIO);
						break;   // do nothing
					case MOV_OBJ_STATUS_REACHED_TARGET_POINT:
						*mov_obj_status = MOV_OBJ_STATUS_OUT_OF_TRIAL;
						mov_obj_paradigm->start_info.selected_position_idx = msg_item.additional_data.robot_start_position_idx;  
						submit_servo_target(&(robot_arm->servos[BASE_SERVO]), mov_obj_paradigm->start_info.robot_pulse_widths[mov_obj_paradigm->start_info.selected_position_idx].pulse[BASE_SERVO], MOV_OBJ_RESET_SPEED_RATIO);
						submit_servo_target(&(robot_arm->servos[SHOULDER_SERVO]), mov_obj_paradigm->start_info.robot_pulse_widths[mov_obj_paradigm->start_info.selected_position_idx].pulse[SHOULDER_SERVO], MOV_OBJ_RESET_SPEED_RATIO);
						submit_servo_target(&(robot_arm->servos[ELBOW_SERVO]), mov_obj_paradigm->start_info.robot_pulse_widths[mov_obj_paradigm->start_info.selected_position_idx].pulse[ELBOW_SERVO], MOV_OBJ_RESET_SPEED_RATIO);
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
			case TRIAL_HAND_2_MOV_OBJ_HAND_MSG_TRIALS_ENABLED:	
				switch (*mov_obj_status)
				{
					case MOV_OBJ_STATUS_DISABLED:
						*mov_obj_status = MOV_OBJ_STATUS_OUT_OF_TRIAL;
						mov_obj_paradigm->start_info.selected_position_idx = msg_item.additional_data.robot_start_position_idx;  
						submit_servo_target(&(robot_arm->servos[BASE_SERVO]), mov_obj_paradigm->start_info.robot_pulse_widths[mov_obj_paradigm->start_info.selected_position_idx].pulse[BASE_SERVO], MOV_OBJ_RESET_SPEED_RATIO);
						submit_servo_target(&(robot_arm->servos[SHOULDER_SERVO]), mov_obj_paradigm->start_info.robot_pulse_widths[mov_obj_paradigm->start_info.selected_position_idx].pulse[SHOULDER_SERVO], MOV_OBJ_RESET_SPEED_RATIO);
						submit_servo_target(&(robot_arm->servos[ELBOW_SERVO]), mov_obj_paradigm->start_info.robot_pulse_widths[mov_obj_paradigm->start_info.selected_position_idx].pulse[ELBOW_SERVO], MOV_OBJ_RESET_SPEED_RATIO);
						if (! write_to_mov_obj_status_history(mov_obj_status_history, current_time, MOV_OBJ_STATUS_OUT_OF_TRIAL))
							return print_message(ERROR_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_hand_to_mov_obj_handler_msg", "! write_to_mov_obj_status_history()");		
						break;
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
			case TRIAL_HAND_2_MOV_OBJ_HAND_MSG_START_RECORDING:	
				recording_number = msg_item.additional_data.recording_number;
				if (! write_to_mov_obj_hand_2_gui_msg_buffer(msgs_mov_obj_hand_2_gui, current_time, MOV_OBJ_HAND_2_GUI_MSG_START_RECORDING, recording_number))
					return print_message(BUG_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "write_to_mov_obj_hand_2_gui_msg_buffer", "! write_to_mov_obj_hand_2_gui_msg_buffer(().");
				break;
			case TRIAL_HAND_2_MOV_OBJ_HAND_MSG_STOP_RECORDING:	
				recording_number = msg_item.additional_data.recording_number;
				if (! write_to_mov_obj_hand_2_gui_msg_buffer(msgs_mov_obj_hand_2_gui, current_time, MOV_OBJ_HAND_2_GUI_MSG_STOP_RECORDING, recording_number))
					return print_message(BUG_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "write_to_mov_obj_hand_2_gui_msg_buffer", "! write_to_mov_obj_hand_2_gui_msg_buffer(().");
				break;
			case TRIAL_HAND_2_MOV_OBJ_HAND_MSG_CANCEL_RECORDING:	
				recording_number = msg_item.additional_data.recording_number;
				if (! write_to_mov_obj_hand_2_gui_msg_buffer(msgs_mov_obj_hand_2_gui, current_time, MOV_OBJ_HAND_2_GUI_MSG_CANCEL_RECORDING, recording_number))
					return print_message(BUG_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "write_to_mov_obj_hand_2_gui_msg_buffer", "! write_to_mov_obj_hand_2_gui_msg_buffer(().");
				break;
			case TRIAL_HAND_2_MOV_OBJ_HAND_MSG_CHANGE_TARGET:	
				switch (*mov_obj_status)
				{
					case MOV_OBJ_STATUS_OUT_OF_TRIAL:
						print_message(BUG_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_handler_to_mov_obj_handler_msg", str_trial_hand_msg);	
						get_mov_obj_status_type_string(*mov_obj_status, str_mov_obj_status);   
						return print_message(BUG_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_handler_to_mov_obj_handler_msg", str_mov_obj_status);
					case MOV_OBJ_STATUS_STAYING_AT_START_POINT:
						print_message(BUG_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_handler_to_mov_obj_handler_msg", str_trial_hand_msg);	
						get_mov_obj_status_type_string(*mov_obj_status, str_mov_obj_status);   
						return print_message(BUG_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_handler_to_mov_obj_handler_msg", str_mov_obj_status);	
					case MOV_OBJ_STATUS_AVAILABLE_TO_CONTROL:
						print_message(BUG_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_handler_to_mov_obj_handler_msg", str_trial_hand_msg);	
						get_mov_obj_status_type_string(*mov_obj_status, str_mov_obj_status);   
						return print_message(BUG_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_handler_to_mov_obj_handler_msg", str_mov_obj_status);	
					case MOV_OBJ_STATUS_RESETTING_TO_TARGET_POINT:
						mov_obj_paradigm->target_info.selected_position_idx = msg_item.additional_data.robot_target_position_idx;  

						target_coordinates = &(mov_obj_paradigm->target_info.cart_coordinates[mov_obj_paradigm->target_info.selected_position_idx]);
						start_coordinates = &(mov_obj_paradigm->start_info.cart_coordinates[mov_obj_paradigm->start_info.selected_position_idx]);
						tip_position = &(robot_arm->tip_position);
						// to standardize returning speed.
						speed = mov_obj_paradigm->servo_pw_change_rate_for_position_reset_max * (distance_btwn_two_points(start_coordinates, target_coordinates) / distance_btwn_two_points(tip_position, target_coordinates));
						submit_servo_target(&(robot_arm->servos[BASE_SERVO]), mov_obj_paradigm->target_info.robot_pulse_widths[mov_obj_paradigm->target_info.selected_position_idx].pulse[BASE_SERVO], speed);

						if (! write_to_mov_obj_status_history(mov_obj_status_history, current_time, MOV_OBJ_STATUS_RESETTING_TO_TARGET_POINT))
							return print_message(ERROR_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_hand_to_mov_obj_handler_msg", "! write_to_mov_obj_status_history()");			
						if (! write_to_mov_obj_status_history(mov_obj_status_history, current_time, MOV_OBJ_STATUS_RESETTING_TO_TARGET_POINT))
							return print_message(ERROR_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_hand_to_mov_obj_handler_msg", "! write_to_mov_obj_status_history()");	
						break;
					case MOV_OBJ_STATUS_REACHED_TARGET_POINT:
						*mov_obj_status = MOV_OBJ_STATUS_RESETTING_TO_TARGET_POINT;

						mov_obj_paradigm->target_info.selected_position_idx = msg_item.additional_data.robot_target_position_idx;  

						target_coordinates = &(mov_obj_paradigm->target_info.cart_coordinates[mov_obj_paradigm->target_info.selected_position_idx]);
						start_coordinates = &(mov_obj_paradigm->start_info.cart_coordinates[mov_obj_paradigm->start_info.selected_position_idx]);
						tip_position = &(robot_arm->tip_position);
						// to standardize returning speed.
						speed = mov_obj_paradigm->servo_pw_change_rate_for_position_reset_max * (distance_btwn_two_points(start_coordinates, target_coordinates) / distance_btwn_two_points(tip_position, target_coordinates));
						submit_servo_target(&(robot_arm->servos[BASE_SERVO]), mov_obj_paradigm->target_info.robot_pulse_widths[mov_obj_paradigm->target_info.selected_position_idx].pulse[BASE_SERVO], speed);

						if (! write_to_mov_obj_status_history(mov_obj_status_history, current_time, MOV_OBJ_STATUS_RESETTING_TO_TARGET_POINT))
							return print_message(ERROR_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_hand_to_mov_obj_handler_msg", "! write_to_mov_obj_status_history()");			
						if (! write_to_mov_obj_status_history(mov_obj_status_history, current_time, MOV_OBJ_STATUS_RESETTING_TO_TARGET_POINT))
							return print_message(ERROR_MSG ,"MovObjHandler", "HandleTrialHand2MovObjHandMsgs", "handle_trial_hand_to_mov_obj_handler_msg", "! write_to_mov_obj_status_history()");	
						break;
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
