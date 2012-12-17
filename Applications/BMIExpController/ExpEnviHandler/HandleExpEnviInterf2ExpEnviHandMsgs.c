#include "HandleExpEnviInterf2ExpEnviHandMsgs.h"

bool handle_exp_envi_interf_to_exp_envi_handler_msg(ExpEnviData *exp_envi_data, TimeStamp current_time, ExpEnviHand2ExpEnviDurHandMsg *msgs_exp_envi_hand_2_exp_envi_dur_hand)
{
	ExpEnviInterf2ExpEnviHandMsgItem msg_item;
	char str_exp_envi_interf_msg[EXP_ENVI_INTERF_2_EXP_ENVI_HAND_MSG_STRING_LENGTH];
	bool valid;
	while (get_next_exp_envi_interf_2_exp_envi_hand_msg_buffer_item(msgs_exp_envi_interf_2_exp_envi_hand, &msg_item))
	{
//		get_exp_envi_interf_2_exp_envi_hand_msg_type_string(msg_item.msg_type, str_exp_envi_interf_msg);
//		print_message(INFO_MSG ,"ExpEnviHandler", "HandleExpEnviInterf2ExpEnviHandMsgs", "handle_exp_envi_interf_to_exp_envi_handler_msg", str_exp_envi_interf_msg);
		switch (msg_item.msg_type)
		{
			case EXP_ENVI_INTERF_2_EXP_ENVI_HAND_MSG_LOW_2_HIGH:	
				switch (msg_item.inp_comp_num)
				{
					case IR_BEAM:
						if (! write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer(msgs_exp_envi_hand_2_exp_envi_dur_hand, current_time,  EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_CANCEL_MIN_TIMER, IR_BEAM, 0))
							return print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviInterf2ExpEnviHandMsgs", "handle_exp_envi_interf_to_exp_envi_handler_msg", "write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer().");			
						if (! write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer(msgs_exp_envi_hand_2_exp_envi_dur_hand, current_time,  EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_CANCEL_MAX_TIMER, IR_BEAM, 0))
							return print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviInterf2ExpEnviHandMsgs", "handle_exp_envi_interf_to_exp_envi_handler_msg", "write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer().");
						if (! exp_envi_input_low_2_high_event(&(exp_envi_data->inp_comp_types[IR_BEAM]), &valid))
							return print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviInterf2ExpEnviHandMsgs", "handle_exp_envi_interf_to_exp_envi_handler_msg", "exp_envi_input_low_2_high_event().");
						if (!valid)
							break;
						if (! write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer(msgs_exp_envi_hand_2_exp_envi_dur_hand, current_time,  EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_START_MIN_TIMER, IR_BEAM, exp_envi_data->inp_comp_types[IR_BEAM].constraints.min_high_status_duration + current_time))
							return print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviInterf2ExpEnviHandMsgs", "handle_exp_envi_interf_to_exp_envi_handler_msg", "write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer().");			
						if (! write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer(msgs_exp_envi_hand_2_exp_envi_dur_hand, current_time,  EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_START_MAX_TIMER, IR_BEAM, exp_envi_data->inp_comp_types[IR_BEAM].constraints.max_high_status_duration + current_time))
							return print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviInterf2ExpEnviHandMsgs", "handle_exp_envi_interf_to_exp_envi_handler_msg", "write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer().");
							break;
					case LEFT_LEVER:
						if (! write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer(msgs_exp_envi_hand_2_exp_envi_dur_hand, current_time,  EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_CANCEL_MIN_TIMER, LEFT_LEVER, 0))
							return print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviInterf2ExpEnviHandMsgs", "handle_exp_envi_interf_to_exp_envi_handler_msg", "write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer().");			
						if (! write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer(msgs_exp_envi_hand_2_exp_envi_dur_hand, current_time,  EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_CANCEL_MAX_TIMER, LEFT_LEVER, 0))
							return print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviInterf2ExpEnviHandMsgs", "handle_exp_envi_interf_to_exp_envi_handler_msg", "write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer().");
						if (! exp_envi_input_low_2_high_event(&(exp_envi_data->inp_comp_types[LEFT_LEVER]), &valid))
							return print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviInterf2ExpEnviHandMsgs", "handle_exp_envi_interf_to_exp_envi_handler_msg", "exp_envi_input_low_2_high_event().");
						if (!valid)
							break;
						if (! write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer(msgs_exp_envi_hand_2_exp_envi_dur_hand, current_time,  EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_START_MIN_TIMER, LEFT_LEVER, exp_envi_data->inp_comp_types[LEFT_LEVER].constraints.min_high_status_duration + current_time))
							return print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviInterf2ExpEnviHandMsgs", "handle_exp_envi_interf_to_exp_envi_handler_msg", "write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer().");			
						if (! write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer(msgs_exp_envi_hand_2_exp_envi_dur_hand, current_time,  EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_START_MAX_TIMER, LEFT_LEVER, exp_envi_data->inp_comp_types[LEFT_LEVER].constraints.max_high_status_duration + current_time))
							return print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviInterf2ExpEnviHandMsgs", "handle_exp_envi_interf_to_exp_envi_handler_msg", "write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer().");
						 break;	
					case RIGHT_LEVER:
						if (! write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer(msgs_exp_envi_hand_2_exp_envi_dur_hand, current_time,  EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_CANCEL_MIN_TIMER, RIGHT_LEVER, 0))
							return print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviInterf2ExpEnviHandMsgs", "handle_exp_envi_interf_to_exp_envi_handler_msg", "write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer().");			
						if (! write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer(msgs_exp_envi_hand_2_exp_envi_dur_hand, current_time,  EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_CANCEL_MAX_TIMER, RIGHT_LEVER, 0))
							return print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviInterf2ExpEnviHandMsgs", "handle_exp_envi_interf_to_exp_envi_handler_msg", "write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer().");
						if (! exp_envi_input_low_2_high_event(&(exp_envi_data->inp_comp_types[RIGHT_LEVER]), &valid))
							return print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviInterf2ExpEnviHandMsgs", "handle_exp_envi_interf_to_exp_envi_handler_msg", "exp_envi_input_low_2_high_event().");
						if (!valid)
							break;
						if (! write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer(msgs_exp_envi_hand_2_exp_envi_dur_hand, current_time,  EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_START_MIN_TIMER, RIGHT_LEVER, exp_envi_data->inp_comp_types[RIGHT_LEVER].constraints.min_high_status_duration + current_time))
							return print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviInterf2ExpEnviHandMsgs", "handle_exp_envi_interf_to_exp_envi_handler_msg", "write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer().");			
						if (! write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer(msgs_exp_envi_hand_2_exp_envi_dur_hand, current_time,  EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_START_MAX_TIMER, RIGHT_LEVER, exp_envi_data->inp_comp_types[RIGHT_LEVER].constraints.max_high_status_duration + current_time))
							return print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviInterf2ExpEnviHandMsgs", "handle_exp_envi_interf_to_exp_envi_handler_msg", "write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer().");
						 break;			
					default:
						print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviInterf2ExpEnviHandMsgs", "handle_exp_envi_interf_to_exp_envi_handler_msg", str_exp_envi_interf_msg);	
						return print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviInterf2ExpEnviHandMsgs", "handle_exp_envi_interf_to_exp_envi_handler_msg", "default - switch.");
				}
				break;
			case EXP_ENVI_INTERF_2_EXP_ENVI_HAND_MSG_HIGH_2_LOW:	
				switch (msg_item.inp_comp_num)
				{
					case IR_BEAM:
						if (! write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer(msgs_exp_envi_hand_2_exp_envi_dur_hand, current_time,  EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_CANCEL_MIN_TIMER, IR_BEAM, 0))
							return print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviInterf2ExpEnviHandMsgs", "handle_exp_envi_interf_to_exp_envi_handler_msg", "write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer().");			
						if (! write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer(msgs_exp_envi_hand_2_exp_envi_dur_hand, current_time,  EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_CANCEL_MAX_TIMER, IR_BEAM, 0))
							return print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviInterf2ExpEnviHandMsgs", "handle_exp_envi_interf_to_exp_envi_handler_msg", "write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer().");
						if (! exp_envi_input_high_2_low_event(&(exp_envi_data->inp_comp_types[IR_BEAM]), &valid))
							return print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviInterf2ExpEnviHandMsgs", "handle_exp_envi_interf_to_exp_envi_handler_msg", "exp_envi_input_high_2_low_event().");
						if (!valid)
							break;
						if (! write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer(msgs_exp_envi_hand_2_exp_envi_dur_hand, current_time,  EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_START_MIN_TIMER, IR_BEAM, exp_envi_data->inp_comp_types[IR_BEAM].constraints.min_low_status_duration + current_time))
							return print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviInterf2ExpEnviHandMsgs", "handle_exp_envi_interf_to_exp_envi_handler_msg", "write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer().");			
						if (! write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer(msgs_exp_envi_hand_2_exp_envi_dur_hand, current_time,  EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_START_MAX_TIMER, IR_BEAM, exp_envi_data->inp_comp_types[IR_BEAM].constraints.max_low_status_duration + current_time))
							return print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviInterf2ExpEnviHandMsgs", "handle_exp_envi_interf_to_exp_envi_handler_msg", "write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer().");
						 break;			
					case LEFT_LEVER:
						if (! write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer(msgs_exp_envi_hand_2_exp_envi_dur_hand, current_time,  EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_CANCEL_MIN_TIMER, LEFT_LEVER, 0))
							return print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviInterf2ExpEnviHandMsgs", "handle_exp_envi_interf_to_exp_envi_handler_msg", "write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer().");			
						if (! write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer(msgs_exp_envi_hand_2_exp_envi_dur_hand, current_time,  EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_CANCEL_MAX_TIMER, LEFT_LEVER, 0))
							return print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviInterf2ExpEnviHandMsgs", "handle_exp_envi_interf_to_exp_envi_handler_msg", "write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer().");
						if (! exp_envi_input_high_2_low_event(&(exp_envi_data->inp_comp_types[LEFT_LEVER]), &valid))
							return print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviInterf2ExpEnviHandMsgs", "handle_exp_envi_interf_to_exp_envi_handler_msg", "exp_envi_input_high_2_low_event().");
						if (!valid)
							break;
						if (! write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer(msgs_exp_envi_hand_2_exp_envi_dur_hand, current_time,  EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_START_MIN_TIMER, LEFT_LEVER, exp_envi_data->inp_comp_types[LEFT_LEVER].constraints.min_low_status_duration + current_time))
							return print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviInterf2ExpEnviHandMsgs", "handle_exp_envi_interf_to_exp_envi_handler_msg", "write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer().");			
						if (! write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer(msgs_exp_envi_hand_2_exp_envi_dur_hand, current_time,  EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_START_MAX_TIMER, LEFT_LEVER, exp_envi_data->inp_comp_types[LEFT_LEVER].constraints.max_low_status_duration + current_time))
							return print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviInterf2ExpEnviHandMsgs", "handle_exp_envi_interf_to_exp_envi_handler_msg", "write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer().");
						 break;	
					case RIGHT_LEVER:
						if (! write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer(msgs_exp_envi_hand_2_exp_envi_dur_hand, current_time,  EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_CANCEL_MIN_TIMER, RIGHT_LEVER, 0))
							return print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviInterf2ExpEnviHandMsgs", "handle_exp_envi_interf_to_exp_envi_handler_msg", "write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer().");			
						if (! write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer(msgs_exp_envi_hand_2_exp_envi_dur_hand, current_time,  EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_CANCEL_MAX_TIMER, RIGHT_LEVER, 0))
							return print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviInterf2ExpEnviHandMsgs", "handle_exp_envi_interf_to_exp_envi_handler_msg", "write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer().");
						if (! exp_envi_input_high_2_low_event(&(exp_envi_data->inp_comp_types[RIGHT_LEVER]), &valid))
							return print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviInterf2ExpEnviHandMsgs", "handle_exp_envi_interf_to_exp_envi_handler_msg", "exp_envi_input_high_2_low_event().");
						if (!valid)
							break;
						if (! write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer(msgs_exp_envi_hand_2_exp_envi_dur_hand, current_time,  EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_START_MIN_TIMER, RIGHT_LEVER, exp_envi_data->inp_comp_types[RIGHT_LEVER].constraints.min_low_status_duration + current_time))
							return print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviInterf2ExpEnviHandMsgs", "handle_exp_envi_interf_to_exp_envi_handler_msg", "write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer().");			
						if (! write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer(msgs_exp_envi_hand_2_exp_envi_dur_hand, current_time,  EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_START_MAX_TIMER, RIGHT_LEVER, exp_envi_data->inp_comp_types[RIGHT_LEVER].constraints.max_low_status_duration + current_time))
							return print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviInterf2ExpEnviHandMsgs", "handle_exp_envi_interf_to_exp_envi_handler_msg", "write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer().");
						 break;			
					default:
						print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviInterf2ExpEnviHandMsgs", "handle_exp_envi_interf_to_exp_envi_handler_msg", str_exp_envi_interf_msg);	
						return print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviInterf2ExpEnviHandMsgs", "handle_exp_envi_interf_to_exp_envi_handler_msg", "default - switch.");
				}
				break;
			default:
				return print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviInterf2ExpEnviHandMsgs", "handle_exp_envi_interf_to_exp_envi_handler_msg", str_exp_envi_interf_msg);
		}
	}
	return TRUE;
}
