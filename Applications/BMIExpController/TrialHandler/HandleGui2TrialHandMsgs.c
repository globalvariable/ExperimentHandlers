#include "HandleGui2TrialHandMsgs.h"




bool handle_gui_to_trial_handler_msg(TrialStatus *trial_status, TimeStamp current_time, Gui2TrialHandMsg *msgs_gui_2_trial_hand)
{
	Gui2TrialHandMsgItem *msg_item;
	char str_gui_msg[GUI_2_TRIAL_HAND_MSG_STRING_LENGTH];
	char str_status[TRIAL_STATUS_MAX_STRING_LENGTH];
	while (get_next_gui_2_trial_hand_msg_buffer_item(msgs_gui_2_trial_hand, &msg_item))
	{
		get_gui_2_trial_hand_msg_type_string(msg_item->msg_type, str_gui_msg);
		print_message(INFO_MSG ,"BMIExpController", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", str_gui_msg);
		switch (msg_item->msg_type)
		{
			case GUI_2_TRIAL_HAND_MSG_ENABLE_TRIAL_HANDLING:	
				switch (*trial_status)
				{
					case TRIAL_STATUS_TRIALS_DISABLED:
						*trial_status = TRIAL_STATUS_IN_REFRACTORY;
						break;
					case TRIAL_STATUS_IN_TRIAL:
						print_message(BUG_MSG ,"BMIExpController", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", str_gui_msg);
						get_trial_status_type_string(*trial_status, str_status);   
						return print_message(BUG_MSG ,"BMIExpController", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", str_status);
					case TRIAL_STATUS_IN_REFRACTORY:
						print_message(BUG_MSG ,"BMIExpController", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", str_gui_msg);
						get_trial_status_type_string(*trial_status, str_status);   
						return print_message(BUG_MSG ,"BMIExpController", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", str_status);
					case TRIAL_STATUS_START_TRIAL_AVAILABLE:	
						print_message(BUG_MSG ,"BMIExpController", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", str_gui_msg);
						get_trial_status_type_string(*trial_status, str_status);   
						return print_message(BUG_MSG ,"BMIExpController", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", str_status);
					default:
						print_message(BUG_MSG ,"BMIExpController", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", str_gui_msg);
						get_trial_status_type_string(*trial_status, str_status);   
						return print_message(BUG_MSG ,"BMIExpController", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", str_status);
				}
				break;
			case GUI_2_TRIAL_HAND_MSG_DISABLE_TRIAL_HANDLING:	
				switch (*trial_status)
				{
					case TRIAL_STATUS_TRIALS_DISABLED:
						print_message(BUG_MSG ,"BMIExpController", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", str_gui_msg);
						get_trial_status_type_string(*trial_status, str_status);   
						return print_message(BUG_MSG ,"BMIExpController", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", str_status);
					case TRIAL_STATUS_IN_TRIAL:
						*trial_status = TRIAL_STATUS_TRIALS_DISABLED;
						break;
					case TRIAL_STATUS_IN_REFRACTORY:
						*trial_status = TRIAL_STATUS_TRIALS_DISABLED;
						break;
					case TRIAL_STATUS_START_TRIAL_AVAILABLE:	
						*trial_status = TRIAL_STATUS_TRIALS_DISABLED;
						break;
					default:
						print_message(BUG_MSG ,"BMIExpController", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", str_gui_msg);
						get_trial_status_type_string(*trial_status, str_status);   
						return print_message(BUG_MSG ,"BMIExpController", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", str_status);
				}
				break;
			case GUI_2_TRIAL_HAND_MSG_QUIT:	
				switch (*trial_status)
				{
					case TRIAL_STATUS_TRIALS_DISABLED:
						break;
					case TRIAL_STATUS_IN_TRIAL:
						break;
					case TRIAL_STATUS_IN_REFRACTORY:
						break;
					case TRIAL_STATUS_START_TRIAL_AVAILABLE:	
						break;
					default:
						print_message(BUG_MSG ,"BMIExpController", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", str_gui_msg);
						get_trial_status_type_string(*trial_status, str_status);   
						return print_message(BUG_MSG ,"BMIExpController", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", str_status);
				}
				break;
			default:
				get_gui_2_trial_hand_msg_type_string(msg_item->msg_type, str_gui_msg);
				return print_message(BUG_MSG ,"BMIExpController", "HandleGui2TrialHandMsgs", "handle_gui_to_trial_handler_msg", str_gui_msg);	
		}
	}
	return TRUE;
}
