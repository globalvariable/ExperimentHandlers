#include "MovObjHand2MovObjDurHand.h"

bool get_mov_obj_hand_2_mov_obj_dur_hand_msg_type_string(MovObjHand2MovObjDurHandMsgType msg_type, char *str)
{
	switch (msg_type)
	{
		case MOV_OBJ_HAND_2_MOV_OBJ_DUR_HAND_MSG_START_TIMER:
			if (str != NULL)
 				strcpy(str, "MOV_OBJ_HAND_2_MOV_OBJ_DUR_HAND_MSG_START_TIMER");
			return TRUE;
		case MOV_OBJ_HAND_2_MOV_OBJ_DUR_HAND_MSG_CANCEL_TIMER:
			if (str != NULL)
 				strcpy(str, "MOV_OBJ_HAND_2_MOV_OBJ_DUR_HAND_MSG_CANCEL_TIMER");
			return TRUE;
/////////////////////////		
		case MOV_OBJ_HAND_2_MOV_OBJ_DUR_HAND_MSG_NULL:
			if (str != NULL)
 				strcpy(str, "MOV_OBJ_HAND_2_MOV_OBJ_DUR_HAND_MSG_NULL");
			return FALSE;
		default:
			if (str != NULL)
 				strcpy(str, "MOV_OBJ_HAND_2_MOV_OBJ_DUR_HAND_MSG_INVALID");
			return FALSE;
	}
}

MovObjHand2MovObjDurHandMsg* allocate_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer(MovObjHand2MovObjDurHandMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer(msg_buffer);
		msg_buffer = allocate_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = g_new0(MovObjHand2MovObjDurHandMsg,1);
	print_message(INFO_MSG ,"ExperimentHandlers", "MovObjHand2MovObjDurHand", "allocate_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer", "Created mov_obj_hand_2_mov_obj_dur_hand_msg_buffer.");
	return msg_buffer;	
}
MovObjHand2MovObjDurHandMsg* deallocate_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer(MovObjHand2MovObjDurHandMsg* msg_buffer)
{
	if (msg_buffer == NULL)
		return (MovObjHand2MovObjDurHandMsg*)print_message(BUG_MSG ,"ExperimentHandlers", "MovObjHand2MovObjDurHand", "deallocate_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer", "msg_buffer == NULL.");    
	g_free(msg_buffer);	
	return NULL;
}


bool write_to_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer(MovObjHand2MovObjDurHandMsg* msg_buffer, TimeStamp msg_time, MovObjHand2MovObjDurHandMsgType msg_type, MovObjHand2MovObjDurHandMsgAdditional additional_data)
{
	unsigned int *idx;
	idx = &(msg_buffer->buff_write_idx);
	MovObjHand2MovObjDurHandMsgItem *buff = msg_buffer->buff;
	buff[*idx].msg_time = msg_time;
	buff[*idx].msg_type = msg_type;
	buff[*idx].additional_data = additional_data;
	if ((*idx + 1) == MOV_OBJ_HAND_2_MOV_OBJ_DUR_HAND_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	if (*idx == msg_buffer->buff_read_idx)
		return print_message(BUG_MSG ,"ExperimentHandlers", "MovObjHand2MovObjDurHand", "write_to_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer", "BUFFER IS FULL!!!.");    		
	return TRUE;
}
bool get_next_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer_item(MovObjHand2MovObjDurHandMsg* msg_buffer, MovObjHand2MovObjDurHandMsgItem *msg_item)	// take care of static read_idx value //only request buffer handler uses
{
	unsigned int *idx;
	MovObjHand2MovObjDurHandMsgItem *buff_item;
	idx = &(msg_buffer->buff_read_idx);
	if (*idx == msg_buffer->buff_write_idx)
		return FALSE;
	buff_item = &(msg_buffer->buff[*idx]);	
	msg_item->msg_time = buff_item->msg_time;		
	msg_item->msg_type = buff_item->msg_type;
	msg_item->additional_data = buff_item->additional_data;	
	if ((*idx + 1) == MOV_OBJ_HAND_2_MOV_OBJ_DUR_HAND_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	return TRUE;
}
