#include "Gui2MovObjInterf.h"

bool get_gui_2_mov_obj_interf_msg_type_string(Gui2MovObjInterfMsgType msg_type, char *str)
{
	switch (msg_type)
	{

/////////////////////////		
		case GUI_2_MOV_OBJ_INTERF_MSG_NULL:
			if (str != NULL)
 				strcpy(str, "GUI_2_MOV_OBJ_INTERF_MSG_NULL");
			return FALSE;
		default:
			if (str != NULL)
 				strcpy(str, "GUI_2_MOV_OBJ_INTERF_MSG_INVALID");
			return FALSE;
	}
}

Gui2MovObjInterfMsg* allocate_gui_2_mov_obj_interf_msg_buffer(Gui2MovObjInterfMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_gui_2_mov_obj_interf_msg_buffer(msg_buffer);
		msg_buffer = allocate_gui_2_mov_obj_interf_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = g_new0(Gui2MovObjInterfMsg,1);
	print_message(INFO_MSG ,"ExperimentHandlers", "Gui2MovObjInterf", "allocate_gui_2_mov_obj_interf_msg", "Created gui_2_mov_obj_interf_msg_buffer.");
	return msg_buffer;	
}
Gui2MovObjInterfMsg* deallocate_gui_2_mov_obj_interf_msg_buffer(Gui2MovObjInterfMsg* msg_buffer)
{
	if (msg_buffer == NULL)
		return (Gui2MovObjInterfMsg*)print_message(BUG_MSG ,"ExperimentHandlers", "Gui2MovObjInterf", "deallocate_gui_2_mov_obj_interf_msg_buffer", "msg_buffer == NULL.");    
	g_free(msg_buffer);	
	return NULL;
}

bool write_to_gui_2_mov_obj_interf_msg_buffer(Gui2MovObjInterfMsg* msg_buffer, TimeStamp msg_time, Gui2MovObjInterfMsgType msg_type, Gui2MovObjInterfMsgAdditional additional_data)
{
	unsigned int *idx;
	idx = &(msg_buffer->buff_write_idx);
	Gui2MovObjInterfMsgItem *buff = msg_buffer->buff;
	buff[*idx].msg_time = msg_time;
	buff[*idx].msg_type = msg_type;
	buff[*idx].additional_data = additional_data;
	if ((*idx + 1) == GUI_2_MOV_OBJ_INTERF_MSG_BUFFER_SIZE)
		*idx = 0;
	else
		(*idx)++;
	if (*idx == msg_buffer->buff_read_idx)
		return print_message(BUG_MSG ,"ExperimentHandlers", "Gui2MovObjInterf", "write_to_gui_2_mov_obj_interf_msg_buffer", "BUFFER IS FULL!!!.");    		
	return TRUE;
}
bool get_next_gui_2_mov_obj_interf_msg_buffer_item(Gui2MovObjInterfMsg* msg_buffer, Gui2MovObjInterfMsgItem **msg_item)	// take care of static read_idx value //only request buffer handler uses
{
	unsigned int *idx;
	idx = &(msg_buffer->buff_read_idx);
	if (*idx == msg_buffer->buff_write_idx)
		return FALSE;
	*msg_item = &(msg_buffer->buff[*idx]);	
	if ((*idx + 1) == GUI_2_MOV_OBJ_INTERF_MSG_BUFFER_SIZE)
		*idx = 0;
	else
		(*idx)++;
	return TRUE;
}
