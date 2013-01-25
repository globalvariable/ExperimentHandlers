#include "TrialHand2MovObjHand.h"


bool get_trial_hand_2_mov_obj_hand_msg_type_string(TrialHand2MovObjHandMsgType msg_type, char *str)
{
	switch (msg_type)
	{
		case TRIAL_HAND_2_MOV_OBJ_HAND_MSG_ARE_YOU_ALIVE:
			if (str != NULL)
 				strcpy(str, "TRIAL_HAND_2_MOV_OBJ_HAND_MSG_ARE_YOU_ALIVE");
			return TRUE;
		case TRIAL_HAND_2_MOV_OBJ_HAND_MSG_START_TRIAL:
			if (str != NULL)
 				strcpy(str, "TRIAL_HAND_2_MOV_OBJ_HAND_MSG_START_TRIAL");
			return TRUE;
		case TRIAL_HAND_2_MOV_OBJ_HAND_MSG_TRIAL_TIMEOUT:
			if (str != NULL)
 				strcpy(str, "TRIAL_HAND_2_MOV_OBJ_HAND_MSG_TRIAL_TIMEOUT");
			return TRUE;
		case TRIAL_HAND_2_MOV_OBJ_HAND_MSG_END_TRIAL:
			if (str != NULL)
 				strcpy(str, "TRIAL_HAND_2_MOV_OBJ_HAND_MSG_END_TRIAL");
			return TRUE;
		case TRIAL_HAND_2_MOV_OBJ_HAND_MSG_ELLIPSOID_THRESHOLD:
			if (str != NULL)
 				strcpy(str, "TRIAL_HAND_2_MOV_OBJ_HAND_MSG_ELLIPSOID_THRESHOLD");
			return TRUE;
		case TRIAL_HAND_2_MOV_OBJ_HAND_MSG_TRIALS_ENABLED:
			if (str != NULL)
 				strcpy(str, "TRIAL_HAND_2_MOV_OBJ_HAND_MSG_TRIALS_ENABLED");
			return TRUE;
		case TRIAL_HAND_2_MOV_OBJ_HAND_MSG_TRIALS_DISABLED:
			if (str != NULL)
 				strcpy(str, "TRIAL_HAND_2_MOV_OBJ_HAND_MSG_TRIALS_DISABLED");
			return TRUE;
		case TRIAL_HAND_2_MOV_OBJ_HAND_MSG_START_RECORDING:
			if (str != NULL)
 				strcpy(str, "TRIAL_HAND_2_MOV_OBJ_HAND_MSG_START_RECORDING");
			return TRUE;
		case TRIAL_HAND_2_MOV_OBJ_HAND_MSG_STOP_RECORDING:
			if (str != NULL)
 				strcpy(str, "TRIAL_HAND_2_MOV_OBJ_HAND_MSG_STOP_RECORDING");
			return TRUE;
		case TRIAL_HAND_2_MOV_OBJ_HAND_MSG_CANCEL_RECORDING:
			if (str != NULL)
 				strcpy(str, "TRIAL_HAND_2_MOV_OBJ_HAND_MSG_CANCEL_RECORDING");
			return TRUE;
/////////////////////////		
		case TRIAL_HAND_2_MOV_OBJ_HAND_MSG_NULL:
			if (str != NULL)
 				strcpy(str, "TRIAL_HAND_2_MOV_OBJ_HAND_MSG_NULL");
			return FALSE;
		default:
			if (str != NULL)
 				strcpy(str, "TRIAL_HAND_2_MOV_OBJ_HAND_MSG_INVALID");
			return FALSE;
	}
}


TrialHand2MovObjHandMsg* allocate_trial_hand_2_mov_obj_hand_msg_buffer(TrialHand2MovObjHandMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_trial_hand_2_mov_obj_hand_msg_buffer(msg_buffer);
		msg_buffer = allocate_trial_hand_2_mov_obj_hand_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = g_new0(TrialHand2MovObjHandMsg,1);
	print_message(INFO_MSG ,"ExperimentHandlers", "TrialHand2MovObjHand", "allocate_trial_hand_2_mov_obj_hand_msg_buffer", "Created trial_hand_2_mov_obj_hand_msg_buffer.");
	return msg_buffer;	
}
TrialHand2MovObjHandMsg* deallocate_trial_hand_2_mov_obj_hand_msg_buffer(TrialHand2MovObjHandMsg* msg_buffer)
{
	if (msg_buffer == NULL)
		return (TrialHand2MovObjHandMsg*)print_message(BUG_MSG ,"ExperimentHandlers", "TrialHand2MovObjHand", "deallocate_trial_hand_2_mov_obj_hand_msg_buffer", "msg_buffer == NULL.");    
	g_free(msg_buffer);	
	return NULL;
}

TrialHand2MovObjHandMsg* allocate_shm_server_trial_hand_2_mov_obj_hand_msg_buffer(TrialHand2MovObjHandMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_shm_trial_hand_2_mov_obj_hand_msg_buffer(msg_buffer);
		msg_buffer = allocate_shm_server_trial_hand_2_mov_obj_hand_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = rtai_malloc(SHM_NUM_TRIAL_HAND_2_MOV_OBJ_HAND, sizeof(TrialHand2MovObjHandMsg));
//	memset(msg_buffer, 0, sizeof(MovObjHand2NeuralNetMsg));
	msg_buffer->buff_write_idx = 0;   // re-allocation with rtai_malloc might lead change in the shm of client's msg_buffer->event_scheduling_delay (if it has)
	msg_buffer->buff_read_idx = 0;  // instead of memset, clear buffer pointers.
	print_message(INFO_MSG ,"ExperimentHandlers", "TrialHand2MovObjHand", "allocate_shm_server_trial_hand_2_mov_obj_hand_msg_buffer", "Created shm_server_trial_hand_2_mov_obj_hand_msg_buffer.");
	return msg_buffer;	
}
TrialHand2MovObjHandMsg* allocate_shm_client_trial_hand_2_mov_obj_hand_msg_buffer(TrialHand2MovObjHandMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_shm_trial_hand_2_mov_obj_hand_msg_buffer(msg_buffer);
		msg_buffer = allocate_shm_server_trial_hand_2_mov_obj_hand_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = rtai_malloc(SHM_NUM_TRIAL_HAND_2_MOV_OBJ_HAND, 0);
	if (msg_buffer == NULL)
		print_message(ERROR_MSG ,"ExperimentHandlers", "TrialHand2MovObjHand", "allocate_shm_client_trial_hand_2_mov_obj_hand_msg_buffer", "Could not create shm_client_trial_hand_2_mov_obj_hand_msg_buffer.");		
	else
		print_message(INFO_MSG ,"ExperimentHandlers", "TrialHand2MovObjHand", "allocate_shm_client_trial_hand_2_mov_obj_hand_msg_buffer", "Created shm_client_trial_hand_2_mov_obj_hand_msg_buffer.");
	return msg_buffer;	
}
TrialHand2MovObjHandMsg* deallocate_shm_trial_hand_2_mov_obj_hand_msg_buffer(TrialHand2MovObjHandMsg* msg_buffer)
{
	if (msg_buffer == NULL)
		return (TrialHand2MovObjHandMsg*)print_message(BUG_MSG ,"ExperimentHandlers", "TrialHand2MovObjHand", "deallocate_shm_trial_hand_2_mov_obj_hand_msg_buffer", "msg_buffer == NULL.");    
	rtai_free(SHM_NUM_TRIAL_HAND_2_MOV_OBJ_HAND, msg_buffer);	
	return NULL;
}
bool write_to_trial_hand_2_mov_obj_hand_msg_buffer(TrialHand2MovObjHandMsg* msg_buffer, TimeStamp msg_time, TrialHand2MovObjHandMsgType msg_type, TrialHand2MovObjHandMsgAdditional additional_data)
{
	unsigned int *idx;
	idx = &(msg_buffer->buff_write_idx);
	TrialHand2MovObjHandMsgItem *buff = msg_buffer->buff;
	buff[*idx].msg_time = msg_time;
	buff[*idx].msg_type = msg_type;
	buff[*idx].additional_data = additional_data;
	if ((*idx + 1) == TRIAL_HAND_2_MOV_OBJ_HAND_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	if (*idx == msg_buffer->buff_read_idx)
		return print_message(BUG_MSG ,"ExperimentHandlers", "TrialHand2MovObjHand", "write_to_trial_hand_2_mov_obj_hand_msg_buffer", "BUFFER IS FULL!!!.");    		
	return TRUE;
}
bool get_next_trial_hand_2_mov_obj_hand_msg_buffer_item(TrialHand2MovObjHandMsg* msg_buffer, TrialHand2MovObjHandMsgItem *msg_item)
{
	unsigned int *idx;
	TrialHand2MovObjHandMsgItem *buff_item;
	idx = &(msg_buffer->buff_read_idx);
	if (*idx == msg_buffer->buff_write_idx)
		return FALSE;
	buff_item = &(msg_buffer->buff[*idx]);	
	msg_item->msg_time = buff_item->msg_time;		
	msg_item->msg_type = buff_item->msg_type;
	msg_item->additional_data = buff_item->additional_data;		
	if ((*idx + 1) == TRIAL_HAND_2_MOV_OBJ_HAND_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	return TRUE;
}
