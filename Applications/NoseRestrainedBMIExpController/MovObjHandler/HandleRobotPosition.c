#include "HandleRobotPosition.h"




bool handle_robot_arm_position_threshold(ThreeDofRobot *robot, MovObjHandParadigmRobotReach *paradigm, MovObjStatus *mov_obj_status, TimeStamp current_time, MovObjHand2MovObjDurHandMsg *msgs_mov_obj_hand_2_mov_obj_dur_hand, MovObjHand2TrialHandMsg *msgs_mov_obj_hand_2_trial_hand, MovObjStatusHistory* mov_obj_status_history, MovObjHand2NeuralNetMsgMultiThread *msgs_mov_obj_hand_2_neural_net_multi_thread)
{
	MovObjThreshold *threshold = &(paradigm->threshold);
	CartesianCoordinates	*target_coordinates;
	ThreeDofRobotPosition	*tip_position;
	MovObjHand2MovObjDurHandMsgAdditional mov_obj_hand_2_mov_obj_dur_hand_additional_data;
	char str_mov_obj_status[MOV_OBJ_STATUS_MAX_STRING_LENGTH];
	double reward, punishment;
	unsigned int i;
	MovObjHand2NeuralNetMsgAdditional	mov_obj_hand_2_neural_net_msg_add;
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
				*mov_obj_status = MOV_OBJ_STATUS_OUT_OF_TRIAL;
				reward = distance_btwn_two_points(&(robot->tip_position), &(paradigm->target_info.cart_coordinates[paradigm->target_info.selected_position_idx]));
				printf ("Distance to target = %f\n", reward);		
				if (! write_to_mov_obj_hand_2_trial_hand_msg_buffer(msgs_mov_obj_hand_2_trial_hand, current_time,  MOV_OBJ_HAND_2_TRIAL_HAND_MSG_REWARD_REQUEST, reward)) 
					return print_message(ERROR_MSG ,"MovObjHandler", "HandleRobotPosition", "handle_robot_arm_position_threshold", "! write_to_mov_obj_hand_2_trial_hand_msg_buffer()");
				mov_obj_hand_2_neural_net_msg_add.binary_reward_add.target_idx = paradigm->target_info.selected_position_idx;
				mov_obj_hand_2_neural_net_msg_add.binary_reward_add.reward = 0;
				for (i = 0; i < NUM_OF_MOV_OBJ_HAND_2_NEURAL_NET_MSG_BUFFERS; i++)
				{
					if (! write_to_mov_obj_hand_2_neural_net_msg_buffer((*msgs_mov_obj_hand_2_neural_net_multi_thread)[i], current_time, MOV_OBJ_HAND_2_NEURAL_NET_MSG_END_TRIAL_W_REWARD, mov_obj_hand_2_neural_net_msg_add))
						return print_message(ERROR_MSG ,"MovObjHandler", "HandleMovObjDurHand2MovObjHandMsgs", "handle_mov_obj_dur_handler_to_mov_obj_handler_msg", "! write_to_mov_obj_hand_2_neural_net_msg_buffer()");
				}
				if (! write_to_mov_obj_status_history(mov_obj_status_history, current_time, MOV_OBJ_STATUS_OUT_OF_TRIAL))
					return print_message(ERROR_MSG ,"MovObjHandler", "HandleRobotPosition", "handle_robot_arm_position_threshold", "! write_to_mov_obj_status_history()");
			}
			if (! apply_ellipsoid_threshold(&(threshold->outer_threshold), tip_position->height, tip_position->depth, tip_position->lateral, target_coordinates->height, target_coordinates->depth, target_coordinates->lateral))
			{
				printf ("Out of ellipsoid space borders\n");
				*mov_obj_status = MOV_OBJ_STATUS_OUT_OF_TRIAL;
				punishment = distance_btwn_two_points(&(robot->tip_position), &(paradigm->target_info.cart_coordinates[paradigm->target_info.selected_position_idx]));
				printf ("Distance to target = %f\n", punishment);		
				if (! write_to_mov_obj_hand_2_trial_hand_msg_buffer(msgs_mov_obj_hand_2_trial_hand, current_time,  MOV_OBJ_HAND_2_TRIAL_HAND_MSG_PUNISHMENT_REQUEST, punishment)) 
					return print_message(ERROR_MSG ,"MovObjHandler", "HandleRobotPosition", "handle_robot_arm_position_threshold", "! write_to_mov_obj_hand_2_trial_hand_msg_buffer()");	
				mov_obj_hand_2_neural_net_msg_add.binary_reward_add.target_idx = paradigm->target_info.selected_position_idx;
				mov_obj_hand_2_neural_net_msg_add.binary_reward_add.reward = 0;
				for (i = 0; i < NUM_OF_MOV_OBJ_HAND_2_NEURAL_NET_MSG_BUFFERS; i++)
				{
					if (! write_to_mov_obj_hand_2_neural_net_msg_buffer((*msgs_mov_obj_hand_2_neural_net_multi_thread)[i], current_time, MOV_OBJ_HAND_2_NEURAL_NET_MSG_END_TRIAL_W_PUNISH, mov_obj_hand_2_neural_net_msg_add))
						return print_message(ERROR_MSG ,"MovObjHandler", "HandleMovObjDurHand2MovObjHandMsgs", "handle_mov_obj_dur_handler_to_mov_obj_handler_msg", "! write_to_mov_obj_hand_2_neural_net_msg_buffer()");
				}
				if (! write_to_mov_obj_status_history(mov_obj_status_history, current_time, MOV_OBJ_STATUS_OUT_OF_TRIAL))
					return print_message(ERROR_MSG ,"MovObjHandler", "HandleMovObjDurHand2MovObjHandMsgs", "handle_mov_obj_dur_handler_to_mov_obj_handler_msg", "! write_to_mov_obj_status_history()");
			}
			if (! check_robot_space_borders(robot, paradigm))
			{
				printf ("Out of cartesian space borders\n");
				*mov_obj_status = MOV_OBJ_STATUS_OUT_OF_TRIAL;
				punishment = distance_btwn_two_points(&(robot->tip_position), &(paradigm->target_info.cart_coordinates[paradigm->target_info.selected_position_idx]));
				printf ("Distance to target = %f\n", punishment);		
				if (! write_to_mov_obj_hand_2_trial_hand_msg_buffer(msgs_mov_obj_hand_2_trial_hand, current_time,  MOV_OBJ_HAND_2_TRIAL_HAND_MSG_PUNISHMENT_REQUEST, punishment)) 
					return print_message(ERROR_MSG ,"MovObjHandler", "HandleRobotPosition", "handle_robot_arm_position_threshold", "! write_to_mov_obj_hand_2_trial_hand_msg_buffer()");
				mov_obj_hand_2_neural_net_msg_add.binary_reward_add.target_idx = paradigm->target_info.selected_position_idx;
				mov_obj_hand_2_neural_net_msg_add.binary_reward_add.reward = 0;
				for (i = 0; i < NUM_OF_MOV_OBJ_HAND_2_NEURAL_NET_MSG_BUFFERS; i++)
				{
					if (! write_to_mov_obj_hand_2_neural_net_msg_buffer((*msgs_mov_obj_hand_2_neural_net_multi_thread)[i], current_time, MOV_OBJ_HAND_2_NEURAL_NET_MSG_END_TRIAL_W_PUNISH, mov_obj_hand_2_neural_net_msg_add))
						return print_message(ERROR_MSG ,"MovObjHandler", "HandleMovObjDurHand2MovObjHandMsgs", "handle_mov_obj_dur_handler_to_mov_obj_handler_msg", "! write_to_mov_obj_hand_2_neural_net_msg_buffer()");	
				}
				if (! write_to_mov_obj_status_history(mov_obj_status_history, current_time, MOV_OBJ_STATUS_OUT_OF_TRIAL))
					return print_message(ERROR_MSG ,"MovObjHandler", "HandleMovObjDurHand2MovObjHandMsgs", "handle_mov_obj_dur_handler_to_mov_obj_handler_msg", "! write_to_mov_obj_status_history()");
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
				if (! write_to_mov_obj_status_history(mov_obj_status_history, current_time, MOV_OBJ_STATUS_REACHED_TARGET_POINT))
					return print_message(ERROR_MSG ,"MovObjHandler", "HandleRobotPosition", "handle_robot_arm_position_threshold", "! write_to_mov_obj_status_history()");
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
