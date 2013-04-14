#include "MovObjHand2TrialHand.h"


bool get_mov_obj_hand_2_trial_hand_msg_type_string(MovObjHand2TrialHandMsgType msg_type, char *str)
{
	switch (msg_type)
	{
		case MOV_OBJ_HAND_2_TRIAL_HAND_MSG_I_AM_ALIVE:
			if (str != NULL)
 				strcpy(str, "MOV_OBJ_HAND_2_TRIAL_HAND_MSG_I_AM_ALIVE");
			return TRUE;
		case MOV_OBJ_HAND_2_TRIAL_HAND_MSG_REWARD_REQUEST:
			if (str != NULL)
 				strcpy(str, "MOV_OBJ_HAND_2_TRIAL_HAND_MSG_REWARD_REQUEST");
			return TRUE;
		case MOV_OBJ_HAND_2_TRIAL_HAND_MSG_PUNISHMENT_REQUEST:
			if (str != NULL)
 				strcpy(str, "MOV_OBJ_HAND_2_TRIAL_HAND_MSG_PUNISHMENT_REQUEST");
			return TRUE;
		case MOV_OBJ_HAND_2_TRIAL_HAND_MSG_END_TRIAL_REQUEST:
			if (str != NULL)
 				strcpy(str, "MOV_OBJ_HAND_2_TRIAL_HAND_MSG_END_TRIAL_REQUEST");
			return TRUE;
		case MOV_OBJ_HAND_2_TRIAL_HAND_MSG_MOV_OBJ_CONTROL_ENABLED:
			if (str != NULL)
 				strcpy(str, "MOV_OBJ_HAND_2_TRIAL_HAND_MSG_MOV_OBJ_CONTROL_ENABLED");
			return TRUE;
		case MOV_OBJ_HAND_2_TRIAL_HAND_MSG_MOV_OBJ_INITIAL_DIST_2_TARGET:
			if (str != NULL)
 				strcpy(str, "MOV_OBJ_HAND_2_TRIAL_HAND_MSG_MOV_OBJ_INITIAL_DIST_2_TARGET");
			return TRUE;
		case MOV_OBJ_HAND_2_TRIAL_HAND_MSG_REACHED_2_TARGET:
			if (str != NULL)
 				strcpy(str, "MOV_OBJ_HAND_2_TRIAL_HAND_MSG_REACHED_2_TARGET");
			return TRUE;
		case MOV_OBJ_HAND_2_TRIAL_HAND_MSG_OUT_OF_ROBOT_SPACE:
			if (str != NULL)
 				strcpy(str, "MOV_OBJ_HAND_2_TRIAL_HAND_MSG_OUT_OF_ROBOT_SPACE");
			return TRUE;
////////////////////////		
		case MOV_OBJ_HAND_2_TRIAL_HAND_MSG_NULL:
			if (str != NULL)
 				strcpy(str, "MOV_OBJ_HAND_2_TRIAL_HAND_MSG_NULL");
			return FALSE;
		default:
			if (str != NULL)
 				strcpy(str, "MOV_OBJ_HAND_2_TRIAL_HAND_MSG_INVALID");
			return FALSE;
	}
}


MovObjHand2TrialHandMsg* allocate_mov_obj_hand_2_trial_hand_msg_buffer(MovObjHand2TrialHandMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_mov_obj_hand_2_trial_hand_msg_buffer(msg_buffer);
		msg_buffer = allocate_mov_obj_hand_2_trial_hand_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = g_new0(MovObjHand2TrialHandMsg,1);
	print_message(INFO_MSG ,"ExperimentHandlers", "MovObjHand2TrialHand", "allocate_mov_obj_hand_2_trial_hand_msg_buffer", "Created mov_obj_hand_2_trial_hand_msg_buffer.");
	return msg_buffer;	
}
MovObjHand2TrialHandMsg* deallocate_mov_obj_hand_2_trial_hand_msg_buffer(MovObjHand2TrialHandMsg* msg_buffer)
{
	if (msg_buffer == NULL)
		return (MovObjHand2TrialHandMsg*)print_message(BUG_MSG ,"ExperimentHandlers", "MovObjHand2TrialHand", "deallocate_mov_obj_hand_2_trial_hand_msg_buffer", "msg_buffer == NULL.");    
	g_free(msg_buffer);	
	return NULL;
}

MovObjHand2TrialHandMsg* allocate_shm_server_mov_obj_hand_2_trial_hand_msg_buffer(MovObjHand2TrialHandMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_shm_mov_obj_hand_2_trial_hand_msg_buffer(msg_buffer);
		msg_buffer = allocate_shm_server_mov_obj_hand_2_trial_hand_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = rtai_malloc(SHM_NUM_MOV_OBJ_HAND_2_TRIAL_HAND, sizeof(MovObjHand2TrialHandMsg));
//	memset(msg_buffer, 0, sizeof(MovObjHand2NeuralNetMsg));
	msg_buffer->buff_write_idx = 0;   // re-allocation with rtai_malloc might lead change in the shm of client's msg_buffer->event_scheduling_delay (if it has)
	msg_buffer->buff_read_idx = 0;  // instead of memset, clear buffer pointers.
	print_message(INFO_MSG ,"ExperimentHandlers", "MovObjHand2TrialHand", "allocate_shm_server_mov_obj_hand_2_trial_hand_msg_buffer", "Created shm_server_mov_obj_hand_2_trial_hand_msg_buffer.");
	return msg_buffer;	
}
MovObjHand2TrialHandMsg* allocate_shm_client_mov_obj_hand_2_trial_hand_msg_buffer(MovObjHand2TrialHandMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_shm_mov_obj_hand_2_trial_hand_msg_buffer(msg_buffer);
		msg_buffer = allocate_shm_server_mov_obj_hand_2_trial_hand_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = rtai_malloc(SHM_NUM_MOV_OBJ_HAND_2_TRIAL_HAND, 0);
	print_message(INFO_MSG ,"ExperimentHandlers", "MovObjHand2TrialHand", "allocate_shm_client_mov_obj_hand_2_trial_hand_msg_buffer", "Created shm_client_mov_obj_hand_2_trial_hand_msg_buffer.");
	return msg_buffer;	
}
MovObjHand2TrialHandMsg* deallocate_shm_mov_obj_hand_2_trial_hand_msg_buffer(MovObjHand2TrialHandMsg* msg_buffer)
{
	if (msg_buffer == NULL)
		return (MovObjHand2TrialHandMsg*)print_message(BUG_MSG ,"ExperimentHandlers", "MovObjHand2TrialHand", "deallocate_shm_mov_obj_hand_2_trial_hand_msg_buffer", "msg_buffer == NULL.");    
	rtai_free(SHM_NUM_MOV_OBJ_HAND_2_TRIAL_HAND, msg_buffer);	
	return NULL;
}
bool write_to_mov_obj_hand_2_trial_hand_msg_buffer(MovObjHand2TrialHandMsg* msg_buffer, TimeStamp msg_time, MovObjHand2TrialHandMsgType msg_type, MovObjHand2TrialHandMsgAdditional additional_data)
{
	unsigned int *idx;
	idx = &(msg_buffer->buff_write_idx);
	MovObjHand2TrialHandMsgItem *buff = msg_buffer->buff;
	buff[*idx].msg_time = msg_time;
	buff[*idx].msg_type = msg_type;
	buff[*idx].additional_data = additional_data;
	if ((*idx + 1) == MOV_OBJ_HAND_2_TRIAL_HAND_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	if (*idx == msg_buffer->buff_read_idx)
		return print_message(BUG_MSG ,"ExperimentHandlers", "MovObjHand2TrialHand", "write_to_mov_obj_hand_2_trial_hand_msg_buffer", "BUFFER IS FULL!!!.");    		
	return TRUE;
}
bool get_next_mov_obj_hand_2_trial_hand_msg_buffer_item(MovObjHand2TrialHandMsg* msg_buffer, MovObjHand2TrialHandMsgItem *msg_item)
{
	unsigned int *idx;
	MovObjHand2TrialHandMsgItem *buff_item;
	idx = &(msg_buffer->buff_read_idx);
	if (*idx == msg_buffer->buff_write_idx)
		return FALSE;
	buff_item = &(msg_buffer->buff[*idx]);	
	msg_item->msg_time = buff_item->msg_time;		
	msg_item->msg_type = buff_item->msg_type;
	msg_item->additional_data = buff_item->additional_data;
	if ((*idx + 1) == MOV_OBJ_HAND_2_TRIAL_HAND_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	return TRUE;
}
