#include "TrialHand2Gui.h"

bool get_trial_hand_2_gui_msg_type_string(TrialHand2GuiMsgType msg_type, char *str)
{
	switch (msg_type)
	{
		case TRIAL_HAND_2_GUI_MSG_BROADCAST_START_RECORDING_MSG_ACK:
			if (str != NULL)
				strcpy(str, "TRIAL_HAND_2_GUI_MSG_BROADCAST_START_RECORDING_MSG_ACK");
			return TRUE;	
		case TRIAL_HAND_2_GUI_MSG_BROADCAST_STOP_RECORDING_MSG_ACK:
			if (str != NULL)
				strcpy(str, "TRIAL_HAND_2_GUI_MSG_BROADCAST_STOP_RECORDING_MSG_ACK");
			return TRUE;	
		case TRIAL_HAND_2_GUI_MSG_BROADCAST_CANCEL_RECORDING_MSG_ACK:
			if (str != NULL)
				strcpy(str, "TRIAL_HAND_2_GUI_MSG_BROADCAST_CANCEL_RECORDING_MSG_ACK");
			return TRUE;	
		case TRIAL_HAND_2_GUI_MSG_TRIAL_STATUS_CHANGE:
			if (str != NULL)
				strcpy(str, "TRIAL_HAND_2_GUI_MSG_TRIAL_STATUS_CHANGE");
			return TRUE;
/////////////////////////		
		case TRIAL_HAND_2_GUI_MSG_NULL:
			if (str != NULL)
 				strcpy(str, "TRIAL_HAND_2_GUI_MSG_NULL");
			return FALSE;
		default:
			if (str != NULL)
 				strcpy(str, "TRIAL_HAND_2_GUI_MSG_INVALID");
			return FALSE;
	}
}

TrialHand2GuiMsg* allocate_trial_hand_2_gui_msg_buffer(TrialHand2GuiMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_trial_hand_2_gui_msg_buffer(msg_buffer);
		msg_buffer = allocate_trial_hand_2_gui_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = g_new0(TrialHand2GuiMsg,1);
	print_message(INFO_MSG ,"ExperimentHandlers", "TrialHand2Gui", "allocate_trial_hand_2_gui_msg", "Created trial_hand_2_gui_msg_buffer.");
	return msg_buffer;	
}
TrialHand2GuiMsg* deallocate_trial_hand_2_gui_msg_buffer(TrialHand2GuiMsg* msg_buffer)
{
	if (msg_buffer == NULL)
		return (TrialHand2GuiMsg*)print_message(BUG_MSG ,"ExperimentHandlers", "TrialHand2Gui", "deallocate_trial_hand_2_gui_msg", "msg_buffer == NULL.");    
	g_free(msg_buffer);	
	return NULL;
}

bool write_to_trial_hand_2_gui_msg_buffer(TrialHand2GuiMsg* msg_buffer, TimeStamp msg_time, TrialHand2GuiMsgType msg_type, TrialHand2GuiMsgAdditional additional_data)
{
	unsigned int *idx;
	idx = &(msg_buffer->buff_write_idx);
	TrialHand2GuiMsgItem *buff = msg_buffer->buff;
	buff[*idx].msg_time = msg_time;
	buff[*idx].msg_type = msg_type;
	buff[*idx].additional_data = additional_data;
	if ((*idx + 1) == TRIAL_HAND_2_GUI_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	if (*idx == msg_buffer->buff_read_idx)
		return print_message(BUG_MSG ,"ExperimentHandlers", "TrialHand2Gui", "write_to_trial_hand_2_gui_msg_buffer", "BUFFER IS FULL!!!.");    		
	return TRUE;
}
bool get_next_trial_hand_2_gui_msg_buffer_item(TrialHand2GuiMsg* msg_buffer, TrialHand2GuiMsgItem *msg_item)	// take care of static read_idx value //only request buffer handler uses
{
	unsigned int *idx;
	TrialHand2GuiMsgItem *buff_item;
	idx = &(msg_buffer->buff_read_idx);
	if (*idx == msg_buffer->buff_write_idx)
		return FALSE;
	buff_item = &(msg_buffer->buff[*idx]);	
	msg_item->msg_time = buff_item->msg_time;		
	msg_item->msg_type = buff_item->msg_type;
	msg_item->additional_data = buff_item->additional_data;	
	if ((*idx + 1) == TRIAL_HAND_2_GUI_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	return TRUE;
}
