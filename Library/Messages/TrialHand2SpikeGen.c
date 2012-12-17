#include "TrialHand2SpikeGen.h"


bool get_trial_hand_2_spike_gen_msg_type_string(TrialHand2SpikeGenMsgType msg_type, char *str)
{
	switch (msg_type)
	{
		case TRIAL_HAND_2_SPIKE_GEN_MSG_ARE_YOU_ALIVE:
			if (str != NULL)
 				strcpy(str, "TRIAL_HAND_2_SPIKE_GEN_MSG_ARE_YOU_ALIVE");
			return TRUE;
		case TRIAL_HAND_2_SPIKE_GEN_MSG_TRIAL_STATUS_CHANGED:
			if (str != NULL)
 				strcpy(str, "TRIAL_HAND_2_SPIKE_GEN_MSG_TRIAL_STATUS_CHANGED");
			return TRUE;
/////////////////////////		
		case TRIAL_HAND_2_SPIKE_GEN_MSG_NULL:
			if (str != NULL)
 				strcpy(str, "TRIAL_HAND_2_SPIKE_GEN_MSG_NULL");
			return FALSE;
		default:
			if (str != NULL)
 				strcpy(str, "TRIAL_HAND_2_SPIKE_GEN_MSG_INVALID");
			return FALSE;
	}

}


TrialHand2SpikeGenMsg* allocate_trial_hand_2_spike_gen_msg_buffer(TrialHand2SpikeGenMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_trial_hand_2_spike_gen_msg_buffer(msg_buffer);
		msg_buffer = allocate_trial_hand_2_spike_gen_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = g_new0(TrialHand2SpikeGenMsg,1);
	print_message(INFO_MSG ,"ExperimentHandlers", "TrialHand2SpikeGen", "allocate_trial_hand_2_spike_gen_msg_buffer", "Created trial_hand_2_spike_gen_msg_buffer.");
	return msg_buffer;	
}
TrialHand2SpikeGenMsg* deallocate_trial_hand_2_spike_gen_msg_buffer(TrialHand2SpikeGenMsg* msg_buffer)
{
	if (msg_buffer == NULL)
		return (TrialHand2SpikeGenMsg*)print_message(BUG_MSG ,"ExperimentHandlers", "TrialHand2SpikeGen", "deallocate_trial_hand_2_spike_gen_msg_buffer", "msg_buffer == NULL.");    
	g_free(msg_buffer);	
	return NULL;
}

TrialHand2SpikeGenMsg* allocate_shm_server_trial_hand_2_spike_gen_msg_buffer(TrialHand2SpikeGenMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_shm_trial_hand_2_spike_gen_msg_buffer(msg_buffer);
		msg_buffer = allocate_shm_server_trial_hand_2_spike_gen_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = rtai_malloc(SHM_NUM_TRIAL_HAND_2_SPIKE_GEN, sizeof(TrialHand2SpikeGenMsg));
//	memset(msg_buffer, 0, sizeof(MovObjHand2NeuralNetMsg));
	msg_buffer->buff_write_idx = 0;   // re-allocation with rtai_malloc might lead change in the shm of client's msg_buffer->event_scheduling_delay (if it has)
	msg_buffer->buff_read_idx = 0;  // instead of memset, clear buffer pointers.
	print_message(INFO_MSG ,"ExperimentHandlers", "TrialHand2SpikeGen", "allocate_shm_server_trial_hand_2_spike_gen_msg_buffer", "Created shm_server_trial_hand_2_spike_gen_msg_buffer.");
	return msg_buffer;	
}
TrialHand2SpikeGenMsg* allocate_shm_client_trial_hand_2_spike_gen_msg_buffer(TrialHand2SpikeGenMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_shm_trial_hand_2_spike_gen_msg_buffer(msg_buffer);
		msg_buffer = allocate_shm_server_trial_hand_2_spike_gen_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = rtai_malloc(SHM_NUM_TRIAL_HAND_2_SPIKE_GEN, 0);
	print_message(INFO_MSG ,"ExperimentHandlers", "TrialHand2SpikeGen", "allocate_shm_client_trial_hand_2_spike_gen_msg_buffer", "Created shm_client_trial_hand_2_spike_gen_msg_buffer.");
	return msg_buffer;	
}
TrialHand2SpikeGenMsg* deallocate_shm_trial_hand_2_spike_gen_msg_buffer(TrialHand2SpikeGenMsg* msg_buffer)
{
	if (msg_buffer == NULL)
		return (TrialHand2SpikeGenMsg*)print_message(BUG_MSG ,"ExperimentHandlers", "TrialHand2SpikeGen", "deallocate_shm_trial_hand_2_spike_gen_msg_buffer", "msg_buffer == NULL.");    
	rtai_free(SHM_NUM_TRIAL_HAND_2_SPIKE_GEN, msg_buffer);	
	return NULL;
}
bool write_to_trial_hand_2_spike_gen_msg_buffer(TrialHand2SpikeGenMsg* msg_buffer, TimeStamp msg_time, TrialHand2SpikeGenMsgType msg_type, TrialHand2SpikeGenMsgAdditional additional_data_0, TrialHand2SpikeGenMsgAdditional additional_data_1)
{
	unsigned int *idx;
	idx = &(msg_buffer->buff_write_idx);
	TrialHand2SpikeGenMsgItem *buff = msg_buffer->buff;
	buff[*idx].msg_time = msg_time;
	buff[*idx].msg_type = msg_type;
	buff[*idx].additional_data_0 = additional_data_0;
	buff[*idx].additional_data_1 = additional_data_1;
	if ((*idx + 1) == TRIAL_HAND_2_SPIKE_GEN_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	if (*idx == msg_buffer->buff_read_idx)
		return print_message(BUG_MSG ,"ExperimentHandlers", "TrialHand2SpikeGen", "write_to_trial_hand_2_spike_gen_msg_buffer", "BUFFER IS FULL!!!.");    		
	return TRUE;
}
bool get_next_trial_hand_2_spike_gen_msg_buffer_item(TrialHand2SpikeGenMsg* msg_buffer, TrialHand2SpikeGenMsgItem *msg_item)
{
	unsigned int *idx;
	TrialHand2SpikeGenMsgItem *buff_item;
	idx = &(msg_buffer->buff_read_idx);
	if (*idx == msg_buffer->buff_write_idx)
		return FALSE;
	buff_item = &(msg_buffer->buff[*idx]);	
	msg_item->msg_time = buff_item->msg_time;		
	msg_item->msg_type = buff_item->msg_type;
	msg_item->additional_data_0 = buff_item->additional_data_0;		
	msg_item->additional_data_1 = buff_item->additional_data_1;		
	if ((*idx + 1) == TRIAL_HAND_2_SPIKE_GEN_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	return TRUE;
}
