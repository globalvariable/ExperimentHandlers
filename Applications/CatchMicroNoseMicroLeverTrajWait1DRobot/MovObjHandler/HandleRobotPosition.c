#include "HandleRobotPosition.h"




bool handle_robot_arm_position_threshold(ThreeDofRobot *robot, MovObjHandParadigmRobotReach *paradigm, MovObjStatus *mov_obj_status, TimeStamp current_time, MovObjHand2MovObjDurHandMsg *msgs_mov_obj_hand_2_mov_obj_dur_hand, MovObjHand2TrialHandMsg *msgs_mov_obj_hand_2_trial_hand, MovObjStatusHistory* mov_obj_status_history)
{
	MovObjThreshold *threshold = &(paradigm->threshold);
	CartesianCoordinates	*target_coordinates;
	CartesianCoordinates	*start_coordinates;
	ThreeDofRobotPosition	*tip_position;
	char str_mov_obj_status[MOV_OBJ_STATUS_MAX_STRING_LENGTH];

	static bool reached_escape_threshold = 0;
	static bool reached_threshold = 0;
	static bool reached_target = 0;

	switch (*mov_obj_status)
	{
		case MOV_OBJ_STATUS_OUT_OF_TRIAL:
			break;	
		case MOV_OBJ_STATUS_STAYING_AT_START_POINT:
			break;
		case MOV_OBJ_STATUS_AVAILABLE_TO_CONTROL: 
			break;
		case MOV_OBJ_STATUS_RESETTING_TO_TARGET_POINT:
			target_coordinates = &(paradigm->target_info.cart_coordinates[paradigm->target_info.selected_position_idx]);
			start_coordinates = &(paradigm->start_info.cart_coordinates[paradigm->start_info.selected_position_idx]);
			tip_position = &(robot->tip_position);
			if (apply_ellipsoid_threshold(&(threshold->target_reach_threshold), tip_position->height, tip_position->depth, tip_position->lateral, target_coordinates->height, target_coordinates->depth, target_coordinates->lateral))
			{
				if (! reached_target)
				{
					*mov_obj_status = MOV_OBJ_STATUS_REACHED_TARGET_POINT;
					if (! write_to_mov_obj_status_history(mov_obj_status_history, current_time, MOV_OBJ_STATUS_REACHED_TARGET_POINT))
						return print_message(ERROR_MSG ,"MovObjHandler", "HandleRobotPosition", "handle_robot_arm_position_threshold", "! write_to_mov_obj_status_history()");
					if (! write_to_mov_obj_hand_2_trial_hand_msg_buffer(msgs_mov_obj_hand_2_trial_hand, current_time,  MOV_OBJ_HAND_2_TRIAL_HAND_MSG_REACHED_2_TARGET, 0))
						return print_message(BUG_MSG ,"MovObjHandler", "HandleRobotPosition", "handle_robot_arm_position_threshold", "! write_to_mov_obj_hand_2_trial_hand_msg_buffer()");
					reached_target = 1;
				}
			}
			if (apply_ellipsoid_threshold(&(threshold->lever_press_reach_threshold), tip_position->height, tip_position->depth, tip_position->lateral, target_coordinates->height, target_coordinates->depth, target_coordinates->lateral))
			{
				if (! reached_threshold)
				{
					if (! write_to_mov_obj_hand_2_trial_hand_msg_buffer(msgs_mov_obj_hand_2_trial_hand, current_time,  MOV_OBJ_HAND_2_TRIAL_HAND_MSG_REACHED_2_THRESHOLD, 0))
						return print_message(BUG_MSG ,"MovObjHandler", "HandleRobotPosition", "handle_robot_arm_position_threshold", "! write_to_mov_obj_hand_2_trial_hand_msg_buffer()");
					reached_threshold = 1;
				}
			}

			if (apply_ellipsoid_threshold(&(threshold->lever_press_reach_threshold_escape), tip_position->height, tip_position->depth, tip_position->lateral, target_coordinates->height, target_coordinates->depth, target_coordinates->lateral))
			{
				if (! reached_escape_threshold)
				{
	/*				if (! write_to_mov_obj_hand_2_trial_hand_msg_buffer(msgs_mov_obj_hand_2_trial_hand, current_time,  MOV_OBJ_HAND_2_TRIAL_HAND_MSG_REACHED_2_THRESHOLD_2, 0))
						return print_message(BUG_MSG ,"MovObjHandler", "HandleRobotPosition", "handle_robot_arm_position_threshold", "! write_to_mov_obj_hand_2_trial_hand_msg_buffer()");
	*/				reached_escape_threshold = 1;
				}
			}

			if (apply_ellipsoid_threshold(&(threshold->start_reach_threshold), tip_position->height, tip_position->depth, tip_position->lateral, start_coordinates->height, start_coordinates->depth, start_coordinates->lateral))
			{
				reached_threshold = 0;
				reached_target = 0;
				reached_escape_threshold = 0;
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
