#include "GuiTrialHandler.h"

static TrialTypesData *static_trial_types_data;	
static TrialStatsData *static_trial_stats_data; 
static TrialsHistory *static_trials_history;   

static Gui2TrialHandMsg *static_msgs_gui_2_trial_hand;    

static GtkWidget *btn_enable_trials;
static TrialTypesCombo *combo_trial_type_stats;


//Stats
static GtkWidget *lbl_num_of_trials;
static GtkWidget *lbl_num_of_rewarded_trials;
static GtkWidget *lbl_num_of_trials_of_trial_type;
static GtkWidget *lbl_num_of_rewarded_trials_of_trial_type;


static void combo_trial_type_stats_func (void);

static void enable_trials_button_func (void);

bool create_trial_handler_gui(GtkWidget *vbox, TrialTypesData *trial_types_data, TrialStatsData *trial_stats, TrialsHistory *trials_history, Gui2TrialHandMsg *msgs_gui_2_trial_hand)
{
	GtkWidget *hbox, *lbl, *table, *vbox1;

	static_trial_types_data = trial_types_data;
	static_trial_stats_data = trial_stats;
	static_trials_history = trials_history;
	static_msgs_gui_2_trial_hand = msgs_gui_2_trial_hand;

	vbox1 = gtk_vbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),vbox1, FALSE,FALSE,0);

	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox1),hbox, FALSE,FALSE,10);

	lbl = gtk_label_new("====== Trial Handler ======");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, TRUE, TRUE, 0);

	table = gtk_table_new(1, 3, TRUE);   // 1 rows 3 columns
	gtk_box_pack_start(GTK_BOX(vbox1),table, FALSE,FALSE,0);

	vbox = gtk_vbox_new(FALSE, 0);
	gtk_table_attach(GTK_TABLE(table), vbox, 0,1, 0, 1, (GTK_EXPAND | GTK_SHRINK | GTK_FILL),  (GTK_EXPAND | GTK_SHRINK | GTK_FILL), 5, 0);  // column 1-2, row 0-1	

	hbox = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	btn_enable_trials = gtk_button_new_with_label("Enable Trials");
	gtk_box_pack_start (GTK_BOX (hbox), btn_enable_trials, TRUE, TRUE, 0);

	vbox = gtk_vbox_new(FALSE, 0);
	gtk_table_attach(GTK_TABLE(table), vbox, 1,2, 0, 1, (GTK_EXPAND | GTK_SHRINK | GTK_FILL), (GTK_EXPAND | GTK_SHRINK | GTK_FILL), 5, 0);  // column 1-2, row 0-1	

	hbox = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	combo_trial_type_stats = allocate_trial_types_combo();
        gtk_box_pack_start(GTK_BOX(hbox),combo_trial_type_stats->combo, TRUE,TRUE,0);
	if(! update_trial_types_combo(trial_types_data, combo_trial_type_stats))
		return print_message(ERROR_MSG ,"BMIExpController", "GuiTrialHandler", "create_trial_handler_gui", "! update_trial_types_combo().");
	gtk_widget_set_size_request(combo_trial_type_stats->combo, 250, 30) ;	

	hbox = gtk_hbox_new(TRUE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,5);

	lbl = gtk_label_new("---- Trial Stats ----");
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

	lbl = gtk_label_new("---- Trial Type Stats ----");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, TRUE, TRUE, 0);

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

	vbox = gtk_vbox_new(FALSE, 0);
	gtk_table_attach(GTK_TABLE(table), vbox, 2,3, 0, 1, (GTK_EXPAND | GTK_SHRINK | GTK_FILL), (GTK_EXPAND | GTK_SHRINK | GTK_FILL), 5, 0);  // column 1-2, row 0-1	

	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	lbl = gtk_label_new("data load save");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, TRUE, TRUE, 0);

	g_signal_connect(G_OBJECT(btn_enable_trials), "clicked", G_CALLBACK(enable_trials_button_func), NULL);
	g_signal_connect(G_OBJECT(combo_trial_type_stats->combo), "changed", G_CALLBACK(combo_trial_type_stats_func), NULL);

	return TRUE;
}

static void enable_trials_button_func (void)
{

}



static void combo_trial_type_stats_func (void)
{

	return;
}
