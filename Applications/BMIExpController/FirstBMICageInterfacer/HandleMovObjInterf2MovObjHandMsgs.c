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

bool handle_mov_obj_interf_2_mov_obj_hand_msgs(char *rx_buff, MovObjInterf2MovObjHandMsg *msgs_mov_obj_interf_2_mov_obj_hand, TimeStamp current_time)
{
	mov_obj_rs232_rx.location.high = rx_buff[0];
	mov_obj_rs232_rx.location.low = rx_buff[1];

	if (mov_obj_prev_status.location.location != mov_obj_rs232_rx.location.location)       // Motor moved
	{
		if (! write_to_mov_obj_interf_2_mov_obj_hand_msg_buffer(msgs_mov_obj_interf_2_mov_obj_hand, current_time, MOV_OBJ_INTERF_2_MOV_OBJ_HAND_MSG_DIRECTION_SPEED_LOCATION, ONE_D_ACTUATOR, MOV_OBJ_DIRECTION_NULL, MOV_OBJ_SPEED_NULL, (mov_obj_rs232_rx.location.location*(80/272.0))))   // send location in means of millitmeters.
			return print_message(ERROR_MSG ,"FirstBMICageManager", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_interf_2_mov_obj_hand_msgs", "! write_to_mov_obj_interf_2_mov_obj_hand_msg_buffer().");
		printf("Location int: %d\n", mov_obj_rs232_rx.location.location);
		mov_obj_prev_status.location.location = mov_obj_rs232_rx.location.location;

	}
	return TRUE;
}

