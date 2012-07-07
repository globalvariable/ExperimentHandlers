#include "HandleSpikeDataBuff.h"

#define OUTPUT_LAYER_FOR_LEFT_MOVE 0
#define OUTPUT_LAYER_FOR_RIGHT_MOVE 1


static TimeStamp previous_system_time = 0;

bool handle_spike_data_buff(MovObjStatus mov_obj_status, TimeStamp current_time, SpikeData *scheduled_spike_data, unsigned int *left_layer_spike_counter, unsigned int *right_layer_spike_counter )
{
	SpikeTimeStampItem *item;
	char str_mov_obj_status[MOV_OBJ_STATUS_MAX_STRING_LENGTH];

	while (get_next_spike_data_item(scheduled_spike_data, &item))
	{
		if (item->peak_time < previous_system_time)
			return print_message(BUG_MSG ,"MovObjHandler", "HandleSpikeDataBuff", "handle_spike_data_buff", "item->peak_time < previous_system_time.");    	
		previous_system_time = current_time;
		if (item->peak_time >= current_time)	
			break;    

		switch (item->mwa_or_layer)
		{
			case OUTPUT_LAYER_FOR_LEFT_MOVE:
				switch (mov_obj_status)
				{
					case MOV_OBJ_STATUS_OUT_OF_TRIAL:
						*left_layer_spike_counter = 0;
						break;
					case MOV_OBJ_STATUS_STAYING_AT_START_POINT:
						*left_layer_spike_counter = 0;
						break;
					case MOV_OBJ_STATUS_AVAILABLE_TO_CONTROL:
						(*left_layer_spike_counter)++;
						break;
					case MOV_OBJ_STATUS_RESETTING_TO_TARGET_POINT_W_FAIL:
						*left_layer_spike_counter = 0;
						break; 
					case MOV_OBJ_STATUS_RESETTING_TO_TARGET_POINT_W_SUCCESS:
						*left_layer_spike_counter = 0;
						break; 
					case MOV_OBJ_STATUS_REACHED_TARGET_POINT_W_FAIL:
						*left_layer_spike_counter = 0;
						break; 
					case MOV_OBJ_STATUS_REACHED_TARGET_POINT_W_SUCCESS:
						*left_layer_spike_counter = 0;
						break; 
					case MOV_OBJ_STATUS_RESETTING_TO_START_POINT:
						*left_layer_spike_counter = 0;
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
						*right_layer_spike_counter = 0;
						break;
					case MOV_OBJ_STATUS_STAYING_AT_START_POINT:
						*right_layer_spike_counter = 0;
						break;
					case MOV_OBJ_STATUS_AVAILABLE_TO_CONTROL:
						(*right_layer_spike_counter)++;
						break;
					case MOV_OBJ_STATUS_RESETTING_TO_TARGET_POINT_W_FAIL:
						*right_layer_spike_counter = 0;
						break; 
					case MOV_OBJ_STATUS_RESETTING_TO_TARGET_POINT_W_SUCCESS:
						*right_layer_spike_counter = 0;
						break; 
					case MOV_OBJ_STATUS_REACHED_TARGET_POINT_W_FAIL:
						*right_layer_spike_counter = 0;
						break; 
					case MOV_OBJ_STATUS_REACHED_TARGET_POINT_W_SUCCESS:
						*right_layer_spike_counter = 0;
						break; 
					case MOV_OBJ_STATUS_RESETTING_TO_START_POINT:
						*right_layer_spike_counter = 0;
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
	return TRUE;
}
