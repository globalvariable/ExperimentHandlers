#include "HandleSpikeDataBuff.h"

#define OUTPUT_LAYER_FOR_LEFT_MOVE 0
#define OUTPUT_LAYER_FOR_RIGHT_MOVE 1


static TimeStamp previous_system_time = 0;

static unsigned int left_layer_spike_counter = 0;
static unsigned int right_layer_spike_counter = 0;

bool handle_spike_data_buff(MovObjStatus mov_obj_status, TimeStamp current_time, SpikeData *scheduled_spike_data)
{
	SpikeTimeStampItem *item;
	char str_mov_obj_status[MOV_OBJ_STATUS_MAX_STRING_LENGTH];

	while (get_next_spike_data_item(scheduled_spike_data, &item))
	{
		if (item->peak_time < previous_system_time)
			return print_message(BUG_MSG ,"MovObjHandler", "HandleSpikeDataBuff", "handle_spike_data_buff", "item->peak_time < previous_system_time.");    	
		if (item->peak_time >= current_time)	
			break;    

		switch (item->mwa_or_layer)
		{
			case OUTPUT_LAYER_FOR_LEFT_MOVE:
				switch (mov_obj_status)
				{
					case MOV_OBJ_STATUS_OUT_OF_TRIAL:
						left_layer_spike_counter = 0;
						break;
					case MOV_OBJ_STATUS_STAYING_AT_START_POINT:
						left_layer_spike_counter = 0;
						break;
					case MOV_OBJ_STATUS_AVAILABLE_TO_CONTROL:
						(left_layer_spike_counter)++;
						break;
					case MOV_OBJ_STATUS_RESETTING_TO_TARGET_POINT_W_FAIL:
						left_layer_spike_counter = 0;
						break; 
					case MOV_OBJ_STATUS_RESETTING_TO_TARGET_POINT_W_SUCCESS:
						left_layer_spike_counter = 0;
						break; 
					case MOV_OBJ_STATUS_REACHED_TARGET_POINT_W_FAIL:
						left_layer_spike_counter = 0;
						break; 
					case MOV_OBJ_STATUS_REACHED_TARGET_POINT_W_SUCCESS:
						left_layer_spike_counter = 0;
						break; 
					case MOV_OBJ_STATUS_RESETTING_TO_START_POINT:
						left_layer_spike_counter = 0;
						break; 
					default:
						get_mov_obj_status_type_string(mov_obj_status, str_mov_obj_status);
						return print_message(BUG_MSG ,"MovObjHandler", "HandleSpikeDataBuff", "handle_spike_data_buff", str_mov_obj_status);
				}
				break;
			case OUTPUT_LAYER_FOR_RIGHT_MOVE:	
				switch (mov_obj_status)
				{
					case MOV_OBJ_STATUS_OUT_OF_TRIAL:
						right_layer_spike_counter = 0;
						break;
					case MOV_OBJ_STATUS_STAYING_AT_START_POINT:
						right_layer_spike_counter = 0;
						break;
					case MOV_OBJ_STATUS_AVAILABLE_TO_CONTROL:
						(right_layer_spike_counter)++;
						break;
					case MOV_OBJ_STATUS_RESETTING_TO_TARGET_POINT_W_FAIL:
						right_layer_spike_counter = 0;
						break; 
					case MOV_OBJ_STATUS_RESETTING_TO_TARGET_POINT_W_SUCCESS:
						right_layer_spike_counter = 0;
						break; 
					case MOV_OBJ_STATUS_REACHED_TARGET_POINT_W_FAIL:
						right_layer_spike_counter = 0;
						break; 
					case MOV_OBJ_STATUS_REACHED_TARGET_POINT_W_SUCCESS:
						right_layer_spike_counter = 0;
						break; 
					case MOV_OBJ_STATUS_RESETTING_TO_START_POINT:
						right_layer_spike_counter = 0;
						break; 
					default:
						get_mov_obj_status_type_string(mov_obj_status, str_mov_obj_status);
						return print_message(BUG_MSG ,"MovObjHandler", "HandleSpikeDataBuff", "handle_spike_data_buff", str_mov_obj_status);
				}
				break;
			default:
				return print_message(BUG_MSG ,"MovObjHandler", "HandleSpikeDataBuff", "handle_spike_data_buff", "Invalid Output Layer Number.");
		}
	}
	previous_system_time = current_time;
	return TRUE;
}


bool handle_spike_data_buff_for_bin(SpikeData *scheduled_spike_data, TimeStamp current_time, MovObjHand2MovObjInterfMsg *msgs_mov_obj_hand_2_mov_obj_interf)
{
	if ((left_layer_spike_counter) > (right_layer_spike_counter))
	{
		left_layer_spike_counter = 0;
		right_layer_spike_counter = 0;
		if (! write_to_mov_obj_hand_2_mov_obj_interf_msg_buffer(msgs_mov_obj_hand_2_mov_obj_interf, current_time, MOV_OBJ_HAND_2_MOV_OBJ_INTERF_SET_DIRECTION_SPEED_LOCATION,  0, MOV_OBJ_DIRECTION_LEFT, NEURONS_MOTOR_OUTPUT_MOTOR_SPEED, MOV_OBJ_LOCATION_NULL))
			return print_message(ERROR_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_dur_handler_to_mov_obj_handler_msg","! write_to_mov_obj_hand_2_mov_obj_interf_msg_buffer()."); 
	}
	else if  ((left_layer_spike_counter) < (right_layer_spike_counter))
	{
		left_layer_spike_counter = 0;
		right_layer_spike_counter = 0;
		if (! write_to_mov_obj_hand_2_mov_obj_interf_msg_buffer(msgs_mov_obj_hand_2_mov_obj_interf, current_time, MOV_OBJ_HAND_2_MOV_OBJ_INTERF_SET_DIRECTION_SPEED_LOCATION,  0, MOV_OBJ_DIRECTION_RIGHT, NEURONS_MOTOR_OUTPUT_MOTOR_SPEED, MOV_OBJ_LOCATION_NULL))
			return print_message(ERROR_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_dur_handler_to_mov_obj_handler_msg","! write_to_mov_obj_hand_2_mov_obj_interf_msg_buffer()."); 
	}
	else
	{
		left_layer_spike_counter = 0;
		right_layer_spike_counter = 0;
		if (! write_to_mov_obj_hand_2_mov_obj_interf_msg_buffer(msgs_mov_obj_hand_2_mov_obj_interf, current_time, MOV_OBJ_HAND_2_MOV_OBJ_INTERF_SET_DIRECTION_SPEED_LOCATION,  0, MOV_OBJ_DIRECTION_STATIONARY, MOV_OBJ_SPEED_NULL, MOV_OBJ_LOCATION_NULL))
			return print_message(ERROR_MSG ,"MovObjHandler", "HandleMovObjInterf2MovObjHandMsgs", "handle_mov_obj_dur_handler_to_mov_obj_handler_msg","! write_to_mov_obj_hand_2_mov_obj_interf_msg_buffer()."); 
	}
	return TRUE;
}
