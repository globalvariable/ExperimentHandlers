#include "HandleNeuralNet2MovObjHandMsgs.h"


bool handle_neural_net_to_mov_obj_handler_msg(MovObjStatus mov_obj_status, TimeStamp current_time, NeuralNet2MovObjHandMsg *msgs_neural_net_2_mov_obj_hand, MovObjHand2MovObjInterfMsg *msgs_mov_obj_hand_2_mov_obj_interf)
{
	NeuralNet2MovObjHandMsgItem *msg_item;
	char str_neural_net_msg[NEURAL_NET_2_MOV_OBJ_HAND_MSG_STRING_LENGTH];
	char str_mov_obj_status[MOV_OBJ_STATUS_MAX_STRING_LENGTH];

	while (get_next_neural_net_2_mov_obj_hand_msg_buffer_item(msgs_neural_net_2_mov_obj_hand, &msg_item))
	{
		get_neural_net_2_mov_obj_hand_msg_type_string(msg_item->msg_type, str_neural_net_msg);
		print_message(INFO_MSG ,"MovObjHandler", "HandleNeuralNet2MovObjHandMsgs", "handle_neural_net_to_mov_obj_handler_msg", str_neural_net_msg);
		switch (msg_item->msg_type)
		{
			case NEURAL_NET_2_MOV_OBJ_HAND_MSG_DIRECTION_SPEED_LOCATION:	
				switch (mov_obj_status)
				{
					case MOV_OBJ_STATUS_OUT_OF_TRIAL:
						break;  // do nothing
					case MOV_OBJ_STATUS_STAYING_AT_START_POINT:
						break; // do nothing
					case MOV_OBJ_STATUS_AVAILABLE_TO_CONTROL:
						if (! write_to_mov_obj_hand_2_mov_obj_interf_msg_buffer(msgs_mov_obj_hand_2_mov_obj_interf, current_time, MOV_OBJ_HAND_2_MOV_OBJ_INTERF_SET_DIRECTION_SPEED_LOCATION, msg_item->comp_num, msg_item->direction, msg_item->speed, msg_item->location))
							print_message(ERROR_MSG ,"MovObjHandler", "HandleNeuralNet2MovObjHandMsgs", "handle_neural_net_to_mov_obj_handler_msg","! write_to_mov_obj_hand_2_mov_obj_interf_msg_buffer().");	
						break;
					case MOV_OBJ_STATUS_RESETTING_TO_TARGET_POINT_W_FAIL:
						break; // do nothing
					case MOV_OBJ_STATUS_RESETTING_TO_TARGET_POINT_W_SUCCESS:
						break; // do nothing
					case MOV_OBJ_STATUS_REACHED_TARGET_POINT_W_FAIL:
						break; // do nothing
					case MOV_OBJ_STATUS_REACHED_TARGET_POINT_W_SUCCESS:
						break; // do nothing
					case MOV_OBJ_STATUS_RESETTING_TO_START_POINT:
						break; // do nothing
					default:
						print_message(BUG_MSG ,"MovObjHandler", "HandleNeuralNet2MovObjHandMsgs", "handle_neural_net_to_mov_obj_handler_msg", str_neural_net_msg);
						get_mov_obj_status_type_string(mov_obj_status, str_mov_obj_status);   
						return print_message(BUG_MSG ,"MovObjHandler", "HandleNeuralNet2MovObjHandMsgs", "handle_neural_net_to_mov_obj_handler_msg", str_mov_obj_status);
				}
				break;
			default:
				return print_message(BUG_MSG ,"MovObjHandler", "HandleNeuralNet2MovObjHandMsgs", "handle_neural_net_to_mov_obj_handler_msg", str_neural_net_msg);
		}
	}
	return TRUE;
}
