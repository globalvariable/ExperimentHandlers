#include "HandleRS232DurHand2RS232HandMsgs.h"

#define RX_BUFF_LEN		3
#define TX_BUFF_LEN		2

static char rx_buff[RX_BUFF_LEN];
static char tx_buff[TX_BUFF_LEN];	

bool handle_rs232_dur_hand_to_rs232_hand_msgs(RS232Data *rs_232_data, TimeStamp current_time, ExpEnviHand2ExpEnviInterfMsg *msgs_exp_envi_hand_2_exp_envi_interf, ExpEnviInterf2ExpEnviHandMsg *msgs_exp_envi_interf_2_exp_envi_hand, MovObjHand2MovObjInterfMsg *msgs_mov_obj_hand_2_mov_obj_interf, MovObjInterf2MovObjHandMsg *msgs_mov_obj_interf_2_mov_obj_hand, RS232DurHand2RS232HandMsg *msgs_rs232_dur_hand_2_rs232_hand, RS232Hand2RS232DurHandMsg *msgs_rs232_hand_2_rs232_dur_hand)
{
	RS232DurHand2RS232HandMsgItem *msg_item;
	char str_rs232_dur_msg[RS232_DUR_HAND_2_RS232_HAND_MSG_STRING_LENGTH];
	unsigned int i;

	while (get_next_rs232_dur_hand_2_rs232_hand_msg_buffer_item(msgs_rs232_dur_hand_2_rs232_hand, &msg_item))
	{
		get_rs232_dur_hand_2_rs232_hand_msg_type_string(msg_item->msg_type, str_rs232_dur_msg);
		print_message(INFO_MSG ,"FirstBMICageInterfacer", "HandleRS232DurHand2RS232HandMsgs", "handle_rs232_dur_handler_to_rs232_handler_msgs", str_rs232_dur_msg);
		switch (msg_item->msg_type)
		{
			case RS232_DUR_HAND_2_RS232_HAND_MSG_TX_TIMEOUT:	
				for (i = 0; i < TX_BUFF_LEN; i++)  tx_buff[i] = 0;
				if (! handle_exp_envi_hand_2_exp_envi_interf_msgs(msgs_exp_envi_hand_2_exp_envi_interf, msgs_exp_envi_interf_2_exp_envi_hand, tx_buff)) 
					return print_message(ERROR_MSG ,"FirstBMICageInterfacer", "HandleRS232DurHand2RS232HandMsgs", "handle_rs232_dur_handler_to_rs232_handler_msgs", "! handle_exp_envi_hand_2_exp_envi_interf_msgs().");
				if (! handle_mov_obj_hand_2_mov_obj_interf_msgs(msgs_mov_obj_hand_2_mov_obj_interf, msgs_mov_obj_interf_2_mov_obj_hand, tx_buff)) 
					return print_message(ERROR_MSG ,"FirstBMICageInterfacer", "HandleRS232DurHand2RS232HandMsgs", "handle_rs232_dur_handler_to_rs232_handler_msgs", "! handle_mov_obj_hand_2_mov_obj_interf_msgs().");
				if (! write_to_rs232_com1(tx_buff, TX_BUFF_LEN))
					return print_message(ERROR_MSG ,"FirstBMICageInterfacer", "HandleRS232DurHand2RS232HandMsgs", "handle_rs232_dur_handler_to_rs232_handler_msgs", "! write_to_rs232_com1().");
				if (!write_to_rs232_hand_2_rs232_dur_hand_msg_buffer(msgs_rs232_hand_2_rs232_dur_hand, current_time, RS232_HAND_2_RS232_DUR_HAND_MSG_ENABLE_TX_TIMER, 0, rs_232_data->comp_data[0].tx_period+current_time))
					return print_message(ERROR_MSG ,"FirstBMICageInterfacer", "HandleRS232DurHand2RS232HandMsgs", "handle_rs232_dur_handler_to_rs232_handler_msgs", "! write_to_rs232_hand_2_rs232_dur_hand_msg_buffer().");
				if (!write_to_rs232_hand_2_rs232_dur_hand_msg_buffer(msgs_rs232_hand_2_rs232_dur_hand, current_time, RS232_HAND_2_RS232_DUR_HAND_MSG_ENABLE_RX_TIMER, 0, rs_232_data->comp_data[0].rx_period+current_time))
					return print_message(ERROR_MSG ,"FirstBMICageInterfacer", "HandleRS232DurHand2RS232HandMsgs", "handle_rs232_dur_handler_to_rs232_handler_msgs", "! write_to_rs232_hand_2_rs232_dur_hand_msg_buffer().");
				break;
			case RS232_DUR_HAND_2_RS232_HAND_MSG_RX_TIMEOUT:
				if (! read_from_rs232_com1(rx_buff, RX_BUFF_LEN))
					return print_message(ERROR_MSG ,"FirstBMICageInterfacer", "HandleRS232DurHand2RS232HandMsgs", "handle_rs232_dur_handler_to_rs232_handler_msgs", "! read_from_rs232_com1().");  
				if (! handle_exp_envi_interf_2_exp_envi_hand_msgs(rx_buff, msgs_exp_envi_interf_2_exp_envi_hand, current_time)) 
					return print_message(ERROR_MSG ,"FirstBMICageInterfacer", "HandleRS232DurHand2RS232HandMsgs", "handle_rs232_dur_handler_to_rs232_handler_msgs", "! handle_exp_envi_interf_2_exp_envi_hand_msgs().");
				if (! handle_mov_obj_interf_2_mov_obj_hand_msgs(rx_buff, msgs_mov_obj_interf_2_mov_obj_hand, current_time)) 
					return print_message(ERROR_MSG ,"FirstBMICageInterfacer", "HandleRS232DurHand2RS232HandMsgs", "handle_rs232_dur_handler_to_rs232_handler_msgs", "! handle_mov_obj_interf_2_mov_obj_hand_msgs()."); 
				break;
			default:
				return print_message(BUG_MSG ,"FirstBMICageInterfacer", "HandleRS232DurHand2RS232HandMsgs", "handle_rs232_dur_handler_to_rs232_handler_msgs", str_rs232_dur_msg);
		}
	}

	return TRUE;
}
