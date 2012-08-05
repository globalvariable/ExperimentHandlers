#include "HandleExpEnviHand2ExpEnviDurHandMsgs.h"

bool handle_exp_envi_handler_to_exp_envi_dur_handler_msg(ExpEnviInputsMinDurationStatus *exp_envi_inputs_min_dur_status, ExpEnviInputsMaxDurationStatus *exp_envi_inputs_max_dur_status, TimeStamp current_time, ExpEnviHand2ExpEnviDurHandMsg *msgs_exp_envi_hand_2_exp_envi_dur_hand, TimeStamp *inputs_handling_end_time_min, TimeStamp *inputs_handling_end_time_max)
{
	ExpEnviHand2ExpEnviDurHandMsgItem msg_item;
	char str_exp_envi_hand_msg[EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_STRING_LENGTH];
	char str_exp_envi_inp_min_dur_status[EXP_ENVI_INPUTS_MIN_DUR_STATUS_MAX_STRING_LENGTH];
	char str_exp_envi_inp_max_dur_status[EXP_ENVI_INPUTS_MAX_DUR_STATUS_MAX_STRING_LENGTH];
	while (get_next_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer_item(msgs_exp_envi_hand_2_exp_envi_dur_hand, &msg_item))
	{
//		get_exp_envi_hand_2_exp_envi_dur_hand_msg_type_string(msg_item.msg_type, str_exp_envi_hand_msg);
//		print_message(INFO_MSG ,"ExpEnviHandler", "HandleExpEnviHand2ExpEnviDurHandMsgs", "handle_exp_envi_handler_to_exp_envi_dur_handler_msg", str_exp_envi_hand_msg);
		switch (msg_item.msg_type)
		{
			case EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_START_MIN_TIMER:	
				switch (msg_item.inp_comp_num)
				{
					case IR_BEAM:
						switch (exp_envi_inputs_min_dur_status[IR_BEAM])
						{
							case EXP_ENVI_INPUTS_MIN_DUR_STATUS_TIMER_ON:
								print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviHand2ExpEnviDurHandMsgs", "handle_exp_envi_handler_to_exp_envi_dur_handler_msg", "IR_BEAM");
								get_exp_envi_input_min_dur_status_type_string(exp_envi_inputs_min_dur_status[IR_BEAM], str_exp_envi_inp_min_dur_status);   
								return print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviHand2ExpEnviDurHandMsgs", "handle_exp_envi_handler_to_exp_envi_dur_handler_msg", str_exp_envi_inp_min_dur_status);
							case EXP_ENVI_INPUTS_MIN_DUR_STATUS_TIMER_OFF:
								inputs_handling_end_time_min[IR_BEAM] = msg_item.additional_data;
								exp_envi_inputs_min_dur_status[IR_BEAM] = EXP_ENVI_INPUTS_MIN_DUR_STATUS_TIMER_ON;
								break;			
							default:
								get_exp_envi_input_min_dur_status_type_string(exp_envi_inputs_min_dur_status[IR_BEAM], str_exp_envi_inp_min_dur_status); 
								return print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviHand2ExpEnviDurHandMsgs", "handle_exp_envi_handler_to_exp_envi_dur_handler_msg", str_exp_envi_inp_min_dur_status);
						}
						 break;			
					case LEFT_LEVER:
						switch (exp_envi_inputs_min_dur_status[LEFT_LEVER])
						{
							case EXP_ENVI_INPUTS_MIN_DUR_STATUS_TIMER_ON:
								print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviHand2ExpEnviDurHandMsgs", "handle_exp_envi_handler_to_exp_envi_dur_handler_msg", "LEFT_LEVER");
								get_exp_envi_input_min_dur_status_type_string(exp_envi_inputs_min_dur_status[LEFT_LEVER], str_exp_envi_inp_min_dur_status);   
								return print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviHand2ExpEnviDurHandMsgs", "handle_exp_envi_handler_to_exp_envi_dur_handler_msg", str_exp_envi_inp_min_dur_status);
							case EXP_ENVI_INPUTS_MIN_DUR_STATUS_TIMER_OFF:
								inputs_handling_end_time_min[LEFT_LEVER] = msg_item.additional_data;
								exp_envi_inputs_min_dur_status[LEFT_LEVER] = EXP_ENVI_INPUTS_MIN_DUR_STATUS_TIMER_ON;
								break;			
							default:
								get_exp_envi_input_min_dur_status_type_string(exp_envi_inputs_min_dur_status[LEFT_LEVER], str_exp_envi_inp_min_dur_status);
								return print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviHand2ExpEnviDurHandMsgs", "handle_exp_envi_handler_to_exp_envi_dur_handler_msg", str_exp_envi_inp_min_dur_status);
						}
						 break;	
					case RIGHT_LEVER:
						switch (exp_envi_inputs_min_dur_status[LEFT_LEVER])
						{
							case EXP_ENVI_INPUTS_MIN_DUR_STATUS_TIMER_ON:
								print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviHand2ExpEnviDurHandMsgs", "handle_exp_envi_handler_to_exp_envi_dur_handler_msg", "LEFT_LEVER");
								get_exp_envi_input_min_dur_status_type_string(exp_envi_inputs_min_dur_status[RIGHT_LEVER], str_exp_envi_inp_min_dur_status);   
								return print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviHand2ExpEnviDurHandMsgs", "handle_exp_envi_handler_to_exp_envi_dur_handler_msg", str_exp_envi_inp_min_dur_status);
							case EXP_ENVI_INPUTS_MIN_DUR_STATUS_TIMER_OFF:
								inputs_handling_end_time_min[RIGHT_LEVER] = msg_item.additional_data;
								exp_envi_inputs_min_dur_status[RIGHT_LEVER] = EXP_ENVI_INPUTS_MIN_DUR_STATUS_TIMER_ON;
								break;			
							default:
								get_exp_envi_input_min_dur_status_type_string(exp_envi_inputs_min_dur_status[RIGHT_LEVER], str_exp_envi_inp_min_dur_status);
								return print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviHand2ExpEnviDurHandMsgs", "handle_exp_envi_handler_to_exp_envi_dur_handler_msg", str_exp_envi_inp_min_dur_status);
						}
						 break;			
					default:
						return print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviHand2ExpEnviDurHandMsgs", "handle_exp_envi_handler_to_exp_envi_dur_handler_msg", "msg_item.inp_comp_num");	
				}
				break;
			case EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_CANCEL_MIN_TIMER:	
				switch (msg_item.inp_comp_num)
				{
					case IR_BEAM:
						switch (exp_envi_inputs_min_dur_status[IR_BEAM])
						{
							case EXP_ENVI_INPUTS_MIN_DUR_STATUS_TIMER_ON:
								exp_envi_inputs_min_dur_status[IR_BEAM] = EXP_ENVI_INPUTS_MIN_DUR_STATUS_TIMER_OFF;
								break;			
							case EXP_ENVI_INPUTS_MIN_DUR_STATUS_TIMER_OFF:
								break; // do nothing
							default:
								get_exp_envi_input_min_dur_status_type_string(exp_envi_inputs_min_dur_status[IR_BEAM], str_exp_envi_inp_min_dur_status);  
								return print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviHand2ExpEnviDurHandMsgs", "handle_exp_envi_handler_to_exp_envi_dur_handler_msg", str_exp_envi_inp_min_dur_status);
						}
						 break;			
					case LEFT_LEVER:
						switch (exp_envi_inputs_min_dur_status[LEFT_LEVER])
						{
							case EXP_ENVI_INPUTS_MIN_DUR_STATUS_TIMER_ON:
								exp_envi_inputs_min_dur_status[LEFT_LEVER] = EXP_ENVI_INPUTS_MIN_DUR_STATUS_TIMER_OFF;
								break;			
							case EXP_ENVI_INPUTS_MIN_DUR_STATUS_TIMER_OFF:
								break; // do nothing
							default:
								get_exp_envi_input_min_dur_status_type_string(exp_envi_inputs_min_dur_status[LEFT_LEVER], str_exp_envi_inp_min_dur_status);  
								return print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviHand2ExpEnviDurHandMsgs", "handle_exp_envi_handler_to_exp_envi_dur_handler_msg", str_exp_envi_inp_min_dur_status);
						}
						 break;	
					case RIGHT_LEVER:
						switch (exp_envi_inputs_min_dur_status[RIGHT_LEVER])
						{
							case EXP_ENVI_INPUTS_MIN_DUR_STATUS_TIMER_ON:
								exp_envi_inputs_min_dur_status[RIGHT_LEVER] = EXP_ENVI_INPUTS_MIN_DUR_STATUS_TIMER_OFF;
								break;			
							case EXP_ENVI_INPUTS_MIN_DUR_STATUS_TIMER_OFF:
								break; // do nothing
							default:
								get_exp_envi_input_min_dur_status_type_string(exp_envi_inputs_min_dur_status[RIGHT_LEVER], str_exp_envi_inp_min_dur_status);  
								return print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviHand2ExpEnviDurHandMsgs", "handle_exp_envi_handler_to_exp_envi_dur_handler_msg", str_exp_envi_inp_min_dur_status);
						}
						 break;			
					default:
						return print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviHand2ExpEnviDurHandMsgs", "handle_exp_envi_handler_to_exp_envi_dur_handler_msg", "msg_item.inp_comp_num");	
				}
				break;
			case EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_START_MAX_TIMER:	
				switch (msg_item.inp_comp_num)
				{
					case IR_BEAM:
						switch (exp_envi_inputs_max_dur_status[IR_BEAM])
						{
							case EXP_ENVI_INPUTS_MAX_DUR_STATUS_TIMER_ON:
								print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviHand2ExpEnviDurHandMsgs", "handle_exp_envi_handler_to_exp_envi_dur_handler_msg", "IR_BEAM");
								get_exp_envi_input_max_dur_status_type_string(exp_envi_inputs_max_dur_status[IR_BEAM], str_exp_envi_inp_max_dur_status);   
								return print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviHand2ExpEnviDurHandMsgs", "handle_exp_envi_handler_to_exp_envi_dur_handler_msg", str_exp_envi_inp_max_dur_status);
							case EXP_ENVI_INPUTS_MAX_DUR_STATUS_TIMER_OFF:
								inputs_handling_end_time_max[IR_BEAM] = msg_item.additional_data;
								exp_envi_inputs_max_dur_status[IR_BEAM] = EXP_ENVI_INPUTS_MAX_DUR_STATUS_TIMER_ON;
								break;			
							default:
								get_exp_envi_input_max_dur_status_type_string(exp_envi_inputs_max_dur_status[IR_BEAM], str_exp_envi_inp_max_dur_status); 
								return print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviHand2ExpEnviDurHandMsgs", "handle_exp_envi_handler_to_exp_envi_dur_handler_msg", str_exp_envi_inp_max_dur_status);
						}
						 break;			
					case LEFT_LEVER:
						switch (exp_envi_inputs_max_dur_status[LEFT_LEVER])
						{
							case EXP_ENVI_INPUTS_MAX_DUR_STATUS_TIMER_ON:
								print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviHand2ExpEnviDurHandMsgs", "handle_exp_envi_handler_to_exp_envi_dur_handler_msg", "LEFT_LEVER");
								get_exp_envi_input_max_dur_status_type_string(exp_envi_inputs_max_dur_status[LEFT_LEVER], str_exp_envi_inp_max_dur_status);   
								return print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviHand2ExpEnviDurHandMsgs", "handle_exp_envi_handler_to_exp_envi_dur_handler_msg", str_exp_envi_inp_max_dur_status);
							case EXP_ENVI_INPUTS_MAX_DUR_STATUS_TIMER_OFF:
								inputs_handling_end_time_max[LEFT_LEVER] = msg_item.additional_data;
								exp_envi_inputs_max_dur_status[LEFT_LEVER] = EXP_ENVI_INPUTS_MAX_DUR_STATUS_TIMER_ON;
								break;			
							default:
								get_exp_envi_input_max_dur_status_type_string(exp_envi_inputs_max_dur_status[LEFT_LEVER], str_exp_envi_inp_max_dur_status);
								return print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviHand2ExpEnviDurHandMsgs", "handle_exp_envi_handler_to_exp_envi_dur_handler_msg", str_exp_envi_inp_max_dur_status);
						}
						 break;	
					case RIGHT_LEVER:
						switch (exp_envi_inputs_max_dur_status[RIGHT_LEVER])
						{
							case EXP_ENVI_INPUTS_MAX_DUR_STATUS_TIMER_ON:
								print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviHand2ExpEnviDurHandMsgs", "handle_exp_envi_handler_to_exp_envi_dur_handler_msg", "RIGHT_LEVER");
								get_exp_envi_input_max_dur_status_type_string(exp_envi_inputs_max_dur_status[RIGHT_LEVER], str_exp_envi_inp_max_dur_status);   
								return print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviHand2ExpEnviDurHandMsgs", "handle_exp_envi_handler_to_exp_envi_dur_handler_msg", str_exp_envi_inp_max_dur_status);
							case EXP_ENVI_INPUTS_MAX_DUR_STATUS_TIMER_OFF:
								inputs_handling_end_time_max[RIGHT_LEVER] = msg_item.additional_data;
								exp_envi_inputs_max_dur_status[RIGHT_LEVER] = EXP_ENVI_INPUTS_MAX_DUR_STATUS_TIMER_ON;
								break;			
							default:
								get_exp_envi_input_max_dur_status_type_string(exp_envi_inputs_max_dur_status[RIGHT_LEVER], str_exp_envi_inp_max_dur_status);  
								return print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviHand2ExpEnviDurHandMsgs", "handle_exp_envi_handler_to_exp_envi_dur_handler_msg", str_exp_envi_inp_max_dur_status);
						}
						 break;			
					default:
						return print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviHand2ExpEnviDurHandMsgs", "handle_exp_envi_handler_to_exp_envi_dur_handler_msg", "msg_item.inp_comp_num");	
				}
				break;
			case EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_CANCEL_MAX_TIMER:	
				switch (msg_item.inp_comp_num)
				{
					case IR_BEAM:
						switch (exp_envi_inputs_max_dur_status[IR_BEAM])
						{
							case EXP_ENVI_INPUTS_MAX_DUR_STATUS_TIMER_ON:
								exp_envi_inputs_max_dur_status[IR_BEAM] = EXP_ENVI_INPUTS_MAX_DUR_STATUS_TIMER_OFF;
								break;			
							case EXP_ENVI_INPUTS_MAX_DUR_STATUS_TIMER_OFF:
								break; // do nothing
							default:
								get_exp_envi_input_max_dur_status_type_string(exp_envi_inputs_max_dur_status[IR_BEAM], str_exp_envi_inp_max_dur_status);  
								return print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviHand2ExpEnviDurHandMsgs", "handle_exp_envi_handler_to_exp_envi_dur_handler_msg", str_exp_envi_inp_max_dur_status);
						}
						 break;			
					case LEFT_LEVER:
						switch (exp_envi_inputs_max_dur_status[LEFT_LEVER])
						{
							case EXP_ENVI_INPUTS_MAX_DUR_STATUS_TIMER_ON:
								exp_envi_inputs_max_dur_status[LEFT_LEVER] = EXP_ENVI_INPUTS_MAX_DUR_STATUS_TIMER_OFF;
								break;			
							case EXP_ENVI_INPUTS_MAX_DUR_STATUS_TIMER_OFF:
								break; // do nothing
							default:
								get_exp_envi_input_max_dur_status_type_string(exp_envi_inputs_max_dur_status[LEFT_LEVER], str_exp_envi_inp_max_dur_status);  
								return print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviHand2ExpEnviDurHandMsgs", "handle_exp_envi_handler_to_exp_envi_dur_handler_msg", str_exp_envi_inp_max_dur_status);
						}
						 break;	
					case RIGHT_LEVER:
						switch (exp_envi_inputs_max_dur_status[RIGHT_LEVER])
						{
							case EXP_ENVI_INPUTS_MAX_DUR_STATUS_TIMER_ON:
								exp_envi_inputs_max_dur_status[RIGHT_LEVER] = EXP_ENVI_INPUTS_MAX_DUR_STATUS_TIMER_OFF;
								break;			
							case EXP_ENVI_INPUTS_MAX_DUR_STATUS_TIMER_OFF:
								break; // do nothing
							default:
								get_exp_envi_input_max_dur_status_type_string(exp_envi_inputs_max_dur_status[RIGHT_LEVER], str_exp_envi_inp_max_dur_status);  
								return print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviHand2ExpEnviDurHandMsgs", "handle_exp_envi_handler_to_exp_envi_dur_handler_msg", str_exp_envi_inp_max_dur_status);
						}
						 break;			
					default:
						return print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviHand2ExpEnviDurHandMsgs", "handle_exp_envi_handler_to_exp_envi_dur_handler_msg", "msg_item.inp_comp_num");	
				}
				break;
			default:
				return print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviHand2ExpEnviDurHandMsgs", "handle_exp_envi_handler_to_exp_envi_dur_handler_msg", str_exp_envi_hand_msg);
		}
	}
	return TRUE;
}
