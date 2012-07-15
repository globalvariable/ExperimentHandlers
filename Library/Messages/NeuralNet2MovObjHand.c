#include "NeuralNet2MovObjHand.h"

bool get_neural_net_2_mov_obj_hand_msg_type_string(NeuralNet2MovObjHandMsgType msg_type, char *str)
{
	switch (msg_type)
	{
		case NEURAL_NET_2_MOV_OBJ_HAND_MSG_I_AM_ALIVE:
			if (str != NULL)
 				strcpy(str, "NEURAL_NET_2_MOV_OBJ_HAND_MSG_I_AM_ALIVE");
			return TRUE;
		case NEURAL_NET_2_MOV_OBJ_HAND_MSG_SPIKE_OUTPUT:
			if (str != NULL)
 				strcpy(str, "NEURAL_NET_2_MOV_OBJ_HAND_MSG_SPIKE_OUTPUT");
			return TRUE;
/////////////////////////		
		case NEURAL_NET_2_MOV_OBJ_HAND_MSG_NULL:
			if (str != NULL)
 				strcpy(str, "NEURAL_NET_2_MOV_OBJ_HAND_MSG_NULL");
			return FALSE;
		default:
			if (str != NULL)
 				strcpy(str, "NEURAL_NET_2_MOV_OBJ_HAND_MSG_INVALID");
			return FALSE;
	}

}

NeuralNet2MovObjHandMsg* allocate_neural_net_2_mov_obj_hand_msg_buffer(NeuralNet2MovObjHandMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_neural_net_2_mov_obj_hand_msg_buffer(msg_buffer);
		msg_buffer = allocate_neural_net_2_mov_obj_hand_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = g_new0(NeuralNet2MovObjHandMsg,1);
	print_message(INFO_MSG ,"ExperimentHandlers", "NeuralNet2MovObjHand", "allocate_neural_net_2_mov_obj_hand_msg_buffer", "Created neural_net_2_mov_obj_hand_msg_buffer.");
	return msg_buffer;	
}
NeuralNet2MovObjHandMsg* deallocate_neural_net_2_mov_obj_hand_msg_buffer(NeuralNet2MovObjHandMsg* msg_buffer)
{
	if (msg_buffer == NULL)
		return (NeuralNet2MovObjHandMsg*)print_message(BUG_MSG ,"ExperimentHandlers", "NeuralNet2MovObjHand", "deallocate_neural_net_2_mov_obj_hand_msg_buffer", "msg_buffer == NULL.");    
	g_free(msg_buffer);	
	return NULL;
}


NeuralNet2MovObjHandMsg* allocate_shm_server_neural_net_2_mov_obj_hand_msg_buffer(NeuralNet2MovObjHandMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_shm_neural_net_2_mov_obj_hand_msg_buffer(msg_buffer);
		msg_buffer = allocate_shm_server_neural_net_2_mov_obj_hand_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = rtai_malloc(nam2num(NEURAL_NET_2_MOV_OBJ_HAND_SHM_NAME), sizeof(NeuralNet2MovObjHandMsg));
	memset(msg_buffer, 0, sizeof(NeuralNet2MovObjHandMsg));
	print_message(INFO_MSG ,"ExperimentHandlers", "NeuralNet2MovObjHand", "allocate_shm_server_neural_net_2_mov_obj_hand_msg_buffer", "Created shm_server_neural_net_2_mov_obj_hand_msg_buffer.");
	return msg_buffer;	
}
NeuralNet2MovObjHandMsg* allocate_shm_client_neural_net_2_mov_obj_hand_msg_buffer(NeuralNet2MovObjHandMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_shm_neural_net_2_mov_obj_hand_msg_buffer(msg_buffer);
		msg_buffer = allocate_shm_client_neural_net_2_mov_obj_hand_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = rtai_malloc(nam2num(NEURAL_NET_2_MOV_OBJ_HAND_SHM_NAME), 0);
	print_message(INFO_MSG ,"ExperimentHandlers", "NeuralNet2MovObjHand", "allocate_shm_client_neural_net_2_mov_obj_hand_msg_buffer", "Created shm_client_neural_net_2_mov_obj_hand_msg_buffer.");
	return msg_buffer;
}
NeuralNet2MovObjHandMsg* deallocate_shm_neural_net_2_mov_obj_hand_msg_buffer(NeuralNet2MovObjHandMsg* msg_buffer)
{
	if (msg_buffer == NULL)
		return (NeuralNet2MovObjHandMsg*)print_message(BUG_MSG ,"ExperimentHandlers", "NeuralNet2MovObjHand", "deallocate_shm_neural_net_2_mov_obj_hand_msg_buffer", "msg_buffer == NULL.");    
	rtai_free(nam2num(NEURAL_NET_2_MOV_OBJ_HAND_SHM_NAME), msg_buffer);	
	return NULL;
}
bool write_to_neural_net_2_mov_obj_hand_msg_buffer(NeuralNet2MovObjHandMsg* msg_buffer, TimeStamp msg_time, NeuralNet2MovObjHandMsgType msg_type, unsigned int layer_num, unsigned int nrn_grp_num, unsigned int neuron_num, TimeStamp spike_time)
{
	unsigned int *idx;
	idx = &(msg_buffer->buff_write_idx);
	NeuralNet2MovObjHandMsgItem *buff = msg_buffer->buff;

	buff[*idx].msg_time = msg_time;
	buff[*idx].msg_type = msg_type;
	buff[*idx].layer_num = layer_num;
	buff[*idx].nrn_grp_num = nrn_grp_num;
	buff[*idx].neuron_num = neuron_num;
	buff[*idx].spike_time = spike_time;
	if ((*idx + 1) == NEURAL_NET_2_MOV_OBJ_HAND_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	if (*idx == msg_buffer->buff_read_idx)
		return print_message(BUG_MSG ,"ExperimentHandlers", "NeuralNet2MovObjHand", "write_to_neural_net_2_mov_obj_hand_msg_buffer", "BUFFER IS FULL!!!.");    		
	return TRUE;
}
bool get_next_neural_net_2_mov_obj_hand_msg_buffer_item(NeuralNet2MovObjHandMsg* msg_buffer, NeuralNet2MovObjHandMsgItem *msg_item)
{
	unsigned int *idx;
	NeuralNet2MovObjHandMsgItem *buff_item;
	idx = &(msg_buffer->buff_read_idx);
	if (*idx == msg_buffer->buff_write_idx)
		return FALSE;
	buff_item = &(msg_buffer->buff[*idx]);	
	msg_item->msg_time = buff_item->msg_time;		
	msg_item->msg_type = buff_item->msg_type;
	msg_item->layer_num = buff_item->layer_num;	
	msg_item->nrn_grp_num = buff_item->nrn_grp_num;	
	msg_item->neuron_num = buff_item->neuron_num;	
	msg_item->spike_time = buff_item->spike_time;	
	if ((*idx + 1) == NEURAL_NET_2_MOV_OBJ_HAND_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	return TRUE;
}

NeuralNet2MovObjHandMsgMultiThread* allocate_shm_server_neural_net_2_mov_obj_hand_multi_thread_msg_buffer(NeuralNet2MovObjHandMsgMultiThread* msg_buffers)
{
	char shared_mem_name[10];
	char shared_mem_num_name[4];	
	unsigned int i;

	if (msg_buffers != NULL)
	{
		msg_buffers = deallocate_shm_neural_net_2_mov_obj_hand_multi_thread_msg_buffer(msg_buffers);
		msg_buffers = allocate_shm_server_neural_net_2_mov_obj_hand_multi_thread_msg_buffer(msg_buffers);
		return msg_buffers;
	}
	msg_buffers = g_new0(NeuralNet2MovObjHandMsgMultiThread, 1);  
	for (i = 0; i < (NUM_OF_NEURAL_NET_2_MOV_OBJ_HAND_MSG_BUFFERS); i++)
	{
		strcpy(shared_mem_name, NEURAL_NET_2_MOV_OBJ_HAND_SHM_NAME);
		sprintf(shared_mem_num_name, "%u", i);
		strcat(shared_mem_name, shared_mem_num_name);
		if (msg_buffers[i] != NULL)
		{
			(*msg_buffers)[i] = deallocate_shm_neural_net_2_mov_obj_hand_msg_buffer((*msg_buffers)[i]);
			(*msg_buffers)[i] = allocate_shm_server_neural_net_2_mov_obj_hand_msg_buffer((*msg_buffers)[i]);
		}  
		(*msg_buffers)[i] = rtai_malloc(nam2num(shared_mem_name), sizeof(NeuralNet2MovObjHandMsg));
		memset((*msg_buffers)[i], 0, sizeof(NeuralNet2MovObjHandMsg));		
	}
	print_message(INFO_MSG ,"ExperimentHandlers", "NeuralNet2MovObjHand", "allocate_shm_server_neural_net_2_mov_obj_hand_multi_thread_msg_buffer", "Created shm_server_neural_net_2_mov_obj_hand_multi_thread_msg_buffer.");
	return msg_buffers;
}

NeuralNet2MovObjHandMsg* allocate_shm_client_neural_net_2_mov_obj_hand_multi_thread_msg_buffer_item(NeuralNet2MovObjHandMsgMultiThread* msg_buffers, unsigned int msg_buffer_num)
{
	char shared_mem_name[10];
	char shared_mem_num_name[4];	
	strcpy(shared_mem_name, NEURAL_NET_2_MOV_OBJ_HAND_SHM_NAME);
	sprintf(shared_mem_num_name, "%u", msg_buffer_num);
	strcat(shared_mem_name, shared_mem_num_name);
	if ((*msg_buffers)[msg_buffer_num] != NULL)
	{
		(*msg_buffers)[msg_buffer_num] = deallocate_shm_neural_net_2_mov_obj_hand_msg_buffer((*msg_buffers)[msg_buffer_num]);
		(*msg_buffers)[msg_buffer_num] = allocate_shm_client_neural_net_2_mov_obj_hand_multi_thread_msg_buffer_item(msg_buffers, msg_buffer_num);
		return (*msg_buffers)[msg_buffer_num] ;
	}  
	(*msg_buffers)[msg_buffer_num]  = rtai_malloc(nam2num(shared_mem_name), 0);
	print_message(INFO_MSG ,"ExperimentHandlers", "NeuralNet2MovObjHand", "allocate_shm_client_neural_net_2_mov_obj_hand_multi_thread_msg_buffer", "Created shm_client_neural_net_2_mov_obj_hand_multi_thread_msg_buffer_item.");
	return (*msg_buffers)[msg_buffer_num] ;
}

NeuralNet2MovObjHandMsgMultiThread* deallocate_shm_neural_net_2_mov_obj_hand_multi_thread_msg_buffer(NeuralNet2MovObjHandMsgMultiThread* msg_buffers)
{
	unsigned int i;
	if (msg_buffers == NULL)
		return (NeuralNet2MovObjHandMsgMultiThread*)print_message(BUG_MSG ,"ExperimentHandlers", "NeuralNet2MovObjHand", "deallocate_shm_neural_net_2_mov_obj_hand_multi_thread_msg_buffer", "msg_buffers == NULL.");
	for (i = 0; i < (NUM_OF_NEURAL_NET_2_MOV_OBJ_HAND_MSG_BUFFERS); i++)
	{
		(*msg_buffers)[i] = deallocate_shm_neural_net_2_mov_obj_hand_msg_buffer((*msg_buffers)[i]);
	}
	g_free(msg_buffers);	
	return NULL;
}

