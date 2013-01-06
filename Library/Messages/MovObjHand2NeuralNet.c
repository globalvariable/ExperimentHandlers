#include "MovObjHand2NeuralNet.h"


bool get_mov_obj_hand_2_neural_net_msg_type_string(MovObjHand2NeuralNetMsgType msg_type, char *str)
{
	switch (msg_type)
	{
		case MOV_OBJ_HAND_2_NEURAL_NET_MSG_ARE_YOU_ALIVE:
			if (str != NULL)
 				strcpy(str, "MOV_OBJ_HAND_2_NEURAL_NET_MSG_ARE_YOU_ALIVE");
			return TRUE;
		case MOV_OBJ_HAND_2_NEURAL_NET_MSG_3_DOF_JOINT_ANGLE:
			if (str != NULL)
 				strcpy(str, "MOV_OBJ_HAND_2_NEURAL_NET_MSG_3_DOF_JOINT_ANGLE");
			return TRUE;
		case MOV_OBJ_HAND_2_NEURAL_NET_MSG_JOINT_ANGLE_MIN:
			if (str != NULL)
 				strcpy(str, "MOV_OBJ_HAND_2_NEURAL_NET_MSG_JOINT_ANGLE_MIN");
			return TRUE;
		case MOV_OBJ_HAND_2_NEURAL_NET_MSG_JOINT_ANGLE_MAX:
			if (str != NULL)
 				strcpy(str, "MOV_OBJ_HAND_2_NEURAL_NET_MSG_JOINT_ANGLE_MAX");
			return TRUE;
/////////////////////////		
		case MOV_OBJ_HAND_2_NEURAL_NET_MSG_NULL:
			if (str != NULL)
 				strcpy(str, "MOV_OBJ_HAND_2_NEURAL_NET_MSG_NULL");
			return FALSE;
		default:
			if (str != NULL)
 				strcpy(str, "MOV_OBJ_HAND_2_NEURAL_NET_MSG_INVALID");
			return FALSE;
	}

}


MovObjHand2NeuralNetMsg* allocate_mov_obj_hand_2_neural_net_msg_buffer(MovObjHand2NeuralNetMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_mov_obj_hand_2_neural_net_msg_buffer(msg_buffer);
		msg_buffer = allocate_mov_obj_hand_2_neural_net_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = g_new0(MovObjHand2NeuralNetMsg,1);
	print_message(INFO_MSG ,"ExperimentHandlers", "MovObjHand2NeuralNet", "allocate_mov_obj_hand_2_neural_net_msg_buffer", "Created mov_obj_hand_2_neural_net_msg_buffer.");
	return msg_buffer;	
}
MovObjHand2NeuralNetMsg* deallocate_mov_obj_hand_2_neural_net_msg_buffer(MovObjHand2NeuralNetMsg* msg_buffer)
{
	if (msg_buffer == NULL)
		return (MovObjHand2NeuralNetMsg*)print_message(BUG_MSG ,"ExperimentHandlers", "MovObjHand2NeuralNet", "deallocate_mov_obj_hand_2_neural_net_msg_buffer", "msg_buffer == NULL.");    
	g_free(msg_buffer);	
	return NULL;
}

MovObjHand2NeuralNetMsg* allocate_shm_server_mov_obj_hand_2_neural_net_msg_buffer(MovObjHand2NeuralNetMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_shm_mov_obj_hand_2_neural_net_msg_buffer(msg_buffer);
		msg_buffer = allocate_shm_server_mov_obj_hand_2_neural_net_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = rtai_malloc(SHM_NUM_MOV_OBJ_HAND_2_NEURAL_NET, sizeof(MovObjHand2NeuralNetMsg));
//	memset(msg_buffer, 0, sizeof(MovObjHand2NeuralNetMsg));
	msg_buffer->buff_write_idx = 0;   // re-allocation with rtai_malloc might lead change in the shm of client's msg_buffer->event_scheduling_delay
	msg_buffer->buff_read_idx = 0;  // instead of memset, clear buffer pointers.
	print_message(INFO_MSG ,"ExperimentHandlers", "MovObjHand2NeuralNet", "allocate_shm_server_mov_obj_hand_2_neural_net_msg_buffer", "Created shm_server_mov_obj_hand_2_neural_net_msg_buffer.");
	return msg_buffer;	
}
MovObjHand2NeuralNetMsg* allocate_shm_client_mov_obj_hand_2_neural_net_msg_buffer(MovObjHand2NeuralNetMsg* msg_buffer, TimeStamp event_scheduling_delay) // since client is the writer to the buffer, it shoud schedule events. server does not need to know the event scheduling delay
{
	if (event_scheduling_delay < MIN_MOV_OBJ_HAND_2_NEURAL_NET_EVENT_SCHEDULING_DELAY)
		return (MovObjHand2NeuralNetMsg*)print_message(ERROR_MSG ,"ExperimentHandlers", "MovObjHand2NeuralNet", "allocate_shm_client_mov_obj_hand_2_neural_net_msg_buffer", "event_scheduling_delay < MIN_MOV_OBJ_HAND_2_NEURAL_NET_EVENT_SCHEDULING_DELAY."); 
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_shm_mov_obj_hand_2_neural_net_msg_buffer(msg_buffer);
		msg_buffer = allocate_shm_server_mov_obj_hand_2_neural_net_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = rtai_malloc(SHM_NUM_MOV_OBJ_HAND_2_NEURAL_NET, 0);
	msg_buffer->event_scheduling_delay = event_scheduling_delay;
	print_message(INFO_MSG ,"ExperimentHandlers", "MovObjHand2NeuralNet", "allocate_shm_client_mov_obj_hand_2_neural_net_msg_buffer", "Created shm_client_mov_obj_hand_2_neural_net_msg_buffer.");
	return msg_buffer;	
}
MovObjHand2NeuralNetMsg* deallocate_shm_mov_obj_hand_2_neural_net_msg_buffer(MovObjHand2NeuralNetMsg* msg_buffer)
{
	if (msg_buffer == NULL)
		return (MovObjHand2NeuralNetMsg*)print_message(BUG_MSG ,"ExperimentHandlers", "MovObjHand2NeuralNet", "deallocate_shm_mov_obj_hand_2_neural_net_msg_buffer", "msg_buffer == NULL.");    
	rtai_free(SHM_NUM_MOV_OBJ_HAND_2_NEURAL_NET, msg_buffer);	
	return NULL;
}
bool write_to_mov_obj_hand_2_neural_net_msg_buffer(MovObjHand2NeuralNetMsg* msg_buffer, TimeStamp msg_time, MovObjHand2NeuralNetMsgType msg_type, MovObjHand2NeuralNetMsgAdditional additional_data)
{
	unsigned int *idx;
	idx = &(msg_buffer->buff_write_idx);
	MovObjHand2NeuralNetMsgItem *buff = msg_buffer->buff;
	buff[*idx].msg_time = msg_time;
	buff[*idx].msg_type = msg_type;
	buff[*idx].scheduled_time = msg_time + msg_buffer->event_scheduling_delay; 
	buff[*idx].additional_data = additional_data;
	if ((*idx + 1) == MOV_OBJ_HAND_2_NEURAL_NET_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	if (*idx == msg_buffer->buff_read_idx)
		return print_message(BUG_MSG ,"ExperimentHandlers", "MovObjHand2NeuralNet", "write_to_mov_obj_hand_2_neural_net_msg_buffer", "BUFFER IS FULL!!!.");    		
	return TRUE;
}
bool get_next_mov_obj_hand_2_neural_net_msg_buffer_item(MovObjHand2NeuralNetMsg* msg_buffer, MovObjHand2NeuralNetMsgItem *msg_item)
{
	unsigned int *idx;
	MovObjHand2NeuralNetMsgItem *buff_item;
	idx = &(msg_buffer->buff_read_idx);
	if (*idx == msg_buffer->buff_write_idx)
		return FALSE;
	buff_item = &(msg_buffer->buff[*idx]);	
	msg_item->msg_time = buff_item->msg_time;		
	msg_item->msg_type = buff_item->msg_type;
	msg_item->additional_data = buff_item->additional_data;		
	if ((*idx + 1) == MOV_OBJ_HAND_2_NEURAL_NET_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	return TRUE;
}

MovObjHand2NeuralNetMsgMultiThread* allocate_shm_server_mov_obj_hand_2_neural_net_multi_thread_msg_buffer(MovObjHand2NeuralNetMsgMultiThread* msg_buffers)
{
	unsigned int i;
	if (msg_buffers != NULL)
	{
		msg_buffers = deallocate_shm_mov_obj_hand_2_neural_net_multi_thread_msg_buffer(msg_buffers);
		msg_buffers = allocate_shm_server_mov_obj_hand_2_neural_net_multi_thread_msg_buffer(msg_buffers);
		return msg_buffers;
	}
	msg_buffers = g_new0(MovObjHand2NeuralNetMsgMultiThread, 1);  
	for (i = 0; i < (NUM_OF_MOV_OBJ_HAND_2_NEURAL_NET_MSG_BUFFERS); i++)
	{
		(*msg_buffers)[i] = rtai_malloc(SHM_NUM_MOV_OBJ_HAND_2_NEURAL_NET+i, sizeof(MovObjHand2NeuralNetMsg));
//		memset((*msg_buffers)[i], 0, sizeof(MovObjHand2NeuralNetMsg));	 // re-allocation with rtai_malloc might lead change in the shm of client's msg_buffer->event_scheduling_delay (if it has)
		(*msg_buffers)[i]->buff_write_idx = 0;   // re-allocation with rtai_malloc might lead change in the shm of client's msg_buffer->event_scheduling_delay (if it has)
		(*msg_buffers)[i]->buff_read_idx = 0;  // instead of memset, clear buffer pointers.		
	}
	print_message(INFO_MSG ,"ExperimentHandlers", "MovObjHand2NeuralNet", "allocate_shm_server_mov_obj_hand_2_neural_net_multi_thread_msg_buffer", "Created shm_server_mov_obj_hand_2_neural_net_multi_thread_msg_buffer.");
	return msg_buffers;
}

MovObjHand2NeuralNetMsg* allocate_shm_client_mov_obj_hand_2_neural_net_multi_thread_msg_buffer_item(MovObjHand2NeuralNetMsgMultiThread* msg_buffers, unsigned int msg_buffer_num, TimeStamp event_scheduling_delay)
{
	if (event_scheduling_delay < MIN_MOV_OBJ_HAND_2_NEURAL_NET_EVENT_SCHEDULING_DELAY)
		return (MovObjHand2NeuralNetMsg*)print_message(ERROR_MSG ,"ExperimentHandlers", "MovObjHand2NeuralNet", "allocate_shm_client_mov_obj_hand_2_neural_net_multi_thread_msg_buffer_item", "event_scheduling_delay < MIN_MOV_OBJ_HAND_2_NEURAL_NET_EVENT_SCHEDULING_DELAY."); 

	(*msg_buffers)[msg_buffer_num]  = rtai_malloc(SHM_NUM_MOV_OBJ_HAND_2_NEURAL_NET+msg_buffer_num, 0);
	if ((*msg_buffers)[msg_buffer_num] == NULL)
		return (MovObjHand2NeuralNetMsg*)print_message(ERROR_MSG ,"ExperimentHandlers", "MovObjHand2NeuralNet", "allocate_shm_client_mov_obj_hand_2_neural_net_multi_thread_msg_buffer_item", "First allocate_shm_SERVER_mov_obj_hand_2_neural_net_multi_thread_msg_buffer_item via running Neural Net."); 
	(*msg_buffers)[msg_buffer_num]->event_scheduling_delay = event_scheduling_delay;
	print_message(INFO_MSG ,"ExperimentHandlers", "MovObjHand2NeuralNet", "allocate_shm_client_mov_obj_hand_2_neural_net_multi_thread_msg_buffer", "Created shm_client_mov_obj_hand_2_neural_net_multi_thread_msg_buffer_item.");
	return (*msg_buffers)[msg_buffer_num] ;
}

MovObjHand2NeuralNetMsgMultiThread* deallocate_shm_mov_obj_hand_2_neural_net_multi_thread_msg_buffer(MovObjHand2NeuralNetMsgMultiThread* msg_buffers)
{
	unsigned int i;
	if (msg_buffers == NULL)
		return (MovObjHand2NeuralNetMsgMultiThread*)print_message(BUG_MSG ,"ExperimentHandlers", "MovObjHand2NeuralNet", "deallocate_shm_mov_obj_hand_2_neural_net_multi_thread_msg_buffer", "msg_buffers == NULL.");
	for (i = 0; i < (NUM_OF_MOV_OBJ_HAND_2_NEURAL_NET_MSG_BUFFERS); i++)
	{
		(*msg_buffers)[i] = deallocate_shm_mov_obj_hand_2_neural_net_msg_buffer((*msg_buffers)[i]);
	}
	g_free(msg_buffers);	
	return NULL;
}
