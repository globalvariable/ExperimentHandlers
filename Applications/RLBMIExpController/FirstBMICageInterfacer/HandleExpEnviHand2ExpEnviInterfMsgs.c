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
	ExpEnviHand2ExpEnviInterfMsgItem msg_item;
	char str_exp_envi_hand_2_exp_envi_interf_msg[EXP_ENVI_HAND_2_EXP_ENVI_INTERF_MSG_STRING_LENGTH];

	exp_envi_rs232_tx.command.ResetTrial = 0;  /// commands should be saved through periods except ResetTrial
	exp_envi_rs232_tx.command.OpenValve = 0;  /// commands should be saved through periods except OpenValve
	exp_envi_rs232_tx.command.Buzzer = 0;  /// commands should be saved through periods except Buzzer

	while (get_next_exp_envi_hand_2_exp_envi_interf_msg_buffer_item(msgs_exp_envi_hand_2_exp_envi_interf, &msg_item))
	{
		get_exp_envi_hand_2_exp_envi_interf_msg_type_string(msg_item.msg_type, str_exp_envi_hand_2_exp_envi_interf_msg);
		print_message(INFO_MSG ,"FirstBMICageManager", "HandleExpEnviHand2ExpEnviInterfMsgs", "handle_exp_envi_hand_2_exp_envi_interf_msgs", str_exp_envi_hand_2_exp_envi_interf_msg);	
		switch (msg_item.msg_type)
		{
			case EXP_ENVI_HAND_2_EXP_ENVI_INTERF_MSG_LOW_2_HIGH:
				switch (msg_item.out_comp_num)
				{
					case LEFT_LED:
						exp_envi_rs232_tx.command.LeftLED = 1;			
						 break;			
					case RIGHT_LED:
						exp_envi_rs232_tx.command.RightLED = 1;			
						 break;	
					case VALVE:
						exp_envi_rs232_tx.command.OpenValve = 1;			
						 break;			
					case LEVER_SOLENOID:
						exp_envi_rs232_tx.command.EnableLever = 1;		// have to send 1 for every tx when in trial. 	
						 break;	
					case BUZZER:
						exp_envi_rs232_tx.command.Buzzer = 1;			
						 break;	
					default:
						print_message(BUG_MSG ,"FirstBMICageManager", "HandleExpEnviHand2ExpEnviInterfMsgs", "handle_exp_envi_hand_2_exp_envi_interf_msgs", str_exp_envi_hand_2_exp_envi_interf_msg);	
						return print_message(BUG_MSG ,"FirstBMICageManager", "HandleExpEnviHand2ExpEnviInterfMsgs", "handle_exp_envi_hand_2_exp_envi_interf_msgs", "switch (msg_item.out_comp_num).");
				}
				 break;			
			case EXP_ENVI_HAND_2_EXP_ENVI_INTERF_MSG_HIGH_2_LOW:
				switch (msg_item.out_comp_num)
				{
					case LEFT_LED:
						exp_envi_rs232_tx.command.LeftLED = 0;			
						 break;			
					case RIGHT_LED:
						exp_envi_rs232_tx.command.RightLED = 0;			
						 break;	
					case VALVE:
						exp_envi_rs232_tx.command.OpenValve = 0;			
						 break;			
					case LEVER_SOLENOID:
						exp_envi_rs232_tx.command.EnableLever = 0;			
						 break;	
					case BUZZER:
						exp_envi_rs232_tx.command.Buzzer = 0;			
						 break;	
					default:
						print_message(BUG_MSG ,"FirstBMICageManager", "HandleExpEnviHand2ExpEnviInterfMsgs", "handle_exp_envi_hand_2_exp_envi_interf_msgs", str_exp_envi_hand_2_exp_envi_interf_msg);	
						return print_message(BUG_MSG ,"FirstBMICageManager", "HandleExpEnviHand2ExpEnviInterfMsgs", "handle_exp_envi_hand_2_exp_envi_interf_msgs", "default - switch.");
				}
				 break;	
			case EXP_ENVI_HAND_2_EXP_ENVI_INTERF_MSG_RESET:
				exp_envi_rs232_tx.command.ResetTrial = 1;			
				 break;	
			default:
				return print_message(BUG_MSG ,"FirstBMICageManager", "HandleExpEnviHand2ExpEnviInterfMsgs", "handle_exp_envi_hand_2_exp_envi_interf_msgs", str_exp_envi_hand_2_exp_envi_interf_msg);	
		}
	}
	tx_buff[1] = exp_envi_rs232_tx.command.all_command;
	return TRUE;
}


