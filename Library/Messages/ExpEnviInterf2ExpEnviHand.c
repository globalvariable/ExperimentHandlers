#include "ExpEnviInterf2ExpEnviHand.h"

bool get_exp_envi_interf_2_exp_envi_hand_msg_type_string(ExpEnviInterf2ExpEnviHandMsgType msg_type, char *str)
{
	switch (msg_type)
	{

/////////////////////////		
		case EXP_ENVI_INTERF_2_EXP_ENVI_HAND_MSG_NULL:
			if (str != NULL)
 				strcpy(str, "EXP_ENVI_INTERF_2_EXP_ENVI_HAND_MSG_NULL");
			return FALSE;
		default:
			if (str != NULL)
 				strcpy(str, "EXP_ENVI_INTERF_2_EXP_ENVI_HAND_MSG_INVALID");
			return FALSE;
	}

}

ExpEnviInterf2ExpEnviHandMsg* allocate_exp_envi_interf_2_exp_envi_hand_msg_buffer(ExpEnviInterf2ExpEnviHandMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_exp_envi_hand_2_exp_envi_interf_msg_buffer(msg_buffer);
		msg_buffer = allocate_exp_envi_hand_2_exp_envi_interf_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = g_new0(ExpEnviHand2ExpEnviInterfMsg,1);
	print_message(INFO_MSG ,"ExperimentHandlers", "ExpEnviInterf2ExpEnviHand", "allocate_exp_envi_interf_2_exp_envi_hand_msg_buffer", "Created exp_envi_interf_2_exp_envi_hand_msg_buffer.");
	return msg_buffer;	
}
ExpEnviInterf2ExpEnviHandMsg* deallocate_exp_envi_interf_2_exp_envi_hand_msg_buffer(ExpEnviInterf2ExpEnviHandMsg* msg_buffer)
{
	if (msg_buffer == NULL)
		return (ExpEnviInterf2ExpEnviHandMsg*)print_message(BUG_MSG ,"ExperimentHandlers", "ExpEnviInterf2ExpEnviHand", "deallocate_exp_envi_interf_2_exp_envi_hand_msg_buffer", "msg_buffer == NULL.");    
	g_free(msg_buffer);	
	return NULL;
}


ExpEnviInterf2ExpEnviHandMsg* allocate_shm_server_exp_envi_interf_2_exp_envi_hand_msg_buffer(ExpEnviInterf2ExpEnviHandMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_shm_server_exp_envi_interf_2_exp_envi_hand_msg_buffer(msg_buffer);
		msg_buffer = allocate_shm_server_exp_envi_interf_2_exp_envi_hand_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = rtai_malloc(nam2num(EXP_ENVI_INTERF_2_EXP_ENVI_HAND_SHM_NAME), sizeof(ExpEnviInterf2ExpEnviHandMsg));
	print_message(INFO_MSG ,"ExperimentHandlers", "ExpEnviInterf2ExpEnviHand", "allocate_shm_server_exp_envi_interf_2_exp_envi_hand_msg_buffer", "Created shm_server_exp_envi_interf_2_exp_envi_hand_msg_buffer.");
	return msg_buffer;	
}
ExpEnviInterf2ExpEnviHandMsg* allocate_shm_client_exp_envi_interf_2_exp_envi_hand_msg_buffer(ExpEnviInterf2ExpEnviHandMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_shm_client_exp_envi_interf_2_exp_envi_hand_msg_buffer(msg_buffer);
		msg_buffer = allocate_shm_client_exp_envi_interf_2_exp_envi_hand_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = rtai_malloc(nam2num(EXP_ENVI_INTERF_2_EXP_ENVI_HAND_SHM_NAME), 0);
	print_message(INFO_MSG ,"ExperimentHandlers", "ExpEnviInterf2ExpEnviHand", "allocate_shm_client_exp_envi_interf_2_exp_envi_hand_msg_buffer", "Created shm_client_exp_envi_interf_2_exp_envi_hand_msg_buffer.");
	return msg_buffer;
}
ExpEnviInterf2ExpEnviHandMsg* deallocate_shm_exp_envi_interf_2_exp_envi_hand_msg_buffer(ExpEnviInterf2ExpEnviHandMsg* msg_buffer)
{
	if (msg_buffer == NULL)
		return (ExpEnviInterf2ExpEnviHandMsg*)print_message(BUG_MSG ,"ExperimentHandlers", "ExpEnviInterf2ExpEnviHand", "deallocate_shm_exp_envi_interf_2_exp_envi_hand_msg_buffer", "msg_buffer == NULL.");    
	rtai_free(nam2num(EXP_ENVI_INTERF_2_EXP_ENVI_HAND_SHM_NAME), msg_buffer);	
	return NULL;
}
bool write_to_exp_envi_interf_2_exp_envi_hand_msg_buffer(ExpEnviInterf2ExpEnviHandMsg* msg_buffer, TimeStamp msg_time, ExpEnviInterf2ExpEnviHandMsgType msg_type, ExpEnviInterf2ExpEnviHandMsgAdditional additional_data)
{
	unsigned int *idx;
	idx = &(msg_buffer->buff_write_idx);
	ExpEnviInterf2ExpEnviHandItem *buff = msg_buffer->buff;
	buff[*idx].msg_time = msg_time;
	buff[*idx].msg_type = msg_type;
	buff[*idx].additional_data = additional_data;
	if ((*idx + 1) == EXP_ENVI_INTERF_2_EXP_ENVI_HAND_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	if (*idx == msg_buffer->buff_read_idx)
		return print_message(BUG_MSG ,"ExperimentHandlers", "ExpEnviInterf2ExpEnviHand", "write_to_exp_envi_interf_2_exp_envi_hand_msg_buffer", "BUFFER IS FULL!!!.");    		
	return TRUE;
}
bool get_next_exp_envi_interf_2_exp_envi_hand_msg_buffer_item(ExpEnviInterf2ExpEnviHandMsg* msg_buffer, ExpEnviInterf2ExpEnviHandMsgItem **msg_item)
{
	unsigned int *idx;
	idx = &(msg_buffer->buff_read_idx);
	if (*idx == msg_buffer->buff_write_idx)
		return FALSE;
	*msg_item = &(msg_buffer->buff[*idx]);	
	if ((*idx + 1) == EXP_ENVI_INTERF_2_EXP_ENVI_HAND_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	return TRUE;
}
