#include "HandleMovObjHand2MovObjDurHandMsgs.h"

static MovObjDurationStatus mov_obj_duration_status = MOV_OBJ_DUR_STATUS_TIMER_OFF;   //  Keep it static. Keep it hidden to other funcitons.  // send messages here to change it 
static TimeStamp handling_end_time = 0;    //  Keep it static. Keep it hidden to other functions.   // send messages here to change it 

bool handle_mov_obj_handler_duration(TimeStamp current_time, MovObjDurHand2MovObjHandMsg *msgs_mov_obj_dur_hand_2_mov_obj_hand)
{
	char str_dur_status[MOV_OBJ_DUR_STATUS_MAX_STRING_LENGTH];

	switch (mov_obj_duration_status)
	{
		case MOV_OBJ_DUR_STATUS_TIMER_OFF:
			break;	// do nothing
		case MOV_OBJ_DUR_STATUS_TIMER_ON:
			if (current_time >= handling_end_time)
			{
				mov_obj_duration_status = MOV_OBJ_DUR_STATUS_TIMER_OFF;	
				if (! write_to_mov_obj_dur_hand_2_mov_obj_hand_msg_buffer(msgs_mov_obj_dur_hand_2_mov_obj_hand, current_time, MOV_OBJ_DUR_HAND_2_MOV_OBJ_HAND_MSG_TIMEOUT, 0))
					return print_message(ERROR_MSG ,"MovObjHandler", "HandleMovObjHandDur", "handle_mov_obj_handler_duration", "! write_to_mov_obj_dur_hand_2_mov_obj_hand_msg_buffer()."); 
			}	
			break;
		default: 
			get_mov_obj_dur_status_type_string(mov_obj_duration_status, str_dur_status);  
			return print_message(BUG_MSG ,"MovObjHandler", "HandleMovObjHandDur", "handle_mov_obj_handler_duration", str_dur_status);		
	}
	return TRUE;
}


bool handle_mov_obj_handler_to_mov_obj_dur_handler_msg(TimeStamp current_time, MovObjHand2MovObjDurHandMsg *msgs_mov_obj_hand_2_mov_obj_dur_hand)
{
	MovObjHand2MovObjDurHandMsgItem *msg_item;
	char str_mov_obj_hand_msg[MOV_OBJ_HAND_2_MOV_OBJ_DUR_HAND_MSG_STRING_LENGTH];
	char str_mov_obj_dur_status[MOV_OBJ_DUR_STATUS_MAX_STRING_LENGTH];
	while (get_next_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer_item(msgs_mov_obj_hand_2_mov_obj_dur_hand, &msg_item))
	{
		get_mov_obj_hand_2_mov_obj_dur_hand_msg_type_string(msg_item->msg_type, str_mov_obj_hand_msg);
		print_message(INFO_MSG ,"MovObjHandler", "HandleMovObjHand2MovObjDurHandMsgs", "handle_mov_obj_handler_to_mov_obj_dur_handler_msg", str_mov_obj_hand_msg);
		switch (msg_item->msg_type)
		{
			case MOV_OBJ_HAND_2_MOV_OBJ_DUR_HAND_MSG_START_TIMER:	
				switch (mov_obj_duration_status)
				{
					case MOV_OBJ_DUR_STATUS_TIMER_ON:
						get_mov_obj_dur_status_type_string(mov_obj_duration_status, str_mov_obj_dur_status);   
						return print_message(BUG_MSG ,"MovObjHandler", "HandleMovObjHand2MovObjDurHandMsgs", "handle_mov_obj_handler_to_mov_obj_dur_handler_msg", str_mov_obj_dur_status);
					case MOV_OBJ_DUR_STATUS_TIMER_OFF:
						handling_end_time = msg_item->additional_data;
						mov_obj_duration_status = MOV_OBJ_DUR_STATUS_TIMER_ON;
						break;			
					default:
						get_mov_obj_dur_status_type_string(mov_obj_duration_status, str_mov_obj_dur_status);   
						return print_message(BUG_MSG ,"MovObjHandler", "HandleMovObjHand2MovObjDurHandMsgs", "handle_mov_obj_handler_to_mov_obj_dur_handler_msg", str_mov_obj_dur_status);
				}
				break;	
			case MOV_OBJ_HAND_2_MOV_OBJ_DUR_HAND_MSG_CANCEL_TIMER:	
				switch (mov_obj_duration_status)
				{
					case MOV_OBJ_DUR_STATUS_TIMER_ON:
						mov_obj_duration_status = MOV_OBJ_DUR_STATUS_TIMER_OFF;
						break;							
					case MOV_OBJ_DUR_STATUS_TIMER_OFF:
						get_mov_obj_dur_status_type_string(mov_obj_duration_status, str_mov_obj_dur_status);   
						return print_message(BUG_MSG ,"MovObjHandler", "HandleMovObjHand2MovObjDurHandMsgs", "handle_mov_obj_handler_to_mov_obj_dur_handler_msg", str_mov_obj_dur_status);		
					default:
						get_mov_obj_dur_status_type_string(mov_obj_duration_status, str_mov_obj_dur_status);   
						return print_message(BUG_MSG ,"MovObjHandler", "HandleMovObjHand2MovObjDurHandMsgs", "handle_mov_obj_handler_to_mov_obj_dur_handler_msg", str_mov_obj_dur_status);
				}
				break;	
			default:
				return print_message(BUG_MSG ,"MovObjHandler", "HandleMovObjHand2MovObjDurHandMsgs", "handle_mov_obj_handler_to_mov_obj_dur_handler_msg", str_mov_obj_hand_msg);
		}
	}
	return TRUE;
}
