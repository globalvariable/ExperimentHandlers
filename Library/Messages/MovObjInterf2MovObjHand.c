#include "MovObjInterf2MovObjHand.h"

bool get_mov_obj_interf_2_mov_obj_hand_msg_type_string(MovObjInterf2MovObjHandMsgType msg_type, char *str)
{
	switch (msg_type)
	{
		case MOV_OBJ_INTERF_2_MOV_OBJ_HAND_MSG_I_AM_ALIVE:
			if (str != NULL)
 				strcpy(str, "MOV_OBJ_INTERF_2_MOV_OBJ_HAND_MSG_I_AM_ALIVE");
			return TRUE;
		case MOV_OBJ_INTERF_2_MOV_OBJ_HAND_MSG_DIRECTION_SPEED_LOCATION:
			if (str != NULL)
 				strcpy(str, "MOV_OBJ_INTERF_2_MOV_OBJ_HAND_MSG_DIRECTION_SPEED_LOCATION");
			return TRUE;
/////////////////////////		
		case MOV_OBJ_INTERF_2_MOV_OBJ_HAND_MSG_NULL:
			if (str != NULL)
 				strcpy(str, "MOV_OBJ_INTERF_2_MOV_OBJ_HAND_MSG_NULL");
			return FALSE;
		default:
			if (str != NULL)
 				strcpy(str, "MOV_OBJ_INTERF_2_MOV_OBJ_HAND_MSG_INVALID");
			return FALSE;
	}

}

MovObjInterf2MovObjHandMsg* allocate_mov_obj_interf_2_mov_obj_hand_msg_buffer(MovObjInterf2MovObjHandMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_mov_obj_interf_2_mov_obj_hand_msg_buffer(msg_buffer);
		msg_buffer = allocate_mov_obj_interf_2_mov_obj_hand_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = g_new0(MovObjInterf2MovObjHandMsg,1);
	print_message(INFO_MSG ,"ExperimentHandlers", "MovObjInterf2MovObjHand", "allocate_mov_obj_interf_2_mov_obj_hand_msg_buffer", "Created mov_obj_interf_2_mov_obj_hand_msg_buffer.");
	return msg_buffer;	
}
MovObjInterf2MovObjHandMsg* deallocate_mov_obj_interf_2_mov_obj_hand_msg_buffer(MovObjInterf2MovObjHandMsg* msg_buffer)
{
	if (msg_buffer == NULL)
		return (MovObjInterf2MovObjHandMsg*)print_message(BUG_MSG ,"ExperimentHandlers", "MovObjInterf2MovObjHand", "deallocate_mov_obj_interf_2_mov_obj_hand_msg_buffer", "msg_buffer == NULL.");    
	g_free(msg_buffer);	
	return NULL;
}


MovObjInterf2MovObjHandMsg* allocate_shm_server_mov_obj_interf_2_mov_obj_hand_msg_buffer(MovObjInterf2MovObjHandMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_shm_mov_obj_interf_2_mov_obj_hand_msg_buffer(msg_buffer);
		msg_buffer = allocate_shm_server_mov_obj_interf_2_mov_obj_hand_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = rtai_malloc(nam2num(MOV_OBJ_INTERF_2_MOV_OBJ_HAND_SHM_NAME), sizeof(MovObjInterf2MovObjHandMsg));
//	memset(msg_buffer, 0, sizeof(MovObjHand2NeuralNetMsg));
	msg_buffer->buff_write_idx = 0;   // re-allocation with rtai_malloc might lead change in the shm of client's msg_buffer->event_scheduling_delay (if it has)
	msg_buffer->buff_read_idx = 0;  // instead of memset, clear buffer pointers.
	print_message(INFO_MSG ,"ExperimentHandlers", "MovObjInterf2MovObjHand", "allocate_shm_server_mov_obj_interf_2_mov_obj_hand_msg_buffer", "Created shm_server_mov_obj_interf_2_mov_obj_hand_msg_buffer.");
	return msg_buffer;	
}
MovObjInterf2MovObjHandMsg* allocate_shm_client_mov_obj_interf_2_mov_obj_hand_msg_buffer(MovObjInterf2MovObjHandMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_shm_mov_obj_interf_2_mov_obj_hand_msg_buffer(msg_buffer);
		msg_buffer = allocate_shm_client_mov_obj_interf_2_mov_obj_hand_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = rtai_malloc(nam2num(MOV_OBJ_INTERF_2_MOV_OBJ_HAND_SHM_NAME), 0);
	print_message(INFO_MSG ,"ExperimentHandlers", "MovObjInterf2MovObjHand", "allocate_shm_client_mov_obj_interf_2_mov_obj_hand_msg_buffer", "Created shm_client_mov_obj_interf_2_mov_obj_hand_msg_buffer.");
	return msg_buffer;
}
MovObjInterf2MovObjHandMsg* deallocate_shm_mov_obj_interf_2_mov_obj_hand_msg_buffer(MovObjInterf2MovObjHandMsg* msg_buffer)
{
	if (msg_buffer == NULL)
		return (MovObjInterf2MovObjHandMsg*)print_message(BUG_MSG ,"ExperimentHandlers", "MovObjInterf2MovObjHand", "deallocate_shm_mov_obj_interf_2_mov_obj_hand_msg_buffer", "msg_buffer == NULL.");    
	rtai_free(nam2num(MOV_OBJ_INTERF_2_MOV_OBJ_HAND_SHM_NAME), msg_buffer);	
	return NULL;
}
bool write_to_mov_obj_interf_2_mov_obj_hand_msg_buffer(MovObjInterf2MovObjHandMsg* msg_buffer, TimeStamp msg_time, MovObjInterf2MovObjHandMsgType msg_type, MovObjCompNum comp_num, MovObjDirectionType direction, MovObjSpeedType speed, MovObjLocationType location)
{
	unsigned int *idx;
	idx = &(msg_buffer->buff_write_idx);
	MovObjInterf2MovObjHandMsgItem *buff = msg_buffer->buff;
	buff[*idx].msg_time = msg_time;
	buff[*idx].msg_type = msg_type;
	buff[*idx].comp_num = comp_num;
	buff[*idx].direction = direction;
	buff[*idx].speed = speed;
	buff[*idx].location = location;
	if ((*idx + 1) == MOV_OBJ_INTERF_2_MOV_OBJ_HAND_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	if (*idx == msg_buffer->buff_read_idx)
		return print_message(BUG_MSG ,"ExperimentHandlers", "MovObjInterf2MovObjHand", "write_to_mov_obj_interf_2_mov_obj_hand_msg_buffer", "BUFFER IS FULL!!!.");    		
	return TRUE;
}
bool get_next_mov_obj_interf_2_mov_obj_hand_msg_buffer_item(MovObjInterf2MovObjHandMsg* msg_buffer, MovObjInterf2MovObjHandMsgItem *msg_item)
{
	unsigned int *idx;
	MovObjInterf2MovObjHandMsgItem *buff_item;
	idx = &(msg_buffer->buff_read_idx);
	if (*idx == msg_buffer->buff_write_idx)
		return FALSE;
	buff_item = &(msg_buffer->buff[*idx]);	
	msg_item->msg_time = buff_item->msg_time;		
	msg_item->msg_type = buff_item->msg_type;
	msg_item->comp_num = buff_item->comp_num;
	msg_item->direction = buff_item->direction;
	msg_item->speed = buff_item->speed;
	msg_item->location = buff_item->location;
	if ((*idx + 1) == MOV_OBJ_INTERF_2_MOV_OBJ_HAND_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	return TRUE;
}
