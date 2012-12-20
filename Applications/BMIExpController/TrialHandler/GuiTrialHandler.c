#include "GuiTrialHandler.h"

static RtTasksData *static_rt_tasks_data = NULL;

static Gui2TrialHandMsg *static_msgs_gui_2_trial_hand = NULL;    

static GtkWidget *btn_reset_connections;
static GtkWidget *btn_enable_trials;
static GtkWidget *btn_disable_trials;
static GtkWidget *btn_quit_trials;


//Stats
static GtkWidget *lbl_num_of_trials;
static GtkWidget *lbl_num_of_rewarded_trials;
static GtkWidget *lbl_num_of_trials_of_trial_type;
static GtkWidget *lbl_num_of_rewarded_trials_of_trial_type;


static void reset_connections_button_func (void);
static void enable_trials_button_func (void);
static void disable_trials_button_func (void);
static void quit_trials_button_func (void);



bool create_trial_handler_tab(GtkWidget *tabs, RtTasksData *rt_tasks_data, Gui2TrialHandMsg *msgs_gui_2_trial_hand)
{
	GtkWidget *frame, *frame_label, *hbox, *lbl, *table, *vbox;

	static_rt_tasks_data = rt_tasks_data;

	static_msgs_gui_2_trial_hand = msgs_gui_2_trial_hand;

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

	hbox = gtk_hbox_new(TRUE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,5);

	lbl = gtk_label_new("---- Trial Statistics ----");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, TRUE, TRUE, 0);

	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);
	lbl = gtk_label_new("Num of Trials: ");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE, FALSE, 0);
	lbl = gtk_label_new("");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, TRUE, TRUE, 0);
	lbl_num_of_trials = gtk_label_new("0");
        gtk_box_pack_start(GTK_BOX(hbox),lbl_num_of_trials, FALSE, FALSE, 0);

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


