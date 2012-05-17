#include "HandleExpEnviInterf2ExpEnviHandMsgs.h"

struct __ExpEnviRS232RX 
{
	union
	{	
		struct
		{
			unsigned RightLever:1;
			unsigned LeftLever:1;
			unsigned NosePoke:1;
			unsigned None1:1;
			unsigned Resetting:1;
			unsigned ReachedRightTarget:1;	// no need to handle it. MovObj event handler will realize if it reached target from location information.
			unsigned ReachedLeftTarget:1;						
			unsigned None7:1;
		};
		char all_status;
	} status;
};

static struct __ExpEnviRS232RX  exp_envi_prev_status = { .status.all_status = 0 };
static struct __ExpEnviRS232RX exp_envi_rs232_rx = { .status.all_status = 0 };


bool handle_exp_envi_interf_2_exp_envi_hand_msgs(char *rx_buff, ExpEnviInterf2ExpEnviHandMsg *msgs_exp_envi_interf_2_exp_envi_hand, TimeStamp current_time)
{
	exp_envi_rs232_rx.status.all_status = rx_buff[2];

	if (exp_envi_prev_status.status.RightLever != exp_envi_rs232_rx.status.RightLever)
	{
		if (exp_envi_rs232_rx.status.RightLever)
		{
			if (! write_to_exp_envi_interf_2_exp_envi_hand_msg_buffer(msgs_exp_envi_interf_2_exp_envi_hand, current_time, EXP_ENVI_INTERF_2_EXP_ENVI_HAND_MSG_LOW_2_HIGH, RIGHT_LEVER, 0))
				return print_message(ERROR_MSG ,"FirstBMICageInterfacer", "HandleExpEnviInterf2ExpEnviHandMsgs", "handle_exp_envi_interf_2_exp_envi_hand_msgs", "! write_to_exp_envi_interf_2_exp_envi_hand_msg_buffer().");	
		}
		else
		{
			if (! write_to_exp_envi_interf_2_exp_envi_hand_msg_buffer(msgs_exp_envi_interf_2_exp_envi_hand, current_time, EXP_ENVI_INTERF_2_EXP_ENVI_HAND_MSG_HIGH_2_LOW, RIGHT_LEVER, 0))
				return print_message(ERROR_MSG ,"FirstBMICageInterfacer", "HandleExpEnviInterf2ExpEnviHandMsgs", "handle_exp_envi_interf_2_exp_envi_hand_msgs", "! write_to_exp_envi_interf_2_exp_envi_hand_msg_buffer().");	
		}
		exp_envi_prev_status.status.RightLever = exp_envi_rs232_rx.status.RightLever;
	}
	if (exp_envi_prev_status.status.LeftLever != exp_envi_rs232_rx.status.LeftLever)
	{
		if (exp_envi_rs232_rx.status.LeftLever)
		{
			if (! write_to_exp_envi_interf_2_exp_envi_hand_msg_buffer(msgs_exp_envi_interf_2_exp_envi_hand, current_time, EXP_ENVI_INTERF_2_EXP_ENVI_HAND_MSG_LOW_2_HIGH, LEFT_LEVER, 0))
				return print_message(ERROR_MSG ,"FirstBMICageInterfacer", "HandleExpEnviInterf2ExpEnviHandMsgs", "handle_exp_envi_interf_2_exp_envi_hand_msgs", "! write_to_exp_envi_interf_2_exp_envi_hand_msg_buffer().");	
		}
		else
		{
			if (! write_to_exp_envi_interf_2_exp_envi_hand_msg_buffer(msgs_exp_envi_interf_2_exp_envi_hand, current_time, EXP_ENVI_INTERF_2_EXP_ENVI_HAND_MSG_HIGH_2_LOW, LEFT_LEVER, 0))
				return print_message(ERROR_MSG ,"FirstBMICageInterfacer", "HandleExpEnviInterf2ExpEnviHandMsgs", "handle_exp_envi_interf_2_exp_envi_hand_msgs", "! write_to_exp_envi_interf_2_exp_envi_hand_msg_buffer().");	
		}
		exp_envi_prev_status.status.LeftLever = exp_envi_rs232_rx.status.LeftLever;
	}
	if (exp_envi_prev_status.status.NosePoke != exp_envi_rs232_rx.status.NosePoke)
	{
		if (exp_envi_rs232_rx.status.NosePoke)
		{
			if (! write_to_exp_envi_interf_2_exp_envi_hand_msg_buffer(msgs_exp_envi_interf_2_exp_envi_hand, current_time, EXP_ENVI_INTERF_2_EXP_ENVI_HAND_MSG_LOW_2_HIGH, IR_BEAM, 0))
				return print_message(ERROR_MSG ,"FirstBMICageInterfacer", "HandleExpEnviInterf2ExpEnviHandMsgs", "handle_exp_envi_interf_2_exp_envi_hand_msgs", "! write_to_exp_envi_interf_2_exp_envi_hand_msg_buffer().");	
		}
		else
		{
			if (! write_to_exp_envi_interf_2_exp_envi_hand_msg_buffer(msgs_exp_envi_interf_2_exp_envi_hand, current_time, EXP_ENVI_INTERF_2_EXP_ENVI_HAND_MSG_HIGH_2_LOW, IR_BEAM, 0))
				return print_message(ERROR_MSG ,"FirstBMICageInterfacer", "HandleExpEnviInterf2ExpEnviHandMsgs", "handle_exp_envi_interf_2_exp_envi_hand_msgs", "! write_to_exp_envi_interf_2_exp_envi_hand_msg_buffer().");	
		}
		exp_envi_prev_status.status.NosePoke = exp_envi_rs232_rx.status.NosePoke;
	}		


	return TRUE;
}

