#include "Gui2TrialHand.h"

bool get_gui_2_trial_hand_msg_type_string(Gui2TrialHandMsgType msg_type, char *str)
{
	switch (msg_type)
	{
		case GUI_2_TRIAL_HAND_MSG_ENABLE_TRIAL_HANDLING:
			if (str != NULL)
				strcpy(str, "GUI_2_TRIAL_HAND_MSG_ENABLE_TRIAL_HANDLING");
			return TRUE;	

		case GUI_2_TRIAL_HAND_MSG_DISABLE_TRIAL_HANDLING:
			if (str != NULL)
				strcpy(str, "GUI_2_TRIAL_HAND_MSG_DISABLE_TRIAL_HANDLING");
			return TRUE;	
/////////////////////////		
		case GUI_2_TRIAL_HAND_MSG_NULL:
			if (str != NULL)
 				strcpy(str, "GUI_2_TRIAL_HAND_MSG_NULL");
			return FALSE;
		default:
			if (str != NULL)
 				strcpy(str, "GUI_2_TRIAL_HAND_MSG_INVALID");
			return FALSE;
	}
}


bool write_to_gui_2_trial_hand_msg_buffer(Gui2TrialHandMsg* msg_buffer, TimeStamp msg_time, Gui2TrialHandMsgType msg_type, Gui2TrialHandMsgAdditional additional_data)
{
	unsigned int *idx;
	idx = &(msg_buffer->buff_write_idx);
	Gui2TrialHandMsgItem *buff = msg_buffer->buff;
	buff[*idx].msg_time = msg_time;
	buff[*idx].msg_type = msg_type;
	buff[*idx].additional_data = additional_data;
	if ((*idx + 1) == GUI_2_TRIAL_HAND_MSG_BUFFER_SIZE)
		*idx = 0;
	else
		(*idx)++;
	return TRUE;
}
bool get_gui_2_trial_hand_msg_buffer_item(Gui2TrialHandMsg* msg_buffer, Gui2TrialHandMsgItem **msg_item)	// take care of static read_idx value //only request buffer handler uses
{
	unsigned int *idx;
	idx = &(msg_buffer->buff_read_idx);
	if (*idx == msg_buffer->buff_write_idx)
		return FALSE;
	*msg_item = &(msg_buffer->buff[*idx]);	
	if ((*idx + 1) == GUI_2_TRIAL_HAND_MSG_BUFFER_SIZE)
		*idx = 0;
	else
		(*idx)++;
	return TRUE;
}
