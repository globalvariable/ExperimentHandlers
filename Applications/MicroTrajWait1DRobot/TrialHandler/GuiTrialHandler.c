#include "GuiTrialHandler.h"

#define MAX_NUM_OF_UNIT_PER_CHAN_TO_HANDLE MAX_NUM_OF_UNIT_PER_CHAN
#define NUM_OF_STATUS_MARKERS		3
#define BUFFER_FOLLOWUP_LATENCY	1000000000ULL	

static RtTasksData *static_rt_tasks_data = NULL;

static Gui2TrialHandMsg *static_msgs_gui_2_trial_hand = NULL;  
static TrialHand2GuiMsg *static_msgs_trial_hand_2_gui = NULL;  

static TrialHandParadigmRobotReach *paradigm = NULL;

static ClassifiedTrialHistory* classified_history = NULL;

static TrialStatusHistory *static_trial_status_history = NULL;

static bool stop_continuous_recording_request = FALSE;

static GtkWidget *btn_reset_connections;
static GtkWidget *btn_enable_trials;
static GtkWidget *btn_disable_trials;
static GtkWidget *btn_quit_trials;

static GtkWidget *btn_select_target;
static GtkWidget *entry_select_target;

static GtkWidget *btn_release_reward;

static GtkWidget *btn_auto_target_select_mode_on_off;

static GtkWidget *btn_catch_trial_mode_on_off;

static GtkWidget *btn_turn_nose_retract_mode_on;
static GtkWidget *btn_turn_nose_retract_mode_off;

static GtkWidget *lbl_threshold_r_x;
static GtkWidget *lbl_threshold_r_y;
static GtkWidget *lbl_threshold_r_z;

static GtkWidget *entry_max_nose_retract_interval;
static GtkWidget *btn_submit_max_nose_retract_interval;

//Stats
static GtkWidget *entry_trial_number;
static GtkWidget *lbl_trial_length;
static GtkWidget *lbl_robot_start_position_idx;
static GtkWidget *lbl_robot_target_position_idx;
static GtkWidget *lbl_reward_amount;
static GtkWidget *lbl_interrogated_threshold_r_x;
static GtkWidget *lbl_interrogated_threshold_r_y;
static GtkWidget *lbl_interrogated_threshold_r_z;
static GtkWidget *btn_submit_trial_number;

static GtkWidget *btn_statistics;

static GtkWidget ***lbl_num_of_trials;		// num_of_start_positions * num_of_target_positions.
static GtkWidget ***lbl_num_of_incomplete;		// num_of_start_positions * num_of_target_positions.
static GtkWidget ***lbl_success_ratio;

static GtkWidget *btn_select_directory_to_save;
static GtkWidget *btn_create_recording_folder;

static GtkWidget *lbl_trial_status;

static GtkWidget *btn_start_recording;
static GtkWidget *btn_stop_recording;
static GtkWidget *btn_cancel_recording;

static GtkWidget *lbl_recording_status;

static void reset_connections_button_func (void);
static void enable_trials_button_func (void);
static void disable_trials_button_func (void);
static void quit_trials_button_func (void);

static void auto_target_select_mode_on_off_button_func(void);
static void catch_trial_mode_on_off_button_func(void);
static void turn_nose_retract_mode_on_button_func (void);
static void turn_nose_retract_mode_off_button_func (void);

static void select_target_button_func (void);
static void release_reward_button_func (void);

static void submit_max_nose_retract_interval_button_func (void);

static void submit_trial_number_button_func (void);

static void statistics_button_func (void);

static void create_recording_folder_button_func (void);

static void start_recording_button_func (void);
static void stop_recording_button_func (void);
static void cancel_recording_button_func (void);

static void set_directory_btn_select_directory_to_save(void);

static Network *blue_spike_network = NULL;
static NetworkSpikePatternGraphScroll *blue_spike_spike_pattern_graph = NULL;
static SpikeData **blue_spike_spike_data_for_graph = NULL;   // for visualization
static SpikeTimeStamp 	*sorted_spike_time_stamp = NULL;    /// spike time stamps from biological neurons // sorted according to unit, not according to spike time.
static TrialStatusEvents	*trial_status_events = NULL;   // to show status changed in graphs
static unsigned int blue_spike_buff_read_idx;
static unsigned int *blue_spike_buff_write_idx;

static GtkWidget *btn_pause;
static bool spike_pattern_graph_resume_request = FALSE;

static void pause_button_func(void);

static gboolean timeout_callback(gpointer user_data) ;

bool create_trial_handler_tab(GtkWidget *tabs, RtTasksData *rt_tasks_data, Gui2TrialHandMsg *msgs_gui_2_trial_hand, TrialHandParadigmRobotReach *trial_hand_paradigm, ClassifiedTrialHistory* classified_trial_history, TrialHand2GuiMsg *msgs_trial_hand_2_gui, TrialStatusHistory *trial_status_history)
{
	GtkWidget *frame, *frame_label, *hbox, *lbl, *table, *vbox;
	char temp[100];
	unsigned int i, j;


	static_rt_tasks_data = rt_tasks_data;

	static_msgs_gui_2_trial_hand = msgs_gui_2_trial_hand;
	static_msgs_trial_hand_2_gui = msgs_trial_hand_2_gui;

	paradigm = trial_hand_paradigm;

	classified_history = classified_trial_history;

	static_trial_status_history = trial_status_history;

        frame = gtk_frame_new ("");
        frame_label = gtk_label_new ("     Trials Handler    ");      
   
        gtk_notebook_append_page (GTK_NOTEBOOK (tabs), frame, frame_label);  

 	hbox = gtk_hbox_new(FALSE, 0);
        gtk_container_add (GTK_CONTAINER (frame), hbox);

	table = gtk_table_new(2 ,3,TRUE);   // 2 rows 3 columns
	gtk_box_pack_start(GTK_BOX(hbox),table, TRUE,TRUE,0);

	vbox = gtk_vbox_new(FALSE, 0);
	gtk_table_attach_defaults(GTK_TABLE(table), vbox, 0,1, 0, 6);  // column 0-1, row 0-6

	hbox = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	btn_reset_connections = gtk_button_new_with_label("Reset Connections");
	gtk_box_pack_start (GTK_BOX (hbox), btn_reset_connections, TRUE, TRUE, 0);

	hbox = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	lbl = gtk_label_new("Trials: ");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, TRUE, TRUE, 0);

	btn_enable_trials = gtk_button_new_with_label("Enable");
	gtk_box_pack_start (GTK_BOX (hbox), btn_enable_trials, TRUE, TRUE, 0);

	btn_disable_trials = gtk_button_new_with_label("Disable");
	gtk_box_pack_start (GTK_BOX (hbox), btn_disable_trials, TRUE, TRUE, 0);

	btn_quit_trials = gtk_button_new_with_label("Quit");
	gtk_box_pack_start (GTK_BOX (hbox), btn_quit_trials, TRUE, TRUE, 0);

       gtk_box_pack_start(GTK_BOX(vbox),gtk_hseparator_new(), FALSE,FALSE, 5);

	hbox = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	btn_auto_target_select_mode_on_off = gtk_button_new_with_label("Target Select: AUTO");
	gtk_box_pack_start (GTK_BOX (hbox), btn_auto_target_select_mode_on_off , TRUE, TRUE, 0);

	hbox = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	btn_select_target = gtk_button_new_with_label("Select Target");
	gtk_box_pack_start (GTK_BOX (hbox), btn_select_target , TRUE, TRUE, 0);

	lbl = gtk_label_new("Idx: ");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE, FALSE, 0);
	entry_select_target = gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(hbox), entry_select_target, FALSE, FALSE, 0);
	gtk_widget_set_size_request(entry_select_target, 50, 25);
	gtk_entry_set_text(GTK_ENTRY(entry_select_target), "0");

       gtk_box_pack_start(GTK_BOX(vbox),gtk_hseparator_new(), FALSE,FALSE, 5);

	hbox = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	btn_catch_trial_mode_on_off = gtk_button_new_with_label("Catch Trial: OFF");
	gtk_box_pack_start (GTK_BOX (hbox), btn_catch_trial_mode_on_off , TRUE, TRUE, 0);

       gtk_box_pack_start(GTK_BOX(vbox),gtk_hseparator_new(), FALSE,FALSE, 5);

	hbox = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	btn_turn_nose_retract_mode_on = gtk_button_new_with_label("Turn Nose Retract Mode ON");
	gtk_box_pack_start (GTK_BOX (hbox), btn_turn_nose_retract_mode_on, TRUE, TRUE, 0);

	hbox = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	btn_turn_nose_retract_mode_off = gtk_button_new_with_label("Turn Nose Retract Mode OFF");
	gtk_box_pack_start (GTK_BOX (hbox), btn_turn_nose_retract_mode_off, TRUE, TRUE, 0);

       gtk_box_pack_start(GTK_BOX(vbox),gtk_hseparator_new(), FALSE,FALSE, 5);

	hbox = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	btn_release_reward = gtk_button_new_with_label("Reward");
	gtk_box_pack_start (GTK_BOX (hbox), btn_release_reward , TRUE, TRUE, 0);

       gtk_box_pack_start(GTK_BOX(vbox),gtk_hseparator_new(), FALSE,FALSE, 5);

 	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	lbl = gtk_label_new("Thresholds: ");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);

 	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	lbl = gtk_label_new("height:	");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);

	lbl_threshold_r_x = gtk_label_new("0");
        gtk_box_pack_start(GTK_BOX(hbox),lbl_threshold_r_x, FALSE,FALSE,0);

	lbl = gtk_label_new("");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, TRUE,TRUE,0);

 	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	lbl = gtk_label_new("depth:	");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);

	lbl_threshold_r_y = gtk_label_new("0");
        gtk_box_pack_start(GTK_BOX(hbox),lbl_threshold_r_y, FALSE,FALSE,0);

	lbl = gtk_label_new("");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, TRUE,TRUE,0);

 	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	lbl = gtk_label_new("lateral:	");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);

	lbl_threshold_r_z = gtk_label_new("0");
        gtk_box_pack_start(GTK_BOX(hbox),lbl_threshold_r_z, FALSE,FALSE,0);

	lbl = gtk_label_new("");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, TRUE,TRUE,0);

   	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE, 0);  	     

	btn_submit_max_nose_retract_interval = gtk_button_new_with_label("Nose Retract Interval");
	gtk_box_pack_start (GTK_BOX (hbox), btn_submit_max_nose_retract_interval, FALSE, FALSE, 0);

	entry_max_nose_retract_interval = gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(hbox), entry_max_nose_retract_interval, FALSE, FALSE, 0);
	gtk_widget_set_size_request(entry_max_nose_retract_interval, 50, 25);
	gtk_entry_set_text(GTK_ENTRY(entry_max_nose_retract_interval), "1500");
	lbl = gtk_label_new("ms");	
     	gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE, FALSE, 0);

	////////   SECOND COLUMN
	vbox = gtk_vbox_new(FALSE, 0);
	gtk_table_attach_defaults(GTK_TABLE(table), vbox, 1,2, 0, 6);  // column 1-2, row 0-6

	lbl_num_of_trials = g_new(GtkWidget **, trial_hand_paradigm->num_of_robot_start_positions);		
	lbl_success_ratio = g_new(GtkWidget **, trial_hand_paradigm->num_of_robot_start_positions);	
	lbl_num_of_incomplete = g_new(GtkWidget **, trial_hand_paradigm->num_of_robot_start_positions);	
	for (i = 0; i < trial_hand_paradigm->num_of_robot_start_positions; i++)
	{
		lbl_num_of_trials[i] = g_new(GtkWidget *, trial_hand_paradigm->num_of_robot_target_positions);		
		lbl_success_ratio[i] = g_new(GtkWidget *, trial_hand_paradigm->num_of_robot_target_positions);	
		lbl_num_of_incomplete[i] = g_new(GtkWidget *, trial_hand_paradigm->num_of_robot_target_positions);	
		for (j = 0; j < trial_hand_paradigm->num_of_robot_target_positions; j++)
		{
			hbox = gtk_hbox_new(FALSE, 0);
     			gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);
			sprintf (temp, "Start: %d; Target: %d", i, j);
			lbl = gtk_label_new(temp);	
     			gtk_box_pack_start(GTK_BOX(hbox),lbl, TRUE, TRUE, 0);

			hbox = gtk_hbox_new(FALSE, 0);
     			gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);
			lbl = gtk_label_new("Num of Trials		:");
	     		gtk_box_pack_start(GTK_BOX(hbox),lbl, TRUE, TRUE, 0);
			lbl_num_of_trials[i][j] = gtk_label_new("0");
	     		gtk_box_pack_start(GTK_BOX(hbox),lbl_num_of_trials[i][j], TRUE, TRUE, 0);

			hbox = gtk_hbox_new(FALSE, 0);
     			gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);
			lbl = gtk_label_new("Num of Incomplete:");
	     		gtk_box_pack_start(GTK_BOX(hbox),lbl, TRUE, TRUE, 0);
			lbl_num_of_incomplete[i][j] = gtk_label_new("0");
	     		gtk_box_pack_start(GTK_BOX(hbox),lbl_num_of_incomplete[i][j], TRUE, TRUE, 0);

			hbox = gtk_hbox_new(FALSE, 0);
     			gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);
			lbl = gtk_label_new("Success Ratio	:");
	     		gtk_box_pack_start(GTK_BOX(hbox),lbl, TRUE, TRUE, 0);
			lbl_success_ratio[i][j] = gtk_label_new("0.0000");
	     		gtk_box_pack_start(GTK_BOX(hbox),lbl_success_ratio[i][j], TRUE, TRUE, 0);

        		gtk_box_pack_start(GTK_BOX(vbox),gtk_hseparator_new(), TRUE,TRUE, 5);
		}
	}

	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,5);

	lbl = gtk_label_new("---- Interrogate Trial ----");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, TRUE, TRUE, 0);

	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);
	lbl = gtk_label_new("Trial #: ");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE, FALSE, 0);
	lbl = gtk_label_new("");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, TRUE, TRUE, 0);
	entry_trial_number = gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(hbox), entry_trial_number, FALSE, FALSE, 0);
	gtk_widget_set_size_request(entry_trial_number, 50, 25);
	gtk_entry_set_text(GTK_ENTRY(entry_trial_number), "0");

	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);
	lbl = gtk_label_new("Length: ");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE, FALSE, 0);
	lbl = gtk_label_new("");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, TRUE, TRUE, 0);
	lbl_trial_length = gtk_label_new("0");
        gtk_box_pack_start(GTK_BOX(hbox), lbl_trial_length, FALSE, FALSE, 0);

	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);
	lbl = gtk_label_new("Robot Start Position Idx: ");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE, FALSE, 0);
	lbl = gtk_label_new("");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, TRUE, TRUE, 0);
	lbl_robot_start_position_idx = gtk_label_new("0");
        gtk_box_pack_start(GTK_BOX(hbox), lbl_robot_start_position_idx, FALSE, FALSE, 0);

	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);
	lbl = gtk_label_new("Robot Target Position Idx: ");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE, FALSE, 0);
	lbl = gtk_label_new("");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, TRUE, TRUE, 0);
	lbl_robot_target_position_idx = gtk_label_new("0");
        gtk_box_pack_start(GTK_BOX(hbox), lbl_robot_target_position_idx, FALSE, FALSE, 0);

	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);
	lbl = gtk_label_new("Reward: ");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE, FALSE, 0);
	lbl = gtk_label_new("");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, TRUE, TRUE, 0);
	lbl_reward_amount = gtk_label_new("0");
        gtk_box_pack_start(GTK_BOX(hbox), lbl_reward_amount, FALSE, FALSE, 0);

	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);
	lbl = gtk_label_new("Threshold: ");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);

 	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);
	lbl = gtk_label_new("h:	");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);
	lbl_interrogated_threshold_r_x = gtk_label_new("0");
        gtk_box_pack_start(GTK_BOX(hbox),lbl_interrogated_threshold_r_x, FALSE,FALSE,0);
	lbl = gtk_label_new("");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, TRUE,TRUE,0);

	lbl = gtk_label_new("d:	");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);
	lbl_interrogated_threshold_r_y = gtk_label_new("0");
        gtk_box_pack_start(GTK_BOX(hbox),lbl_interrogated_threshold_r_y, FALSE,FALSE,0);
	lbl = gtk_label_new("");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, TRUE,TRUE,0);

	lbl = gtk_label_new("l:	");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);
	lbl_interrogated_threshold_r_z = gtk_label_new("0");
        gtk_box_pack_start(GTK_BOX(hbox),lbl_interrogated_threshold_r_z, FALSE,FALSE,0);

	hbox = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	btn_submit_trial_number = gtk_button_new_with_label("Submit Trial Number");
	gtk_box_pack_start (GTK_BOX (hbox), btn_submit_trial_number, TRUE, TRUE, 0);

        gtk_box_pack_start(GTK_BOX(vbox),gtk_hseparator_new(), TRUE,TRUE, 5);

	hbox = gtk_hbox_new(TRUE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE, 5);

	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	btn_statistics = gtk_button_new_with_label("Statistics");
	gtk_box_pack_start (GTK_BOX (hbox), btn_statistics, TRUE, TRUE, 0);


	////////   LAST COLUMN
	vbox = gtk_vbox_new(FALSE, 0);
	gtk_table_attach_defaults(GTK_TABLE(table), vbox, 2, 3, 0, 6);  // column 5-6, row 0-6

   	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE, 0);  	     

	lbl_trial_status = gtk_label_new("TRIAL_STATUS_NOT_KNOWN");
        gtk_box_pack_start(GTK_BOX(hbox),lbl_trial_status, TRUE, TRUE, 0);
	gtk_widget_set_size_request(lbl_trial_status, 300, 30);	

        gtk_box_pack_start(GTK_BOX(vbox),gtk_hseparator_new(), FALSE,FALSE, 10);

   	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE, 0);  	      

  	btn_select_directory_to_save = gtk_file_chooser_button_new ("Select Directory", GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER);
        gtk_box_pack_start(GTK_BOX(hbox), btn_select_directory_to_save, TRUE,TRUE,0);
	set_directory_btn_select_directory_to_save();


   	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE, 0);  	     

	btn_create_recording_folder = gtk_button_new_with_label("Create Recording Folders");
	gtk_box_pack_start (GTK_BOX (hbox), btn_create_recording_folder, TRUE, TRUE, 0);

        gtk_box_pack_start(GTK_BOX(vbox),gtk_hseparator_new(), FALSE,FALSE, 5);

	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	lbl = gtk_label_new("DATA RECORDING CONTROL");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, TRUE, TRUE, 5);

   	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE, 0);  	     

	btn_start_recording = gtk_button_new_with_label("START");
	gtk_box_pack_start (GTK_BOX (hbox), btn_start_recording, TRUE, TRUE, 0);
	gtk_widget_set_size_request(btn_start_recording, 20, 80);	

   	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE, 0);  	     

	btn_stop_recording = gtk_button_new_with_label("STOP");
	gtk_box_pack_start (GTK_BOX (hbox), btn_stop_recording, TRUE, TRUE, 0);
	gtk_widget_set_size_request(btn_stop_recording, 20, 80);	

   	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE, 0);  	     

	btn_cancel_recording = gtk_button_new_with_label("CANCEL");
	gtk_box_pack_start (GTK_BOX (hbox), btn_cancel_recording, TRUE, TRUE, 0);

   	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE, 0);  	     

	lbl_recording_status = gtk_label_new("RECORDING IDLE");
        gtk_box_pack_start(GTK_BOX(hbox),lbl_recording_status, TRUE, TRUE, 0);
	gtk_widget_set_size_request(lbl_recording_status, 300, 30);	

	g_signal_connect(G_OBJECT(btn_reset_connections), "clicked", G_CALLBACK(reset_connections_button_func), NULL);
	g_signal_connect(G_OBJECT(btn_enable_trials), "clicked", G_CALLBACK(enable_trials_button_func), NULL);
	g_signal_connect(G_OBJECT(btn_disable_trials), "clicked", G_CALLBACK(disable_trials_button_func), NULL);
	g_signal_connect(G_OBJECT(btn_quit_trials), "clicked", G_CALLBACK(quit_trials_button_func), NULL);

	g_signal_connect(G_OBJECT(btn_auto_target_select_mode_on_off), "clicked", G_CALLBACK(auto_target_select_mode_on_off_button_func), NULL);
	g_signal_connect(G_OBJECT(btn_select_target), "clicked", G_CALLBACK(select_target_button_func), NULL);

	g_signal_connect(G_OBJECT(btn_catch_trial_mode_on_off), "clicked", G_CALLBACK(catch_trial_mode_on_off_button_func), NULL);

	g_signal_connect(G_OBJECT(btn_turn_nose_retract_mode_on), "clicked", G_CALLBACK(turn_nose_retract_mode_on_button_func), NULL);
	g_signal_connect(G_OBJECT(btn_turn_nose_retract_mode_off), "clicked", G_CALLBACK(turn_nose_retract_mode_off_button_func), NULL);

	g_signal_connect(G_OBJECT(btn_release_reward), "clicked", G_CALLBACK(release_reward_button_func), NULL);

	g_signal_connect(G_OBJECT(btn_submit_max_nose_retract_interval), "clicked", G_CALLBACK(submit_max_nose_retract_interval_button_func), NULL);

	g_signal_connect(G_OBJECT(btn_submit_trial_number), "clicked", G_CALLBACK(submit_trial_number_button_func), NULL);

	g_signal_connect(G_OBJECT(btn_statistics), "clicked", G_CALLBACK(statistics_button_func), NULL);

	g_signal_connect(G_OBJECT(btn_create_recording_folder), "clicked", G_CALLBACK(create_recording_folder_button_func), NULL);

	g_signal_connect(G_OBJECT(btn_start_recording), "clicked", G_CALLBACK(start_recording_button_func), NULL);
	g_signal_connect(G_OBJECT(btn_stop_recording), "clicked", G_CALLBACK(stop_recording_button_func), NULL);
	g_signal_connect(G_OBJECT(btn_cancel_recording), "clicked", G_CALLBACK(cancel_recording_button_func), NULL);

	gtk_widget_set_sensitive(btn_disable_trials, FALSE);	
	gtk_widget_set_sensitive(btn_stop_recording, FALSE);	
	gtk_widget_set_sensitive(btn_cancel_recording, FALSE);	

        frame = gtk_frame_new ("");
        frame_label = gtk_label_new ("     BlueSpike Spikes    ");      
   
        gtk_notebook_append_page (GTK_NOTEBOOK (tabs), frame, frame_label);  

 	hbox = gtk_hbox_new(FALSE, 0);
        gtk_container_add (GTK_CONTAINER (frame), hbox);

	vbox = gtk_vbox_new(TRUE, 0);
        gtk_box_pack_start(GTK_BOX(hbox),vbox, TRUE,TRUE,0);

  	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, TRUE,TRUE,0);

	btn_pause = gtk_button_new_with_label("P");
	gtk_box_pack_start (GTK_BOX (hbox), btn_pause, FALSE, FALSE, 0);

	blue_spike_network = allocate_network(blue_spike_network);
	for (i=0; i < MAX_NUM_OF_MWA; i++)
	{
		for (j = 0; j < MAX_NUM_OF_CHAN_PER_MWA; j++)
		{
			if (!add_neuron_nodes_to_layer(blue_spike_network, MAX_NUM_OF_UNIT_PER_CHAN_TO_HANDLE ,i, FALSE)) 
				return print_message(ERROR_MSG ,"TrialHandler", "GuiTrialHandler", "create_trial_handler_tab", " !add_neuron_nodes_to_layer.");	
		}
	}
	blue_spike_spike_data_for_graph = g_new0(SpikeData*, 1);
	blue_spike_spike_data_for_graph[0] = allocate_spike_data(blue_spike_spike_data_for_graph[0], get_num_of_neurons_in_network(blue_spike_network)*3*500 ); // 3 seconds buffer assuming

	trial_status_events = allocate_trial_status_events_buffer(trial_status_events, 100, 3000000);  //  3 ms latency

	blue_spike_spike_pattern_graph = allocate_network_spike_pattern_graph_scroll(blue_spike_network, hbox, blue_spike_spike_pattern_graph, 3000, 1000000, 900, 1000, BUFFER_FOLLOWUP_LATENCY, blue_spike_spike_data_for_graph,  NUM_OF_STATUS_MARKERS, trial_status_events, 1);    // 3 seconds, 1000 samples/sec, 100 ms latency

	sorted_spike_time_stamp = rtai_malloc(SHM_NUM_KERNEL_SPIKE_SPIKE_TIME_STAMP, 0);
	if (sorted_spike_time_stamp == NULL) 
		return print_message(ERROR_MSG ,"TrialHandler", "GuiTrialHandler", "create_trial_handler_tab", "sorted_spike_time_stamp == NULL.");	
	blue_spike_buff_write_idx = &(sorted_spike_time_stamp->buff_idx_write);
	blue_spike_buff_read_idx = *blue_spike_buff_write_idx;

	g_signal_connect(G_OBJECT(btn_pause), "clicked", G_CALLBACK(pause_button_func), NULL);

	g_timeout_add(50, timeout_callback, NULL);		

	return TRUE;
}

static gboolean timeout_callback(gpointer user_data) 
{
	char *path_temp, *path;
	char temp[TRIAL_HAND_2_GUI_MSG_STRING_LENGTH];
	TrialHand2GuiMsgItem msg_item;
	static bool recording = FALSE, first_start_recording_msg = TRUE;
	static bool continuous_recording = FALSE;
	TrialStatus trial_status;
	unsigned int recording_number, i, j, end_idx;
	TrialData *trial_data;
	TrialHand2NeuralNetTrialStatusMsgAdd trial_status_change_msg_add;
	SpikeTimeStampItem *spike_time_stamp_item; 

	sprintf (temp, "%.2f", paradigm->current_trial_data.rewarding_threshold.r_x);
	gtk_label_set_text (GTK_LABEL (lbl_threshold_r_x), temp);
	
	sprintf (temp, "%.2f", paradigm->current_trial_data.rewarding_threshold.r_y);
	gtk_label_set_text (GTK_LABEL (lbl_threshold_r_y), temp);

	sprintf (temp, "%.2f", paradigm->current_trial_data.rewarding_threshold.r_z);
	gtk_label_set_text (GTK_LABEL (lbl_threshold_r_z), temp);

	while (get_next_trial_hand_2_gui_msg_buffer_item(static_msgs_trial_hand_2_gui, &msg_item))
	{
		switch (msg_item.msg_type)
		{
			case TRIAL_HAND_2_GUI_MSG_BROADCAST_START_RECORDING_MSG_ACK:
				if (first_start_recording_msg)
				{
					first_start_recording_msg = FALSE;
					continuous_recording = TRUE;
					gtk_widget_set_sensitive(btn_start_recording, FALSE);
					gtk_widget_set_sensitive(btn_stop_recording, TRUE);
				}
				recording = TRUE;	
				path_temp = NULL; path = NULL;
				path_temp = gtk_file_chooser_get_uri (GTK_FILE_CHOOSER (btn_select_directory_to_save));
				path = &path_temp[7];   // since     uri returns file:///home/....	
				recording_number = msg_item.additional_data;
				if (! (*create_data_directory[MAX_NUMBER_OF_DATA_FORMAT_VER-1])(3, path, static_rt_tasks_data->current_system_time, recording_number))	
				{
					print_message(ERROR_MSG ,"TrialHandler", "GuiTrialHandler", "timeout_callback", " *create_data_directory().");	
					exit(1);
				}
				if (!(*write_to_data_files[MAX_NUMBER_OF_DATA_FORMAT_VER-1])(1, static_trial_status_history))	// this function handles history buffers
				{
					print_message(ERROR_MSG ,"TrialHandler", "GuiTrialHandler", "timeout_callback", " *write_to_data_files().");		
					exit(1);
				}	
				sprintf (temp, "RECORDING DAT%u", recording_number);
				gtk_label_set_text (GTK_LABEL (lbl_recording_status), temp);
				gtk_widget_set_sensitive(btn_cancel_recording, TRUE);
				break;
			case TRIAL_HAND_2_GUI_MSG_BROADCAST_STOP_RECORDING_MSG_ACK:
				if (!(*write_to_data_files[MAX_NUMBER_OF_DATA_FORMAT_VER-1])(1, static_trial_status_history))	// this function handles history buffers
				{
					print_message(ERROR_MSG ,"TrialHandler", "GuiTrialHandler", "timeout_callback", " *write_to_data_files().");		
					exit(1);
				}	
				recording_number = msg_item.additional_data;
				if (! (*fclose_all_data_files[MAX_NUMBER_OF_DATA_FORMAT_VER-1])(2, static_rt_tasks_data->current_system_time, &(classified_history->all_trials->history[recording_number])))	
				{
					print_message(ERROR_MSG ,"TrialHandler", "GuiTrialHandler", "timeout_callback", " *fclose_all_data_files().");
					exit(1);
				}
				sprintf (temp, "FINISHED RECORDING DAT%u", recording_number);
				gtk_label_set_text (GTK_LABEL (lbl_recording_status), temp);
				recording = FALSE;	
				gtk_widget_set_sensitive(btn_cancel_recording, FALSE);
				if (stop_continuous_recording_request)
				{
					first_start_recording_msg = TRUE;
					continuous_recording = FALSE;
					stop_continuous_recording_request = FALSE;
					gtk_widget_set_sensitive(btn_stop_recording, FALSE);
					gtk_widget_set_sensitive(btn_start_recording, TRUE);
				}
				else	// it comes here when there is continous recording.
				{
					if (!write_to_gui_2_trial_hand_msg_buffer(static_msgs_gui_2_trial_hand, static_rt_tasks_data->current_system_time, GUI_2_TRIAL_HAND_MSG_BROADCAST_START_RECORDING, 0))
						return print_message(ERROR_MSG ,"TrialHandler", "GuiTrialHandler", "enable_trials_button_func", "! write_to_gui_2_trial_hand_msg_buffer().");			
				}
				break;
			case TRIAL_HAND_2_GUI_MSG_BROADCAST_CANCEL_RECORDING_MSG_ACK:
				path_temp = NULL; path = NULL;
				path_temp = gtk_file_chooser_get_uri (GTK_FILE_CHOOSER (btn_select_directory_to_save));
				path = &path_temp[7];   // since     uri returns file:///home/....	

				static_trial_status_history->buff_read_idx = static_trial_status_history->buff_write_idx;	

				recording_number = msg_item.additional_data;
				if (! (*fclose_all_data_files[MAX_NUMBER_OF_DATA_FORMAT_VER-1])(2, static_rt_tasks_data->current_system_time, &(classified_history->all_trials->history[recording_number])))	
				{
					print_message(ERROR_MSG ,"TrialHandler", "GuiTrialHandler", "timeout_callback", "! *fclose_all_data_files().");
					exit(1);
				}
				if (! (*delete_data_directory[MAX_NUMBER_OF_DATA_FORMAT_VER-1])(2, path, recording_number))
				{
					print_message(ERROR_MSG ,"TrialHandler", "GuiTrialHandler", "timeout_callback", " *fdelete_all_data_files().");
					exit(1);
				}
				sprintf (temp, "DELETED DAT%u", recording_number);
				gtk_label_set_text (GTK_LABEL (lbl_recording_status), temp);
				recording = FALSE;	
				stop_continuous_recording_request = FALSE;
				continuous_recording = FALSE;
				first_start_recording_msg = TRUE;
				gtk_widget_set_sensitive(btn_start_recording, TRUE);
				gtk_widget_set_sensitive(btn_stop_recording, FALSE);
				gtk_widget_set_sensitive(btn_cancel_recording, FALSE);
				break;
			case TRIAL_HAND_2_GUI_MSG_TRIAL_STATUS_CHANGE:
				trial_status = msg_item.additional_data;
				get_trial_status_type_string(trial_status, temp);  
				gtk_label_set_text(GTK_LABEL (lbl_trial_status ), temp);
				switch (trial_status)
				{
					case TRIAL_STATUS_TRIALS_DISABLED:
						break;
					case TRIAL_STATUS_IN_TRIAL:
						trial_status_change_msg_add.new_trial_status = TRIAL_STATUS_IN_TRIAL;
						schedule_trial_status_event(trial_status_events, msg_item.msg_time, trial_status_change_msg_add) ; 
						gtk_widget_set_sensitive(btn_start_recording, FALSE);
						gtk_widget_set_sensitive(btn_cancel_recording, FALSE);					
						break;
					case TRIAL_STATUS_IN_REFRACTORY:
						trial_status_change_msg_add.new_trial_status = TRIAL_STATUS_IN_REFRACTORY;
						schedule_trial_status_event(trial_status_events, msg_item.msg_time, trial_status_change_msg_add) ; 
						for (i = 0; i < paradigm->num_of_robot_start_positions; i++)
						{
							for (j = 0; j < paradigm->num_of_robot_target_positions; j++)
							{
								trial_data = get_previous_trial_history_data_ptr(classified_history->trial_types_sessions[0][i][j]);
								sprintf (temp,"%u",  trial_data->num_of_trials);
								gtk_label_set_text (GTK_LABEL (lbl_num_of_trials[i][j]), temp);
								sprintf (temp,"%u", trial_data->num_of_incomplete_trials);
								gtk_label_set_text (GTK_LABEL (lbl_num_of_incomplete[i][j]), temp);
								sprintf (temp,"%.4f",  trial_data->success_ratio);
								gtk_label_set_text (GTK_LABEL (lbl_success_ratio[i][j]), temp);
							}
						}
						if ( continuous_recording)
						{
							sleep(1);
							if (!write_to_gui_2_trial_hand_msg_buffer(static_msgs_gui_2_trial_hand, static_rt_tasks_data->current_system_time, GUI_2_TRIAL_HAND_MSG_BROADCAST_STOP_RECORDING, 0))
								return print_message(ERROR_MSG ,"TrialHandler", "GuiTrialHandler", "enable_trials_button_func", "! write_to_gui_2_trial_hand_msg_buffer().");	
						}
						else
						{
							gtk_widget_set_sensitive(btn_start_recording, TRUE);
						}
						break;
					case TRIAL_STATUS_START_TRIAL_AVAILABLE:	
						trial_status_change_msg_add.new_trial_status = TRIAL_STATUS_START_TRIAL_AVAILABLE;
						schedule_trial_status_event(trial_status_events, msg_item.msg_time, trial_status_change_msg_add) ; 
						if (! continuous_recording)
						{
							gtk_widget_set_sensitive(btn_start_recording, TRUE);
						}
						break;
					case  TRIAL_STATUS_GET_READY_TO_START:	
						gtk_widget_set_sensitive(btn_start_recording, FALSE);
						gtk_widget_set_sensitive(btn_cancel_recording, FALSE);	
						break;
					default:
						return print_message(BUG_MSG ,"TrialHandler", "GuiTrialHandler", "timeout_callback", "switch (trial_status) - default");
				}
				break;
			default:
				return print_message(ERROR_MSG ,"TrialHandler", "GuiTrialHandler", "timeout_callback", "switch (msg_item.msg_type) - default");
		}
	}
	if (recording)
	{
		if (!(*write_to_data_files[MAX_NUMBER_OF_DATA_FORMAT_VER-1])(1, static_trial_status_history))	// this function handles history buffers
		{
			print_message(ERROR_MSG ,"TrialHandler", "GuiTrialHandler", "timeout_callback", " *write_to_data_files().");		
			exit(1);
		}			
	}
	else
	{
		static_trial_status_history->buff_read_idx = static_trial_status_history->buff_write_idx;	
	}
	end_idx = *blue_spike_buff_write_idx;
	while (blue_spike_buff_read_idx != end_idx)
	{
		spike_time_stamp_item = &(sorted_spike_time_stamp->spike_time_stamp_buff[blue_spike_buff_read_idx]);
		write_to_spike_data(blue_spike_spike_data_for_graph[0], spike_time_stamp_item->mwa_or_layer, spike_time_stamp_item->channel_or_neuron_group, spike_time_stamp_item->unit_or_neuron, spike_time_stamp_item->peak_time);	
		if ((blue_spike_buff_read_idx+1) == SPIKE_TIME_STAMP_BUFF_SIZE)
			blue_spike_buff_read_idx = 0;
		else
			blue_spike_buff_read_idx++;
	}
	if (spike_pattern_graph_resume_request)
	{
		spike_pattern_graph_resume_request = FALSE;
		if (! determine_spike_pattern_graph_scroll_start_time_and_read_indexes(blue_spike_spike_pattern_graph, static_rt_tasks_data->current_system_time))
		{
			print_message(ERROR_MSG ,"TrialHandler", "GuiTrialHandler", "timeout_callback", " ! determine_spike_pattern_graph_scroll_start_time_and_read_indexes().");		
			exit(1);
		}	
		clear_network_spike_pattern_graph_w_scroll(blue_spike_network, blue_spike_spike_pattern_graph);
		blue_spike_spike_pattern_graph->locally_paused = FALSE;
	}
	if (! handle_spike_pattern_graph_scrolling_and_plotting(blue_spike_spike_pattern_graph, blue_spike_network, static_rt_tasks_data->current_system_time))
	{
		print_message(ERROR_MSG ,"TrialHandler", "GuiTrialHandler", "timeout_callback", " ! handle_spike_pattern_graph_scrolling_and_plotting().");		
		exit(1);
	}		
	return TRUE;
}

static void reset_connections_button_func (void)
{
	// order via "gui 2 exp envi handler" & "gui 2 mov obj handler"
}


static void enable_trials_button_func (void)
{
	if (!write_to_gui_2_trial_hand_msg_buffer(static_msgs_gui_2_trial_hand, static_rt_tasks_data->current_system_time, GUI_2_TRIAL_HAND_MSG_ENABLE_TRIAL_HANDLING, 0))
		return (void)print_message(ERROR_MSG ,"TrialHandler", "GuiTrialHandler", "enable_trials_button_func", "! write_to_gui_2_trial_hand_msg_buffer().");		
	gtk_widget_set_sensitive(btn_enable_trials, FALSE);	
	gtk_widget_set_sensitive(btn_disable_trials, TRUE);	
}

static void disable_trials_button_func (void)
{
	if (!write_to_gui_2_trial_hand_msg_buffer(static_msgs_gui_2_trial_hand, static_rt_tasks_data->current_system_time, GUI_2_TRIAL_HAND_MSG_DISABLE_TRIAL_HANDLING, 0))
		return (void)print_message(ERROR_MSG ,"TrialHandler", "GuiTrialHandler", "disable_trials_button_func", "! write_to_gui_2_trial_hand_msg_buffer().");		
	gtk_widget_set_sensitive(btn_enable_trials, TRUE);	
	gtk_widget_set_sensitive(btn_disable_trials, FALSE);		
	gtk_widget_set_sensitive(btn_quit_trials, TRUE);		
}

static void quit_trials_button_func (void)
{
	if (!write_to_gui_2_trial_hand_msg_buffer(static_msgs_gui_2_trial_hand, static_rt_tasks_data->current_system_time, GUI_2_TRIAL_HAND_MSG_QUIT, 0))
		return (void)print_message(ERROR_MSG ,"TrialHandler", "GuiTrialHandler", "quit_trials_button_func", "! write_to_gui_2_trial_hand_msg_buffer().");		
}

static void auto_target_select_mode_on_off_button_func(void)
{
	if (paradigm->current_trial_data.auto_target_select_mode_on)
	{
		if (!write_to_gui_2_trial_hand_msg_buffer(static_msgs_gui_2_trial_hand, static_rt_tasks_data->current_system_time, GUI_2_TRIAL_HAND_MSG_AUTO_TARGET_SELECTION_OFF, 0))
			return (void)print_message(ERROR_MSG ,"TrialHandler", "GuiTrialHandler", "auto_target_select_mode_on_off_button_func", "! write_to_gui_2_trial_hand_msg_buffer().");
		gtk_button_set_label (GTK_BUTTON (btn_auto_target_select_mode_on_off),"Target Select: MANUAL");		
	}
	else
	{
		if (!write_to_gui_2_trial_hand_msg_buffer(static_msgs_gui_2_trial_hand, static_rt_tasks_data->current_system_time, GUI_2_TRIAL_HAND_MSG_AUTO_TARGET_SELECTION_ON, 0))
			return (void)print_message(ERROR_MSG ,"TrialHandler", "GuiTrialHandler", "auto_target_select_mode_on_off_button_func", "! write_to_gui_2_trial_hand_msg_buffer().");	
		gtk_button_set_label (GTK_BUTTON (btn_auto_target_select_mode_on_off),"Target Select: AUTO");		
	}	
}

static void catch_trial_mode_on_off_button_func(void)
{
	if (paradigm->current_trial_data.catch_trial_mode_on)
	{
		if (!write_to_gui_2_trial_hand_msg_buffer(static_msgs_gui_2_trial_hand, static_rt_tasks_data->current_system_time, GUI_2_TRIAL_HAND_MSG_CATCH_TRIAL_MODE_OFF, 0))
			return (void)print_message(ERROR_MSG ,"TrialHandler", "GuiTrialHandler", "catch_trial_mode_on_off_button_func", "! write_to_gui_2_trial_hand_msg_buffer().");
		gtk_button_set_label (GTK_BUTTON (btn_catch_trial_mode_on_off),"Catch Trial: OFF");		
	}
	else
	{
		if (!write_to_gui_2_trial_hand_msg_buffer(static_msgs_gui_2_trial_hand, static_rt_tasks_data->current_system_time, GUI_2_TRIAL_HAND_MSG_CATCH_TRIAL_MODE_ON, 0))
			return (void)print_message(ERROR_MSG ,"TrialHandler", "GuiTrialHandler", "catch_trial_mode_on_off_button_func", "! write_to_gui_2_trial_hand_msg_buffer().");	
		gtk_button_set_label (GTK_BUTTON (btn_catch_trial_mode_on_off),"Catch Trial: ON");		
	}	
}

static void turn_nose_retract_mode_on_button_func (void)
{
	if (!write_to_gui_2_trial_hand_msg_buffer(static_msgs_gui_2_trial_hand, static_rt_tasks_data->current_system_time, GUI_2_TRIAL_HAND_MSG_TURN_NOSE_RETRACT_MODE_ON, 0))
		return (void)print_message(ERROR_MSG ,"TrialHandler", "GuiTrialHandler", "turn_nose_retract_mode_on_button_func", "! write_to_gui_2_trial_hand_msg_buffer().");		
}

static void turn_nose_retract_mode_off_button_func (void)
{
	if (!write_to_gui_2_trial_hand_msg_buffer(static_msgs_gui_2_trial_hand, static_rt_tasks_data->current_system_time, GUI_2_TRIAL_HAND_MSG_TURN_NOSE_RETRACT_MODE_OFF, 0))
		return (void)print_message(ERROR_MSG ,"TrialHandler", "GuiTrialHandler", "turn_nose_retract_mode_off_button_func", "! write_to_gui_2_trial_hand_msg_buffer().");		
}


static void select_target_button_func (void)
{
	unsigned int target_idx;
	target_idx = (unsigned int)atof(gtk_entry_get_text(GTK_ENTRY(entry_select_target)));
	if (target_idx >= paradigm->num_of_robot_target_positions)
		return (void)print_message(ERROR_MSG ,"TrialHandler", "GuiTrialHandler", "select_target_button_func", "target_idx >= static_trial_hand_paradigm->num_of_robot_target_positions.");	
	if (!write_to_gui_2_trial_hand_msg_buffer(static_msgs_gui_2_trial_hand, static_rt_tasks_data->current_system_time, GUI_2_TRIAL_HAND_MSG_SELECT_TARGET, target_idx))
		return (void)print_message(ERROR_MSG ,"TrialHandler", "GuiTrialHandler", "increase_threshold_button_func", "! write_to_gui_2_trial_hand_msg_buffer().");	
}


static void submit_trial_number_button_func (void)
{
	unsigned int trial_number;
	char temp[50];
	double trial_length = 0;

	trial_number = (unsigned int)atof(gtk_entry_get_text(GTK_ENTRY(entry_trial_number)));
	
	if (trial_number >= classified_history->all_trials->buffer_size)
		return (void)print_message(ERROR_MSG ,"TrialHandler", "GuiTrialHandler", "disable_trials_button_func", "Invalid Trial Number.");	
	trial_length = classified_history->all_trials->history[trial_number].trial_end_time - classified_history->all_trials->history[trial_number].trial_start_time;
	sprintf (temp, "%.2f", trial_length/1000000000.0);
	gtk_label_set_text (GTK_LABEL (lbl_trial_length), temp);

	sprintf (temp, "%u",  classified_history->all_trials->history[trial_number].robot_start_position_idx);
	gtk_label_set_text (GTK_LABEL (lbl_robot_start_position_idx), temp);

	sprintf (temp, "%u", classified_history->all_trials->history[trial_number].robot_target_position_idx);
	gtk_label_set_text (GTK_LABEL (lbl_robot_target_position_idx), temp);

	sprintf (temp, "%.2f", classified_history->all_trials->history[trial_number].reward_magnitude);
	gtk_label_set_text (GTK_LABEL (lbl_reward_amount), temp);

	sprintf (temp, "%.2f", classified_history->all_trials->history[trial_number].rewarding_threshold.r_x);
	gtk_label_set_text (GTK_LABEL (lbl_interrogated_threshold_r_x), temp);

	sprintf (temp, "%.2f", classified_history->all_trials->history[trial_number].rewarding_threshold.r_y);
	gtk_label_set_text (GTK_LABEL (lbl_interrogated_threshold_r_y), temp);

	sprintf (temp, "%.2f", classified_history->all_trials->history[trial_number].rewarding_threshold.r_z);
	gtk_label_set_text (GTK_LABEL (lbl_interrogated_threshold_r_z), temp);
}

static void statistics_button_func (void)
{
	unsigned int i, j;

	printf ("----------------------------------- Trial Statistics -----------------------------------\n");

	for (i = 0; i < classified_history->num_of_start_positions; i ++)
	{
		for (j = 0; j < classified_history->num_of_target_positions; j ++)
		{
			printf ("------------- Robot Start Position Idx : %u --- Robot Target Position Idx : %u ---\n", i , j);	
			printf ("Reward Magnitude: %.2f \n", classified_history->trial_types[i][j]->history[classified_history->trial_types[i][j]->buff_write_idx].reward_magnitude);	
		}		
	}


	printf ("----------------------------- End of Trial Statistics --------------------------------\n");
}

static void create_recording_folder_button_func (void)
{
	unsigned int path_len;
	char *path_temp = NULL, *path = NULL;
	path_temp = gtk_file_chooser_get_uri (GTK_FILE_CHOOSER (btn_select_directory_to_save));
	path = &path_temp[7];   // since     uri returns file:///home/....	
	path_len = strlen(path_temp);
	if (strcmp(&(path_temp[path_len-8]),"EXP_DATA") == 0)
		return (void)print_message(ERROR_MSG ,"TrialHandler", "GuiTrialHandler", "create_recording_folder_button_func", "Selected folder is /EXP_DATA main folder. Select a folder inside this folder.");				
	if ((*create_main_directory[MAX_NUMBER_OF_DATA_FORMAT_VER-1])(2, path, paradigm))		// record in last format version
	{
		
	}
	else
		print_message(ERROR_MSG ,"TrialHandler", "GuiTrialHandler", "create_recording_folder_button_func", " *create_main_directory().");				
}


static void start_recording_button_func (void)
{
	if (!write_to_gui_2_trial_hand_msg_buffer(static_msgs_gui_2_trial_hand, static_rt_tasks_data->current_system_time, GUI_2_TRIAL_HAND_MSG_BROADCAST_START_RECORDING, 0))
		return (void)print_message(ERROR_MSG ,"TrialHandler", "GuiTrialHandler", "start_recording_button_func ", "! write_to_gui_2_trial_hand_msg_buffer().");
}
static void stop_recording_button_func (void)
{
	stop_continuous_recording_request = TRUE;
	gtk_widget_set_sensitive(btn_stop_recording, FALSE);
}
static void cancel_recording_button_func (void)
{
	if (!write_to_gui_2_trial_hand_msg_buffer(static_msgs_gui_2_trial_hand, static_rt_tasks_data->current_system_time, GUI_2_TRIAL_HAND_MSG_BROADCAST_CANCEL_RECORDING, 0))
		return (void)print_message(ERROR_MSG ,"TrialHandler", "GuiTrialHandler", "enable_trials_button_func", "! write_to_gui_2_trial_hand_msg_buffer().");	
}

static void set_directory_btn_select_directory_to_save(void)
{
	char line[600];
	FILE *fp = NULL;
       	if ((fp = fopen("./path_initial_directory", "r")) == NULL)  
       	{ 
		print_message(ERROR_MSG ,"TrialHandler", "GuiTrialHandler", "set_directory_btn_select_directory_to_save", "Couldn't find file: ./path_initial_directory.");
		print_message(ERROR_MSG ,"TrialHandler", "GuiTrialHandler", "set_directory_btn_select_directory_to_save", "/home is loaded as initial direcoty to create data folder.");
		gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER (btn_select_directory_to_save),"/home");
       	}
       	else
       	{
		if (fgets(line, sizeof line, fp ) == NULL) 
		{ 
			print_message(ERROR_MSG ,"TrialHandler", "GuiTrialHandler", "set_directory_btn_select_directory_to_save", "Couldn' t read ./path_initial_directory.");
			print_message(ERROR_MSG ,"TrialHandler", "GuiTrialHandler", "set_directory_btn_select_directory_to_save", "/home is loaded as initial direcoty to create data folder.");
			gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER (btn_select_directory_to_save),"/home");
		}
		else
		{
			line[strlen(line)-16] = 0;   
			gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER (btn_select_directory_to_save),line);
		}
		fclose(fp); 		
	}  	 
}

static void release_reward_button_func (void)
{
	if (!write_to_gui_2_trial_hand_msg_buffer(static_msgs_gui_2_trial_hand, static_rt_tasks_data->current_system_time, GUI_2_TRIAL_HAND_MSG_RELEASE_REWARD, 0))
		return (void)print_message(ERROR_MSG ,"TrialHandler", "GuiTrialHandler", "start_recording_button_func ", "! write_to_gui_2_trial_hand_msg_buffer().");	
}

static void submit_max_nose_retract_interval_button_func (void)
{
	paradigm->max_nose_retract_interval = (TimeStamp)(1000000.0 * atof(gtk_entry_get_text(GTK_ENTRY(entry_max_nose_retract_interval))));

}

static void pause_button_func(void)
{
	if (blue_spike_spike_pattern_graph->locally_paused)
	{
		spike_pattern_graph_resume_request = TRUE;
		gtk_button_set_label (GTK_BUTTON(btn_pause),"R");  
	}
	else
	{
		blue_spike_spike_pattern_graph->local_pause_request = TRUE;
		gtk_button_set_label (GTK_BUTTON(btn_pause),"P");		
	}  
}

