#include "HandleRS232Buffers.h"




#define EXP_ENVI_STATUS_MSG_LEN			1
#define EXP_ENVI_STATUS_MSG_START_IDX	1
#define EXP_ENVI_CMD_MSG_LEN				1
#define EXP_ENVI_CMD_MSG_START_IDX		1

static SEM *static_exp_envi_rx_buff_sem = NULL;
static SEM *static_exp_envi_tx_buff_sem = NULL;
static ExpEnviRxShm *static_exp_envi_rx_buff_shm = NULL;
static ExpEnviTxShm *static_exp_envi_tx_buff_shm = NULL;

bool init_rs232_buffers(SEM **exp_envi_rx_buff_sem, SEM **exp_envi_tx_buff_sem, ExpEnviRxShm **exp_envi_rx_buff_shm, ExpEnviTxShm **exp_envi_tx_buff_shm)
{
	if (! bind_to_exp_envi_rx_buffer_semaphore(exp_envi_rx_buff_sem))
		return print_message(ERROR_MSG ,"BMIExpController", "HandleRxTxBuffer", "init_rx_tx_buffer", "! bind_to_exp_envi_rx_buffer_semaphore().");	
	if (! bind_to_exp_envi_tx_buffer_semaphore(exp_envi_tx_buff_sem))
		return print_message(ERROR_MSG ,"BMIExpController", "HandleRxTxBuffer", "init_rx_tx_buffer", "! bind_to_exp_envi_tx_buffer_semaphore().");	
	if (! bind_to_exp_envi_tx_buffer_shm(exp_envi_tx_buff_shm) )
		return print_message(ERROR_MSG ,"BMIExpController", "HandleRxTxBuffer", "init_rx_tx_buffer", "! bind_to_exp_envi_tx_buffer_shm().");	
	if (! bind_to_exp_envi_rx_buffer_shm(exp_envi_rx_buff_shm) )
		return print_message(ERROR_MSG ,"BMIExpController", "HandleRxTxBuffer", "init_rx_tx_buffer", "! bind_to_exp_envi_rx_buffer_shm().");	

	static_exp_envi_rx_buff_sem = *exp_envi_rx_buff_sem; 
	static_exp_envi_tx_buff_sem = *exp_envi_tx_buff_sem;
	static_exp_envi_rx_buff_shm = *exp_envi_rx_buff_shm;
	static_exp_envi_tx_buff_shm = *exp_envi_tx_buff_shm;

	return TRUE;
}

bool handle_exp_envi_tx_shm(ExpEnviRS232Cmd *exp_envi_rs232_cmd, TimeStamp current_time)
{
	ExpEnviTxShm exp_envi_tx_buffer;
	exp_envi_tx_buffer.last_write_time = current_time;
	exp_envi_tx_buffer.exp_envi_tx_buff[0] = exp_envi_rs232_cmd->all_cmd;
	if (! write_to_exp_envi_tx_buff_shm(&exp_envi_tx_buffer, static_exp_envi_tx_buff_shm, EXP_ENVI_CMD_MSG_LEN, static_exp_envi_tx_buff_sem))  //  Exp Envi Handler writes its command to static_exp_envi_tx_buff for delivery by this process
		print_message(ERROR_MSG ,"BMIExpController", "HandleRxTxBuffer", "handle_exp_envi_tx_shm", "! read_exp_envi_tx_buff_shm()."); 

	return TRUE;
}

bool handle_exp_envi_rx_shm(ExpEnviRS232Status *exp_envi_rs232_status, ExpEnviData *exp_envi_data, TimeStamp current_time, ExpEnviHand2ExpEnviDurHandMsg *msgs_exp_envi_hand_2_exp_envi_dur_hand)
{
	static ExpEnviRS232Status exp_envi_rs232_status_prev = { .all_status = 0 };
	ExpEnviRxShm exp_envi_rx_buffer;
	bool valid;

	if (! read_exp_envi_rx_buff_shm(&exp_envi_rx_buffer, static_exp_envi_rx_buff_shm, EXP_ENVI_STATUS_MSG_LEN, static_exp_envi_rx_buff_sem)) 
		print_message(ERROR_MSG ,"BMIExpController", "HandleRxTxBuffer", "handle_exp_envi_rx_shm", "! read_exp_envi_tx_buff_shm()."); 
	exp_envi_rs232_status->all_status = exp_envi_rx_buffer.exp_envi_rx_buff[0];
//	printf ("%u\n", exp_envi_rs232_status->all_status);
	if (exp_envi_rs232_status_prev.ir_beam != exp_envi_rs232_status->ir_beam)
	{
		exp_envi_rs232_status_prev.ir_beam = exp_envi_rs232_status->ir_beam;
		if (! write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer(msgs_exp_envi_hand_2_exp_envi_dur_hand, current_time,  EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_CANCEL_MIN_TIMER, IR_BEAM, 0))
				return print_message(BUG_MSG ,"BMIExpController", "HandleRS232Buffers", "handle_exp_envi_rx_shm", "write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer().");			
		if (! write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer(msgs_exp_envi_hand_2_exp_envi_dur_hand, current_time,  EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_CANCEL_MAX_TIMER, IR_BEAM, 0))
				return print_message(BUG_MSG ,"BMIExpController", "HandleRS232Buffers", "handle_exp_envi_rx_shm", "write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer().");
		if (exp_envi_rs232_status->ir_beam)
		{
			if (! exp_envi_input_low_2_high_event(&(exp_envi_data->inp_comp_types[IR_BEAM]), &valid))
							return print_message(BUG_MSG ,"BMIExpController", "HandleRS232Buffers", "handle_exp_envi_rx_shm", "exp_envi_input_low_2_high_event().");
			if (valid)	 
			{
				if (! write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer(msgs_exp_envi_hand_2_exp_envi_dur_hand, current_time,  EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_START_MIN_TIMER, IR_BEAM, exp_envi_data->inp_comp_types[IR_BEAM].constraints.min_high_status_duration + current_time))
					return print_message(BUG_MSG ,"BMIExpController", "HandleRS232Buffers", "handle_exp_envi_rx_shm", "write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer().");			
				if (! write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer(msgs_exp_envi_hand_2_exp_envi_dur_hand, current_time,  EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_START_MAX_TIMER, IR_BEAM, exp_envi_data->inp_comp_types[IR_BEAM].constraints.max_high_status_duration + current_time))
					return print_message(BUG_MSG ,"BMIExpController", "HandleRS232Buffers", "handle_exp_envi_rx_shm", "write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer().");
			}
		}
		else
		{
			if (! exp_envi_input_high_2_low_event(&(exp_envi_data->inp_comp_types[IR_BEAM]), &valid))
				return print_message(BUG_MSG ,"ExpEnviHandler", "HandleRS232Buffers", "handle_exp_envi_rx_shm", "exp_envi_input_high_2_low_event().");
			if (valid)
			{
				if (! write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer(msgs_exp_envi_hand_2_exp_envi_dur_hand, current_time,  EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_START_MIN_TIMER, IR_BEAM, exp_envi_data->inp_comp_types[IR_BEAM].constraints.min_low_status_duration + current_time))
					return print_message(BUG_MSG ,"ExpEnviHandler", "HandleRS232Buffers", "handle_exp_envi_rx_shm", "write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer().");			
				if (! write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer(msgs_exp_envi_hand_2_exp_envi_dur_hand, current_time,  EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_START_MAX_TIMER, IR_BEAM, exp_envi_data->inp_comp_types[IR_BEAM].constraints.max_low_status_duration + current_time))
					return print_message(BUG_MSG ,"ExpEnviHandler", "HandleRS232Buffers", "handle_exp_envi_rx_shm", "write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer().");		
			}	
		}
	}
	if (exp_envi_rs232_status_prev.left_lever != exp_envi_rs232_status->left_lever)
	{
		exp_envi_rs232_status_prev.left_lever = exp_envi_rs232_status->left_lever;
		if (! write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer(msgs_exp_envi_hand_2_exp_envi_dur_hand, current_time,  EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_CANCEL_MIN_TIMER, LEFT_LEVER, 0))
				return print_message(BUG_MSG ,"BMIExpController", "HandleRS232Buffers", "handle_exp_envi_rx_shm", "write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer().");			
		if (! write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer(msgs_exp_envi_hand_2_exp_envi_dur_hand, current_time,  EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_CANCEL_MAX_TIMER, LEFT_LEVER, 0))
				return print_message(BUG_MSG ,"BMIExpController", "HandleRS232Buffers", "handle_exp_envi_rx_shm", "write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer().");
		if (exp_envi_rs232_status->left_lever)
		{
			if (! exp_envi_input_low_2_high_event(&(exp_envi_data->inp_comp_types[LEFT_LEVER]), &valid))
							return print_message(BUG_MSG ,"BMIExpController", "HandleRS232Buffers", "handle_exp_envi_rx_shm", "exp_envi_input_low_2_high_event().");
			if (valid)	 
			{
				if (! write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer(msgs_exp_envi_hand_2_exp_envi_dur_hand, current_time,  EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_START_MIN_TIMER, LEFT_LEVER, exp_envi_data->inp_comp_types[LEFT_LEVER].constraints.min_high_status_duration + current_time))
					return print_message(BUG_MSG ,"BMIExpController", "HandleRS232Buffers", "handle_exp_envi_rx_shm", "write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer().");			
				if (! write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer(msgs_exp_envi_hand_2_exp_envi_dur_hand, current_time,  EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_START_MAX_TIMER, LEFT_LEVER, exp_envi_data->inp_comp_types[LEFT_LEVER].constraints.max_high_status_duration + current_time))
					return print_message(BUG_MSG ,"BMIExpController", "HandleRS232Buffers", "handle_exp_envi_rx_shm", "write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer().");
			}
		}
		else
		{
			if (! exp_envi_input_high_2_low_event(&(exp_envi_data->inp_comp_types[LEFT_LEVER]), &valid))
				return print_message(BUG_MSG ,"ExpEnviHandler", "HandleRS232Buffers", "handle_exp_envi_rx_shm", "exp_envi_input_high_2_low_event().");
			if (valid)
			{
				if (! write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer(msgs_exp_envi_hand_2_exp_envi_dur_hand, current_time,  EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_START_MIN_TIMER, LEFT_LEVER, exp_envi_data->inp_comp_types[LEFT_LEVER].constraints.min_low_status_duration + current_time))
					return print_message(BUG_MSG ,"ExpEnviHandler", "HandleRS232Buffers", "handle_exp_envi_rx_shm", "write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer().");			
				if (! write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer(msgs_exp_envi_hand_2_exp_envi_dur_hand, current_time,  EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_START_MAX_TIMER, LEFT_LEVER, exp_envi_data->inp_comp_types[LEFT_LEVER].constraints.max_low_status_duration + current_time))
					return print_message(BUG_MSG ,"ExpEnviHandler", "HandleRS232Buffers", "handle_exp_envi_rx_shm", "write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer().");		
			}	
		}
	}
	if (exp_envi_rs232_status_prev.right_lever != exp_envi_rs232_status->right_lever)
	{
		exp_envi_rs232_status_prev.right_lever = exp_envi_rs232_status->right_lever;
		if (! write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer(msgs_exp_envi_hand_2_exp_envi_dur_hand, current_time,  EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_CANCEL_MIN_TIMER, RIGHT_LEVER, 0))
				return print_message(BUG_MSG ,"BMIExpController", "HandleRS232Buffers", "handle_exp_envi_rx_shm", "write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer().");			
		if (! write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer(msgs_exp_envi_hand_2_exp_envi_dur_hand, current_time,  EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_CANCEL_MAX_TIMER, RIGHT_LEVER, 0))
				return print_message(BUG_MSG ,"BMIExpController", "HandleRS232Buffers", "handle_exp_envi_rx_shm", "write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer().");
		if (exp_envi_rs232_status->right_lever)
		{
			if (! exp_envi_input_low_2_high_event(&(exp_envi_data->inp_comp_types[RIGHT_LEVER]), &valid))
							return print_message(BUG_MSG ,"BMIExpController", "HandleRS232Buffers", "handle_exp_envi_rx_shm", "exp_envi_input_low_2_high_event().");
			if (valid)	 
			{
				if (! write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer(msgs_exp_envi_hand_2_exp_envi_dur_hand, current_time,  EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_START_MIN_TIMER, RIGHT_LEVER, exp_envi_data->inp_comp_types[RIGHT_LEVER].constraints.min_high_status_duration + current_time))
					return print_message(BUG_MSG ,"BMIExpController", "HandleRS232Buffers", "handle_exp_envi_rx_shm", "write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer().");			
				if (! write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer(msgs_exp_envi_hand_2_exp_envi_dur_hand, current_time,  EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_START_MAX_TIMER, RIGHT_LEVER, exp_envi_data->inp_comp_types[RIGHT_LEVER].constraints.max_high_status_duration + current_time))
					return print_message(BUG_MSG ,"BMIExpController", "HandleRS232Buffers", "handle_exp_envi_rx_shm", "write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer().");
			}
		}
		else
		{
			if (! exp_envi_input_high_2_low_event(&(exp_envi_data->inp_comp_types[RIGHT_LEVER]), &valid))
				return print_message(BUG_MSG ,"ExpEnviHandler", "HandleRS232Buffers", "handle_exp_envi_rx_shm", "exp_envi_input_high_2_low_event().");
			if (valid)
			{
				if (! write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer(msgs_exp_envi_hand_2_exp_envi_dur_hand, current_time,  EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_START_MIN_TIMER, RIGHT_LEVER, exp_envi_data->inp_comp_types[RIGHT_LEVER].constraints.min_low_status_duration + current_time))
					return print_message(BUG_MSG ,"ExpEnviHandler", "HandleRS232Buffers", "handle_exp_envi_rx_shm", "write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer().");			
				if (! write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer(msgs_exp_envi_hand_2_exp_envi_dur_hand, current_time,  EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_START_MAX_TIMER, RIGHT_LEVER, exp_envi_data->inp_comp_types[RIGHT_LEVER].constraints.max_low_status_duration + current_time))
					return print_message(BUG_MSG ,"ExpEnviHandler", "HandleRS232Buffers", "handle_exp_envi_rx_shm", "write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer().");		
			}	
		}
	}
	return TRUE;
}
