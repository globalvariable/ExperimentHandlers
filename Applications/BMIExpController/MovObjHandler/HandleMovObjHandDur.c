#include "HandleMovObjHandDur.h"


bool handle_mov_obj_handler_duration(MovObjDurationStatus *mov_obj_duration_status, TimeStamp current_time, TimeStamp handling_end_time, MovObjDurHand2MovObjHandMsg *msgs_mov_obj_dur_hand_2_mov_obj_hand)
{
	char str_dur_status[MOV_OBJ_DUR_STATUS_MAX_STRING_LENGTH];

	switch (*mov_obj_duration_status)
	{
		case MOV_OBJ_DUR_STATUS_TIMER_OFF:
			break;	// do nothing
		case MOV_OBJ_DUR_STATUS_TIMER_ON:
			if (current_time >= handling_end_time)
			{
				*mov_obj_duration_status = MOV_OBJ_DUR_STATUS_TIMER_OFF;	
				if (! write_to_mov_obj_dur_hand_2_mov_obj_hand_msg_buffer(msgs_mov_obj_dur_hand_2_mov_obj_hand, current_time, MOV_OBJ_DUR_HAND_2_MOV_OBJ_HAND_MSG_TIMEOUT, 0))
					return print_message(ERROR_MSG ,"MovObjHandler", "HandleMovObjHandDur", "handle_mov_obj_handler_duration", "! write_to_mov_obj_dur_hand_2_mov_obj_hand_msg_buffer()."); 
			}	
			break;
		default: 
			get_mov_obj_dur_status_type_string(*mov_obj_duration_status, str_dur_status);  
			return print_message(BUG_MSG ,"MovObjHandler", "HandleMovObjHandDur", "handle_mov_obj_handler_duration", str_dur_status);		
	}
	return TRUE;
}
