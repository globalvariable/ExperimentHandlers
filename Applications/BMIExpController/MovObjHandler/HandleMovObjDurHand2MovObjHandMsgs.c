#include "HandleMovObjDurHand2MovObjHandMsgs.h"


bool handle_mov_obj_dur_handler_to_mov_obj_handler_msg(ThreeDofRobot *robot_arm, MovObjStatus *mov_obj_status, TimeStamp current_time, MovObjDurHand2MovObjHandMsg *msgs_mov_obj_dur_hand_2_mov_obj_hand, MovObjHand2TrialHandMsg *msgs_mov_obj_hand_2_trial_hand, MovObjHand2MovObjDurHandMsg *msgs_mov_obj_hand_2_mov_obj_dur_hand, MovObjHand2NeuralNetMsgMultiThread *msgs_mov_obj_hand_2_neural_net_multi_thread, SpikeData *scheduled_spike_data, MovObjLocationType current_location)
{
	MovObjDurHand2MovObjHandMsgItem msg_item;
	char str_mov_obj_dur_msg[MOV_OBJ_DUR_HAND_2_MOV_OBJ_HAND_MSG_STRING_LENGTH];
	char str_mov_obj_status[MOV_OBJ_STATUS_MAX_STRING_LENGTH];
	while (get_next_mov_obj_dur_hand_2_mov_obj_hand_msg_buffer_item(msgs_mov_obj_dur_hand_2_mov_obj_hand, &msg_item))
	{
		get_mov_obj_dur_hand_2_mov_obj_hand_msg_type_string(msg_item.msg_type, str_mov_obj_dur_msg);
		print_message(INFO_MSG ,"MovObjHandler", "HandleMovObjDurHand2MovObjHandMsgs", "handle_mov_obj_dur_handler_to_mov_obj_handler_msg", str_mov_obj_dur_msg);

		switch (msg_item.msg_type)
		{
			case MOV_OBJ_DUR_HAND_2_MOV_OBJ_HAND_MSG_TIMEOUT:
				switch (msg_item.additional_data)
				{
					case MOV_OBJ_DUR_STATUS_ITEM_STAY_AT_CURRENT_POSITION:
						switch (*mov_obj_status)
						{
							case MOV_OBJ_STATUS_OUT_OF_TRIAL:
								break;
							case MOV_OBJ_STATUS_STAYING_AT_START_POINT:
								break;
							case MOV_OBJ_STATUS_AVAILABLE_TO_CONTROL:
								break;
							case MOV_OBJ_STATUS_RESETTING_TO_TARGET_POINT:
								break;
							default:
								return FALSE;
						}
						break;	
					case MOV_OBJ_DUR_STATUS_ITEM_SEND_PULSE_WIDTH:
						switch (*mov_obj_status)
						{
							case MOV_OBJ_STATUS_OUT_OF_TRIAL:
								break;
							case MOV_OBJ_STATUS_STAYING_AT_START_POINT:
								break;
							case MOV_OBJ_STATUS_AVAILABLE_TO_CONTROL:
								break;
							case MOV_OBJ_STATUS_RESETTING_TO_TARGET_POINT:
								break;
							default:
								return FALSE;
						}
						break;	
					case MOV_OBJ_DUR_STATUS_ITEM_READ_POSITION:
						switch (*mov_obj_status)
						{
							case MOV_OBJ_STATUS_OUT_OF_TRIAL:
								break;
							case MOV_OBJ_STATUS_STAYING_AT_START_POINT:
								break;
							case MOV_OBJ_STATUS_AVAILABLE_TO_CONTROL:
								break;
							case MOV_OBJ_STATUS_RESETTING_TO_TARGET_POINT:
								break;
							default:
								return FALSE;
						}
						break;	
					default:
						return FALSE;
				}
				break;
			default:
				return FALSE;
		}
	}

	return TRUE;
}
