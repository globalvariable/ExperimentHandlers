#include "NeuralNet2TrialHand.h"

bool get_neural_net_2_trial_hand_msg_type_string(NeuralNet2TrialHandMsgType msg_type, char *str)
{
	switch (msg_type)
	{
		case NEURAL_NET_2_TRIAL_HAND_MSG_I_AM_ALIVE:
			if (str != NULL)
 				strcpy(str, "NEURAL_NET_2_TRIAL_HAND_MSG_I_AM_ALIVE");
			return TRUE;
/////////////////////////		
		case NEURAL_NET_2_TRIAL_HAND_MSG_NULL:
			if (str != NULL)
 				strcpy(str, "NEURAL_NET_2_TRIAL_HAND_MSG_NULL");
			return FALSE;
		default:
			if (str != NULL)
 				strcpy(str, "NEURAL_NET_2_TRIAL_HAND_MSG_INVALID");
			return FALSE;
	}

}

NeuralNet2TrialHandMsg* allocate_neural_net_2_trial_hand_msg_buffer(NeuralNet2TrialHandMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_neural_net_2_trial_hand_msg_buffer(msg_buffer);
		msg_buffer = allocate_neural_net_2_trial_hand_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = g_new0(NeuralNet2TrialHandMsg,1);
	print_message(INFO_MSG ,"ExperimentHandlers", "NeuralNet2TrialHand", "allocate_neural_net_2_trial_hand_msg_buffer", "Created neural_net_2_trial_hand_msg_buffer.");
	return msg_buffer;	
}
NeuralNet2TrialHandMsg* deallocate_neural_net_2_trial_hand_msg_buffer(NeuralNet2TrialHandMsg* msg_buffer)
{
	if (msg_buffer == NULL)
		return (NeuralNet2TrialHandMsg*)print_message(BUG_MSG ,"ExperimentHandlers", "NeuralNet2TrialHand", "deallocate_neural_net_2_trial_hand_msg_buffer", "msg_buffer == NULL.");    
	g_free(msg_buffer);	
	return NULL;
}


NeuralNet2TrialHandMsg* allocate_shm_server_neural_net_2_trial_hand_msg_buffer(NeuralNet2TrialHandMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_shm_neural_net_2_trial_hand_msg_buffer(msg_buffer);
		msg_buffer = allocate_shm_server_neural_net_2_trial_hand_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = rtai_malloc(SHM_NUM_NEURAL_NET_2_TRIAL_HAND, sizeof(NeuralNet2TrialHandMsg));
//	memset(msg_buffer, 0, sizeof(MovObjHand2NeuralNetMsg));
	msg_buffer->buff_write_idx = 0;   // re-allocation with rtai_malloc might lead change in the shm of client's msg_buffer->event_scheduling_delay (if it has)
	msg_buffer->buff_read_idx = 0;  // instead of memset, clear buffer pointers.
	print_message(INFO_MSG ,"ExperimentHandlers", "NeuralNet2TrialHand", "allocate_shm_server_neural_net_2_trial_hand_msg_buffer", "Created shm_server_neural_net_2_trial_hand_msg_buffer.");
	return msg_buffer;	
}
NeuralNet2TrialHandMsg* allocate_shm_client_neural_net_2_trial_hand_msg_buffer(NeuralNet2TrialHandMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_shm_neural_net_2_trial_hand_msg_buffer(msg_buffer);
		msg_buffer = allocate_shm_client_neural_net_2_trial_hand_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = rtai_malloc(SHM_NUM_NEURAL_NET_2_TRIAL_HAND, 0);
	print_message(INFO_MSG ,"ExperimentHandlers", "NeuralNet2TrialHand", "allocate_shm_client_neural_net_2_trial_hand_msg_buffer", "Created shm_client_neural_net_2_trial_hand_msg_buffer.");
	return msg_buffer;
}
NeuralNet2TrialHandMsg* deallocate_shm_neural_net_2_trial_hand_msg_buffer(NeuralNet2TrialHandMsg* msg_buffer)
{
	if (msg_buffer == NULL)
		return (NeuralNet2TrialHandMsg*)print_message(BUG_MSG ,"ExperimentHandlers", "NeuralNet2TrialHand", "deallocate_shm_neural_net_2_trial_hand_msg_buffer", "msg_buffer == NULL.");    
	rtai_free(SHM_NUM_NEURAL_NET_2_TRIAL_HAND, msg_buffer);	
	return NULL;
}
bool write_to_neural_net_2_trial_hand_msg_buffer(NeuralNet2TrialHandMsg* msg_buffer, TimeStamp msg_time, NeuralNet2TrialHandMsgType msg_type,  NeuralNet2TrialHandMsgAdditional additional_data)
{
	unsigned int *idx;
	idx = &(msg_buffer->buff_write_idx);
	NeuralNet2TrialHandMsgItem *buff = msg_buffer->buff;
	buff[*idx].msg_time = msg_time;
	buff[*idx].msg_type = msg_type;
	buff[*idx].additional_data = additional_data;
	if ((*idx + 1) == NEURAL_NET_2_TRIAL_HAND_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	if (*idx == msg_buffer->buff_read_idx)
		return print_message(BUG_MSG ,"ExperimentHandlers", "NeuralNet2TrialHand", "write_to_neural_net_2_trial_hand_msg_buffer", "BUFFER IS FULL!!!.");    		
	return TRUE;
}
bool get_next_neural_net_2_trial_hand_msg_buffer_item(NeuralNet2TrialHandMsg* msg_buffer, NeuralNet2TrialHandMsgItem *msg_item)
{
	unsigned int *idx;
	NeuralNet2TrialHandMsgItem *buff_item;
	idx = &(msg_buffer->buff_read_idx);
	if (*idx == msg_buffer->buff_write_idx)
		return FALSE;
	buff_item = &(msg_buffer->buff[*idx]);	
	msg_item->msg_time = buff_item->msg_time;		
	msg_item->msg_type = buff_item->msg_type;
	msg_item->additional_data = buff_item->additional_data;
	if ((*idx + 1) == NEURAL_NET_2_TRIAL_HAND_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	return TRUE;
}
