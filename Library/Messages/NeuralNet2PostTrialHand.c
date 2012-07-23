#include "NeuralNet2PostTrialHand.h"

bool get_neural_net_2_post_trial_hand_msg_type_string(NeuralNet2PostTrialHandMsgType msg_type, char *str)
{
	switch (msg_type)
	{
		case NEURAL_NET_2_POST_TRIAL_HAND_MSG_I_AM_ALIVE:
			if (str != NULL)
 				strcpy(str, "NEURAL_NET_2_POST_TRIAL_HAND_MSG_I_AM_ALIVE");
			return TRUE;
		case NEURAL_NET_2_POST_TRIAL_HAND_MSG_TRIAL_END:
			if (str != NULL)
 				strcpy(str, "NEURAL_NET_2_POST_TRIAL_HAND_MSG_TRIAL_END");
			return TRUE;
/////////////////////////		
		case NEURAL_NET_2_POST_TRIAL_HAND_MSG_NULL:
			if (str != NULL)
 				strcpy(str, "NEURAL_NET_2_POST_TRIAL_HAND_MSG_NULL");
			return FALSE;
		default:
			if (str != NULL)
 				strcpy(str, "NEURAL_NET_2_POST_TRIAL_HAND_MSG_INVALID");
			return FALSE;
	}

}

NeuralNet2PostTrialHandMsg* allocate_neural_net_2_post_trial_hand_msg_buffer(NeuralNet2PostTrialHandMsg* msg_buffer)
{
	if (msg_buffer != NULL)
	{
		msg_buffer = deallocate_neural_net_2_post_trial_hand_msg_buffer(msg_buffer);
		msg_buffer = allocate_neural_net_2_post_trial_hand_msg_buffer(msg_buffer);
		return msg_buffer;
	}  
	msg_buffer = g_new0(NeuralNet2PostTrialHandMsg,1);
	print_message(INFO_MSG ,"ExperimentHandlers", "NeuralNet2PostTrialHand", "allocate_neural_net_2_post_trial_hand_msg_buffer", "Created neural_net_2_post_trial_hand_msg_buffer.");
	return msg_buffer;	
}
NeuralNet2PostTrialHandMsg* deallocate_neural_net_2_post_trial_hand_msg_buffer(NeuralNet2PostTrialHandMsg* msg_buffer)
{
	if (msg_buffer == NULL)
		return (NeuralNet2PostTrialHandMsg*)print_message(BUG_MSG ,"ExperimentHandlers", "NeuralNet2PostTrialHand", "deallocate_neural_net_2_post_trial_hand_msg_buffer", "msg_buffer == NULL.");    
	g_free(msg_buffer);	
	return NULL;
}

bool write_to_neural_net_2_post_trial_hand_msg_buffer(NeuralNet2PostTrialHandMsg* msg_buffer, TimeStamp msg_time, NeuralNet2PostTrialHandMsgType msg_type,  NeuralNet2PostTrialHandMsgAdditional additional_data)
{
	unsigned int *idx;
	idx = &(msg_buffer->buff_write_idx);
	NeuralNet2PostTrialHandMsgItem *buff = msg_buffer->buff;

	buff[*idx].msg_time = msg_time;
	buff[*idx].msg_type = msg_type;
	buff[*idx].additional_data = additional_data;
	if ((*idx + 1) == NEURAL_NET_2_POST_TRIAL_HAND_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	if (*idx == msg_buffer->buff_read_idx)
		return print_message(BUG_MSG ,"ExperimentHandlers", "NeuralNet2PostTrialHand", "write_to_neural_net_2_post_trial_hand_msg_buffer", "BUFFER IS FULL!!!.");    		
	return TRUE;
}
bool get_next_neural_net_2_post_trial_hand_msg_buffer_item(NeuralNet2PostTrialHandMsg* msg_buffer, NeuralNet2PostTrialHandMsgItem *msg_item)
{
	unsigned int *idx;
	NeuralNet2PostTrialHandMsgItem *buff_item;
	idx = &(msg_buffer->buff_read_idx);
	if (*idx == msg_buffer->buff_write_idx)
		return FALSE;
	buff_item = &(msg_buffer->buff[*idx]);	
	msg_item->msg_time = buff_item->msg_time;		
	msg_item->msg_type = buff_item->msg_type;
	msg_item->additional_data = buff_item->additional_data;
	if ((*idx + 1) == NEURAL_NET_2_POST_TRIAL_HAND_MSG_BUFF_SIZE)
		*idx = 0;
	else
		(*idx)++;
	return TRUE;
}


