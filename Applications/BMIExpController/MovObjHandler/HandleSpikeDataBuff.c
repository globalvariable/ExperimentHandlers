#include "HandleSpikeDataBuff.h"

static TimeStamp previous_system_time = 0;


bool handle_spike_data_buff(MovObjStatus mov_obj_status, TimeStamp current_time, SpikeData *scheduled_spike_data, ThreeDofRobot *robot, MovObjHandParadigmRobotReach *mov_obj_paradigm)
{
	SpikeTimeStampItem *item;
	char str_mov_obj_status[MOV_OBJ_STATUS_MAX_STRING_LENGTH];
	unsigned int			*read_idx, write_idx, buffer_size;

	unsigned int base_servo_extensor_spike_counter;
	unsigned int base_servo_flexor_spike_counter;
	unsigned int shoulder_servo_extensor_spike_counter;
	unsigned int shoulder_servo_flexor_spike_counter;
	unsigned int elbow_servo_extensor_spike_counter;
	unsigned int elbow_servo_flexor_spike_counter;
	double spike_2_pulse_width_multiplier;
	ServoPulseChange pulse_change, max_pulse_change;

	read_idx = &(scheduled_spike_data->buff_idx_read);
	write_idx = scheduled_spike_data->buff_idx_write;	
	buffer_size = scheduled_spike_data->buffer_size;

	switch (mov_obj_status)
	{
		case MOV_OBJ_STATUS_OUT_OF_TRIAL:
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
			base_servo_extensor_spike_counter = 0;
			base_servo_flexor_spike_counter = 0;
			shoulder_servo_extensor_spike_counter = 0;
			shoulder_servo_flexor_spike_counter = 0;
			elbow_servo_extensor_spike_counter = 0;
			elbow_servo_flexor_spike_counter = 0;
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
					case LAYER_BASE_SERVO_EXTENSOR_MOTOR:
						base_servo_extensor_spike_counter++;
						break;
					case LAYER_BASE_SERVO_FLEXOR_MOTOR:
						base_servo_flexor_spike_counter++;	
						break;
					case LAYER_SHOULDER_SERVO_EXTENSOR_MOTOR:
						shoulder_servo_extensor_spike_counter++;
						break;
					case LAYER_SHOULDER_SERVO_FLEXOR_MOTOR:
						shoulder_servo_flexor_spike_counter++;	
						break;
					case LAYER_ELBOW_SERVO_EXTENSOR_MOTOR:
						elbow_servo_extensor_spike_counter++;
						break;
					case LAYER_ELBOW_SERVO_FLEXOR_MOTOR:
						elbow_servo_flexor_spike_counter++;	
						break;
					default:		
						return print_message(BUG_MSG ,"MovObjHandler", "HandleSpikeDataBuff", "handle_spike_data_buff", "Invalid Output Layer Number.");
				}
			}

			spike_2_pulse_width_multiplier = mov_obj_paradigm->spike_2_pulse_width_multiplier ;
			max_pulse_change = mov_obj_paradigm->max_pulse_width_change;

			pulse_change = (ServoPulseChange)(spike_2_pulse_width_multiplier*(base_servo_flexor_spike_counter - base_servo_extensor_spike_counter));
			if (pulse_change < 0)
			{
				if (pulse_change < (-max_pulse_change))
					pulse_change = -max_pulse_change;
			}
			else
			{
				if (pulse_change > max_pulse_change)
					pulse_change = max_pulse_change;	
			}
			submit_servo_direction_and_speed(&(robot->servos[BASE_SERVO]), pulse_change);

			pulse_change = (ServoPulseChange)(spike_2_pulse_width_multiplier*(shoulder_servo_flexor_spike_counter - shoulder_servo_extensor_spike_counter));
			if (pulse_change < 0)
			{
				if (pulse_change < (-max_pulse_change))
					pulse_change = -max_pulse_change;
			}
			else
			{
				if (pulse_change > max_pulse_change)
					pulse_change = max_pulse_change;	
			}
			submit_servo_direction_and_speed(&(robot->servos[SHOULDER_SERVO]), pulse_change);

			pulse_change = (ServoPulseChange)(spike_2_pulse_width_multiplier*(elbow_servo_flexor_spike_counter - elbow_servo_extensor_spike_counter));
			if (pulse_change < 0)
			{
				if (pulse_change < (-max_pulse_change))
					pulse_change = -max_pulse_change;
			}
			else
			{
				if (pulse_change > max_pulse_change)
					pulse_change = max_pulse_change;	
			}
			submit_servo_direction_and_speed(&(robot->servos[ELBOW_SERVO]), pulse_change);
			break;
		case MOV_OBJ_STATUS_RESETTING_TO_TARGET_POINT:
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
		case MOV_OBJ_STATUS_DISABLED:
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

	previous_system_time = current_time;

	return TRUE;
}



