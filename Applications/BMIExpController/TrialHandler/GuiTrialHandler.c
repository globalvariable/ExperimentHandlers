#include "GuiTrialHandler.h"

static RtTasksData *static_rt_tasks_data = NULL;

static Gui2TrialHandMsg *static_msgs_gui_2_trial_hand = NULL;  

static TrialHandParadigmRobotReach *paradigm = NULL;

static ClassifiedTrialHistory* classified_history = NULL;

static GtkWidget *btn_reset_connections;
static GtkWidget *btn_enable_trials;
static GtkWidget *btn_disable_trials;
static GtkWidget *btn_quit_trials;

static GtkWidget *lbl_threshold_r_x;
static GtkWidget *lbl_threshold_r_y;
static GtkWidget *lbl_threshold_r_z;

static GtkWidget *btn_increase_threshold;
static GtkWidget *btn_decrease_threshold;

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


static GtkWidget *lbl_num_of_trials;
static GtkWidget *lbl_num_of_rewarded_trials;
static GtkWidget *lbl_num_of_trials_of_trial_type;
static GtkWidget *lbl_num_of_rewarded_trials_of_trial_type;

static void reset_connections_button_func (void);
static void enable_trials_button_func (void);
static void disable_trials_button_func (void);
static void quit_trials_button_func (void);

static void increase_threshold_button_func (void);
static void decrease_threshold_button_func (void);

static void submit_trial_number_button_func (void);

static void statistics_button_func (void);

static gboolean timeout_callback(gpointer user_data) ;

bool create_trial_handler_tab(GtkWidget *tabs, RtTasksData *rt_tasks_data, Gui2TrialHandMsg *msgs_gui_2_trial_hand, TrialHandParadigmRobotReach *trial_hand_paradigm, ClassifiedTrialHistory* classified_trial_history)
{
	GtkWidget *frame, *frame_label, *hbox, *lbl, *table, *vbox;

	static_rt_tasks_data = rt_tasks_data;

	static_msgs_gui_2_trial_hand = msgs_gui_2_trial_hand;

	paradigm = trial_hand_paradigm;

	classified_history = classified_trial_history;

        frame = gtk_frame_new ("");
        frame_label = gtk_label_new ("     Trials Handler    ");      
   
        gtk_notebook_append_page (GTK_NOTEBOOK (tabs), frame, frame_label);  

 	hbox = gtk_hbox_new(TRUE, 0);
        gtk_container_add (GTK_CONTAINER (frame), hbox);

	table = gtk_table_new(2 ,6,TRUE);   // 2 rows 6 columns
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
	gtk_widget_set_sensitive(btn_disable_trials, FALSE);	

	btn_quit_trials = gtk_button_new_with_label("Quit");
	gtk_box_pack_start (GTK_BOX (hbox), btn_quit_trials, TRUE, TRUE, 0);

       gtk_box_pack_start(GTK_BOX(vbox),gtk_hseparator_new(), TRUE,TRUE, 5);

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
	gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	btn_increase_threshold = gtk_button_new_with_label("Increase Threshold");
	gtk_box_pack_start (GTK_BOX (hbox), btn_increase_threshold, TRUE, TRUE, 0);

	hbox = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	btn_decrease_threshold = gtk_button_new_with_label("Decrease Threshold");
	gtk_box_pack_start (GTK_BOX (hbox), btn_decrease_threshold, TRUE, TRUE, 0);

	////////   SECOND COLUMN
	vbox = gtk_vbox_new(FALSE, 0);
	gtk_table_attach_defaults(GTK_TABLE(table), vbox, 1,2, 0, 6);  // column 5-6, row 0-6

	hbox = gtk_hbox_new(TRUE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,5);

	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);
	lbl = gtk_label_new("Num of Trials #: ");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE, FALSE, 0);
	lbl = gtk_label_new("");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, TRUE, TRUE, 0);
	lbl_num_of_trials = gtk_label_new("0");
        gtk_box_pack_start(GTK_BOX(hbox), lbl_num_of_trials, FALSE, FALSE, 0);

	hbox = gtk_hbox_new(TRUE, 0);
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

	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);
	lbl = gtk_label_new("Num of Rewarded: ");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE, FALSE, 0);
	lbl = gtk_label_new("");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, TRUE, TRUE, 0);
	lbl_num_of_rewarded_trials = gtk_label_new("0");
        gtk_box_pack_start(GTK_BOX(hbox),lbl_num_of_rewarded_trials, FALSE, FALSE, 0);

        gtk_box_pack_start(GTK_BOX(vbox),gtk_hseparator_new(), TRUE,TRUE, 5);

	hbox = gtk_hbox_new(TRUE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE, 5);

	lbl = gtk_label_new("---- Trial Type Statistics ----");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, TRUE, TRUE, 0);

	hbox = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);
	lbl = gtk_label_new("Num of Trials: ");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE, FALSE, 0);
	lbl = gtk_label_new("");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, TRUE, TRUE, 0);
	lbl_num_of_trials_of_trial_type = gtk_label_new("0");
        gtk_box_pack_start(GTK_BOX(hbox),lbl_num_of_trials_of_trial_type, FALSE, FALSE, 0);

	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);
	lbl = gtk_label_new("Num of Rewarded: ");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE, FALSE, 0);
	lbl = gtk_label_new("");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, TRUE, TRUE, 0);
	lbl_num_of_rewarded_trials_of_trial_type = gtk_label_new("0");
        gtk_box_pack_start(GTK_BOX(hbox),lbl_num_of_rewarded_trials_of_trial_type, FALSE, FALSE, 0);


	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	btn_statistics = gtk_button_new_with_label("Statistics");
	gtk_box_pack_start (GTK_BOX (hbox), btn_statistics, TRUE, TRUE, 0);

	////////   LAST COLUMN
	vbox = gtk_vbox_new(FALSE, 0);
	gtk_table_attach_defaults(GTK_TABLE(table), vbox, 5,6, 0, 6);  // column 5-6, row 0-6

	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	lbl = gtk_label_new("data load save");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, TRUE, TRUE, 0);

	g_signal_connect(G_OBJECT(btn_reset_connections), "clicked", G_CALLBACK(reset_connections_button_func), NULL);
	g_signal_connect(G_OBJECT(btn_enable_trials), "clicked", G_CALLBACK(enable_trials_button_func), NULL);
	g_signal_connect(G_OBJECT(btn_disable_trials), "clicked", G_CALLBACK(disable_trials_button_func), NULL);
	g_signal_connect(G_OBJECT(btn_quit_trials), "clicked", G_CALLBACK(quit_trials_button_func), NULL);

	g_signal_connect(G_OBJECT(btn_increase_threshold), "clicked", G_CALLBACK(increase_threshold_button_func), NULL);
	g_signal_connect(G_OBJECT(btn_decrease_threshold), "clicked", G_CALLBACK(decrease_threshold_button_func), NULL);

	g_signal_connect(G_OBJECT(btn_submit_trial_number), "clicked", G_CALLBACK(submit_trial_number_button_func), NULL);

	g_signal_connect(G_OBJECT(btn_statistics), "clicked", G_CALLBACK(statistics_button_func), NULL);


	g_timeout_add(1000, timeout_callback, NULL);		// timeout shoud be less than buffer_followup_latency,

	return TRUE;
}

static gboolean timeout_callback(gpointer user_data) 
{
	char temp[50];

	sprintf (temp, "%.2f", paradigm->selected_target_reach_threshold.r_x);
	gtk_label_set_text (GTK_LABEL (lbl_threshold_r_x), temp);
	
	sprintf (temp, "%.2f", paradigm->selected_target_reach_threshold.r_y);
	gtk_label_set_text (GTK_LABEL (lbl_threshold_r_y), temp);

	sprintf (temp, "%.2f", paradigm->selected_target_reach_threshold.r_z);
	gtk_label_set_text (GTK_LABEL (lbl_threshold_r_z), temp);

	sprintf (temp, "%u", classified_history->all_trials->buff_write_idx);
	gtk_label_set_text (GTK_LABEL (lbl_num_of_trials), temp);

	return TRUE;
}

static void reset_connections_button_func (void)
{
	// order via "gui 2 exp envi handler" & "gui 2 mov obj handler"
}


static void enable_trials_button_func (void)
{
	if (!write_to_gui_2_trial_hand_msg_buffer(static_msgs_gui_2_trial_hand, static_rt_tasks_data->current_system_time, GUI_2_TRIAL_HAND_MSG_ENABLE_TRIAL_HANDLING, 0))
		return (void)print_message(ERROR_MSG ,"BMIExpController", "GuiTrialHandler", "enable_trials_button_func", "! write_to_gui_2_trial_hand_msg_buffer().");		
	gtk_widget_set_sensitive(btn_enable_trials, FALSE);		
	gtk_widget_set_sensitive(btn_disable_trials, TRUE);	
	gtk_widget_set_sensitive(btn_quit_trials, FALSE);		

}

static void disable_trials_button_func (void)
{
	if (!write_to_gui_2_trial_hand_msg_buffer(static_msgs_gui_2_trial_hand, static_rt_tasks_data->current_system_time, GUI_2_TRIAL_HAND_MSG_DISABLE_TRIAL_HANDLING, 0))
		return (void)print_message(ERROR_MSG ,"BMIExpController", "GuiTrialHandler", "disable_trials_button_func", "! write_to_gui_2_trial_hand_msg_buffer().");		
	gtk_widget_set_sensitive(btn_enable_trials, TRUE);	
	gtk_widget_set_sensitive(btn_disable_trials, FALSE);		
	gtk_widget_set_sensitive(btn_quit_trials, TRUE);		
}

static void quit_trials_button_func (void)
{
	if (!write_to_gui_2_trial_hand_msg_buffer(static_msgs_gui_2_trial_hand, static_rt_tasks_data->current_system_time, GUI_2_TRIAL_HAND_MSG_QUIT, 0))
		return (void)print_message(ERROR_MSG ,"BMIExpController", "GuiTrialHandler", "disable_trials_button_func", "! write_to_gui_2_trial_hand_msg_buffer().");		
}

static void increase_threshold_button_func (void)
{
	if (!write_to_gui_2_trial_hand_msg_buffer(static_msgs_gui_2_trial_hand, static_rt_tasks_data->current_system_time, GUI_2_TRIAL_HAND_MSG_INCREASE_THRESHOLD, 0))
		return (void)print_message(ERROR_MSG ,"BMIExpController", "GuiTrialHandler", "increase_threshold_button_func", "! write_to_gui_2_trial_hand_msg_buffer().");		
}

static void decrease_threshold_button_func (void)
{
	if (!write_to_gui_2_trial_hand_msg_buffer(static_msgs_gui_2_trial_hand, static_rt_tasks_data->current_system_time, GUI_2_TRIAL_HAND_MSG_DECREASE_THRESHOLD, 0))
		return (void)print_message(ERROR_MSG ,"BMIExpController", "GuiTrialHandler", "decrease_threshold_button_func", "! write_to_gui_2_trial_hand_msg_buffer().");		
}

static void submit_trial_number_button_func (void)
{
	unsigned int trial_number;
	char temp[50];
	double trial_length = 0;

	trial_number = (unsigned int)atof(gtk_entry_get_text(GTK_ENTRY(entry_trial_number)));
	
	if (trial_number >= classified_history->all_trials->buffer_size)
		return (void)print_message(ERROR_MSG ,"BMIExpController", "GuiTrialHandler", "disable_trials_button_func", "Invalid Trial Number.");	
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
