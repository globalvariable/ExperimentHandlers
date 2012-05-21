#include "HandleMovObjHandStatus.h"



#define MOV_OBJ_RESETING_SPEED 3.0

bool handle_mov_obj_handler_status(MovObjStatus mov_obj_status, TrialType mov_obj_trial_type_status, TimeStamp current_time, MovObjHand2MovObjInterfMsg *msgs_mov_obj_hand_2_mov_obj_interf)
{
	char str_mov_obj_status[MOV_OBJ_STATUS_MAX_STRING_LENGTH];
	if ((mov_obj_status == MOV_OBJ_STATUS_RESETTING_TO_TARGET_POINT_W_SUCCESS) || (mov_obj_status == MOV_OBJ_STATUS_RESETTING_TO_TARGET_POINT_W_FAIL))
	{
		switch (mov_obj_trial_type_status)
		{
			case TRIAL_TYPE_IN_VIVO_BMI_LEFT_TARGET:	// left locations are below zero
				if (! write_to_mov_obj_hand_2_mov_obj_interf_msg_buffer(msgs_mov_obj_hand_2_mov_obj_interf, current_time, MOV_OBJ_HAND_2_MOV_OBJ_INTERF_SET_DIRECTION_SPEED_LOCATION, ONE_D_ACTUATOR, MOV_OBJ_DIRECTION_LEFT, MOV_OBJ_RESETING_SPEED, MOV_OBJ_LOCATION_NULL))
					print_message(ERROR_MSG ,"MovObjHandler", "HandleMobObjHandStatus", "handle_mov_obj_handler_status","! write_to_mov_obj_hand_2_mov_obj_interf_msg_buffer().");	
				break;
			case TRIAL_TYPE_IN_VIVO_BMI_RIGHT_TARGET:  // right locations are above zero
				if (! write_to_mov_obj_hand_2_mov_obj_interf_msg_buffer(msgs_mov_obj_hand_2_mov_obj_interf, current_time, MOV_OBJ_HAND_2_MOV_OBJ_INTERF_SET_DIRECTION_SPEED_LOCATION, ONE_D_ACTUATOR, MOV_OBJ_DIRECTION_RIGHT, MOV_OBJ_RESETING_SPEED, MOV_OBJ_LOCATION_NULL))
					print_message(ERROR_MSG ,"MovObjHandler", "HandleMobObjHandStatus", "handle_mov_obj_handler_status","! write_to_mov_obj_hand_2_mov_obj_interf_msg_buffer().");	
				break;
			default:
				get_mov_obj_status_type_string(mov_obj_status, str_mov_obj_status);   
				return print_message(BUG_MSG ,"MovObjHandler", "HandleMobObjHandStatus", "handle_mov_obj_handler_status", str_mov_obj_status);	
		}
	}
	return TRUE;
}
