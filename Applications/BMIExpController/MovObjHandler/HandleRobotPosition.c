#include "HandleRobotPosition.h"




bool handle_robot_arm_position_threshold(ThreeDofRobot *robot, MovObjHandParadigmRobotReach *paradigm, MovObjStatus *mov_obj_status, TimeStamp current_time, MovObjHand2MovObjDurHandMsg *msgs_mov_obj_hand_2_mov_obj_dur_hand, MovObjHand2TrialHandMsg *msgs_mov_obj_hand_2_trial_hand)
{
	MovObjThreshold *threshold = &(paradigm->threshold);
	CartesianCoordinates	*target_coordinates;
	ThreeDofRobotPosition	*tip_position;
	MovObjHand2MovObjDurHandMsgAdditional mov_obj_hand_2_mov_obj_dur_hand_additional_data;
	char str_mov_obj_status[MOV_OBJ_STATUS_MAX_STRING_LENGTH];
	switch (*mov_obj_status)
	{
		case MOV_OBJ_STATUS_OUT_OF_TRIAL:
			break;	
		case MOV_OBJ_STATUS_STAYING_AT_START_POINT:
			break;
		case MOV_OBJ_STATUS_AVAILABLE_TO_CONTROL: 
			target_coordinates = &(paradigm->target_info.cart_coordinates[paradigm->target_info.selected_position_idx]);
			tip_position = &(robot->tip_position);
			if (apply_ellipsoid_threshold(&(threshold->selected_target_reach_threshold), tip_position->height, tip_position->depth, tip_position->lateral, target_coordinates->height, target_coordinates->depth, target_coordinates->lateral))
			{
				printf ("Reached Ellipsoid Threshold\n");
				*mov_obj_status = MOV_OBJ_STATUS_RESETTING_TO_TARGET_POINT;
				if (! write_to_mov_obj_hand_2_trial_hand_msg_buffer(msgs_mov_obj_hand_2_trial_hand, current_time,  MOV_OBJ_HAND_2_TRIAL_HAND_MSG_REWARD_REQUEST, 0)) 
					return print_message(ERROR_MSG ,"MovObjHandler", "HandleRobotPosition", "handle_robot_arm_position_threshold", "! write_to_mov_obj_hand_2_trial_hand_msg_buffer()");
				submit_servo_target(&(robot->servos[BASE_SERVO]), paradigm->target_info.robot_pulse_widths[paradigm->target_info.selected_position_idx].pulse[BASE_SERVO], SERVO_PW_CHANGE_RATE_FOR_POSITION_RESET);
				submit_servo_target(&(robot->servos[SHOULDER_SERVO]), paradigm->target_info.robot_pulse_widths[paradigm->target_info.selected_position_idx].pulse[SHOULDER_SERVO], SERVO_PW_CHANGE_RATE_FOR_POSITION_RESET);
				submit_servo_target(&(robot->servos[ELBOW_SERVO]), paradigm->target_info.robot_pulse_widths[paradigm->target_info.selected_position_idx].pulse[ELBOW_SERVO], SERVO_PW_CHANGE_RATE_FOR_POSITION_RESET);
			}
			if (! apply_ellipsoid_threshold(&(threshold->outer_threshold), tip_position->height, tip_position->depth, tip_position->lateral, target_coordinates->height, target_coordinates->depth, target_coordinates->lateral))
			{
				printf ("Out of ellipsoid space borders\n");
				*mov_obj_status = MOV_OBJ_STATUS_RESETTING_TO_TARGET_POINT;
				if (! write_to_mov_obj_hand_2_trial_hand_msg_buffer(msgs_mov_obj_hand_2_trial_hand, current_time,  MOV_OBJ_HAND_2_TRIAL_HAND_MSG_PUNISHMENT_REQUEST, 0)) 
					return print_message(ERROR_MSG ,"MovObjHandler", "HandleRobotPosition", "handle_robot_arm_position_threshold", "! write_to_mov_obj_hand_2_trial_hand_msg_buffer()");	
				submit_servo_target(&(robot->servos[BASE_SERVO]), paradigm->target_info.robot_pulse_widths[paradigm->target_info.selected_position_idx].pulse[BASE_SERVO], SERVO_PW_CHANGE_RATE_FOR_POSITION_RESET);
				submit_servo_target(&(robot->servos[SHOULDER_SERVO]), paradigm->target_info.robot_pulse_widths[paradigm->target_info.selected_position_idx].pulse[SHOULDER_SERVO], SERVO_PW_CHANGE_RATE_FOR_POSITION_RESET);
				submit_servo_target(&(robot->servos[ELBOW_SERVO]), paradigm->target_info.robot_pulse_widths[paradigm->target_info.selected_position_idx].pulse[ELBOW_SERVO], SERVO_PW_CHANGE_RATE_FOR_POSITION_RESET);	
			}
			if (! check_three_dof_robot_out_of_robotic_space_borders(robot))
			{
				printf ("Out of cartesian space borders\n");
				*mov_obj_status = MOV_OBJ_STATUS_RESETTING_TO_TARGET_POINT;
				if (! write_to_mov_obj_hand_2_trial_hand_msg_buffer(msgs_mov_obj_hand_2_trial_hand, current_time,  MOV_OBJ_HAND_2_TRIAL_HAND_MSG_PUNISHMENT_REQUEST, 0)) 
					return print_message(ERROR_MSG ,"MovObjHandler", "HandleRobotPosition", "handle_robot_arm_position_threshold", "! write_to_mov_obj_hand_2_trial_hand_msg_buffer()");	
				submit_servo_target(&(robot->servos[BASE_SERVO]), paradigm->target_info.robot_pulse_widths[paradigm->target_info.selected_position_idx].pulse[BASE_SERVO], SERVO_PW_CHANGE_RATE_FOR_POSITION_RESET);
				submit_servo_target(&(robot->servos[SHOULDER_SERVO]), paradigm->target_info.robot_pulse_widths[paradigm->target_info.selected_position_idx].pulse[SHOULDER_SERVO], SERVO_PW_CHANGE_RATE_FOR_POSITION_RESET);
				submit_servo_target(&(robot->servos[ELBOW_SERVO]), paradigm->target_info.robot_pulse_widths[paradigm->target_info.selected_position_idx].pulse[ELBOW_SERVO], SERVO_PW_CHANGE_RATE_FOR_POSITION_RESET);			
			}
			break;
		case MOV_OBJ_STATUS_RESETTING_TO_TARGET_POINT:
			target_coordinates = &(paradigm->target_info.cart_coordinates[paradigm->target_info.selected_position_idx]);
			tip_position = &(robot->tip_position);
			if (apply_ellipsoid_threshold(&(threshold->point_reach_threshold), tip_position->height, tip_position->depth, tip_position->lateral, target_coordinates->height, target_coordinates->depth, target_coordinates->lateral))
			{
				*mov_obj_status = MOV_OBJ_STATUS_REACHED_TARGET_POINT;
				mov_obj_hand_2_mov_obj_dur_hand_additional_data.schedule.schedule = current_time + paradigm->stay_at_target_duration;
				mov_obj_hand_2_mov_obj_dur_hand_additional_data.schedule.item_idx = MOV_OBJ_DUR_STATUS_ITEM_STAY_AT_CURRENT_POSITION;
				if (! write_to_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer(msgs_mov_obj_hand_2_mov_obj_dur_hand, current_time,  MOV_OBJ_HAND_2_MOV_OBJ_DUR_HAND_MSG_SET_SCHEDULE, mov_obj_hand_2_mov_obj_dur_hand_additional_data))
					return print_message(BUG_MSG ,"MovObjHandler", "HandleRobotPosition", "handle_robot_arm_position_threshold", "! write_to_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer()");
			}
			break;
		case MOV_OBJ_STATUS_REACHED_TARGET_POINT:
			break;
		case MOV_OBJ_STATUS_RESETTING_TO_START_POINT:
			break;
		case MOV_OBJ_STATUS_DISABLED:
			break;
		default:
			get_mov_obj_status_type_string(*mov_obj_status, str_mov_obj_status);   
			return print_message(BUG_MSG ,"MovObjHandler", "HandleRobotPosition", "handle_robot_arm_position_threshold", str_mov_obj_status);
	}

	return TRUE;
}
