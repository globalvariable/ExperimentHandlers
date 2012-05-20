#include "MovObjDurHand2MovObjHand.h"

bool get_mov_obj_dur_hand_2_mov_obj_hand_msg_type_string(MovObjDurHand2MovObjHandMsgType msg_type, char *str)
{
	switch (msg_type)
	{
		case MOV_OBJ_DUR_HAND_2_MOV_OBJ_HAND_MSG_TIMEOUT:
			if (str != NULL)
 				strcpy(str, "MOV_OBJ_DUR_HAND_2_MOV_OBJ_HAND_MSG_TIMEOUT");
			return TRUE;
/////////////////////////		
		case MOV_OBJ_DUR_HAND_2_MOV_OBJ_HAND_MSG_NULL:
			if (str != NULL)
 				strcpy(str, "MOV_OBJ_DUR_HAND_2_MOV_OBJ_HAND_MSG_NULL");
			return FALSE;
		default:
			if (str != NULL)
 				strcpy(str, "MOV_OBJ_DUR_HAND_2_MOV_OBJ_HAND_MSG_INVALID");
			return FALSE;
	}
}

MovObjDurHand2MovObjHandMsg* allocate_mov_obj_dur_hand_2_mov_obj_hand_msg_buffer(MovObjDurHand2MovObjHandMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_mov_obj_dur_hand_2_mov_obj_hand_msg_buffer(msg_buffer);
		msg_buffer = allocate_mov_obj_dur_hand_2_mov_obj_hand_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = g_new0(MovObjDurHand2MovObjHandMsg,1);
	print_message(INFO_MSG ,"ExperimentHandlers", "MovObjDurHand2MovObjHand", "allocate_mov_obj_dur_hand_2_mov_obj_hand_msg_buffer", "Created mov_obj_dur_hand_2_mov_obj_hand_msg_buffer.");
	return msg_buffer;	
}
MovObjDurHand2MovObjHandMsg* deallocate_mov_obj_dur_hand_2_mov_obj_hand_msg_buffer(MovObjDurHand2MovObjHandMsg* msg_buffer)
{
	if (msg_buffer == NULL)
		return (MovObjDurHand2MovObjHandMsg*)print_message(BUG_MSG ,"ExperimentHandlers", "MovObjDurHand2MovObjHand", "deallocate_mov_obj_dur_hand_2_mov_obj_hand_msg_buffer", "msg_buffer == NULL.");    
	g_free(msg_buffer);	
	return NULL;
}


bool write_to_mov_obj_dur_hand_2_mov_obj_hand_msg_buffer(MovObjDurHand2MovObjHandMsg* msg_buffer, TimeStamp msg_time, MovObjDurHand2MovObjHandMsgType msg_type, MovObjDurHand2MovObjHandMsgAdditional additional_data)
{
	unsigned int *idx;
	idx = &(msg_buffer->buff_write_idx);
	MovObjDurHand2MovObjHandMsgItem *buff = msg_buffer->buff;
	buff[*idx].msg_time = msg_time;
	buff[*idx].msg_type = msg_type;
	buff[*idx].additional_data = additional_data;
	if ((*idx + 1) == MOV_OBJ_DUR_HAND_2_MOV_OBJ_HAND_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	if (*idx == msg_buffer->buff_read_idx)
		return print_message(BUG_MSG ,"ExperimentHandlers", "MovObjDurHand2MovObjHand", "write_to_mov_obj_dur_hand_2_mov_obj_hand_msg_buffer", "BUFFER IS FULL!!!.");    		
	return TRUE;
}
bool get_next_mov_obj_dur_hand_2_mov_obj_hand_msg_buffer_item(MovObjDurHand2MovObjHandMsg* msg_buffer, MovObjDurHand2MovObjHandMsgItem **msg_item)	// take care of static read_idx value //only request buffer handler uses
{
	unsigned int *idx;
	idx = &(msg_buffer->buff_read_idx);
	if (*idx == msg_buffer->buff_write_idx)
		return FALSE;
	*msg_item = &(msg_buffer->buff[*idx]);	
	if ((*idx + 1) == MOV_OBJ_DUR_HAND_2_MOV_OBJ_HAND_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	return TRUE;
}
