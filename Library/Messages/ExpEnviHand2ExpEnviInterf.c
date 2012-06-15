#include "ExpEnviHand2ExpEnviInterf.h"


bool get_exp_envi_hand_2_exp_envi_interf_msg_type_string(ExpEnviHand2ExpEnviInterfMsgType msg_type, char *str)
{
	switch (msg_type)
	{
		case EXP_ENVI_HAND_2_EXP_ENVI_INTERF_MSG_ARE_YOU_ALIVE:
			if (str != NULL)
 				strcpy(str, "EXP_ENVI_HAND_2_EXP_ENVI_INTERF_MSG_ARE_YOU_ALIVE");
			return TRUE;
		case EXP_ENVI_HAND_2_EXP_ENVI_INTERF_MSG_LOW_2_HIGH:
			if (str != NULL)
 				strcpy(str, "EXP_ENVI_HAND_2_EXP_ENVI_INTERF_MSG_LOW_2_HIGH");
			return TRUE;
		case EXP_ENVI_HAND_2_EXP_ENVI_INTERF_MSG_HIGH_2_LOW:
			if (str != NULL)
 				strcpy(str, "EXP_ENVI_HAND_2_EXP_ENVI_INTERF_MSG_HIGH_2_LOW");
			return TRUE;
		case EXP_ENVI_HAND_2_EXP_ENVI_INTERF_MSG_RESET:
			if (str != NULL)
 				strcpy(str, "EXP_ENVI_HAND_2_EXP_ENVI_INTERF_MSG_RESET");
			return TRUE;
/////////////////////////		
		case EXP_ENVI_HAND_2_EXP_ENVI_INTERF_MSG_NULL:
			if (str != NULL)
 				strcpy(str, "EXP_ENVI_HAND_2_EXP_ENVI_INTERF_MSG_NULL");
			return FALSE;
		default:
			if (str != NULL)
 				strcpy(str, "EXP_ENVI_HAND_2_EXP_ENVI_INTERF_MSG_INVALID");
			return FALSE;
	}

}


ExpEnviHand2ExpEnviInterfMsg* allocate_exp_envi_hand_2_exp_envi_interf_msg_buffer(ExpEnviHand2ExpEnviInterfMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_exp_envi_hand_2_exp_envi_interf_msg_buffer(msg_buffer);
		msg_buffer = allocate_exp_envi_hand_2_exp_envi_interf_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = g_new0(ExpEnviHand2ExpEnviInterfMsg,1);
	print_message(INFO_MSG ,"ExperimentHandlers", "ExpEnviHand2ExpEnviInterf", "allocate_exp_envi_hand_2_exp_envi_interf_msg_buffer", "Created exp_envi_hand_2_exp_envi_interf_msg_buffer.");
	return msg_buffer;	
}
ExpEnviHand2ExpEnviInterfMsg* deallocate_exp_envi_hand_2_exp_envi_interf_msg_buffer(ExpEnviHand2ExpEnviInterfMsg* msg_buffer)
{
	if (msg_buffer == NULL)
		return (ExpEnviHand2ExpEnviInterfMsg*)print_message(BUG_MSG ,"ExperimentHandlers", "ExpEnviHand2ExpEnviInterf", "deallocate_exp_envi_hand_2_exp_envi_interf_msg_buffer", "msg_buffer == NULL.");    
	g_free(msg_buffer);	
	return NULL;
}

ExpEnviHand2ExpEnviInterfMsg* allocate_shm_server_exp_envi_hand_2_exp_envi_interf_msg_buffer(ExpEnviHand2ExpEnviInterfMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_shm_exp_envi_hand_2_exp_envi_interf_msg_buffer(msg_buffer);
		msg_buffer = allocate_shm_server_exp_envi_hand_2_exp_envi_interf_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = rtai_malloc(nam2num(EXP_ENVI_HAND_2_EXP_ENVI_INTERF_SHM_NAME), sizeof(ExpEnviHand2ExpEnviInterfMsg));
	memset(msg_buffer, 0, sizeof(ExpEnviHand2ExpEnviInterfMsg));
	print_message(INFO_MSG ,"ExperimentHandlers", "ExpEnviHand2ExpEnviInterf", "allocate_shm_server_exp_envi_hand_2_exp_envi_interf_msg_buffer", "Created shm_server_exp_envi_hand_2_exp_envi_interf_msg_buffer.");
	return msg_buffer;	
}
ExpEnviHand2ExpEnviInterfMsg* allocate_shm_client_exp_envi_hand_2_exp_envi_interf_msg_buffer(ExpEnviHand2ExpEnviInterfMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_shm_exp_envi_hand_2_exp_envi_interf_msg_buffer(msg_buffer);
		msg_buffer = allocate_shm_server_exp_envi_hand_2_exp_envi_interf_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = rtai_malloc(nam2num(EXP_ENVI_HAND_2_EXP_ENVI_INTERF_SHM_NAME), 0);
	print_message(INFO_MSG ,"ExperimentHandlers", "ExpEnviHand2ExpEnviInterf", "allocate_shm_client_exp_envi_hand_2_exp_envi_interf_msg_buffer", "Created shm_client_exp_envi_hand_2_exp_envi_interf_msg_buffer.");
	return msg_buffer;	
}
ExpEnviHand2ExpEnviInterfMsg* deallocate_shm_exp_envi_hand_2_exp_envi_interf_msg_buffer(ExpEnviHand2ExpEnviInterfMsg* msg_buffer)
{
	if (msg_buffer == NULL)
		return (ExpEnviHand2ExpEnviInterfMsg*)print_message(BUG_MSG ,"ExperimentHandlers", "ExpEnviHand2ExpEnviInterf", "deallocate_shm_exp_envi_hand_2_exp_envi_interf_msg_buffer", "msg_buffer == NULL.");    
	rtai_free(nam2num(EXP_ENVI_HAND_2_EXP_ENVI_INTERF_SHM_NAME), msg_buffer);	
	return NULL;
}
bool write_to_exp_envi_hand_2_exp_envi_interf_msg_buffer(ExpEnviHand2ExpEnviInterfMsg* msg_buffer, TimeStamp msg_time, ExpEnviHand2ExpEnviInterfMsgType msg_type, ExpEnviOutputCompNum out_comp_num, ExpEnviHand2ExpEnviInterfMsgAdditional additional_data)
{
	unsigned int *idx;
	idx = &(msg_buffer->buff_write_idx);
	ExpEnviHand2ExpEnviInterfMsgItem *buff = msg_buffer->buff;
	buff[*idx].msg_time = msg_time;
	buff[*idx].msg_type = msg_type;
	buff[*idx].out_comp_num = out_comp_num;
	buff[*idx].additional_data = additional_data;
	if ((*idx + 1) == EXP_ENVI_HAND_2_EXP_ENVI_INTERF_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	if (*idx == msg_buffer->buff_read_idx)
		return print_message(BUG_MSG ,"ExperimentHandlers", "ExpEnviHand2ExpEnviInterf", "write_to_exp_envi_hand_2_exp_envi_interf_msg_buffer", "BUFFER IS FULL!!!.");    		
	return TRUE;
}
bool get_next_exp_envi_hand_2_exp_envi_interf_msg_buffer_item(ExpEnviHand2ExpEnviInterfMsg* msg_buffer, ExpEnviHand2ExpEnviInterfMsgItem **msg_item)
{
	unsigned int *idx;
	idx = &(msg_buffer->buff_read_idx);
	if (*idx == msg_buffer->buff_write_idx)
		return FALSE;
	*msg_item = &(msg_buffer->buff[*idx]);	
	if ((*idx + 1) == EXP_ENVI_HAND_2_EXP_ENVI_INTERF_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	return TRUE;
}
