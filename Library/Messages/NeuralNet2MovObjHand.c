#include "NeuralNet2MovObjHand.h"

bool get_neural_net_2_mov_obj_hand_msg_type_string(NeuralNet2MovObjHandMsgType msg_type, char *str)
{
	switch (msg_type)
	{
		case NEURAL_NET_2_MOV_OBJ_HAND_MSG_I_AM_ALIVE:
			if (str != NULL)
 				strcpy(str, "NEURAL_NET_2_MOV_OBJ_HAND_MSG_I_AM_ALIVE");
			return TRUE;
		case NEURAL_NET_2_MOV_OBJ_HAND_MSG_DIRECTION_SPEED_LOCATION:
			if (str != NULL)
 				strcpy(str, "NEURAL_NET_2_MOV_OBJ_HAND_MSG_DIRECTION_SPEED_LOCATION");
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
bool write_to_neural_net_2_mov_obj_hand_msg_buffer(NeuralNet2MovObjHandMsg* msg_buffer, TimeStamp msg_time, NeuralNet2MovObjHandMsgType msg_type, MovObjCompNum comp_num, MovObjDirectionType direction, MovObjSpeedType speed, MovObjLocationType location)
{
	unsigned int *idx;
	idx = &(msg_buffer->buff_write_idx);
	NeuralNet2MovObjHandMsgItem *buff = msg_buffer->buff;
	buff[*idx].msg_time = msg_time;
	buff[*idx].msg_type = msg_type;
	buff[*idx].comp_num = comp_num;
	buff[*idx].direction = direction;
	buff[*idx].speed = speed;
	buff[*idx].location = location;
	if ((*idx + 1) == NEURAL_NET_2_MOV_OBJ_HAND_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	if (*idx == msg_buffer->buff_read_idx)
		return print_message(BUG_MSG ,"ExperimentHandlers", "NeuralNet2MovObjHand", "write_to_neural_net_2_mov_obj_hand_msg_buffer", "BUFFER IS FULL!!!.");    		
	return TRUE;
}
bool get_next_neural_net_2_mov_obj_hand_msg_buffer_item(NeuralNet2MovObjHandMsg* msg_buffer, NeuralNet2MovObjHandMsgItem **msg_item)
{
	unsigned int *idx;
	idx = &(msg_buffer->buff_read_idx);
	if (*idx == msg_buffer->buff_write_idx)
		return FALSE;
	*msg_item = &(msg_buffer->buff[*idx]);	
	if ((*idx + 1) == NEURAL_NET_2_MOV_OBJ_HAND_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	return TRUE;
}
