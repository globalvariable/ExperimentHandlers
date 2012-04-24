#include "Gui.h"

static GtkWidget *btn_interrogate_trial_type;

static GtkWidget *btn_enable_trials;

static GtkWidget *entry_location_threshold_increment;
static GtkWidget *entry_location_threshold_increment_success_percent;

static GtkWidget *entry_time_stay_at_start;
static GtkWidget *entry_time_stay_at_target;


static GtkWidget *btn_quit;

static void interrogate_trial_type_button_func(void);
static void enable_trials_button_func(void);
static void quit_button_func(void);
void create_gui(void)
{
	GtkWidget *window, *table, *vbox, *hbox, *lbl;


 	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  	gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);
  	gtk_window_set_title(GTK_WINDOW(window), "BMI_Exp_Controller");
  	gtk_window_set_deletable(GTK_WINDOW(window), FALSE);
  	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
  	gtk_container_set_border_width(GTK_CONTAINER(window), 10);

	vbox = gtk_vbox_new(TRUE, 0);
	gtk_container_add(GTK_CONTAINER(window), vbox);

	table = gtk_table_new(14 ,9,TRUE);   // 14 rows 9 columns
	gtk_box_pack_start(GTK_BOX(vbox),table, FALSE,FALSE,0);

	vbox = gtk_vbox_new(TRUE, 0);
	gtk_table_attach_defaults(GTK_TABLE(table), vbox, 0,9, 0, 4);  
	if (!create_trial_handler_gui(vbox))
		print_message(ERROR_MSG ,"BMIExpController", "Gui", "create_gui", "create_trial_handler_gui().");

	vbox = gtk_vbox_new(TRUE, 0);
	gtk_table_attach_defaults(GTK_TABLE(table), vbox, 0,9, 4, 5);  
        gtk_box_pack_start(GTK_BOX(vbox),gtk_hseparator_new(), TRUE,TRUE, 5);

	vbox = gtk_vbox_new(TRUE, 0);
	gtk_table_attach_defaults(GTK_TABLE(table), vbox, 0,4, 5, 9);  
	if (!create_exp_envi_handler_gui(vbox))
		print_message(ERROR_MSG ,"BMIExpController", "Gui", "create_gui", "create_exp_envi_handler_gui().");

	vbox = gtk_vbox_new(TRUE, 0);
	gtk_table_attach_defaults(GTK_TABLE(table), vbox, 0,4, 9, 10);  
        gtk_box_pack_start(GTK_BOX(vbox),gtk_hseparator_new(), TRUE,TRUE, 5);

	vbox = gtk_vbox_new(TRUE, 0);
	gtk_table_attach_defaults(GTK_TABLE(table), vbox, 0,4, 10, 14);  
	if (!create_exp_envi_interfacer_gui(vbox))
		print_message(ERROR_MSG ,"BMIExpController", "Gui", "create_gui", "create_exp_envi_interfacer_gui().");

	vbox = gtk_vbox_new(TRUE, 0);
	gtk_table_attach_defaults(GTK_TABLE(table), vbox, 5, 9, 5, 9);  
	if (!create_mov_obj_handler_gui(vbox))
		print_message(ERROR_MSG ,"BMIExpController", "Gui", "create_gui", "create_mov_obj_handler_gui().");

	vbox = gtk_vbox_new(TRUE, 0);
	gtk_table_attach_defaults(GTK_TABLE(table), vbox, 5, 9, 9, 10);  
        gtk_box_pack_start(GTK_BOX(vbox),gtk_hseparator_new(), TRUE,TRUE, 5);

	vbox = gtk_vbox_new(TRUE, 0);
	gtk_table_attach_defaults(GTK_TABLE(table), vbox, 5, 9, 10, 14);  
	if (!create_mov_obj_interfacer_gui(vbox))
		print_message(ERROR_MSG ,"BMIExpController", "Gui", "create_gui", "create_mov_obj_interfacer_gui().");

	hbox = gtk_hbox_new(TRUE, 0);
	gtk_table_attach_defaults(GTK_TABLE(table), hbox, 4, 5, 5, 14);  
        gtk_box_pack_start(GTK_BOX(hbox),gtk_vseparator_new(), TRUE,TRUE,5);

/*	btn_quit = gtk_button_new_with_label("Quit");
	gtk_box_pack_start (GTK_BOX (vbox), btn_quit, FALSE, FALSE, 0);

	vbox = gtk_vbox_new(FALSE, 0);
	gtk_table_attach_defaults(GTK_TABLE(table), vbox, 0,1, 0, 1);  

	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);
 
	// trial types combo

	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	btn_interrogate_trial_type = gtk_button_new_with_label("Interrogate Trial Type");
	gtk_box_pack_start (GTK_BOX (hbox), btn_interrogate_trial_type, TRUE, TRUE, 0);

        gtk_box_pack_start(GTK_BOX(vbox),gtk_hseparator_new(), FALSE,FALSE,5);

	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	lbl = gtk_label_new("----- Location Thresholding -----");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);

	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);
	lbl = gtk_label_new("Threshold Increment :");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);
	lbl = gtk_label_new("");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, TRUE,TRUE,0);
	entry_location_threshold_increment = gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(hbox),entry_location_threshold_increment, FALSE,FALSE,0);
	gtk_widget_set_size_request(entry_location_threshold_increment, 50, 25) ;
	gtk_entry_set_text(GTK_ENTRY(entry_location_threshold_increment), "10");

	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);
	lbl = gtk_label_new("Success Criterion(%) :");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);
	lbl = gtk_label_new("");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, TRUE,TRUE,0);
	entry_location_threshold_increment_success_percent = gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(hbox),entry_location_threshold_increment_success_percent, FALSE,FALSE,0);
	gtk_widget_set_size_request(entry_location_threshold_increment_success_percent, 50, 25) ;
	gtk_entry_set_text(GTK_ENTRY(entry_location_threshold_increment_success_percent), "60");

        gtk_box_pack_start(GTK_BOX(vbox),gtk_hseparator_new(), FALSE,FALSE,5);

	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);
	lbl = gtk_label_new("Stay At Start (ms):");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);
	lbl = gtk_label_new("");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, TRUE,TRUE,0);
	entry_time_stay_at_start = gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(hbox),entry_time_stay_at_start, FALSE,FALSE,0);
	gtk_widget_set_size_request(entry_time_stay_at_start, 50, 25) ;
	gtk_entry_set_text(GTK_ENTRY(entry_time_stay_at_start), "100");

	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);
	lbl = gtk_label_new("Stay At Target (ms):");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);
	lbl = gtk_label_new("");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, TRUE,TRUE,0);
	entry_time_stay_at_target = gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(hbox),entry_time_stay_at_target, FALSE,FALSE,0);
	gtk_widget_set_size_request(entry_time_stay_at_target, 50, 25) ;
	gtk_entry_set_text(GTK_ENTRY(entry_time_stay_at_target), "300");

        gtk_box_pack_start(GTK_BOX(vbox),gtk_hseparator_new(), FALSE,FALSE,5);

	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	btn_enable_trials = gtk_button_new_with_label("Trials: Disabled");
	gtk_box_pack_start (GTK_BOX (hbox), btn_enable_trials, TRUE, TRUE, 0);

	vbox = gtk_vbox_new(FALSE, 0);
	gtk_table_attach_defaults(GTK_TABLE(table), vbox, 1,2, 0, 1);  

       	g_signal_connect(G_OBJECT(btn_interrogate_trial_type), "clicked", G_CALLBACK(interrogate_trial_type_button_func ), NULL);   	
       	g_signal_connect(G_OBJECT(btn_enable_trials), "clicked", G_CALLBACK(enable_trials_button_func ), NULL);   	
       	g_signal_connect(G_OBJECT(btn_quit), "clicked", G_CALLBACK(quit_button_func ), NULL);       
*/
	gtk_widget_show_all(window);
}

static void interrogate_trial_type_button_func(void)
{

}
static void enable_trials_button_func(void)
{

}
static void quit_button_func(void)
{
}
