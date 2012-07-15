#include "ExpEnviInterf2ExpEnviHand.h"

bool get_exp_envi_interf_2_exp_envi_hand_msg_type_string(ExpEnviInterf2ExpEnviHandMsgType msg_type, char *str)
{
	switch (msg_type)
	{
		case EXP_ENVI_INTERF_2_EXP_ENVI_HAND_MSG_I_AM_ALIVE:
			if (str != NULL)
 				strcpy(str, "EXP_ENVI_INTERF_2_EXP_ENVI_HAND_MSG_I_AM_ALIVE");
			return TRUE;
		case EXP_ENVI_INTERF_2_EXP_ENVI_HAND_MSG_LOW_2_HIGH:
			if (str != NULL)
 				strcpy(str, "EXP_ENVI_INTERF_2_EXP_ENVI_HAND_MSG_LOW_2_HIGH");
			return TRUE;
		case EXP_ENVI_INTERF_2_EXP_ENVI_HAND_MSG_HIGH_2_LOW:
			if (str != NULL)
 				strcpy(str, "EXP_ENVI_INTERF_2_EXP_ENVI_HAND_MSG_HIGH_2_LOW");
			return TRUE;
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
		msg_buffer = deallocate_exp_envi_interf_2_exp_envi_hand_msg_buffer(msg_buffer);
		msg_buffer = allocate_exp_envi_interf_2_exp_envi_hand_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = g_new0(ExpEnviInterf2ExpEnviHandMsg,1);
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
		msg_buffer = deallocate_shm_exp_envi_interf_2_exp_envi_hand_msg_buffer(msg_buffer);
		msg_buffer = allocate_shm_server_exp_envi_interf_2_exp_envi_hand_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = rtai_malloc(nam2num(EXP_ENVI_INTERF_2_EXP_ENVI_HAND_SHM_NAME), sizeof(ExpEnviInterf2ExpEnviHandMsg));
	memset(msg_buffer, 0, sizeof(ExpEnviInterf2ExpEnviHandMsg));
	print_message(INFO_MSG ,"ExperimentHandlers", "ExpEnviInterf2ExpEnviHand", "allocate_shm_server_exp_envi_interf_2_exp_envi_hand_msg_buffer", "Created shm_server_exp_envi_interf_2_exp_envi_hand_msg_buffer.");
	return msg_buffer;	
}
ExpEnviInterf2ExpEnviHandMsg* allocate_shm_client_exp_envi_interf_2_exp_envi_hand_msg_buffer(ExpEnviInterf2ExpEnviHandMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_shm_exp_envi_interf_2_exp_envi_hand_msg_buffer(msg_buffer);
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
bool write_to_exp_envi_interf_2_exp_envi_hand_msg_buffer(ExpEnviInterf2ExpEnviHandMsg* msg_buffer, TimeStamp msg_time, ExpEnviInterf2ExpEnviHandMsgType msg_type, ExpEnviInputCompNum inp_comp_num, ExpEnviInterf2ExpEnviHandMsgAdditional additional_data)
{
	unsigned int *idx;
	idx = &(msg_buffer->buff_write_idx);
	ExpEnviInterf2ExpEnviHandMsgItem *buff = msg_buffer->buff;
	buff[*idx].msg_time = msg_time;
	buff[*idx].inp_comp_num = inp_comp_num;
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
bool get_next_exp_envi_interf_2_exp_envi_hand_msg_buffer_item(ExpEnviInterf2ExpEnviHandMsg* msg_buffer, ExpEnviInterf2ExpEnviHandMsgItem *msg_item)
{
	ExpEnviInterf2ExpEnviHandMsgItem *buff_item;
	unsigned int *idx;
	idx = &(msg_buffer->buff_read_idx);
	if (*idx == msg_buffer->buff_write_idx)
		return FALSE;
	buff_item = &(msg_buffer->buff[*idx]);	
	msg_item->msg_time = buff_item->msg_time;		
	msg_item->msg_type = buff_item->msg_type;
	msg_item->inp_comp_num = buff_item->inp_comp_num;
	msg_item->additional_data = buff_item->additional_data;
	if ((*idx + 1) == EXP_ENVI_INTERF_2_EXP_ENVI_HAND_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	return TRUE;
}
