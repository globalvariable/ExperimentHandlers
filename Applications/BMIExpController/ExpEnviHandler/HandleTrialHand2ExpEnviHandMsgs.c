#include "HandleTrialHand2ExpEnviHandMsgs.h"



bool handle_trial_handler_to_exp_envi_handler_msg(ExpEnviData *exp_envi_data, ExpEnviStatus *exp_envi_status, TimeStamp current_time, TrialHand2ExpEnviHandMsg *msgs_trial_hand_2_exp_envi_hand, ExpEnviHand2ExpEnviDurHandMsg *msgs_exp_envi_hand_2_exp_envi_dur_hand, ExpEnviHandParadigmRobotReach *exp_envi_paradigm, ExpEnviRS232Cmd *exp_envi_rs232_cmd)
{
	TrialHand2ExpEnviHandMsgItem msg_item;
	char str_trial_hand_msg[TRIAL_HAND_2_EXP_ENVI_HAND_MSG_STRING_LENGTH];
	char str_exp_envi_status[EXP_ENVI_STATUS_MAX_STRING_LENGTH];
	unsigned int i;
	
	while (get_next_trial_hand_2_exp_envi_hand_msg_buffer_item(msgs_trial_hand_2_exp_envi_hand, &msg_item))
	{
		get_trial_hand_2_exp_envi_hand_msg_type_string(msg_item.msg_type, str_trial_hand_msg);
		print_message(INFO_MSG ,"ExpEnviHandler", "HandleTrialHand2ExpEnviHandMsgs", "handle_trial_handler_to_exp_envi_handler_msg", str_trial_hand_msg);
		switch (msg_item.msg_type)
		{
			case TRIAL_HAND_2_EXP_ENVI_HAND_MSG_START_TRIAL:	
				switch (*exp_envi_status)
				{
					case EXP_ENVI_STATUS_OUT_OF_TRIAL:
						exp_envi_paradigm->target_led_comp_idx = msg_item.additional_data;
						switch (exp_envi_paradigm->target_led_comp_idx)
						{
							case LEFT_LED:	
								*exp_envi_status = EXP_ENVI_STATUS_COMPONENTS_AVAILABLE;
								for (i = 0; i < exp_envi_data->num_of_inp_comps; i++)
								{
									reset_exp_envi_input_comp(&(exp_envi_data->inp_comp_types[i]));
									if (! write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer(msgs_exp_envi_hand_2_exp_envi_dur_hand, current_time,  EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_CANCEL_MIN_TIMER, i, 0))
										return print_message(BUG_MSG ,"ExpEnviHandler", "HandleTrialHand2ExpEnviHandMsgs", "handle_exp_envi_interf_to_exp_envi_handler_msg", "write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer().");
									if (! write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer(msgs_exp_envi_hand_2_exp_envi_dur_hand, current_time,  EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_CANCEL_MAX_TIMER, i, 0))
										return print_message(BUG_MSG ,"ExpEnviHandler", "HandleTrialHand2ExpEnviHandMsgs", "handle_exp_envi_interf_to_exp_envi_handler_msg", "write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer().");
								}
								exp_envi_rs232_cmd->guide_led = 1;
								exp_envi_rs232_cmd->left_led = 1;
								exp_envi_rs232_cmd->levers_available = 1;
								break;
							case RIGHT_LED:
								*exp_envi_status = EXP_ENVI_STATUS_COMPONENTS_AVAILABLE;
								for (i = 0; i < exp_envi_data->num_of_inp_comps; i++)
								{
									reset_exp_envi_input_comp(&(exp_envi_data->inp_comp_types[i]));
									if (! write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer(msgs_exp_envi_hand_2_exp_envi_dur_hand, current_time,  EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_CANCEL_MIN_TIMER, i, 0))
										return print_message(BUG_MSG ,"ExpEnviHandler", "HandleTrialHand2ExpEnviHandMsgs", "handle_exp_envi_interf_to_exp_envi_handler_msg", "write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer().");
									if (! write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer(msgs_exp_envi_hand_2_exp_envi_dur_hand, current_time,  EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_CANCEL_MAX_TIMER, i, 0))
										return print_message(BUG_MSG ,"ExpEnviHandler", "HandleTrialHand2ExpEnviHandMsgs", "handle_exp_envi_interf_to_exp_envi_handler_msg", "write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer().");
								}
								exp_envi_rs232_cmd->guide_led = 1;
								exp_envi_rs232_cmd->right_led = 1;
								exp_envi_rs232_cmd->levers_available = 1;
								break;
							default:
								return print_message(BUG_MSG ,"ExpEnviHandler", "HandleTrialHand2ExpEnviHandMsgs", "handle_trial_handler_to_exp_envi_handler_msg", "switch (exp_envi_paradigm.target_led_comp_idx) -default");	
						}
						break;
					case EXP_ENVI_STATUS_COMPONENTS_AVAILABLE:
						print_message(BUG_MSG ,"ExpEnviHandler", "HandleTrialHand2ExpEnviHandMsgs", "handle_trial_handler_to_exp_envi_handler_msg", str_trial_hand_msg);	
						get_exp_envi_status_type_string(*exp_envi_status, str_exp_envi_status);   
						return print_message(BUG_MSG ,"ExpEnviHandler", "HandleTrialHand2ExpEnviHandMsgs", "handle_trial_handler_to_exp_envi_handler_msg", str_exp_envi_status);	
					default:
						print_message(BUG_MSG ,"ExpEnviHandler", "HandleTrialHand2ExpEnviHandMsgs", "handle_trial_handler_to_exp_envi_handler_msg", str_trial_hand_msg);
						get_exp_envi_status_type_string(*exp_envi_status, str_exp_envi_status);   
						return print_message(BUG_MSG ,"ExpEnviHandler", "HandleTrialHand2ExpEnviHandMsgs", "handle_trial_handler_to_exp_envi_handler_msg", str_exp_envi_status);
				}
				break;
			case TRIAL_HAND_2_EXP_ENVI_HAND_MSG_END_TRIAL:	
				switch (*exp_envi_status)
				{
					case EXP_ENVI_STATUS_OUT_OF_TRIAL:
						print_message(BUG_MSG ,"ExpEnviHandler", "HandleTrialHand2ExpEnviHandMsgs", "handle_trial_handler_to_exp_envi_handler_msg", str_trial_hand_msg);	
						get_exp_envi_status_type_string(*exp_envi_status, str_exp_envi_status);   
						return print_message(BUG_MSG ,"ExpEnviHandler", "HandleTrialHand2ExpEnviHandMsgs", "handle_trial_handler_to_exp_envi_handler_msg", str_exp_envi_status);	
					case EXP_ENVI_STATUS_COMPONENTS_AVAILABLE:
						*exp_envi_status = EXP_ENVI_STATUS_OUT_OF_TRIAL;

						exp_envi_rs232_cmd->all_cmd = 0;

						for (i = 0; i < exp_envi_data->num_of_inp_comps; i++)
						{
							reset_exp_envi_input_comp(&(exp_envi_data->inp_comp_types[i]));
							if (! write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer(msgs_exp_envi_hand_2_exp_envi_dur_hand, current_time,  EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_CANCEL_MIN_TIMER, i, 0))
								return print_message(BUG_MSG ,"ExpEnviHandler", "HandleTrialHand2ExpEnviHandMsgs", "handle_exp_envi_interf_to_exp_envi_handler_msg", "write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer().");
							if (! write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer(msgs_exp_envi_hand_2_exp_envi_dur_hand, current_time,  EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_CANCEL_MAX_TIMER, i, 0))
								return print_message(BUG_MSG ,"ExpEnviHandler", "HandleTrialHand2ExpEnviHandMsgs", "handle_exp_envi_interf_to_exp_envi_handler_msg", "write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer().");
						}
						break;
					default:
						print_message(BUG_MSG ,"ExpEnviHandler", "HandleTrialHand2ExpEnviHandMsgs", "handle_trial_handler_to_exp_envi_handler_msg", str_trial_hand_msg);
						get_exp_envi_status_type_string(*exp_envi_status, str_exp_envi_status);   
						return print_message(BUG_MSG ,"ExpEnviHandler", "HandleTrialHand2ExpEnviHandMsgs", "handle_trial_handler_to_exp_envi_handler_msg", str_exp_envi_status);
				}
				break;
			case TRIAL_HAND_2_EXP_ENVI_HAND_MSG_RELEASE_REWARD:	// trial handler should send reward before ending trial.
				switch (*exp_envi_status)
				{
					case EXP_ENVI_STATUS_OUT_OF_TRIAL:  // first you should have rewarded and later on end the trial.
						print_message(BUG_MSG ,"ExpEnviHandler", "HandleTrialHand2ExpEnviHandMsgs", "handle_trial_handler_to_exp_envi_handler_msg", str_trial_hand_msg);	
						get_exp_envi_status_type_string(*exp_envi_status, str_exp_envi_status);   
						return print_message(BUG_MSG ,"ExpEnviHandler", "HandleTrialHand2ExpEnviHandMsgs", "handle_trial_handler_to_exp_envi_handler_msg", str_exp_envi_status);	
					case EXP_ENVI_STATUS_COMPONENTS_AVAILABLE:


						
						break;
					default:
						print_message(BUG_MSG ,"ExpEnviHandler", "HandleTrialHand2ExpEnviHandMsgs", "handle_trial_handler_to_exp_envi_handler_msg", str_trial_hand_msg);
						get_exp_envi_status_type_string(*exp_envi_status, str_exp_envi_status);   
						return print_message(BUG_MSG ,"ExpEnviHandler", "HandleTrialHand2ExpEnviHandMsgs", "handle_trial_handler_to_exp_envi_handler_msg", str_exp_envi_status);
				}
				break;
			case TRIAL_HAND_2_EXP_ENVI_HAND_MSG_RELEASE_PUNISHMENT:	
				switch (*exp_envi_status)
				{
					case EXP_ENVI_STATUS_OUT_OF_TRIAL:  // first you should have punished and later on end the trial.
						print_message(BUG_MSG ,"ExpEnviHandler", "HandleTrialHand2ExpEnviHandMsgs", "handle_trial_handler_to_exp_envi_handler_msg", str_trial_hand_msg);	
						get_exp_envi_status_type_string(*exp_envi_status, str_exp_envi_status);   
						return print_message(BUG_MSG ,"ExpEnviHandler", "HandleTrialHand2ExpEnviHandMsgs", "handle_trial_handler_to_exp_envi_handler_msg", str_exp_envi_status);	
					case EXP_ENVI_STATUS_COMPONENTS_AVAILABLE:



						break;
					default:
						print_message(BUG_MSG ,"ExpEnviHandler", "HandleTrialHand2ExpEnviHandMsgs", "handle_trial_handler_to_exp_envi_handler_msg", str_trial_hand_msg);
						get_exp_envi_status_type_string(*exp_envi_status, str_exp_envi_status);   
						return print_message(BUG_MSG ,"ExpEnviHandler", "HandleTrialHand2ExpEnviHandMsgs", "handle_trial_handler_to_exp_envi_handler_msg", str_exp_envi_status);
				}
				break;
			default:
				return print_message(BUG_MSG ,"ExpEnviHandler", "HandleTrialHand2ExpEnviHandMsgs", "handle_trial_handler_to_exp_envi_handler_msg", str_trial_hand_msg);
		}
	}
	return TRUE;
}
