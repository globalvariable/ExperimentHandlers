#include "SpikeGen2TrialHand.h"

bool get_spike_gen_2_trial_hand_msg_type_string(SpikeGen2TrialHandMsgType msg_type, char *str)
{
	switch (msg_type)
	{
		case SPIKE_GEN_2_TRIAL_HAND_MSG_I_AM_ALIVE:
			if (str != NULL)
 				strcpy(str, "SPIKE_GEN_2_TRIAL_HAND_MSG_I_AM_ALIVE");
			return TRUE;
/////////////////////////		
		case SPIKE_GEN_2_TRIAL_HAND_MSG_NULL:
			if (str != NULL)
 				strcpy(str, "SPIKE_GEN_2_TRIAL_HAND_MSG_NULL");
			return FALSE;
		default:
			if (str != NULL)
 				strcpy(str, "SPIKE_GEN_2_TRIAL_HAND_MSG_INVALID");
			return FALSE;
	}

}

SpikeGen2TrialHandMsg* allocate_spike_gen_2_trial_hand_msg_buffer(SpikeGen2TrialHandMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_spike_gen_2_trial_hand_msg_buffer(msg_buffer);
		msg_buffer = allocate_spike_gen_2_trial_hand_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = g_new0(SpikeGen2TrialHandMsg,1);
	print_message(INFO_MSG ,"ExperimentHandlers", "SpikeGen2TrialHand", "allocate_spike_gen_2_trial_hand_msg_buffer", "Created spike_gen_2_trial_hand_msg_buffer.");
	return msg_buffer;	
}
SpikeGen2TrialHandMsg* deallocate_spike_gen_2_trial_hand_msg_buffer(SpikeGen2TrialHandMsg* msg_buffer)
{
	if (msg_buffer == NULL)
		return (SpikeGen2TrialHandMsg*)print_message(BUG_MSG ,"ExperimentHandlers", "SpikeGen2TrialHand", "deallocate_spike_gen_2_trial_hand_msg_buffer", "msg_buffer == NULL.");    
	g_free(msg_buffer);	
	return NULL;
}


SpikeGen2TrialHandMsg* allocate_shm_server_spike_gen_2_trial_hand_msg_buffer(SpikeGen2TrialHandMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_shm_spike_gen_2_trial_hand_msg_buffer(msg_buffer);
		msg_buffer = allocate_shm_server_spike_gen_2_trial_hand_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = rtai_malloc(nam2num(SPIKE_GEN_2_TRIAL_HAND_SHM_NAME), sizeof(SpikeGen2TrialHandMsg));
	print_message(INFO_MSG ,"ExperimentHandlers", "SpikeGen2TrialHand", "allocate_shm_server_spike_gen_2_trial_hand_msg_buffer", "Created shm_server_spike_gen_2_trial_hand_msg_buffer.");
	return msg_buffer;	
}
SpikeGen2TrialHandMsg* allocate_shm_client_spike_gen_2_trial_hand_msg_buffer(SpikeGen2TrialHandMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_shm_spike_gen_2_trial_hand_msg_buffer(msg_buffer);
		msg_buffer = allocate_shm_client_spike_gen_2_trial_hand_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = rtai_malloc(nam2num(SPIKE_GEN_2_TRIAL_HAND_SHM_NAME), 0);
	print_message(INFO_MSG ,"ExperimentHandlers", "SpikeGen2TrialHand", "allocate_shm_client_spike_gen_2_trial_hand_msg_buffer", "Created shm_client_spike_gen_2_trial_hand_msg_buffer.");
	return msg_buffer;
}
SpikeGen2TrialHandMsg* deallocate_shm_spike_gen_2_trial_hand_msg_buffer(SpikeGen2TrialHandMsg* msg_buffer)
{
	if (msg_buffer == NULL)
		return (SpikeGen2TrialHandMsg*)print_message(BUG_MSG ,"ExperimentHandlers", "SpikeGen2TrialHand", "deallocate_shm_spike_gen_2_trial_hand_msg_buffer", "msg_buffer == NULL.");    
	rtai_free(nam2num(SPIKE_GEN_2_TRIAL_HAND_SHM_NAME), msg_buffer);	
	return NULL;
}
bool write_to_spike_gen_2_trial_hand_msg_buffer(SpikeGen2TrialHandMsg* msg_buffer, TimeStamp msg_time, SpikeGen2TrialHandMsgType msg_type,  SpikeGen2TrialHandMsgAdditional additional_data)
{
	unsigned int *idx;
	idx = &(msg_buffer->buff_write_idx);
	SpikeGen2TrialHandMsgItem *buff = msg_buffer->buff;
	buff[*idx].msg_time = msg_time;
	buff[*idx].msg_type = msg_type;
	buff[*idx].additional_data = additional_data;
	if ((*idx + 1) == SPIKE_GEN_2_TRIAL_HAND_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	if (*idx == msg_buffer->buff_read_idx)
		return print_message(BUG_MSG ,"ExperimentHandlers", "SpikeGen2TrialHand", "write_to_spike_gen_2_trial_hand_msg_buffer", "BUFFER IS FULL!!!.");    		
	return TRUE;
}
bool get_next_spike_gen_2_trial_hand_msg_buffer_item(SpikeGen2TrialHandMsg* msg_buffer, SpikeGen2TrialHandMsgItem **msg_item)
{
	unsigned int *idx;
	idx = &(msg_buffer->buff_read_idx);
	if (*idx == msg_buffer->buff_write_idx)
		return FALSE;
	*msg_item = &(msg_buffer->buff[*idx]);	
	if ((*idx + 1) == SPIKE_GEN_2_TRIAL_HAND_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	return TRUE;
}
