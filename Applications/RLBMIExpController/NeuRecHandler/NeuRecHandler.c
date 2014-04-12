#include "NeuRecHandler.h"

static bool connect_to_trial_hand(RtTasksData *rt_tasks_data, TrialHand2NeuRecHandMsg *msgs_trial_hand_2_neu_rec_hand, NeuRecHand2TrialHandMsg **msgs_neu_rec_hand_2_trial_hand);

int main( int argc, char *argv[])
{
	RtTasksData *rt_tasks_data = NULL;
	RecordingData *recording_data = NULL;
	SortedSpikes 	*bluespike_sorted_spikes = NULL;    /// spike time stamps from biological neurons // sorted according to unit, not according to spike time.
	GtkWidget *btn_select_directory_to_save = NULL;

	TrialHand2NeuRecHandMsg *msgs_trial_hand_2_neu_rec_hand = NULL;
	NeuRecHand2TrialHandMsg *msgs_neu_rec_hand_2_trial_hand = NULL;

   	rt_tasks_data = rtai_malloc(SHM_NUM_RT_TASKS_DATA, 0);
	if (rt_tasks_data == NULL) 
		return print_message(ERROR_MSG ,"NeuRecHandler", "NeuRecHandler", "main", "rt_tasks_data == NULL.");

#ifdef	SIMULATION_MODE
	sys_time_ptr = &(rt_tasks_data->current_periodic_system_time);
#else
	sys_time_ptr = &(rt_tasks_data->current_daq_system_time);
	if (*sys_time_ptr == 0)
		return print_message(ERROR_MSG ,"NeuRecHandler", "NeuRecHandler", "main", "rt_tasks_data->current_daq_system_time.");
#endif	

   	recording_data = rtai_malloc(SHM_NUM_BLUESPIKE_RECORDING_DATA, 0);
	if (recording_data == NULL) 
		return print_message(ERROR_MSG ,"NeuRecHandler", "NeuRecHandler", "main", "recording_data == NULL.");

   	bluespike_sorted_spikes = rtai_malloc(SHM_NUM_BLUESPIKE_SORTED_SPIKES, 0);
	if (bluespike_sorted_spikes == NULL) 
		return print_message(ERROR_MSG ,"NeuRecHandler", "NeuRecHandler", "main", "bluespike_sorted_spikes == NULL.");

	initialize_data_read_write_handlers();

	msgs_trial_hand_2_neu_rec_hand = allocate_shm_server_trial_hand_2_neu_rec_hand_msg_buffer(msgs_trial_hand_2_neu_rec_hand);

	if (! connect_to_trial_hand(rt_tasks_data, msgs_trial_hand_2_neu_rec_hand, &msgs_neu_rec_hand_2_trial_hand))
		return print_message(ERROR_MSG ,"NeuRecHandler", "NeuRecHandler", "main", "connect_to_trial_hand().");	

	gtk_init(&argc, &argv);
  	btn_select_directory_to_save = gtk_file_chooser_button_new ("Select Directory", GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER);

	if(! create_neu_rec_handler_non_rt_thread(rt_tasks_data, recording_data, bluespike_sorted_spikes, msgs_trial_hand_2_neu_rec_hand, btn_select_directory_to_save))
		return print_message(ERROR_MSG ,"NeuRecHandler", "NeuRecHandler", "main", "create_neu_rec_handler_non_rt_thread().");

///	gtk_init(&argc, &argv);   call it before gtk_file_chooser_button_new() above;
	create_gui_handler(btn_select_directory_to_save);
	gtk_main();
	return 0;
}	

static bool connect_to_trial_hand(RtTasksData *rt_tasks_data, TrialHand2NeuRecHandMsg *msgs_trial_hand_2_neu_rec_hand, NeuRecHand2TrialHandMsg **msgs_neu_rec_hand_2_trial_hand)
{
	TrialHand2NeuRecHandMsgItem msg_item;
	char str_trial_hand_2_neu_rec_hand_msg[TRIAL_HAND_2_NEU_REC_HAND_MSG_STRING_LENGTH];

	while (1) 
	{ 
		while (get_next_trial_hand_2_neu_rec_hand_msg_buffer_item(msgs_trial_hand_2_neu_rec_hand, &msg_item))
		{
			get_trial_hand_2_neu_rec_hand_msg_type_string(msg_item.msg_type, str_trial_hand_2_neu_rec_hand_msg);
			print_message(INFO_MSG ,"NeuRecHandler", "NeuRecHandler", "connect_to_trial_hand", str_trial_hand_2_neu_rec_hand_msg);	
			switch (msg_item.msg_type)
			{
				case TRIAL_HAND_2_NEU_REC_HAND_MSG_ARE_YOU_ALIVE:
					*msgs_neu_rec_hand_2_trial_hand = allocate_shm_client_neu_rec_hand_2_trial_hand_msg_buffer(*msgs_neu_rec_hand_2_trial_hand);
					usleep(1000);
					if (*msgs_neu_rec_hand_2_trial_hand == NULL)
						return print_message(ERROR_MSG ,"NeuRecHandler", "NeuRecHandler", "connect_to_trial_hand", "msgs_neu_rec_hand_2_trial_hand == NULL.");	
					if (!write_to_neu_rec_hand_2_trial_hand_msg_buffer(*msgs_neu_rec_hand_2_trial_hand, *sys_time_ptr , NEU_REC_HAND_2_TRIAL_HAND_MSG_I_AM_ALIVE, 0))
						return print_message(ERROR_MSG ,"NeuRecHandler", "NeuRecHandler", "connect_to_trial_hand", "write_to_neu_rec_hand_2_trial_hand_msg_buffer().");	
					print_message(INFO_MSG ,"NeuRecHandler", "NeuRecHandler", "connect_to_trial_hand", "Connection to TRIAL_HANDLER is successful!!!");	
					return TRUE;		
				default:
					print_message(BUG_MSG ,"NeuRecHandler", "NeuRecHandler", "connect_to_trial_hand", str_trial_hand_2_neu_rec_hand_msg);	
					return print_message(BUG_MSG ,"NeuRecHandler", "NeuRecHandler", "connect_to_trial_hand", "default - switch.");
			}
		}
		print_message(INFO_MSG ,"NeuRecHandler", "NeuRecHandler", "connect_to_trial_hand", "Waiting for TRIAL_HANDLER to connect.");	
		sleep(1);
	}
	return print_message(BUG_MSG ,"NeuRecHandler", "NeuRecHandler", "connect_to_trial_hand", "Wrong hit in the code.");
}

