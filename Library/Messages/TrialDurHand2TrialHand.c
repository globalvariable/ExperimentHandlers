#include "TrialDurHand2TrialHand.h"

bool get_trial_dur_hand_2_trial_hand_msg_type_string(TrialDurHand2TrialHandMsgType msg_type, char *str)
{
	switch (msg_type)
	{
		case TRIAL_DUR_HAND_2_TRIAL_HAND_MSG_TIMEOUT:
			if (str != NULL)
				strcpy(str, "TRIAL_DUR_HAND_2_TRIAL_HAND_MSG_TIMEOUT");
			return TRUE;	
		case TRIAL_DUR_HAND_2_TRIAL_HAND_MSG_EMERGENCY_EXIT:
			if (str != NULL)
				strcpy(str, "TRIAL_DUR_HAND_2_TRIAL_HAND_MSG_EMERGENCY_EXIT");
			return TRUE;	
/////////////////////////		
		case TRIAL_DUR_HAND_2_TRIAL_HAND_MSG_NULL:
			if (str != NULL)
 				strcpy(str, "TRIAL_DUR_HAND_2_TRIAL_HAND_MSG_NULL");
			return FALSE;
		default:
			if (str != NULL)
 				strcpy(str, "TRIAL_DUR_HAND_2_TRIAL_HAND_MSG_INVALID");
			return FALSE;
	}
}

TrialDurHand2TrialHandMsg* allocate_trial_dur_hand_2_trial_hand_msg_buffer(TrialDurHand2TrialHandMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_trial_dur_hand_2_trial_hand_msg_buffer(msg_buffer);
		msg_buffer = allocate_trial_dur_hand_2_trial_hand_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = g_new0(TrialDurHand2TrialHandMsg,1);
	print_message(INFO_MSG ,"ExperimentHandlers", "TrialDurHand2TrialHand", "allocate_trial_dur_hand_2_trial_hand_msg_buffer", "Created trial_dur_hand_2_trial_hand_msg_buffer.");
	return msg_buffer;	
}
TrialDurHand2TrialHandMsg* deallocate_trial_dur_hand_2_trial_hand_msg_buffer(TrialDurHand2TrialHandMsg* msg_buffer)
{
	if (msg_buffer == NULL)
		return (TrialDurHand2TrialHandMsg*)print_message(BUG_MSG ,"ExperimentHandlers", "TrialDurHand2TrialHand", "deallocate_trial_dur_hand_2_trial_hand_msg_buffer", "msg_buffer == NULL.");    
	g_free(msg_buffer);	
	return NULL;
}


bool write_to_trial_dur_hand_2_trial_hand_msg_buffer(TrialDurHand2TrialHandMsg* msg_buffer, TimeStamp msg_time, TrialDurHand2TrialHandMsgType msg_type, TrialDurHand2TrialHandMsgAdditional additional_data)
{
	unsigned int *idx;
	idx = &(msg_buffer->buff_write_idx);
	TrialDurHand2TrialHandMsgItem *buff = msg_buffer->buff;
	buff[*idx].msg_time = msg_time;
	buff[*idx].msg_type = msg_type;
	buff[*idx].additional_data = additional_data;
	if ((*idx + 1) == TRIAL_DUR_HAND_2_TRIAL_HAND_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	if (*idx == msg_buffer->buff_read_idx)
		return print_message(BUG_MSG ,"ExperimentHandlers", "TrialDurHand2TrialHand", "write_to_trial_dur_hand_2_trial_hand_msg_buffer", "BUFFER IS FULL!!!.");    		
	return TRUE;
}
bool get_next_trial_dur_hand_2_trial_hand_msg_buffer_item(TrialDurHand2TrialHandMsg* msg_buffer, TrialDurHand2TrialHandMsgItem **msg_item)	// take care of static read_idx value //only request buffer handler uses
{
	unsigned int *idx;
	idx = &(msg_buffer->buff_read_idx);
	if (*idx == msg_buffer->buff_write_idx)
		return FALSE;
	*msg_item = &(msg_buffer->buff[*idx]);	
	if ((*idx + 1) == TRIAL_DUR_HAND_2_TRIAL_HAND_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	return TRUE;
}
