#include "ExpEnviDurHand2ExpEnviHand.h"

bool get_exp_envi_dur_hand_2_exp_envi_hand_msg_type_string(ExpEnviDurHand2ExpEnviHandMsgType msg_type, char *str)
{
	switch (msg_type)
	{
		case EXP_ENVI_DUR_HAND_2_EXP_ENVI_HAND_MSG_INPUT_TIMEOUT_FOR_MIN:
			if (str != NULL)
 				strcpy(str, "EXP_ENVI_DUR_HAND_2_EXP_ENVI_HAND_MSG_INPUT_TIMEOUT_FOR_MIN");
			return TRUE;
		case EXP_ENVI_DUR_HAND_2_EXP_ENVI_HAND_MSG_INPUT_TIMEOUT_FOR_MAX:
			if (str != NULL)
 				strcpy(str, "EXP_ENVI_DUR_HAND_2_EXP_ENVI_HAND_MSG_INPUT_TIMEOUT_FOR_MAX");
			return TRUE;
		case EXP_ENVI_DUR_HAND_2_EXP_ENVI_HAND_MSG_OUTPUT_TIMEOUT:
			if (str != NULL)
 				strcpy(str, "EXP_ENVI_DUR_HAND_2_EXP_ENVI_HAND_MSG_OUTPUT_TIMEOUT");
			return TRUE;
/////////////////////////		
		case EXP_ENVI_DUR_HAND_2_EXP_ENVI_HAND_MSG_NULL:
			if (str != NULL)
 				strcpy(str, "EXP_ENVI_DUR_HAND_2_EXP_ENVI_HAND_MSG_NULL");
			return FALSE;
		default:
			if (str != NULL)
 				strcpy(str, "EXP_ENVI_DUR_HAND_2_EXP_ENVI_HAND_MSG_INVALID");
			return FALSE;
	}
}

ExpEnviDurHand2ExpEnviHandMsg* allocate_exp_envi_dur_hand_2_exp_envi_hand_msg_buffer(ExpEnviDurHand2ExpEnviHandMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_exp_envi_dur_hand_2_exp_envi_hand_msg_buffer(msg_buffer);
		msg_buffer = allocate_exp_envi_dur_hand_2_exp_envi_hand_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = g_new0(ExpEnviDurHand2ExpEnviHandMsg,1);
	print_message(INFO_MSG ,"ExperimentHandlers", "ExpEnviDurHand2ExpEnviHand", "allocate_exp_envi_dur_hand_2_exp_envi_hand_msg_buffer", "Created exp_envi_dur_hand_2_exp_envi_hand_msg_buffer.");
	return msg_buffer;	
}
ExpEnviDurHand2ExpEnviHandMsg* deallocate_exp_envi_dur_hand_2_exp_envi_hand_msg_buffer(ExpEnviDurHand2ExpEnviHandMsg* msg_buffer)
{
	if (msg_buffer == NULL)
		return (ExpEnviDurHand2ExpEnviHandMsg*)print_message(BUG_MSG ,"ExperimentHandlers", "ExpEnviDurHand2ExpEnviHand", "deallocate_exp_envi_dur_hand_2_exp_envi_hand_msg_buffer", "msg_buffer == NULL.");    
	g_free(msg_buffer);	
	return NULL;
}


bool write_to_exp_envi_dur_hand_2_exp_envi_hand_msg_buffer(ExpEnviDurHand2ExpEnviHandMsg* msg_buffer, TimeStamp msg_time, ExpEnviDurHand2ExpEnviHandMsgType msg_type, ExpEnviCompNum comp_num, ExpEnviDurHand2ExpEnviHandMsgAdditional additional_data)
{
	unsigned int *idx;
	idx = &(msg_buffer->buff_write_idx);
	ExpEnviDurHand2ExpEnviHandMsgItem *buff = msg_buffer->buff;
	buff[*idx].msg_time = msg_time;
	buff[*idx].msg_type = msg_type;
	buff[*idx].comp_num = comp_num;
	buff[*idx].additional_data = additional_data;
	if ((*idx + 1) == EXP_ENVI_DUR_HAND_2_EXP_ENVI_HAND_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	if (*idx == msg_buffer->buff_read_idx)
		return print_message(BUG_MSG ,"ExperimentHandlers", "ExpEnviDurHand2ExpEnviHand", "write_to_exp_envi_dur_hand_2_exp_envi_hand_msg_buffer", "BUFFER IS FULL!!!.");    		
	return TRUE;
}
bool get_next_exp_envi_dur_hand_2_exp_envi_hand_msg_buffer_item(ExpEnviDurHand2ExpEnviHandMsg* msg_buffer, ExpEnviDurHand2ExpEnviHandMsgItem *msg_item)	// take care of static read_idx value //only request buffer handler uses
{
	unsigned int *idx;
	ExpEnviDurHand2ExpEnviHandMsgItem *buff_item;
	idx = &(msg_buffer->buff_read_idx);
	if (*idx == msg_buffer->buff_write_idx)
		return FALSE;
	buff_item = &(msg_buffer->buff[*idx]);	
	msg_item->msg_time = buff_item->msg_time;		
	msg_item->msg_type = buff_item->msg_type;
	msg_item->comp_num = buff_item->comp_num;
	msg_item->additional_data = buff_item->additional_data;
	if ((*idx + 1) == EXP_ENVI_DUR_HAND_2_EXP_ENVI_HAND_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	return TRUE;
}
