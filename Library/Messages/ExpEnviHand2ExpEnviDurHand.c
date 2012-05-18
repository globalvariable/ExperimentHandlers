#include "ExpEnviHand2ExpEnviDurHand.h"

bool get_exp_envi_hand_2_exp_envi_dur_hand_msg_type_string(ExpEnviHand2ExpEnviDurHandMsgType msg_type, char *str)
{
	switch (msg_type)
	{
		case EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_START_MIN_TIMER:
			if (str != NULL)
 				strcpy(str, "EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_START_MIN_TIMER");
			return TRUE;
		case EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_START_MAX_TIMER:
			if (str != NULL)
 				strcpy(str, "EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_START_MAX_TIMER");
			return TRUE;
		case EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_CANCEL_MIN_TIMER:
			if (str != NULL)
 				strcpy(str, "EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_CANCEL_MIN_TIMER");
			return TRUE;
		case EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_CANCEL_MAX_TIMER:
			if (str != NULL)
 				strcpy(str, "EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_CANCEL_MAX_TIMER");
			return TRUE;
/////////////////////////		
		case EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_NULL:
			if (str != NULL)
 				strcpy(str, "EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_NULL");
			return FALSE;
		default:
			if (str != NULL)
 				strcpy(str, "EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_INVALID");
			return FALSE;
	}
}

ExpEnviHand2ExpEnviDurHandMsg* allocate_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer(ExpEnviHand2ExpEnviDurHandMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer(msg_buffer);
		msg_buffer = allocate_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = g_new0(ExpEnviHand2ExpEnviDurHandMsg,1);
	print_message(INFO_MSG ,"ExperimentHandlers", "ExpEnviHand2ExpEnviDurHand", "allocate_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer", "Created exp_envi_hand_2_exp_envi_dur_hand_msg_buffer.");
	return msg_buffer;	
}
ExpEnviHand2ExpEnviDurHandMsg* deallocate_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer(ExpEnviHand2ExpEnviDurHandMsg* msg_buffer)
{
	if (msg_buffer == NULL)
		return (ExpEnviHand2ExpEnviDurHandMsg*)print_message(BUG_MSG ,"ExperimentHandlers", "ExpEnviHand2ExpEnviDurHand", "deallocate_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer", "msg_buffer == NULL.");    
	g_free(msg_buffer);	
	return NULL;
}


bool write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer(ExpEnviHand2ExpEnviDurHandMsg* msg_buffer, TimeStamp msg_time, ExpEnviHand2ExpEnviDurHandMsgType msg_type, ExpEnviInputCompNum inp_comp_num, ExpEnviHand2ExpEnviDurHandMsgAdditional additional_data)
{
	unsigned int *idx;
	idx = &(msg_buffer->buff_write_idx);
	ExpEnviHand2ExpEnviDurHandMsgItem *buff = msg_buffer->buff;
	buff[*idx].msg_time = msg_time;
	buff[*idx].msg_type = msg_type;
	buff[*idx].inp_comp_num = inp_comp_num;
	buff[*idx].additional_data = additional_data;
	if ((*idx + 1) == EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	if (*idx == msg_buffer->buff_read_idx)
		return print_message(BUG_MSG ,"ExperimentHandlers", "ExpEnviHand2ExpEnviDurHand", "write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer", "BUFFER IS FULL!!!.");    		
	return TRUE;
}
bool get_next_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer_item(ExpEnviHand2ExpEnviDurHandMsg* msg_buffer, ExpEnviHand2ExpEnviDurHandMsgItem **msg_item)	// take care of static read_idx value //only request buffer handler uses
{
	unsigned int *idx;
	idx = &(msg_buffer->buff_read_idx);
	if (*idx == msg_buffer->buff_write_idx)
		return FALSE;
	*msg_item = &(msg_buffer->buff[*idx]);	
	if ((*idx + 1) == EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	return TRUE;
}
