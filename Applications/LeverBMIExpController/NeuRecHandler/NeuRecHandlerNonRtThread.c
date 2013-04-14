#include "NeuRecHandlerNonRtThread.h"

static RtTasksData *rt_tasks_data = NULL;
static RecordingData *recording_data = NULL;
static SpikeTimeStamp *spike_time_stamps = NULL;
static TrialHand2NeuRecHandMsg *msgs_trial_hand_2_neu_rec_hand = NULL;
static GtkWidget *btn_select_directory_to_save = NULL;

static pthread_t recording_thread;
void *recording_thread_function( void *dummy );

bool create_neu_rec_handler_non_rt_thread(RtTasksData *arg_rt_tasks_data, RecordingData *arg_recording_data, SpikeTimeStamp *arg_spike_time_stamps, TrialHand2NeuRecHandMsg *arg_msgs_trial_hand_2_neu_rec_hand, GtkWidget *arg_btn_select_directory_to_save)
{
	rt_tasks_data = arg_rt_tasks_data;
	recording_data = arg_recording_data;
	spike_time_stamps = arg_spike_time_stamps;
	msgs_trial_hand_2_neu_rec_hand = arg_msgs_trial_hand_2_neu_rec_hand;

	btn_select_directory_to_save = arg_btn_select_directory_to_save;

    	pthread_create( &recording_thread, NULL, recording_thread_function, NULL);
	return TRUE;

}


void *recording_thread_function( void *dummy )
{
	TrialHand2NeuRecHandMsgItem msg_item;
	char *path_temp, *path;
	static bool recording = FALSE;
	unsigned int recording_number;
	while (1)
	{
		usleep(50000);  // 50 msec

		while (get_next_trial_hand_2_neu_rec_hand_msg_buffer_item(msgs_trial_hand_2_neu_rec_hand, &msg_item))
		{
			switch (msg_item.msg_type)
			{
				case TRIAL_HAND_2_NEU_REC_HAND_MSG_START_RECORDING:
					path_temp = NULL; path = NULL;
					path_temp = gtk_file_chooser_get_uri (GTK_FILE_CHOOSER (btn_select_directory_to_save));
					path = &path_temp[7];   // since     uri returns file:///home/....	
					recording_number = msg_item.additional_data;
					if (!(*create_data_directory[MAX_NUMBER_OF_DATA_FORMAT_VER-1])(5, path, &rt_tasks_data->current_system_time, recording_number, recording_data, spike_time_stamps))	
					{
						print_message(ERROR_MSG ,"NeuRecHandler", "Gui", "timeout_callback", " *create_data_directory().");		
						exit(1);
					}
					recording = TRUE;	
					break;
				case TRIAL_HAND_2_NEU_REC_HAND_MSG_STOP_RECORDING:
					if (! (*fclose_all_data_files[MAX_NUMBER_OF_DATA_FORMAT_VER-1])(3, &rt_tasks_data->current_system_time, recording_data, spike_time_stamps))	
					{
						print_message(ERROR_MSG ,"NeuRecHandler", "Gui", "timeout_callback", " *fclose_all_data_file().");		
						exit(1);
					}
					recording = FALSE;	
					break;
				case TRIAL_HAND_2_NEU_REC_HAND_MSG_CANCEL_RECORDING:
					path_temp = NULL; path = NULL;
					path_temp = gtk_file_chooser_get_uri (GTK_FILE_CHOOSER (btn_select_directory_to_save));
					path = &path_temp[7];   // since     uri returns file:///home/....		

					recording_number = msg_item.additional_data;
					if (! (*fclose_all_data_files[MAX_NUMBER_OF_DATA_FORMAT_VER-1])(3, &rt_tasks_data->current_system_time, recording_data, spike_time_stamps))	
					{
						print_message(ERROR_MSG ,"NeuRecHandler", "Gui", "timeout_callback", "! *fclose_all_data_files().");
						exit(1);
					}
					if (! (*delete_data_directory[MAX_NUMBER_OF_DATA_FORMAT_VER-1])(2, path, recording_number))
					{
						print_message(ERROR_MSG ,"NeuRecHandler", "Gui", "timeout_callback", " *delete_all_data_files().");
						exit(1);
					}
					recording = FALSE;	
					break;
				default:
					return (void *)print_message(BUG_MSG ,"NeuRecHandler", "Gui", "timeout_callback", "switch (msg_item.msg_type) - default");
			}
		}

		if (recording)
		{
			if (!(*write_to_data_files[MAX_NUMBER_OF_DATA_FORMAT_VER-1])(2, recording_data, spike_time_stamps))	
			{
				print_message(ERROR_MSG ,"MovObjHandler", "GuiMovObjHandler", "timeout_callback", " *write_to_data_files().");		
				exit(1);
			}			
		}
	}
	return NULL;	

}
