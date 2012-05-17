#include "HandleTrialHand2ExpEnviHandMsgs.h"



bool handle_trial_handler_to_exp_envi_handler_msg(ExpEnviData *exp_envi_data, ExpEnviStatus *exp_envi_status, TimeStamp current_time, TrialHand2ExpEnviHandMsg *msgs_trial_hand_2_exp_envi_hand, ExpEnviHand2ExpEnviInterfMsg *msgs_exp_envi_hand_2_exp_envi_interf, ExpEnviHand2ExpEnviDurHandMsg *msgs_exp_envi_hand_2_exp_envi_dur_hand)
{
	TrialHand2ExpEnviHandMsgItem *msg_item;
	char str_trial_hand_msg[TRIAL_HAND_2_EXP_ENVI_HAND_MSG_STRING_LENGTH];
	char str_exp_envi_status[EXP_ENVI_STATUS_MAX_STRING_LENGTH];
	while (get_next_trial_hand_2_exp_envi_hand_msg_buffer_item(msgs_trial_hand_2_exp_envi_hand, &msg_item))
	{
		get_trial_hand_2_exp_envi_hand_msg_type_string(msg_item->msg_type, str_trial_hand_msg);
		print_message(INFO_MSG ,"ExpEnviHandler", "HandleTrialHand2ExpEnviHandMsgs", "handle_trial_handler_to_exp_envi_handler_msg", str_trial_hand_msg);
		switch (msg_item->msg_type)
		{
			case TRIAL_HAND_2_EXP_ENVI_HAND_MSG_START_TRIAL:	
				switch (*exp_envi_status)
				{
					case EXP_ENVI_STATUS_OUT_OF_TRIAL:
						switch (msg_item->additional_data)
						{
							case TRIAL_TYPE_IN_VIVO_BMI_LEFT_TARGET:	
								*exp_envi_status = EXP_ENVI_STATUS_LEFT_TARGET_SELECTED;
								if (! write_to_exp_envi_hand_2_exp_envi_interf_msg_buffer(msgs_exp_envi_hand_2_exp_envi_interf, current_time, EXP_ENVI_HAND_2_EXP_ENVI_INTERF_MSG_LOW_2_HIGH, LEFT_LED, 0))
									return print_message(ERROR_MSG ,"ExpEnviHandler", "HandleTrialHand2ExpEnviHandMsgs", "handle_trial_handler_to_exp_envi_handler_msg", "! write_to_exp_envi_hand_2_exp_envi_interf_msg_buffer()");
								if (! write_to_exp_envi_hand_2_exp_envi_interf_msg_buffer(msgs_exp_envi_hand_2_exp_envi_interf, current_time, EXP_ENVI_HAND_2_EXP_ENVI_INTERF_MSG_LOW_2_HIGH, LEVER_SOLENOID, 0))
									return print_message(ERROR_MSG ,"ExpEnviHandler", "HandleTrialHand2ExpEnviHandMsgs", "handle_trial_handler_to_exp_envi_handler_msg", "! write_to_exp_envi_hand_2_exp_envi_interf_msg_buffer()");
								break;
							case TRIAL_TYPE_IN_VIVO_BMI_RIGHT_TARGET:
								*exp_envi_status = EXP_ENVI_STATUS_RIGHT_TARGET_SELECTED;	
								if (! write_to_exp_envi_hand_2_exp_envi_interf_msg_buffer(msgs_exp_envi_hand_2_exp_envi_interf, current_time, EXP_ENVI_HAND_2_EXP_ENVI_INTERF_MSG_LOW_2_HIGH, RIGHT_LED, 0))
									return print_message(ERROR_MSG ,"ExpEnviHandler", "HandleTrialHand2ExpEnviHandMsgs", "handle_trial_handler_to_exp_envi_handler_msg", "! write_to_exp_envi_hand_2_exp_envi_interf_msg_buffer()");
								if (! write_to_exp_envi_hand_2_exp_envi_interf_msg_buffer(msgs_exp_envi_hand_2_exp_envi_interf, current_time, EXP_ENVI_HAND_2_EXP_ENVI_INTERF_MSG_LOW_2_HIGH, LEVER_SOLENOID, 0))
									return print_message(ERROR_MSG ,"ExpEnviHandler", "HandleTrialHand2ExpEnviHandMsgs", "handle_trial_handler_to_exp_envi_handler_msg", "! write_to_exp_envi_hand_2_exp_envi_interf_msg_buffer()");
								break;
							default:
								print_message(BUG_MSG ,"ExpEnviHandler", "HandleTrialHand2ExpEnviHandMsgs", "handle_trial_handler_to_exp_envi_handler_msg", str_trial_hand_msg);	
								get_exp_envi_status_type_string(*exp_envi_status, str_exp_envi_status);   
								return print_message(BUG_MSG ,"ExpEnviHandler", "HandleTrialHand2ExpEnviHandMsgs", "handle_trial_handler_to_exp_envi_handler_msg", str_exp_envi_status);	
						}
						break;
					case EXP_ENVI_STATUS_LEFT_TARGET_SELECTED:
						print_message(BUG_MSG ,"ExpEnviHandler", "HandleTrialHand2ExpEnviHandMsgs", "handle_trial_handler_to_exp_envi_handler_msg", str_trial_hand_msg);	
						get_exp_envi_status_type_string(*exp_envi_status, str_exp_envi_status);   
						return print_message(BUG_MSG ,"ExpEnviHandler", "HandleTrialHand2ExpEnviHandMsgs", "handle_trial_handler_to_exp_envi_handler_msg", str_exp_envi_status);	
					case EXP_ENVI_STATUS_RIGHT_TARGET_SELECTED:
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
					case EXP_ENVI_STATUS_LEFT_TARGET_SELECTED:
						*exp_envi_status = EXP_ENVI_STATUS_OUT_OF_TRIAL;
						if (! write_to_exp_envi_hand_2_exp_envi_interf_msg_buffer(msgs_exp_envi_hand_2_exp_envi_interf, current_time, EXP_ENVI_HAND_2_EXP_ENVI_INTERF_MSG_HIGH_2_LOW, LEFT_LED, 0))
							return print_message(ERROR_MSG ,"ExpEnviHandler", "HandleTrialHand2ExpEnviHandMsgs", "handle_trial_handler_to_exp_envi_handler_msg", "! write_to_exp_envi_hand_2_exp_envi_interf_msg_buffer()");
						if (! write_to_exp_envi_hand_2_exp_envi_interf_msg_buffer(msgs_exp_envi_hand_2_exp_envi_interf, current_time, EXP_ENVI_HAND_2_EXP_ENVI_INTERF_MSG_HIGH_2_LOW, LEVER_SOLENOID, 0))
							return print_message(ERROR_MSG ,"ExpEnviHandler", "HandleTrialHand2ExpEnviHandMsgs", "handle_trial_handler_to_exp_envi_handler_msg", "! write_to_exp_envi_hand_2_exp_envi_interf_msg_buffer()");
						if (! write_to_exp_envi_hand_2_exp_envi_interf_msg_buffer(msgs_exp_envi_hand_2_exp_envi_interf, current_time, EXP_ENVI_HAND_2_EXP_ENVI_INTERF_MSG_RESET, EXP_ENVI_COMP_NUM_NULL, 0))
							return print_message(ERROR_MSG ,"ExpEnviHandler", "HandleTrialHand2ExpEnviHandMsgs", "handle_trial_handler_to_exp_envi_handler_msg", "! write_to_exp_envi_hand_2_exp_envi_interf_msg_buffer()");
						if (! write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer(msgs_exp_envi_hand_2_exp_envi_dur_hand, current_time,  EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_CANCEL_TIMER, LEFT_LEVER, 0, 0))
							return print_message(BUG_MSG ,"ExpEnviHandler", "HandleTrialHand2ExpEnviHandMsgs", "handle_exp_envi_interf_to_exp_envi_handler_msg", "write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer().");
						if (! write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer(msgs_exp_envi_hand_2_exp_envi_dur_hand, current_time,  EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_CANCEL_TIMER, RIGHT_LEVER, 0, 0))
							return print_message(BUG_MSG ,"ExpEnviHandler", "HandleTrialHand2ExpEnviHandMsgs", "handle_exp_envi_interf_to_exp_envi_handler_msg", "write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer().");
						if (! write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer(msgs_exp_envi_hand_2_exp_envi_dur_hand, current_time,  EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_CANCEL_TIMER, IR_BEAM, 0, 0))
							return print_message(BUG_MSG ,"ExpEnviHandler", "HandleTrialHand2ExpEnviHandMsgs", "handle_exp_envi_interf_to_exp_envi_handler_msg", "write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer().");
						break;
					case EXP_ENVI_STATUS_RIGHT_TARGET_SELECTED:
						*exp_envi_status = EXP_ENVI_STATUS_OUT_OF_TRIAL;
						if (! write_to_exp_envi_hand_2_exp_envi_interf_msg_buffer(msgs_exp_envi_hand_2_exp_envi_interf, current_time, EXP_ENVI_HAND_2_EXP_ENVI_INTERF_MSG_HIGH_2_LOW, RIGHT_LED, 0))
							return print_message(ERROR_MSG ,"ExpEnviHandler", "HandleTrialHand2ExpEnviHandMsgs", "handle_trial_handler_to_exp_envi_handler_msg", "! write_to_exp_envi_hand_2_exp_envi_interf_msg_buffer()");
						if (! write_to_exp_envi_hand_2_exp_envi_interf_msg_buffer(msgs_exp_envi_hand_2_exp_envi_interf, current_time, EXP_ENVI_HAND_2_EXP_ENVI_INTERF_MSG_HIGH_2_LOW, LEVER_SOLENOID, 0))
							return print_message(ERROR_MSG ,"ExpEnviHandler", "HandleTrialHand2ExpEnviHandMsgs", "handle_trial_handler_to_exp_envi_handler_msg", "! write_to_exp_envi_hand_2_exp_envi_interf_msg_buffer()");
						if (! write_to_exp_envi_hand_2_exp_envi_interf_msg_buffer(msgs_exp_envi_hand_2_exp_envi_interf, current_time, EXP_ENVI_HAND_2_EXP_ENVI_INTERF_MSG_RESET, EXP_ENVI_COMP_NUM_NULL, 0))
							return print_message(ERROR_MSG ,"ExpEnviHandler", "HandleTrialHand2ExpEnviHandMsgs", "handle_trial_handler_to_exp_envi_handler_msg", "! write_to_exp_envi_hand_2_exp_envi_interf_msg_buffer()");
						if (! write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer(msgs_exp_envi_hand_2_exp_envi_dur_hand, current_time,  EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_CANCEL_TIMER, LEFT_LEVER, 0, 0))
							return print_message(BUG_MSG ,"ExpEnviHandler", "HandleTrialHand2ExpEnviHandMsgs", "handle_exp_envi_interf_to_exp_envi_handler_msg", "write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer().");
						if (! write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer(msgs_exp_envi_hand_2_exp_envi_dur_hand, current_time,  EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_CANCEL_TIMER, RIGHT_LEVER, 0, 0))
							return print_message(BUG_MSG ,"ExpEnviHandler", "HandleTrialHand2ExpEnviHandMsgs", "handle_exp_envi_interf_to_exp_envi_handler_msg", "write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer().");
						if (! write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer(msgs_exp_envi_hand_2_exp_envi_dur_hand, current_time,  EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_CANCEL_TIMER, IR_BEAM, 0, 0))
							return print_message(BUG_MSG ,"ExpEnviHandler", "HandleTrialHand2ExpEnviHandMsgs", "handle_exp_envi_interf_to_exp_envi_handler_msg", "write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer().");
						break;
					default:
						print_message(BUG_MSG ,"ExpEnviHandler", "HandleTrialHand2ExpEnviHandMsgs", "handle_trial_handler_to_exp_envi_handler_msg", str_trial_hand_msg);
						get_exp_envi_status_type_string(*exp_envi_status, str_exp_envi_status);   
						return print_message(BUG_MSG ,"ExpEnviHandler", "HandleTrialHand2ExpEnviHandMsgs", "handle_trial_handler_to_exp_envi_handler_msg", str_exp_envi_status);
				}
				break;
			case TRIAL_HAND_2_EXP_ENVI_HAND_MSG_RELEASE_REWARD:	
				switch (*exp_envi_status)
				{
					case EXP_ENVI_STATUS_OUT_OF_TRIAL:  // first you should have rewarded and later on end the trial.
						print_message(BUG_MSG ,"ExpEnviHandler", "HandleTrialHand2ExpEnviHandMsgs", "handle_trial_handler_to_exp_envi_handler_msg", str_trial_hand_msg);	
						get_exp_envi_status_type_string(*exp_envi_status, str_exp_envi_status);   
						return print_message(BUG_MSG ,"ExpEnviHandler", "HandleTrialHand2ExpEnviHandMsgs", "handle_trial_handler_to_exp_envi_handler_msg", str_exp_envi_status);	
					case EXP_ENVI_STATUS_LEFT_TARGET_SELECTED:
						if (! write_to_exp_envi_hand_2_exp_envi_interf_msg_buffer(msgs_exp_envi_hand_2_exp_envi_interf, current_time, EXP_ENVI_HAND_2_EXP_ENVI_INTERF_MSG_LOW_2_HIGH, VALVE, 0))
							return print_message(ERROR_MSG ,"ExpEnviHandler", "HandleTrialHand2ExpEnviHandMsgs", "handle_trial_handler_to_exp_envi_handler_msg", "! write_to_exp_envi_hand_2_exp_envi_interf_msg_buffer()");
						break;
					case EXP_ENVI_STATUS_RIGHT_TARGET_SELECTED:
						if (! write_to_exp_envi_hand_2_exp_envi_interf_msg_buffer(msgs_exp_envi_hand_2_exp_envi_interf, current_time, EXP_ENVI_HAND_2_EXP_ENVI_INTERF_MSG_LOW_2_HIGH, VALVE, 0))
							return print_message(ERROR_MSG ,"ExpEnviHandler", "HandleTrialHand2ExpEnviHandMsgs", "handle_trial_handler_to_exp_envi_handler_msg", "! write_to_exp_envi_hand_2_exp_envi_interf_msg_buffer()");
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
					case EXP_ENVI_STATUS_LEFT_TARGET_SELECTED:
						if (! write_to_exp_envi_hand_2_exp_envi_interf_msg_buffer(msgs_exp_envi_hand_2_exp_envi_interf, current_time, EXP_ENVI_HAND_2_EXP_ENVI_INTERF_MSG_LOW_2_HIGH, BUZZER, 0))
							return print_message(ERROR_MSG ,"ExpEnviHandler", "HandleTrialHand2ExpEnviHandMsgs", "handle_trial_handler_to_exp_envi_handler_msg", "! write_to_exp_envi_hand_2_exp_envi_interf_msg_buffer()");
						break;
					case EXP_ENVI_STATUS_RIGHT_TARGET_SELECTED:
						if (! write_to_exp_envi_hand_2_exp_envi_interf_msg_buffer(msgs_exp_envi_hand_2_exp_envi_interf, current_time, EXP_ENVI_HAND_2_EXP_ENVI_INTERF_MSG_LOW_2_HIGH, BUZZER, 0))
							return print_message(ERROR_MSG ,"ExpEnviHandler", "HandleTrialHand2ExpEnviHandMsgs", "handle_trial_handler_to_exp_envi_handler_msg", "! write_to_exp_envi_hand_2_exp_envi_interf_msg_buffer()");
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
