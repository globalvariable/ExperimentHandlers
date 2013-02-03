#include "TrialHand2NeuRecHand.h"


bool get_trial_hand_2_neu_rec_hand_msg_type_string(TrialHand2NeuRecHandMsgType msg_type, char *str)
{
	switch (msg_type)
	{
		case TRIAL_HAND_2_NEU_REC_HAND_MSG_ARE_YOU_ALIVE:
			if (str != NULL)
 				strcpy(str, "TRIAL_HAND_2_NEU_REC_HAND_MSG_ARE_YOU_ALIVE");
			return TRUE;
		case TRIAL_HAND_2_NEU_REC_HAND_MSG_START_RECORDING:
			if (str != NULL)
 				strcpy(str, "TRIAL_HAND_2_NEU_REC_HAND_MSG_START_RECORDING");
			return TRUE;
		case TRIAL_HAND_2_NEU_REC_HAND_MSG_STOP_RECORDING:
			if (str != NULL)
 				strcpy(str, "TRIAL_HAND_2_NEU_REC_HAND_MSG_STOP_RECORDING");
			return TRUE;
		case TRIAL_HAND_2_NEU_REC_HAND_MSG_CANCEL_RECORDING:
			if (str != NULL)
 				strcpy(str, "TRIAL_HAND_2_NEU_REC_HAND_MSG_CANCEL_RECORDING");
			return TRUE;
/////////////////////////		
		case TRIAL_HAND_2_NEU_REC_HAND_MSG_NULL:
			if (str != NULL)
 				strcpy(str, "TRIAL_HAND_2_NEU_REC_HAND_MSG_NULL");
			return FALSE;
		default:
			if (str != NULL)
 				strcpy(str, "TRIAL_HAND_2_NEU_REC_HAND_MSG_INVALID");
			return FALSE;
	}
}


TrialHand2NeuRecHandMsg* allocate_trial_hand_2_neu_rec_hand_msg_buffer(TrialHand2NeuRecHandMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_trial_hand_2_neu_rec_hand_msg_buffer(msg_buffer);
		msg_buffer = allocate_trial_hand_2_neu_rec_hand_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = g_new0(TrialHand2NeuRecHandMsg,1);
	print_message(INFO_MSG ,"ExperimentHandlers", "TrialHand2NeuRecHand", "allocate_trial_hand_2_neu_rec_hand_msg_buffer", "Created trial_hand_2_neu_rec_hand_msg_buffer.");
	return msg_buffer;	
}
TrialHand2NeuRecHandMsg* deallocate_trial_hand_2_neu_rec_hand_msg_buffer(TrialHand2NeuRecHandMsg* msg_buffer)
{
	if (msg_buffer == NULL)
		return (TrialHand2NeuRecHandMsg*)print_message(BUG_MSG ,"ExperimentHandlers", "TrialHand2NeuRecHand", "deallocate_trial_hand_2_neu_rec_hand_msg_buffer", "msg_buffer == NULL.");    
	g_free(msg_buffer);	
	return NULL;
}

TrialHand2NeuRecHandMsg* allocate_shm_server_trial_hand_2_neu_rec_hand_msg_buffer(TrialHand2NeuRecHandMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_shm_trial_hand_2_neu_rec_hand_msg_buffer(msg_buffer);
		msg_buffer = allocate_shm_server_trial_hand_2_neu_rec_hand_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = rtai_malloc(SHM_NUM_TRIAL_HAND_2_NEU_REC_HAND, sizeof(TrialHand2NeuRecHandMsg));
//	memset(msg_buffer, 0, sizeof(MovObjHand2NeuralNetMsg));
	msg_buffer->buff_write_idx = 0;   // re-allocation with rtai_malloc might lead change in the shm of client's msg_buffer->event_scheduling_delay (if it has)
	msg_buffer->buff_read_idx = 0;  // instead of memset, clear buffer pointers.
	print_message(INFO_MSG ,"ExperimentHandlers", "TrialHand2NeuRecHand", "allocate_shm_server_trial_hand_2_neu_rec_hand_msg_buffer", "Created shm_server_trial_hand_2_neu_rec_hand_msg_buffer.");
	return msg_buffer;	
}
TrialHand2NeuRecHandMsg* allocate_shm_client_trial_hand_2_neu_rec_hand_msg_buffer(TrialHand2NeuRecHandMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_shm_trial_hand_2_neu_rec_hand_msg_buffer(msg_buffer);
		msg_buffer = allocate_shm_server_trial_hand_2_neu_rec_hand_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = rtai_malloc(SHM_NUM_TRIAL_HAND_2_NEU_REC_HAND, 0);
	if (msg_buffer == NULL)
		print_message(ERROR_MSG ,"ExperimentHandlers", "TrialHand2NeuRecHand", "allocate_shm_client_trial_hand_2_neu_rec_hand_msg_buffer", "Could not create shm_client_trial_hand_2_neu_rec_hand_msg_buffer.");		
	else
		print_message(INFO_MSG ,"ExperimentHandlers", "TrialHand2NeuRecHand", "allocate_shm_client_trial_hand_2_neu_rec_hand_msg_buffer", "Created shm_client_trial_hand_2_neu_rec_hand_msg_buffer.");
	return msg_buffer;	
}
TrialHand2NeuRecHandMsg* deallocate_shm_trial_hand_2_neu_rec_hand_msg_buffer(TrialHand2NeuRecHandMsg* msg_buffer)
{
	if (msg_buffer == NULL)
		return (TrialHand2NeuRecHandMsg*)print_message(BUG_MSG ,"ExperimentHandlers", "TrialHand2NeuRecHand", "deallocate_shm_trial_hand_2_neu_rec_hand_msg_buffer", "msg_buffer == NULL.");    
	rtai_free(SHM_NUM_TRIAL_HAND_2_NEU_REC_HAND, msg_buffer);	
	return NULL;
}
bool write_to_trial_hand_2_neu_rec_hand_msg_buffer(TrialHand2NeuRecHandMsg* msg_buffer, TimeStamp msg_time, TrialHand2NeuRecHandMsgType msg_type, TrialHand2NeuRecHandMsgAdditional additional_data)
{
	unsigned int *idx;
	idx = &(msg_buffer->buff_write_idx);
	TrialHand2NeuRecHandMsgItem *buff = msg_buffer->buff;
	buff[*idx].msg_time = msg_time;
	buff[*idx].msg_type = msg_type;
	buff[*idx].additional_data = additional_data;
	if ((*idx + 1) == TRIAL_HAND_2_NEU_REC_HAND_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	if (*idx == msg_buffer->buff_read_idx)
		return print_message(BUG_MSG ,"ExperimentHandlers", "TrialHand2NeuRecHand", "write_to_trial_hand_2_neu_rec_hand_msg_buffer", "BUFFER IS FULL!!!.");    		
	return TRUE;
}
bool get_next_trial_hand_2_neu_rec_hand_msg_buffer_item(TrialHand2NeuRecHandMsg* msg_buffer, TrialHand2NeuRecHandMsgItem *msg_item)
{
	unsigned int *idx;
	TrialHand2NeuRecHandMsgItem *buff_item;
	idx = &(msg_buffer->buff_read_idx);
	if (*idx == msg_buffer->buff_write_idx)
		return FALSE;
	buff_item = &(msg_buffer->buff[*idx]);	
	msg_item->msg_time = buff_item->msg_time;		
	msg_item->msg_type = buff_item->msg_type;
	msg_item->additional_data = buff_item->additional_data;		
	if ((*idx + 1) == TRIAL_HAND_2_NEU_REC_HAND_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	return TRUE;
}
