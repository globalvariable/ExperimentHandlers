#include "HandleMovObjInterf2MovObjHandMsgs.h"

struct __MovObjRS232RX 
{
	union 
	{
		struct
		{
			char low;
			char high;
		};
		short int location;
	} location;
} ;

static struct __MovObjRS232RX  mov_obj_prev_status =  { .location.location = 0 };
static struct __MovObjRS232RX  mov_obj_rs232_rx =  { .location.location = 0 };

static MovObjInterf2MovObjHandMsg *msgs_mov_obj_interf_2_mov_obj_hand = NULL;

bool handle_mov_obj_interf_2_mov_obj_hand_msgs(char *rx_buff)
{
	mov_obj_rs232_rx.location.high = rx_buff[0];
	mov_obj_rs232_rx.location.low = rx_buff[1];
	return TRUE;
}

