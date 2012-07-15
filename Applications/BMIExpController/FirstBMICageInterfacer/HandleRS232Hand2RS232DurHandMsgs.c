#include "HandleRS232Hand2RS232DurHandMsgs.h"

static TimeStamp *rx_timer_end_time = NULL;
static TimeStamp *tx_timer_end_time = NULL;
static RS232DurationStatus  *rx_timer_status = NULL;
static RS232DurationStatus  *tx_timer_status = NULL;
static unsigned int num_of_rs232_components = 0;

bool create_rs232_duration_handler_data(unsigned int arg_num_of_rs232_components)
{
	unsigned int i;
	rx_timer_end_time = g_new0(TimeStamp,arg_num_of_rs232_components );
	tx_timer_end_time = g_new0(TimeStamp,arg_num_of_rs232_components );
	rx_timer_status = g_new0(RS232DurationStatus,arg_num_of_rs232_components );
	tx_timer_status = g_new0(RS232DurationStatus,arg_num_of_rs232_components );
	for (i = 0; i < arg_num_of_rs232_components; i++)
	{
		rx_timer_status[i] = RS232_DUR_STATUS_TIMER_OFF;
		tx_timer_status[i] = RS232_DUR_STATUS_TIMER_OFF;
	}
	num_of_rs232_components = arg_num_of_rs232_components;
	return TRUE;
}

bool handle_rs232_handler_to_rs232_dur_handler_msgs(RS232Data *rs_232_data, TimeStamp current_time, RS232DurHand2RS232HandMsg *msgs_rs232_dur_hand_2_rs232_hand, RS232Hand2RS232DurHandMsg *msgs_rs232_hand_2_rs232_dur_hand)
{
	RS232Hand2RS232DurHandMsgItem msg_item;
	char str_rs232_msg[RS232_HAND_2_RS232_DUR_HAND_MSG_STRING_LENGTH];
	char str_rs232_dur_status[RS232_DUR_STATUS_MAX_STRING_LENGTH];
	unsigned int comp_num;
	while (get_next_rs232_hand_2_rs232_dur_hand_msg_buffer_item(msgs_rs232_hand_2_rs232_dur_hand, &msg_item))
	{
		get_rs232_hand_2_rs232_dur_hand_msg_type_string(msg_item.msg_type, str_rs232_msg);
		print_message(INFO_MSG ,"FirstBMICageInterfacer", "HandleRS232Hand2RS232DurHandMsgs", "handle_rs232_handler_to_rs232_dur_handler_msgs", str_rs232_msg);
		switch (msg_item.msg_type)
		{
			case RS232_HAND_2_RS232_DUR_HAND_MSG_ENABLE_TX_TIMER:	
				comp_num = msg_item.component_num;
				switch (tx_timer_status[comp_num])
				{
					case RS232_DUR_STATUS_TIMER_ON:
						get_rs232_dur_status_type_string(tx_timer_status[comp_num], str_rs232_dur_status);   
						return print_message(BUG_MSG ,"FirstBMICageInterfacer", "HandleRS232Hand2RS232DurHandMsgs", "handle_rs232_handler_to_rs232_dur_handler_msgs", str_rs232_dur_status);
					case RS232_DUR_STATUS_TIMER_OFF:
						tx_timer_end_time[comp_num] = msg_item.additional_data;
						tx_timer_status[comp_num] = RS232_DUR_STATUS_TIMER_ON;
						break;			
					default:
						get_rs232_dur_status_type_string(tx_timer_status[comp_num], str_rs232_dur_status);   
						return print_message(BUG_MSG ,"FirstBMICageInterfacer", "HandleRS232Hand2RS232DurHandMsgs", "handle_rs232_handler_to_rs232_dur_handler_msgs", str_rs232_dur_status);
				}
				break;
			case RS232_HAND_2_RS232_DUR_HAND_MSG_ENABLE_RX_TIMER:
				comp_num = msg_item.component_num;
				switch (rx_timer_status[comp_num])
				{
					case RS232_DUR_STATUS_TIMER_ON:
						get_rs232_dur_status_type_string(rx_timer_status[comp_num], str_rs232_dur_status);   
						return print_message(BUG_MSG ,"FirstBMICageInterfacer", "HandleRS232Hand2RS232DurHandMsgs", "handle_rs232_handler_to_rs232_dur_handler_msgs", str_rs232_dur_status);
					case RS232_DUR_STATUS_TIMER_OFF:
						rx_timer_end_time[comp_num] = msg_item.additional_data;
						rx_timer_status[comp_num] = RS232_DUR_STATUS_TIMER_ON;
						break;			
					default:
						get_rs232_dur_status_type_string(rx_timer_status[comp_num], str_rs232_dur_status);   
						return print_message(BUG_MSG ,"FirstBMICageInterfacer", "HandleRS232Hand2RS232DurHandMsgs", "handle_rs232_handler_to_rs232_dur_handler_msgs", str_rs232_dur_status);
				}
				break;
			default:
				return print_message(BUG_MSG ,"FirstBMICageInterfacer", "HandleRS232Hand2RS232DurHandMsgs", "handle_rs232_handler_to_rs232_dur_handler_msgs", str_rs232_msg);
		}
	}

	return TRUE;
}

bool handle_rs232_duration_handler(TimeStamp current_time, RS232DurHand2RS232HandMsg *msgs_rs232_dur_hand_2_rs232_hand)
{
	char str_dur_status[RS232_DUR_STATUS_MAX_STRING_LENGTH];
	unsigned int i;

	for (i = 0; i < num_of_rs232_components; i++)
	{
		switch (rx_timer_status[i])
		{
			case RS232_DUR_STATUS_TIMER_OFF:
				break;	// do nothing
			case RS232_DUR_STATUS_TIMER_ON:
				if (current_time >= rx_timer_end_time[i])
				{
					rx_timer_status[i] = RS232_DUR_STATUS_TIMER_OFF;	
					if (! write_to_rs232_dur_hand_2_rs232_hand_msg_buffer(msgs_rs232_dur_hand_2_rs232_hand, current_time, RS232_DUR_HAND_2_RS232_HAND_MSG_RX_TIMEOUT, i, 0))
						return print_message(ERROR_MSG ,"FirstBMICageInterfacer", "HandleRS232Hand2RS232DurHandMsgs", "handle_rs232_handler_duration", "! write_to_rs232_dur_hand_2_rs232_hand_msg_buffer()."); 
				}	
				break;
			default: 
				get_rs232_dur_status_type_string(rx_timer_status[i], str_dur_status);  
				return print_message(BUG_MSG ,"FirstBMICageInterfacer", "HandleRS232Hand2RS232DurHandMsgs", "handle_rs232_handler_duration", str_dur_status);		
		}
		switch (tx_timer_status[i])
		{
			case RS232_DUR_STATUS_TIMER_OFF:
				break;	// do nothing
			case RS232_DUR_STATUS_TIMER_ON:
				if (current_time >= tx_timer_end_time[i])
				{
					tx_timer_status[i] = RS232_DUR_STATUS_TIMER_OFF;	
					if (! write_to_rs232_dur_hand_2_rs232_hand_msg_buffer(msgs_rs232_dur_hand_2_rs232_hand, current_time, RS232_DUR_HAND_2_RS232_HAND_MSG_TX_TIMEOUT, i, 0))
						return print_message(ERROR_MSG ,"FirstBMICageInterfacer", "HandleRS232Hand2RS232DurHandMsgs", "handle_rs232_handler_duration", "! write_to_rs232_dur_hand_2_rs232_hand_msg_buffer()."); 
				}	
				break;
			default: 
				get_rs232_dur_status_type_string(tx_timer_status[i], str_dur_status);  
				return print_message(BUG_MSG ,"FirstBMICageInterfacer", "HandleRS232Hand2RS232DurHandMsgs", "handle_rs232_handler_duration", str_dur_status);		
		}
	}
	return TRUE;
}

