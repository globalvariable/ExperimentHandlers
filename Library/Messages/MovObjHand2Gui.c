#include "MovObjHand2Gui.h"

bool get_mov_obj_hand_2_gui_msg_type_string(MovObjHand2GuiMsgType msg_type, char *str)
{
	switch (msg_type)
	{
		case MOV_OBJ_HAND_2_GUI_MSG_START_RECORDING:
			if (str != NULL)
 				strcpy(str, "MOV_OBJ_HAND_2_GUI_MSG_START_RECORDING");
			return TRUE;
		case MOV_OBJ_HAND_2_GUI_MSG_STOP_RECORDING:
			if (str != NULL)
 				strcpy(str, "MOV_OBJ_HAND_2_GUI_MSG_STOP_RECORDING");
			return TRUE;
		case MOV_OBJ_HAND_2_GUI_MSG_CANCEL_RECORDING:
			if (str != NULL)
 				strcpy(str, "MOV_OBJ_HAND_2_GUI_MSG_CANCEL_RECORDING");
			return TRUE;
/////////////////////////		
		case MOV_OBJ_HAND_2_GUI_MSG_NULL:
			if (str != NULL)
 				strcpy(str, "MOV_OBJ_HAND_2_GUI_MSG_NULL");
			return FALSE;
		default:
			if (str != NULL)
 				strcpy(str, "MOV_OBJ_HAND_2_GUI_MSG_INVALID");
			return FALSE;
	}
}

MovObjHand2GuiMsg* allocate_mov_obj_hand_2_gui_msg_buffer(MovObjHand2GuiMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_mov_obj_hand_2_gui_msg_buffer(msg_buffer);
		msg_buffer = allocate_mov_obj_hand_2_gui_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = g_new0(MovObjHand2GuiMsg,1);
	print_message(INFO_MSG ,"ExperimentHandlers", "MovObjHand2Gui", "allocate_mov_obj_hand_2_gui_msg", "Created mov_obj_hand_2_gui_msg_buffer.");
	return msg_buffer;	
}
MovObjHand2GuiMsg* deallocate_mov_obj_hand_2_gui_msg_buffer(MovObjHand2GuiMsg* msg_buffer)
{
	if (msg_buffer == NULL)
		return (MovObjHand2GuiMsg*)print_message(BUG_MSG ,"ExperimentHandlers", "MovObjHand2Gui", "deallocate_mov_obj_hand_2_gui_msg_buffer", "msg_buffer == NULL.");    
	g_free(msg_buffer);	
	return NULL;
}

bool write_to_mov_obj_hand_2_gui_msg_buffer(MovObjHand2GuiMsg* msg_buffer, TimeStamp msg_time, MovObjHand2GuiMsgType msg_type, MovObjHand2GuiMsgAdditional additional_data)
{
	unsigned int *idx;
	idx = &(msg_buffer->buff_write_idx);
	MovObjHand2GuiMsgItem *buff = msg_buffer->buff;
	buff[*idx].msg_time = msg_time;
	buff[*idx].msg_type = msg_type;
	buff[*idx].additional_data = additional_data;
	if ((*idx + 1) == MOV_OBJ_HAND_2_GUI_MSG_BUFFER_SIZE)
		*idx = 0;
	else
		(*idx)++;
	if (*idx == msg_buffer->buff_read_idx)
		return print_message(BUG_MSG ,"ExperimentHandlers", "MovObjHand2Gui", "write_to_mov_obj_hand_2_gui_msg_buffer", "BUFFER IS FULL!!!.");    		
	return TRUE;
}
bool get_next_mov_obj_hand_2_gui_msg_buffer_item(MovObjHand2GuiMsg* msg_buffer, MovObjHand2GuiMsgItem *msg_item)	// take care of static read_idx value //only request buffer handler uses
{
	unsigned int *idx;
	MovObjHand2GuiMsgItem *buff_item;
	idx = &(msg_buffer->buff_read_idx);
	if (*idx == msg_buffer->buff_write_idx)
		return FALSE;
	buff_item = &(msg_buffer->buff[*idx]);	
	msg_item->msg_time = buff_item->msg_time;		
	msg_item->msg_type = buff_item->msg_type;
	msg_item->additional_data = buff_item->additional_data;	
	if ((*idx + 1) == MOV_OBJ_HAND_2_GUI_MSG_BUFFER_SIZE)
		*idx = 0;
	else
		(*idx)++;
	return TRUE;
}
