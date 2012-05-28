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
	MovObjHand2MovObjInterfMsgItem *msg_item;
	char str_mov_obj_hand_2_mov_obj_interf_msg[MOV_OBJ_HAND_2_MOV_OBJ_INTERF_MSG_STRING_LENGTH];
	char str_direction_type[MOV_OBJ_DIRECTION_TYPE_MAX_STRING_LENGTH];	

//	mov_obj_rs232_tx.command.all_command = 0;

	while (get_next_mov_obj_hand_2_mov_obj_interf_msg_buffer_item(msgs_mov_obj_hand_2_mov_obj_interf, &msg_item))
	{
		get_mov_obj_hand_2_mov_obj_interf_msg_type_string(msg_item->msg_type, str_mov_obj_hand_2_mov_obj_interf_msg);
//		print_message(INFO_MSG ,"FirstBMICageManager", "HandleMovObjHand2MovObjInterfMsgs", "handle_mov_obj_hand_2_mov_obj_interf_msgs", str_mov_obj_hand_2_mov_obj_interf_msg);	
		switch (msg_item->msg_type)
		{
			case MOV_OBJ_HAND_2_MOV_OBJ_INTERF_SET_DIRECTION_SPEED_LOCATION:
				switch (msg_item->comp_num)
				{
					case ONE_D_ACTUATOR:
						mov_obj_rs232_tx.command.Speed = msg_item->speed;
						printf ("Speed: %f\n", msg_item->speed);
						printf ("Speed int: %d\n", mov_obj_rs232_tx.command.Speed);
						switch (msg_item->direction)
						{
							case MOV_OBJ_DIRECTION_LEFT:		// left direction is 0, right is 1
								mov_obj_rs232_tx.command.Direction = 0;
								break;
							case MOV_OBJ_DIRECTION_RIGHT:		// left direction is 1, right is 0
								mov_obj_rs232_tx.command.Direction = 1;
								break;
							case MOV_OBJ_DIRECTION_STATIONARY:   // might come from neural net output
								mov_obj_rs232_tx.command.Speed = 0;			
								break;
							default:
								get_mov_obj_direction_type_string(msg_item->direction, str_direction_type);
								return print_message(BUG_MSG ,"BMISimulationTrialController", "ExpEnviMovObjInterfacerHandler", "exp_envi_mov_obj_interfacer_handler", str_direction_type);
						}
						break;			
					default:
						print_message(BUG_MSG ,"FirstBMICageManager", "HandleMovObjHand2MovObjInterfMsgs", "handle_mov_obj_hand_2_mov_obj_interf_msgs", str_mov_obj_hand_2_mov_obj_interf_msg);	
						return print_message(BUG_MSG ,"FirstBMICageManager", "HandleMovObjHand2MovObjInterfMsgs", "handle_mov_obj_hand_2_mov_obj_interf_msgs", "switch (msg_item->comp_num).");
				}
				break;			
			default:
				return print_message(BUG_MSG ,"FirstBMICageManager", "HandleMovObjHand2MovObjInterfMsgs", "handle_mov_obj_hand_2_mov_obj_interf_msgs", str_mov_obj_hand_2_mov_obj_interf_msg);	
		}
	}

	tx_buff[0] = mov_obj_rs232_tx.command.all_command;

	return TRUE;
}

