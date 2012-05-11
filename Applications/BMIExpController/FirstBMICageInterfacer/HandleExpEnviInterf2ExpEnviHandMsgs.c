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


static ExpEnviInterf2ExpEnviHandMsg *msgs_exp_envi_interf_2_exp_envi_hand = NULL;

bool handle_exp_envi_interf_2_exp_envi_hand_msgs(char *rx_buff)
{
	exp_envi_rs232_rx.status.all_status = rx_buff[2];

	return TRUE;
}

