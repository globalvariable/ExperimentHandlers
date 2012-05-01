#include "GuiTrialHandler.h"

static TrialTypesData *static_trial_types_data;	
static TrialStatsData *static_trial_stats_data; 
static TrialsHistory *static_trials_history;   
static Gui2TrialHandMsg *static_msgs_gui_2_trial_hand;    

static GtkWidget *btn_enable_trials;
static GtkWidget *btn_disable_trials;
static TrialTypesCombo *combo_trial_type_stats;


//Stats
static GtkWidget *lbl_num_of_trials;
static GtkWidget *lbl_num_of_rewarded_trials;
static GtkWidget *lbl_num_of_trials_of_trial_type;
static GtkWidget *lbl_num_of_rewarded_trials_of_trial_type;



static void enable_trials_button_func (void);
static void disable_trials_button_func (void);
static void combo_trial_type_stats_func (void);

bool create_trial_handler_tab(GtkWidget *tabs, TrialTypesData *trial_types_data, TrialStatsData *trial_stats, TrialsHistory *trials_history, Gui2TrialHandMsg *msgs_gui_2_trial_hand)
{
	GtkWidget *frame, *frame_label, *hbox, *lbl, *table, *vbox;

	static_trial_types_data = trial_types_data;
	static_trial_stats_data = trial_stats;
	static_trials_history = trials_history;
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

	lbl = gtk_label_new("Trials: ");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, TRUE, TRUE, 0);

	btn_enable_trials = gtk_button_new_with_label("Enable");
	gtk_box_pack_start (GTK_BOX (hbox), btn_enable_trials, TRUE, TRUE, 0);

	btn_disable_trials = gtk_button_new_with_label("Disable");
	gtk_box_pack_start (GTK_BOX (hbox), btn_disable_trials, TRUE, TRUE, 0);
	gtk_widget_set_sensitive(btn_disable_trials, FALSE);		

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

	combo_trial_type_stats = allocate_trial_types_combo();
        gtk_box_pack_start(GTK_BOX(hbox),combo_trial_type_stats->combo, TRUE,TRUE,0);
	if(! update_trial_types_combo(trial_types_data, combo_trial_type_stats))
		return print_message(ERROR_MSG ,"BMIExpController", "GuiTrialHandler", "create_trial_handler_gui", "! update_trial_types_combo().");
	gtk_widget_set_size_request(combo_trial_type_stats->combo, 250, 30) ;	

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

	g_signal_connect(G_OBJECT(btn_enable_trials), "clicked", G_CALLBACK(enable_trials_button_func), NULL);
	g_signal_connect(G_OBJECT(btn_disable_trials), "clicked", G_CALLBACK(disable_trials_button_func), NULL);
	g_signal_connect(G_OBJECT(combo_trial_type_stats->combo), "changed", G_CALLBACK(combo_trial_type_stats_func), NULL);

	return TRUE;
}

static void enable_trials_button_func (void)
{
	if (!write_to_gui_2_trial_hand_msg_buffer(static_msgs_gui_2_trial_hand, shared_memory->rt_tasks_data.current_system_time, GUI_2_TRIAL_HAND_MSG_ENABLE_TRIAL_HANDLING, 0))
		return (void)print_message(ERROR_MSG ,"BMIExpController", "GuiTrialHandler", "enable_trials_button_func", "! write_to_gui_2_trial_hand_msg_buffer().");		
	gtk_widget_set_sensitive(btn_enable_trials, FALSE);		
	gtk_widget_set_sensitive(btn_disable_trials, TRUE);	
}

static void disable_trials_button_func (void)
{
	if (!write_to_gui_2_trial_hand_msg_buffer(static_msgs_gui_2_trial_hand, shared_memory->rt_tasks_data.current_system_time, GUI_2_TRIAL_HAND_MSG_DISABLE_TRIAL_HANDLING, 0))
		return (void)print_message(ERROR_MSG ,"BMIExpController", "GuiTrialHandler", "disable_trials_button_func", "! write_to_gui_2_trial_hand_msg_buffer().");		
	gtk_widget_set_sensitive(btn_disable_trials, FALSE);		
	gtk_widget_set_sensitive(btn_enable_trials, TRUE);	
}

static void combo_trial_type_stats_func (void)
{

	return;
}
