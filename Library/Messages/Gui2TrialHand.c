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

		case GUI_2_TRIAL_HAND_MSG_QUIT:
			if (str != NULL)
				strcpy(str, "GUI_2_TRIAL_HAND_MSG_QUIT");
			return TRUE;	
		case GUI_2_TRIAL_HAND_MSG_INCREASE_THRESHOLD:
			if (str != NULL)
				strcpy(str, "GUI_2_TRIAL_HAND_MSG_INCREASE_THRESHOLD");
			return TRUE;	
		case GUI_2_TRIAL_HAND_MSG_DECREASE_THRESHOLD:
			if (str != NULL)
				strcpy(str, "GUI_2_TRIAL_HAND_MSG_DECREASE_THRESHOLD");
			return TRUE;	
		case GUI_2_TRIAL_HAND_MSG_SELECT_TARGET:
			if (str != NULL)
				strcpy(str, "GUI_2_TRIAL_HAND_MSG_SELECT_TARGET");
			return TRUE;	
		case GUI_2_TRIAL_HAND_MSG_AUTO_TARGET_SELECTION_ON:
			if (str != NULL)
				strcpy(str, "GUI_2_TRIAL_HAND_MSG_AUTO_TARGET_SELECTION_ON");
			return TRUE;	
		case GUI_2_TRIAL_HAND_MSG_AUTO_TARGET_SELECTION_OFF:
			if (str != NULL)
				strcpy(str, "GUI_2_TRIAL_HAND_MSG_AUTO_TARGET_SELECTION_OFF");
			return TRUE;	
		case GUI_2_TRIAL_HAND_MSG_BROADCAST_START_RECORDING:
			if (str != NULL)
				strcpy(str, "GUI_2_TRIAL_HAND_MSG_BROADCAST_START_RECORDING");
			return TRUE;	
		case GUI_2_TRIAL_HAND_MSG_BROADCAST_STOP_RECORDING:
			if (str != NULL)
				strcpy(str, "GUI_2_TRIAL_HAND_MSG_BROADCAST_STOP_RECORDING");
			return TRUE;	
		case GUI_2_TRIAL_HAND_MSG_BROADCAST_CANCEL_RECORDING:
			if (str != NULL)
				strcpy(str, "GUI_2_TRIAL_HAND_MSG_BROADCAST_CANCEL_RECORDING");
			return TRUE;	
		case GUI_2_TRIAL_HAND_MSG_RELEASE_REWARD:
			if (str != NULL)
				strcpy(str, "GUI_2_TRIAL_HAND_MSG_RELEASE_REWARD");
			return TRUE;	
		case GUI_2_TRIAL_HAND_MSG_INCREASE_ROBOT_START_POSITION_IDX:
			if (str != NULL)
				strcpy(str, "GUI_2_TRIAL_HAND_MSG_INCREASE_ROBOT_START_POSITION_IDX");
			return TRUE;	
		case GUI_2_TRIAL_HAND_MSG_DECREASE_ROBOT_START_POSITION_IDX:
			if (str != NULL)
				strcpy(str, "GUI_2_TRIAL_HAND_MSG_DECREASE_ROBOT_START_POSITION_IDX");
			return TRUE;
		case GUI_2_TRIAL_HAND_MSG_CATCH_TRIAL_MODE_ON:
			if (str != NULL)
				strcpy(str, "GUI_2_TRIAL_HAND_MSG_CATCH_TRIAL_MODE_ON");
			return TRUE;
		case GUI_2_TRIAL_HAND_MSG_CATCH_TRIAL_MODE_OFF:
			if (str != NULL)
				strcpy(str, "GUI_2_TRIAL_HAND_MSG_CATCH_TRIAL_MODE_OFF");
			return TRUE;
		case GUI_2_TRIAL_HAND_MSG_LEVER_PRESS_MODE_ON:
			if (str != NULL)
				strcpy(str, "GUI_2_TRIAL_HAND_MSG_LEVER_PRESS_MODE_ON");
			return TRUE;
		case GUI_2_TRIAL_HAND_MSG_LEVER_PRESS_MODE_OFF:
			if (str != NULL)
				strcpy(str, "GUI_2_TRIAL_HAND_MSG_LEVER_PRESS_MODE_OFF");
			return TRUE;
		case GUI_2_TRIAL_HAND_MSG_TURN_LEVER_PRESS_MODE_ON:
			if (str != NULL)
				strcpy(str, "GUI_2_TRIAL_HAND_MSG_TURN_LEVER_PRESS_MODE_ON");
			return TRUE;
		case GUI_2_TRIAL_HAND_MSG_TURN_LEVER_PRESS_MODE_OFF:
			if (str != NULL)
				strcpy(str, "GUI_2_TRIAL_HAND_MSG_TURN_LEVER_PRESS_MODE_OFF");
			return TRUE;
		case GUI_2_TRIAL_HAND_MSG_TURN_NOSE_RETRACT_MODE_ON:
			if (str != NULL)
				strcpy(str, "GUI_2_TRIAL_HAND_MSG_TURN_NOSE_RETRACT_MODE_ON");
			return TRUE;
		case GUI_2_TRIAL_HAND_MSG_TURN_NOSE_RETRACT_MODE_OFF:
			if (str != NULL)
				strcpy(str, "GUI_2_TRIAL_HAND_MSG_TURN_NOSE_RETRACT_MODE_OFF");
			return TRUE;
		case GUI_2_TRIAL_HAND_MSG_END_TRIAL:
			if (str != NULL)
				strcpy(str, "GUI_2_TRIAL_HAND_MSG_END_TRIAL");
			return TRUE;
		case GUI_2_TRIAL_HAND_MSG_FULL_CATCH_TRIAL_MODE_ON:
			if (str != NULL)
				strcpy(str, "GUI_2_TRIAL_HAND_MSG_FULL_CATCH_TRIAL_MODE_ON");
			return TRUE;
		case GUI_2_TRIAL_HAND_MSG_START_TRIAL_REQUEST:
			if (str != NULL)
				strcpy(str, "GUI_2_TRIAL_HAND_MSG_START_TRIAL_REQUEST");
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

Gui2TrialHandMsg* allocate_gui_2_trial_hand_msg_buffer(Gui2TrialHandMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_gui_2_trial_hand_msg_buffer(msg_buffer);
		msg_buffer = allocate_gui_2_trial_hand_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = g_new0(Gui2TrialHandMsg,1);
	print_message(INFO_MSG ,"ExperimentHandlers", "Gui2TrialHand", "allocate_gui_2_trial_hand_msg", "Created gui_2_trial_hand_msg_buffer.");
	return msg_buffer;	
}
Gui2TrialHandMsg* deallocate_gui_2_trial_hand_msg_buffer(Gui2TrialHandMsg* msg_buffer)
{
	if (msg_buffer == NULL)
		return (Gui2TrialHandMsg*)print_message(BUG_MSG ,"ExperimentHandlers", "Gui2TrialHand", "deallocate_gui_2_trial_hand_msg", "msg_buffer == NULL.");    
	g_free(msg_buffer);	
	return NULL;
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
	if (*idx == msg_buffer->buff_read_idx)
		return print_message(BUG_MSG ,"ExperimentHandlers", "Gui2TrialHand", "write_to_gui_2_trial_hand_msg_buffer", "BUFFER IS FULL!!!.");    		
	return TRUE;
}
bool get_next_gui_2_trial_hand_msg_buffer_item(Gui2TrialHandMsg* msg_buffer, Gui2TrialHandMsgItem *msg_item)	// take care of static read_idx value //only request buffer handler uses
{
	unsigned int *idx;
	Gui2TrialHandMsgItem *buff_item;
	idx = &(msg_buffer->buff_read_idx);
	if (*idx == msg_buffer->buff_write_idx)
		return FALSE;
	buff_item = &(msg_buffer->buff[*idx]);	
	msg_item->msg_time = buff_item->msg_time;		
	msg_item->msg_type = buff_item->msg_type;
	msg_item->additional_data = buff_item->additional_data;	
	if ((*idx + 1) == GUI_2_TRIAL_HAND_MSG_BUFFER_SIZE)
		*idx = 0;
	else
		(*idx)++;
	return TRUE;
}
