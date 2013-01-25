#include "ExpEnviHand2Gui.h"

bool get_exp_envi_hand_2_gui_msg_type_string(ExpEnviHand2GuiMsgType msg_type, char *str)
{
	switch (msg_type)
	{
		case EXP_ENVI_HAND_2_GUI_MSG_START_RECORDING:
			if (str != NULL)
				strcpy(str, "EXP_ENVI_HAND_2_GUI_MSG_START_RECORDING");
			return TRUE;	
		case EXP_ENVI_HAND_2_GUI_MSG_STOP_RECORDING:
			if (str != NULL)
				strcpy(str, "EXP_ENVI_HAND_2_GUI_MSG_STOP_RECORDING");
			return TRUE;	
		case EXP_ENVI_HAND_2_GUI_MSG_CANCEL_RECORDING:
			if (str != NULL)
				strcpy(str, "EXP_ENVI_HAND_2_GUI_MSG_CANCEL_RECORDING");
			return TRUE;	
/////////////////////////		
		case EXP_ENVI_HAND_2_GUI_MSG_NULL:
			if (str != NULL)
 				strcpy(str, "EXP_ENVI_HAND_2_GUI_MSG_NULL");
			return FALSE;
		default:
			if (str != NULL)
 				strcpy(str, "EXP_ENVI_HAND_2_GUI_MSG_INVALID");
			return FALSE;
	}
}

ExpEnviHand2GuiMsg* allocate_exp_envi_hand_2_gui_msg_buffer(ExpEnviHand2GuiMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_exp_envi_hand_2_gui_msg_buffer(msg_buffer);
		msg_buffer = allocate_exp_envi_hand_2_gui_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = g_new0(ExpEnviHand2GuiMsg,1);
	print_message(INFO_MSG ,"ExperimentHandlers", "ExpEnviHand2Gui", "allocate_exp_envi_hand_2_gui_msg", "Created exp_envi_hand_2_gui_msg_buffer.");
	return msg_buffer;	
}
ExpEnviHand2GuiMsg* deallocate_exp_envi_hand_2_gui_msg_buffer(ExpEnviHand2GuiMsg* msg_buffer)
{
	if (msg_buffer == NULL)
		return (ExpEnviHand2GuiMsg*)print_message(BUG_MSG ,"ExperimentHandlers", "ExpEnviHand2Gui", "deallocate_exp_envi_hand_2_gui_msg", "msg_buffer == NULL.");    
	g_free(msg_buffer);	
	return NULL;
}

bool write_to_exp_envi_hand_2_gui_msg_buffer(ExpEnviHand2GuiMsg* msg_buffer, TimeStamp msg_time, ExpEnviHand2GuiMsgType msg_type, ExpEnviHand2GuiMsgAdditional additional_data)
{
	unsigned int *idx;
	idx = &(msg_buffer->buff_write_idx);
	ExpEnviHand2GuiMsgItem *buff = msg_buffer->buff;
	buff[*idx].msg_time = msg_time;
	buff[*idx].msg_type = msg_type;
	buff[*idx].additional_data = additional_data;
	if ((*idx + 1) == EXP_ENVI_HAND_2_GUI_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	if (*idx == msg_buffer->buff_read_idx)
		return print_message(BUG_MSG ,"ExperimentHandlers", "ExpEnviHand2Gui", "write_to_exp_envi_hand_2_gui_msg_buffer", "BUFFER IS FULL!!!.");    		
	return TRUE;
}
bool get_next_exp_envi_hand_2_gui_msg_buffer_item(ExpEnviHand2GuiMsg* msg_buffer, ExpEnviHand2GuiMsgItem *msg_item)	// take care of static read_idx value //only request buffer handler uses
{
	unsigned int *idx;
	ExpEnviHand2GuiMsgItem *buff_item;
	idx = &(msg_buffer->buff_read_idx);
	if (*idx == msg_buffer->buff_write_idx)
		return FALSE;
	buff_item = &(msg_buffer->buff[*idx]);	
	msg_item->msg_time = buff_item->msg_time;		
	msg_item->msg_type = buff_item->msg_type;
	msg_item->additional_data = buff_item->additional_data;	
	if ((*idx + 1) == EXP_ENVI_HAND_2_GUI_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	return TRUE;
}
