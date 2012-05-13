#include "TrialHand2TrialDurHand.h"

bool get_trial_hand_2_trial_dur_hand_msg_type_string(TrialHand2TrialDurHandMsgType msg_type, char *str)
{
	switch (msg_type)
	{
		case TRIAL_HAND_2_TRIAL_DUR_HAND_MSG_ENABLE_DURATION_HANDLING:
			if (str != NULL)
				strcpy(str, "TRIAL_HAND_2_TRIAL_DUR_HAND_MSG_ENABLE_DURATION_HANDLING");
			return TRUE;	
		case TRIAL_HAND_2_TRIAL_DUR_HAND_MSG_DISABLE_DURATION_HANDLING:
			if (str != NULL)
				strcpy(str, "TRIAL_HAND_2_TRIAL_DUR_HAND_MSG_DISABLE_DURATION_HANDLING");
			return TRUE;	
/////////////////////////		
		case TRIAL_HAND_2_TRIAL_DUR_HAND_MSG_NULL:
			if (str != NULL)
 				strcpy(str, "TRIAL_HAND_2_TRIAL_DUR_HAND_MSG_NULL");
			return FALSE;
		default:
			if (str != NULL)
 				strcpy(str, "TRIAL_HAND_2_TRIAL_DUR_HAND_MSG_INVALID");
			return FALSE;
	}
}

TrialHand2TrialDurHandMsg* allocate_trial_hand_2_trial_dur_hand_msg_buffer(TrialHand2TrialDurHandMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_trial_hand_2_trial_dur_hand_msg_buffer(msg_buffer);
		msg_buffer = allocate_trial_hand_2_trial_dur_hand_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = g_new0(TrialHand2TrialDurHandMsg,1);
	print_message(INFO_MSG ,"ExperimentHandlers", "TrialHand2TrialDurHand", "allocate_trial_hand_2_trial_dur_hand_msg_buffer", "Created trial_hand_2_trial_dur_hand_msg_buffer.");
	return msg_buffer;	
}
TrialHand2TrialDurHandMsg* deallocate_trial_hand_2_trial_dur_hand_msg_buffer(TrialHand2TrialDurHandMsg* msg_buffer)
{
	if (msg_buffer == NULL)
		return (TrialHand2TrialDurHandMsg*)print_message(BUG_MSG ,"ExperimentHandlers", "TrialHand2TrialDurHand", "deallocate_trial_hand_2_trial_dur_hand_msg_buffer", "msg_buffer == NULL.");    
	g_free(msg_buffer);	
	return NULL;
}


bool write_to_trial_hand_2_trial_dur_hand_msg_buffer(TrialHand2TrialDurHandMsg* msg_buffer, TimeStamp msg_time, TrialHand2TrialDurHandMsgType msg_type, TrialHand2TrialDurHandMsgAdditional additional_data)
{
	unsigned int *idx;
	idx = &(msg_buffer->buff_write_idx);
	TrialHand2TrialDurHandMsgItem *buff = msg_buffer->buff;
	buff[*idx].msg_time = msg_time;
	buff[*idx].msg_type = msg_type;
	buff[*idx].additional_data = additional_data;
	if ((*idx + 1) == TRIAL_HAND_2_TRIAL_DUR_HAND_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	if (*idx == msg_buffer->buff_read_idx)
		return print_message(BUG_MSG ,"ExperimentHandlers", "TrialHand2TrialDurHand", "write_to_trial_hand_2_trial_dur_hand_msg_buffer", "BUFFER IS FULL!!!.");    		
	return TRUE;
}
bool get_next_trial_hand_2_trial_dur_hand_msg_buffer_item(TrialHand2TrialDurHandMsg* msg_buffer, TrialHand2TrialDurHandMsgItem **msg_item)	// take care of static read_idx value //only request buffer handler uses
{
	unsigned int *idx;
	idx = &(msg_buffer->buff_read_idx);
	if (*idx == msg_buffer->buff_write_idx)
		return FALSE;
	*msg_item = &(msg_buffer->buff[*idx]);	
	if ((*idx + 1) == TRIAL_HAND_2_TRIAL_DUR_HAND_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	return TRUE;
}
