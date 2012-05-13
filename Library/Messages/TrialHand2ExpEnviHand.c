#include "TrialHand2ExpEnviHand.h"


bool get_trial_hand_2_exp_envi_hand_msg_type_string(TrialHand2ExpEnviHandMsgType msg_type, char *str)
{
	switch (msg_type)
	{
		case TRIAL_HAND_2_EXP_ENVI_HAND_MSG_ARE_YOU_ALIVE:
			if (str != NULL)
 				strcpy(str, "TRIAL_HAND_2_EXP_ENVI_HAND_MSG_ARE_YOU_ALIVE");
			return TRUE;
		case TRIAL_HAND_2_EXP_ENVI_HAND_MSG_END_TRIAL:
			if (str != NULL)
 				strcpy(str, "TRIAL_HAND_2_EXP_ENVI_HAND_MSG_END_TRIAL");
			return TRUE;
		case TRIAL_HAND_2_EXP_ENVI_HAND_MSG_RELEASE_REWARD:
			if (str != NULL)
 				strcpy(str, "TRIAL_HAND_2_EXP_ENVI_HAND_MSG_RELEASE_REWARD");
			return TRUE;
		case TRIAL_HAND_2_EXP_ENVI_HAND_MSG_RELEASE_PUNISHMENT:
			if (str != NULL)
 				strcpy(str, "TRIAL_HAND_2_EXP_ENVI_HAND_MSG_RELEASE_PUNISHMENT");
			return TRUE;
/////////////////////////		
		case TRIAL_HAND_2_EXP_ENVI_HAND_MSG_NULL:
			if (str != NULL)
 				strcpy(str, "TRIAL_HAND_2_EXP_ENVI_HAND_MSG_NULL");
			return FALSE;
		default:
			if (str != NULL)
 				strcpy(str, "TRIAL_HAND_2_EXP_ENVI_HAND_MSG_INVALID");
			return FALSE;
	}
}


TrialHand2ExpEnviHandMsg* allocate_trial_hand_2_exp_envi_hand_msg_buffer(TrialHand2ExpEnviHandMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_trial_hand_2_exp_envi_hand_msg_buffer(msg_buffer);
		msg_buffer = allocate_trial_hand_2_exp_envi_hand_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = g_new0(TrialHand2ExpEnviHandMsg,1);
	print_message(INFO_MSG ,"ExperimentHandlers", "TrialHand2ExpEnviHand", "allocate_trial_hand_2_exp_envi_hand_msg_buffer", "Created trial_hand_2_exp_envi_hand_msg_buffer.");
	return msg_buffer;	
}
TrialHand2ExpEnviHandMsg* deallocate_trial_hand_2_exp_envi_hand_msg_buffer(TrialHand2ExpEnviHandMsg* msg_buffer)
{
	if (msg_buffer == NULL)
		return (TrialHand2ExpEnviHandMsg*)print_message(BUG_MSG ,"ExperimentHandlers", "TrialHand2ExpEnviHand", "deallocate_trial_hand_2_exp_envi_hand_msg_buffer", "msg_buffer == NULL.");    
	g_free(msg_buffer);	
	return NULL;
}

TrialHand2ExpEnviHandMsg* allocate_shm_server_trial_hand_2_exp_envi_hand_msg_buffer(TrialHand2ExpEnviHandMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_shm_trial_hand_2_exp_envi_hand_msg_buffer(msg_buffer);
		msg_buffer = allocate_shm_server_trial_hand_2_exp_envi_hand_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = rtai_malloc(nam2num(TRIAL_HAND_2_EXP_ENVI_HAND_SHM_NAME), sizeof(TrialHand2ExpEnviHandMsg));
	print_message(INFO_MSG ,"ExperimentHandlers", "TrialHand2ExpEnviHand", "allocate_shm_server_trial_hand_2_exp_envi_hand_msg_buffer", "Created shm_server_trial_hand_2_exp_envi_hand_msg_buffer.");
	return msg_buffer;	
}
TrialHand2ExpEnviHandMsg* allocate_shm_client_trial_hand_2_exp_envi_hand_msg_buffer(TrialHand2ExpEnviHandMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_shm_trial_hand_2_exp_envi_hand_msg_buffer(msg_buffer);
		msg_buffer = allocate_shm_server_trial_hand_2_exp_envi_hand_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = rtai_malloc(nam2num(TRIAL_HAND_2_EXP_ENVI_HAND_SHM_NAME), 0);
	if (msg_buffer == NULL)
		print_message(ERROR_MSG ,"ExperimentHandlers", "TrialHand2ExpEnviHand", "allocate_shm_client_trial_hand_2_exp_envi_hand_msg_buffer", "Could not create shm_client_trial_hand_2_exp_envi_hand_msg_buffer.");		
	else
		print_message(INFO_MSG ,"ExperimentHandlers", "TrialHand2ExpEnviHand", "allocate_shm_client_trial_hand_2_exp_envi_hand_msg_buffer", "Created shm_client_trial_hand_2_exp_envi_hand_msg_buffer.");
	return msg_buffer;	
}
TrialHand2ExpEnviHandMsg* deallocate_shm_trial_hand_2_exp_envi_hand_msg_buffer(TrialHand2ExpEnviHandMsg* msg_buffer)
{
	if (msg_buffer == NULL)
		return (TrialHand2ExpEnviHandMsg*)print_message(BUG_MSG ,"ExperimentHandlers", "TrialHand2ExpEnviHand", "deallocate_shm_trial_hand_2_exp_envi_hand_msg_buffer", "msg_buffer == NULL.");    
	rtai_free(nam2num(TRIAL_HAND_2_EXP_ENVI_HAND_SHM_NAME), msg_buffer);	
	return NULL;
}
bool write_to_trial_hand_2_exp_envi_hand_msg_buffer(TrialHand2ExpEnviHandMsg* msg_buffer, TimeStamp msg_time, TrialHand2ExpEnviHandMsgType msg_type, TrialHand2ExpEnviHandMsgAdditional additional_data)
{
	unsigned int *idx;
	idx = &(msg_buffer->buff_write_idx);
	TrialHand2ExpEnviHandMsgItem *buff = msg_buffer->buff;
	buff[*idx].msg_time = msg_time;
	buff[*idx].msg_type = msg_type;
	buff[*idx].additional_data = additional_data;
	if ((*idx + 1) == TRIAL_HAND_2_EXP_ENVI_HAND_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	if (*idx == msg_buffer->buff_read_idx)
		return print_message(BUG_MSG ,"ExperimentHandlers", "TrialHand2ExpEnviHand", "write_to_trial_hand_2_exp_envi_hand_msg_buffer", "BUFFER IS FULL!!!.");    		
	return TRUE;
}
bool get_next_trial_hand_2_exp_envi_hand_msg_buffer_item(TrialHand2ExpEnviHandMsg* msg_buffer, TrialHand2ExpEnviHandMsgItem **msg_item)
{
	unsigned int *idx;
	idx = &(msg_buffer->buff_read_idx);
	if (*idx == msg_buffer->buff_write_idx)
		return FALSE;
	*msg_item = &(msg_buffer->buff[*idx]);	
	if ((*idx + 1) == TRIAL_HAND_2_EXP_ENVI_HAND_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	return TRUE;
}
