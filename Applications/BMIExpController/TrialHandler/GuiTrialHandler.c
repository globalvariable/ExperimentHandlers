#include "GuiTrialHandler.h"

static AllTrialTypesCombo *combo_all_trial_types;
static GtkWidget *entry_max_trial_type_length;
static GtkWidget *entry_max_trial_type_refractory;
static GtkWidget *btn_add_trial_type;

static TrialTypesCombo *combo_trial_type_stats;

static GtkWidget *btn_get_trial_info;


//Stats
static GtkWidget *lbl_num_of_trials;
static GtkWidget *lbl_num_of_rewarded_trials;
static GtkWidget *lbl_num_of_trials_of_trial_type;
static GtkWidget *lbl_num_of_rewarded_trials_of_trial_type;

bool create_trial_handler_gui(GtkWidget *vbox)
{
	GtkWidget *hbox, *lbl, *table, *vbox1;

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

	combo_all_trial_types = allocate_all_trial_types_combo();
        gtk_box_pack_start(GTK_BOX(hbox),combo_all_trial_types->combo, TRUE,TRUE,0);
	gtk_widget_set_size_request(combo_all_trial_types->combo, 250, 30) ;	

	hbox = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);
	lbl = gtk_label_new("Max Trial Len (ms): ");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE, FALSE, 0);
	lbl = gtk_label_new("");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, TRUE, TRUE, 0);
	entry_max_trial_type_length = gtk_entry_new();
	gtk_widget_set_size_request(entry_max_trial_type_length, 50, 25) ;
        gtk_box_pack_start(GTK_BOX(hbox),entry_max_trial_type_length, FALSE,FALSE,0);
	gtk_entry_set_text(GTK_ENTRY(entry_max_trial_type_length), "5000");

	hbox = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);
	lbl = gtk_label_new("Max Refractory Len (ms): ");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE, FALSE, 0);
	lbl = gtk_label_new("");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, TRUE, TRUE, 0);
	entry_max_trial_type_refractory = gtk_entry_new();
	gtk_widget_set_size_request(entry_max_trial_type_refractory, 50, 25) ;
        gtk_box_pack_start(GTK_BOX(hbox),entry_max_trial_type_refractory, FALSE,FALSE,0);
	gtk_entry_set_text(GTK_ENTRY(entry_max_trial_type_refractory), "4000");	

	hbox = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	btn_add_trial_type = gtk_button_new_with_label("Add Trial Type");
	gtk_box_pack_start (GTK_BOX (hbox), btn_add_trial_type, TRUE, TRUE, 0);

	vbox = gtk_vbox_new(FALSE, 0);
	gtk_table_attach(GTK_TABLE(table), vbox, 1,2, 0, 1, (GTK_EXPAND | GTK_SHRINK | GTK_FILL), (GTK_EXPAND | GTK_SHRINK | GTK_FILL), 5, 0);  // column 1-2, row 0-1	

	hbox = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	combo_trial_type_stats = allocate_trial_types_combo();
        gtk_box_pack_start(GTK_BOX(hbox),combo_trial_type_stats->combo, TRUE,TRUE,0);
	if(! update_trial_types_combo(get_trial_types_data(), combo_trial_type_stats))
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

	return TRUE;
}
