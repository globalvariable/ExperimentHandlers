#include "HandleMovObjHand2MovObjInterfMsgs.h"

struct __MovObjRS232TX 
{
	union 
	{
		struct
		{
			unsigned Speed:4;
			unsigned Direction:1;
			unsigned Check:3;
		};
		char all_command;   // 8 bit data to TX
	} command; 
} ;

static struct __MovObjRS232TX  mov_obj_rs232_tx = { .command.all_command = 0 };	


bool handle_mov_obj_hand_2_mov_obj_interf_msgs(MovObjHand2MovObjInterfMsg *msgs_mov_obj_hand_2_mov_obj_interf, MovObjInterf2MovObjHandMsg *msgs_mov_obj_interf_2_mov_obj_hand, char *tx_buff)
{
	tx_buff[0] = mov_obj_rs232_tx.command.all_command;
	return TRUE;
}

