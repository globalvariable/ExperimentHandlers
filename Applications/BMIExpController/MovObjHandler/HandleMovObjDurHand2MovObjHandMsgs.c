#include "HandleMovObjDurHand2MovObjHandMsgs.h"


bool handle_mov_obj_dur_handler_to_mov_obj_handler_msg(ThreeDofRobot *robot_arm, TimeStamp current_time, MovObjDurHand2MovObjHandMsg *msgs_mov_obj_dur_hand_2_mov_obj_hand, MovObjHand2TrialHandMsg *msgs_mov_obj_hand_2_trial_hand, MovObjHand2MovObjDurHandMsg *msgs_mov_obj_hand_2_mov_obj_dur_hand, MovObjHand2NeuralNetMsgMultiThread *msgs_mov_obj_hand_2_neural_net_multi_thread, SpikeData *scheduled_spike_data, MovObjLocationType current_location, MessageLogBuffer *message_log, MovObjHandParadigmRobotReach *mov_obj_paradigm)
{
	MovObjHand2MovObjDurHandMsgAdditional mov_obj_hand_2_mov_obj_dur_hand_additional_data;
	MovObjDurHand2MovObjHandMsgItem msg_item;
	char str_mov_obj_dur_msg[MOV_OBJ_DUR_HAND_2_MOV_OBJ_HAND_MSG_STRING_LENGTH];
	while (get_next_mov_obj_dur_hand_2_mov_obj_hand_msg_buffer_item(msgs_mov_obj_dur_hand_2_mov_obj_hand, &msg_item))
	{
		switch (msg_item.msg_type)
		{
			case MOV_OBJ_DUR_HAND_2_MOV_OBJ_HAND_MSG_TIMEOUT:
				switch (msg_item.additional_data)
				{
					case MOV_OBJ_DUR_STATUS_ITEM_STAY_AT_CURRENT_POSITION:
						get_mov_obj_dur_hand_2_mov_obj_hand_msg_type_string(msg_item.msg_type, str_mov_obj_dur_msg);
						if (! write_to_message_log_buffer(message_log, INFO_MSG, current_time, "MovObjHandler", "HandleMovObjDurHand2MovObjHandMsgs", "handle_mov_obj_dur_handler_to_mov_obj_handler_msg", str_mov_obj_dur_msg))
							print_message(ERROR_MSG ,"MovObjHandler", "HandleMovObjDurHand2MovObjHandMsgs", "handle_mov_obj_dur_handler_to_mov_obj_handler_msg", "! write_to_message_log_buffer()");
						break;	
					case MOV_OBJ_DUR_STATUS_ITEM_SEND_PULSE_WIDTH:
						if (! handle_exp_envi_tx_shm_and_send_rs232_pulse_width_command(current_time))
							return print_message(ERROR_MSG ,"MovObjHandler", "HandleMovObjDurHand2MovObjHandMsgs", "handle_mov_obj_dur_handler_to_mov_obj_handler_msg", "! handle_exp_envi_tx_shm_and_send_rs232_pulse_width_command");
						// Schedule adc conversion results reading and pulse width sending again.
						mov_obj_hand_2_mov_obj_dur_hand_additional_data.schedule.schedule = current_time + mov_obj_paradigm->send_pw_command_wait_period;
						mov_obj_hand_2_mov_obj_dur_hand_additional_data.schedule.item_idx = MOV_OBJ_DUR_STATUS_ITEM_SEND_PULSE_WIDTH;
						if (! write_to_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer(msgs_mov_obj_hand_2_mov_obj_dur_hand, current_time,  MOV_OBJ_HAND_2_MOV_OBJ_DUR_HAND_MSG_SET_SCHEDULE, mov_obj_hand_2_mov_obj_dur_hand_additional_data)) 
							print_message(BUG_MSG ,"MovObjHandler", "MovObjHandlerRtTask", "handle_mov_obj_dur_handler_to_mov_obj_handler_msg", "write_to_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer().");
						mov_obj_hand_2_mov_obj_dur_hand_additional_data.schedule.schedule = current_time + mov_obj_paradigm->receive_position_wait_period;
						mov_obj_hand_2_mov_obj_dur_hand_additional_data.schedule.item_idx = MOV_OBJ_DUR_STATUS_ITEM_READ_POSITION;
						if (! write_to_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer(msgs_mov_obj_hand_2_mov_obj_dur_hand, current_time,  MOV_OBJ_HAND_2_MOV_OBJ_DUR_HAND_MSG_SET_SCHEDULE, mov_obj_hand_2_mov_obj_dur_hand_additional_data)) 
							print_message(BUG_MSG ,"MovObjHandler", "MovObjHandlerRtTask", "rt_mov_obj_handler", "write_to_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer().");
						break;	
					case MOV_OBJ_DUR_STATUS_ITEM_SEND_AD_CONVERSION:
						if (! handle_exp_envi_tx_shm_and_send_rs232_adc_command(current_time))
							return print_message(ERROR_MSG ,"MovObjHandler", "HandleMovObjDurHand2MovObjHandMsgs", "handle_mov_obj_dur_handler_to_mov_obj_handler_msg", "! handle_exp_envi_tx_shm_and_send_rs232_adc_command()"); 
						mov_obj_hand_2_mov_obj_dur_hand_additional_data.schedule.schedule = current_time + mov_obj_paradigm->send_pw_command_wait_period;
						mov_obj_hand_2_mov_obj_dur_hand_additional_data.schedule.item_idx = MOV_OBJ_DUR_STATUS_ITEM_SEND_PULSE_WIDTH;
						if (! write_to_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer(msgs_mov_obj_hand_2_mov_obj_dur_hand, current_time,  MOV_OBJ_HAND_2_MOV_OBJ_DUR_HAND_MSG_SET_SCHEDULE, mov_obj_hand_2_mov_obj_dur_hand_additional_data)) 
							return print_message(ERROR_MSG ,"MovObjHandler", "HandleMovObjDurHand2MovObjHandMsgs", "handle_mov_obj_dur_handler_to_mov_obj_handler_msg", "! write_to_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer()"); 
						mov_obj_hand_2_mov_obj_dur_hand_additional_data.schedule.schedule = current_time + mov_obj_paradigm->receive_position_wait_period;
						mov_obj_hand_2_mov_obj_dur_hand_additional_data.schedule.item_idx = MOV_OBJ_DUR_STATUS_ITEM_READ_POSITION;
						if (! write_to_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer(msgs_mov_obj_hand_2_mov_obj_dur_hand, current_time,  MOV_OBJ_HAND_2_MOV_OBJ_DUR_HAND_MSG_SET_SCHEDULE, mov_obj_hand_2_mov_obj_dur_hand_additional_data)) 
							return print_message(ERROR_MSG ,"MovObjHandler", "HandleMovObjDurHand2MovObjHandMsgs", "handle_mov_obj_dur_handler_to_mov_obj_handler_msg", "! write_to_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer()"); 
						break;
					case MOV_OBJ_DUR_STATUS_ITEM_READ_POSITION:
						if (! handle_rs232_rx_buffer_and_write_to_exp_envi_rx_shm())
							return print_message(ERROR_MSG ,"MovObjHandler", "HandleMovObjDurHand2MovObjHandMsgs", "handle_mov_obj_dur_handler_to_mov_obj_handler_msg", "! ! handle_rs232_rx_buffer_and_write_to_exp_envi_rx_shm()");
						calculate_forward_kinematics(robot_arm);
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
