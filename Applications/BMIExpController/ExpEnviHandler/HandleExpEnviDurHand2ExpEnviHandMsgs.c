#include "HandleExpEnviDurHand2ExpEnviHandMsgs.h"


bool handle_exp_envi_dur_handler_to_exp_envi_handler_msg(ExpEnviData *exp_envi_data, ExpEnviStatus *exp_envi_status, TimeStamp current_time, ExpEnviDurHand2ExpEnviHandMsg *msgs_exp_envi_dur_hand_2_exp_envi_hand, ExpEnviHand2TrialHandMsg *msgs_exp_envi_hand_2_trial_hand)
{
	bool has_response;
	ExpEnviDurHand2ExpEnviHandMsgItem msg_item;
	char str_exp_envi_dur_msg[EXP_ENVI_DUR_HAND_2_EXP_ENVI_HAND_MSG_STRING_LENGTH];
	while (get_next_exp_envi_dur_hand_2_exp_envi_hand_msg_buffer_item(msgs_exp_envi_dur_hand_2_exp_envi_hand, &msg_item))
	{
		get_exp_envi_dur_hand_2_exp_envi_hand_msg_type_string(msg_item.msg_type, str_exp_envi_dur_msg);
		print_message(INFO_MSG ,"ExpEnviHandler", "HandleExpEnviDurHand2ExpEnviHandMsgs", "handle_exp_envi_dur_handler_to_exp_envi_handler_msg", str_exp_envi_dur_msg);
		switch (msg_item.msg_type)
		{
			case EXP_ENVI_DUR_HAND_2_EXP_ENVI_HAND_MSG_TIMEOUT_FOR_MIN:	
				switch (msg_item.inp_comp_num)
				{
					case IR_BEAM:
						if (! time_out_success_for_input_comp(&(exp_envi_data->inp_comp_types[IR_BEAM]), &has_response))
							return print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviDurHand2ExpEnviHandMsgs", "handle_exp_envi_dur_handler_to_exp_envi_handler_msg", "time_out_success_for_input_comp().");
						if (has_response)
						{
							print_message(INFO_MSG ,"ExpEnviHandler", "HandleExpEnviDurHand2ExpEnviHandMsgs", "handle_exp_envi_dur_handler_to_exp_envi_handler_msg", "IR_BEAM RESPONSE");
							if (! write_to_exp_envi_hand_2_trial_hand_msg_buffer(msgs_exp_envi_hand_2_trial_hand, current_time, EXP_ENVI_HAND_2_TRIAL_HAND_MSG_START_TRIAL_REQUEST, 0))
								return print_message(ERROR_MSG ,"ExpEnviHandler", "HandleExpEnviDurHand2ExpEnviHandMsgs", "handle_exp_envi_dur_handler_to_exp_envi_handler_msg", "write_to_exp_envi_hand_2_trial_hand_msg_buffer().");
						} 
						break;			
					case LEFT_LEVER:
						if (! time_out_success_for_input_comp(&(exp_envi_data->inp_comp_types[LEFT_LEVER]), &has_response))
							return print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviDurHand2ExpEnviHandMsgs", "handle_exp_envi_dur_handler_to_exp_envi_handler_msg", "min_time_out_for_input_comp().");
						if (has_response)
						{
							print_message(INFO_MSG ,"ExpEnviHandler", "HandleExpEnviDurHand2ExpEnviHandMsgs", "handle_exp_envi_dur_handler_to_exp_envi_handler_msg", "LEFT_LEVER RESPONSE");
						} 
						 break;	
					case RIGHT_LEVER:
						if (! time_out_success_for_input_comp(&(exp_envi_data->inp_comp_types[RIGHT_LEVER]), &has_response))
							return print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviDurHand2ExpEnviHandMsgs", "handle_exp_envi_dur_handler_to_exp_envi_handler_msg", "min_time_out_for_input_comp().");
						if (has_response)
						{
							print_message(INFO_MSG ,"ExpEnviHandler", "HandleExpEnviDurHand2ExpEnviHandMsgs", "handle_exp_envi_dur_handler_to_exp_envi_handler_msg", "RIGHT_LEVER RESPONSE");
						} 
						 break;			
					default:
						return print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviDurHand2ExpEnviHandMsgs", "handle_exp_envi_dur_handler_to_exp_envi_handler_msg", "switch (msg_item.inp_comp_num)");	
				}
				break;
			case EXP_ENVI_DUR_HAND_2_EXP_ENVI_HAND_MSG_TIMEOUT_FOR_MAX:	
				switch (msg_item.inp_comp_num)
				{
					case IR_BEAM:
						if (! time_out_fail_for_input_comp(&(exp_envi_data->inp_comp_types[IR_BEAM])))
							return print_message(ERROR_MSG ,"ExpEnviHandler", "HandleExpEnviDurHand2ExpEnviHandMsgs", "handle_exp_envi_dur_handler_to_exp_envi_handler_msg", "time_out_fail_for_input_comp().");
						break;			
					case LEFT_LEVER:
						if (! time_out_fail_for_input_comp(&(exp_envi_data->inp_comp_types[LEFT_LEVER])))
							return print_message(ERROR_MSG ,"ExpEnviHandler", "HandleExpEnviDurHand2ExpEnviHandMsgs", "handle_exp_envi_dur_handler_to_exp_envi_handler_msg", "time_out_fail_for_input_comp().");
						break;	
					case RIGHT_LEVER:
						if (! time_out_fail_for_input_comp(&(exp_envi_data->inp_comp_types[RIGHT_LEVER])))
							return print_message(ERROR_MSG ,"ExpEnviHandler", "HandleExpEnviDurHand2ExpEnviHandMsgs", "handle_exp_envi_dur_handler_to_exp_envi_handler_msg", "time_out_fail_for_input_comp().");
						break;			
					default:
						return print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviDurHand2ExpEnviHandMsgs", "handle_exp_envi_dur_handler_to_exp_envi_handler_msg", "switch (msg_item.inp_comp_num)");
				}
				break;
			default:
				return print_message(BUG_MSG ,"ExpEnviHandler", "HandleExpEnviDurHand2ExpEnviHandMsgs", "handle_exp_envi_dur_handler_to_exp_envi_handler_msg", str_exp_envi_dur_msg);
		}
	}
	return TRUE;
}
