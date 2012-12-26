#include "HandleSpikeDataBuff.h"

#define OUTPUT_LAYER_FOR_BASE_SERVO_MUSCLE_0 				0
#define OUTPUT_LAYER_FOR_BASE_SERVO_MUSCLE_1 				1
#define OUTPUT_LAYER_FOR_SHOULDER_SERVO_MUSCLE_0 		2
#define OUTPUT_LAYER_FOR_SHOULDER_SERVO_MUSCLE_1 		3
#define OUTPUT_LAYER_FOR_ELBOW_SERVO_MUSCLE_0 			4
#define OUTPUT_LAYER_FOR_ELBOW_SERVO_MUSCLE_1 			5


static TimeStamp previous_system_time = 0;

static unsigned int base_servo_muscle_0_spike_counter = 0;
static unsigned int base_servo_muscle_1_spike_counter = 0;
static unsigned int shoulder_servo_muscle_0_spike_counter = 0;
static unsigned int shoulder_servo_muscle_1_spike_counter = 0;
static unsigned int elbow_servo_muscle_0_spike_counter = 0;
static unsigned int elbow_servo_muscle_1_spike_counter = 0;

bool handle_spike_data_buff(MovObjStatus mov_obj_status, TimeStamp current_time, SpikeData *scheduled_spike_data, ThreeDofRobot *robot)
{
	SpikeTimeStampItem *item;
	char str_mov_obj_status[MOV_OBJ_STATUS_MAX_STRING_LENGTH];
	unsigned int			*read_idx, write_idx, buffer_size;;

	read_idx = &(scheduled_spike_data->buff_idx_read);
	write_idx = scheduled_spike_data->buff_idx_write;	
	buffer_size = scheduled_spike_data->buffer_size;

	switch (mov_obj_status)
	{
		case MOV_OBJ_STATUS_OUT_OF_TRIAL:
			base_servo_muscle_0_spike_counter = 0;
			base_servo_muscle_1_spike_counter = 0;
			shoulder_servo_muscle_0_spike_counter = 0;
			shoulder_servo_muscle_1_spike_counter = 0;
			elbow_servo_muscle_0_spike_counter = 0;
			elbow_servo_muscle_1_spike_counter = 0;
			while ((*read_idx) != write_idx)		
			{
				item = &(scheduled_spike_data->buff[*read_idx]);
				if (item->peak_time < previous_system_time)
					return print_message(BUG_MSG ,"MovObjHandler", "HandleSpikeDataBuff", "handle_spike_data_buff", "item->peak_time < previous_system_time.");    	
				if (item->peak_time >= current_time)	
					break;
				if ((*read_idx + 1) == buffer_size)
					*read_idx = 0;
				else
					(*read_idx)++;
			}    
			break;
		case MOV_OBJ_STATUS_STAYING_AT_START_POINT:
			base_servo_muscle_0_spike_counter = 0;
			base_servo_muscle_1_spike_counter = 0;
			shoulder_servo_muscle_0_spike_counter = 0;
			shoulder_servo_muscle_1_spike_counter = 0;
			elbow_servo_muscle_0_spike_counter = 0;
			elbow_servo_muscle_1_spike_counter = 0;
			while ((*read_idx) != write_idx)		
			{
				item = &(scheduled_spike_data->buff[*read_idx]);
				if (item->peak_time < previous_system_time)
					return print_message(BUG_MSG ,"MovObjHandler", "HandleSpikeDataBuff", "handle_spike_data_buff", "item->peak_time < previous_system_time.");    	
				if (item->peak_time >= current_time)	
					break;
				if ((*read_idx + 1) == buffer_size)
					*read_idx = 0;
				else
					(*read_idx)++;
			}    
			break;
		case MOV_OBJ_STATUS_AVAILABLE_TO_CONTROL:
			base_servo_muscle_0_spike_counter = 0;
			base_servo_muscle_1_spike_counter = 0;
			shoulder_servo_muscle_0_spike_counter = 0;
			shoulder_servo_muscle_1_spike_counter = 0;
			elbow_servo_muscle_0_spike_counter = 0;
			elbow_servo_muscle_1_spike_counter = 0;
			while ((*read_idx) != write_idx)		
			{
				item = &(scheduled_spike_data->buff[*read_idx]);
				if (item->peak_time < previous_system_time)
					return print_message(BUG_MSG ,"MovObjHandler", "HandleSpikeDataBuff", "handle_spike_data_buff", "item->peak_time < previous_system_time.");    	
				if (item->peak_time >= current_time)	
					break;
				if ((*read_idx + 1) == buffer_size)
					*read_idx = 0;
				else
					(*read_idx)++;
				switch (item->mwa_or_layer)
				{
					case OUTPUT_LAYER_FOR_BASE_SERVO_MUSCLE_0:
						base_servo_muscle_0_spike_counter++;
						break;
					case OUTPUT_LAYER_FOR_BASE_SERVO_MUSCLE_1:
						base_servo_muscle_1_spike_counter++;	
						break;
					case OUTPUT_LAYER_FOR_SHOULDER_SERVO_MUSCLE_0:
						shoulder_servo_muscle_0_spike_counter++;
						break;
					case OUTPUT_LAYER_FOR_SHOULDER_SERVO_MUSCLE_1:
						shoulder_servo_muscle_1_spike_counter++;	
						break;
					case OUTPUT_LAYER_FOR_ELBOW_SERVO_MUSCLE_0:
						elbow_servo_muscle_0_spike_counter++;
						break;
					case OUTPUT_LAYER_FOR_ELBOW_SERVO_MUSCLE_1:
						elbow_servo_muscle_1_spike_counter++;	
						break;
					default:		
						return print_message(BUG_MSG ,"MovObjHandler", "HandleSpikeDataBuff", "handle_spike_data_buff", "Invalid Output Layer Number.");
				}
			}
			submit_servo_direction_and_speed(&(robot->servos[BASE_SERVO]), 20*(base_servo_muscle_0_spike_counter - base_servo_muscle_1_spike_counter));
			submit_servo_direction_and_speed(&(robot->servos[SHOULDER_SERVO]), -20*(shoulder_servo_muscle_0_spike_counter - shoulder_servo_muscle_1_spike_counter));
			submit_servo_direction_and_speed(&(robot->servos[ELBOW_SERVO]), 20*(elbow_servo_muscle_0_spike_counter - elbow_servo_muscle_1_spike_counter));
			break;
		case MOV_OBJ_STATUS_RESETTING_TO_TARGET_POINT:
			base_servo_muscle_0_spike_counter = 0;
			base_servo_muscle_1_spike_counter = 0;
			shoulder_servo_muscle_0_spike_counter = 0;
			shoulder_servo_muscle_1_spike_counter = 0;
			elbow_servo_muscle_0_spike_counter = 0;
			elbow_servo_muscle_1_spike_counter = 0;
			while ((*read_idx) != write_idx)		
			{
				item = &(scheduled_spike_data->buff[*read_idx]);
				if (item->peak_time < previous_system_time)
					return print_message(BUG_MSG ,"MovObjHandler", "HandleSpikeDataBuff", "handle_spike_data_buff", "item->peak_time < previous_system_time.");    	
				if (item->peak_time >= current_time)	
					break;
				if ((*read_idx + 1) == buffer_size)
					*read_idx = 0;
				else
					(*read_idx)++;
			}    
			break; 
		case MOV_OBJ_STATUS_REACHED_TARGET_POINT:
			base_servo_muscle_0_spike_counter = 0;
			base_servo_muscle_1_spike_counter = 0;
			shoulder_servo_muscle_0_spike_counter = 0;
			shoulder_servo_muscle_1_spike_counter = 0;
			elbow_servo_muscle_0_spike_counter = 0;
			elbow_servo_muscle_1_spike_counter = 0;
			while ((*read_idx) != write_idx)		
			{
				item = &(scheduled_spike_data->buff[*read_idx]);
				if (item->peak_time < previous_system_time)
					return print_message(BUG_MSG ,"MovObjHandler", "HandleSpikeDataBuff", "handle_spike_data_buff", "item->peak_time < previous_system_time.");    	
				if (item->peak_time >= current_time)	
					break;
				if ((*read_idx + 1) == buffer_size)
					*read_idx = 0;
				else
					(*read_idx)++;
			}    
			break; 
		case MOV_OBJ_STATUS_RESETTING_TO_START_POINT:
			base_servo_muscle_0_spike_counter = 0;
			base_servo_muscle_1_spike_counter = 0;
			shoulder_servo_muscle_0_spike_counter = 0;
			shoulder_servo_muscle_1_spike_counter = 0;
			elbow_servo_muscle_0_spike_counter = 0;
			elbow_servo_muscle_1_spike_counter = 0;
			while ((*read_idx) != write_idx)		
			{
				item = &(scheduled_spike_data->buff[*read_idx]);
				if (item->peak_time < previous_system_time)
					return print_message(BUG_MSG ,"MovObjHandler", "HandleSpikeDataBuff", "handle_spike_data_buff", "item->peak_time < previous_system_time.");    	
				if (item->peak_time >= current_time)	
					break;
				if ((*read_idx + 1) == buffer_size)
					*read_idx = 0;
				else
					(*read_idx)++;
			}    
			break; 
		default:
			get_mov_obj_status_type_string(mov_obj_status, str_mov_obj_status);
			return print_message(BUG_MSG ,"MovObjHandler", "HandleSpikeDataBuff", "handle_spike_data_buff", str_mov_obj_status);
	}

	return TRUE;
}



