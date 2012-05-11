#include "HandleExpEnviHand2ExpEnviInterfMsgs.h"


struct __ExpEnviRS232TX
{
	union
	{
		struct{
			unsigned OpenValve:1;
			unsigned ResetTrial:1;
			unsigned RightLED:1;
			unsigned LeftLED:1;
			unsigned Buzzer:1;
			unsigned EnableLever:1;
			unsigned None6:1;						
			unsigned None7:1;
		};
		char all_command;    // 8 bit data to TX
	} command;
};

static struct __ExpEnviRS232TX exp_envi_rs232_tx = { .command.all_command = 0 };	


bool handle_exp_envi_hand_2_exp_envi_interf_msgs(ExpEnviHand2ExpEnviInterfMsg *msgs_exp_envi_hand_2_exp_envi_interf, ExpEnviInterf2ExpEnviHandMsg *msgs_exp_envi_interf_2_exp_envi_hand, char *tx_buff)
{
	ExpEnviHand2ExpEnviInterfMsgItem *msg_item;
	char str_exp_envi_hand_2_exp_envi_interf_msg[EXP_ENVI_HAND_2_EXP_ENVI_INTERF_MSG_STRING_LENGTH];

	while (get_next_exp_envi_hand_2_exp_envi_interf_msg_buffer_item(msgs_exp_envi_hand_2_exp_envi_interf, &msg_item))
	{
		get_exp_envi_hand_2_exp_envi_interf_msg_type_string(msg_item->msg_type, str_exp_envi_hand_2_exp_envi_interf_msg);
		print_message(INFO_MSG ,"FirstBMICageManager", "HandleExpEnviHand2ExpEnviInterfMsgs", "handle_exp_envi_hand_2_exp_envi_interf_msgs", str_exp_envi_hand_2_exp_envi_interf_msg);	
		switch (msg_item->msg_type)
		{
			case EXP_ENVI_HAND_2_EXP_ENVI_INTERF_MSG_ARE_YOU_ALIVE:
				 break;			
			default:
				print_message(BUG_MSG ,"FirstBMICageManager", "HandleExpEnviHand2ExpEnviInterfMsgs", "handle_exp_envi_hand_2_exp_envi_interf_msgs", str_exp_envi_hand_2_exp_envi_interf_msg);	
				return print_message(BUG_MSG ,"FirstBMICageManager", "HandleExpEnviHand2ExpEnviInterfMsgs", "handle_exp_envi_hand_2_exp_envi_interf_msgs", "default - switch.");
		}
	}
	tx_buff[1] = exp_envi_rs232_tx.command.all_command;
	return TRUE;
}


