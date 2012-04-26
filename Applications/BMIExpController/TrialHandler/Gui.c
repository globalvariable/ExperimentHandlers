#include "Gui.h"

void create_gui_handler(TrialTypesData *trial_types_data, TrialStatsData *trial_stats, TrialsHistory *trials_history, Gui2TrialHandMsg *msgs_gui_2_trial_hand)
{
	GtkWidget *window, *table, *vbox, *hbox;


 	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  	gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);
  	gtk_window_set_title(GTK_WINDOW(window), "BMI_Exp_Controller");
  	gtk_window_set_deletable(GTK_WINDOW(window), FALSE);
  	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
  	gtk_container_set_border_width(GTK_CONTAINER(window), 10);

	vbox = gtk_vbox_new(TRUE, 0);
	gtk_container_add(GTK_CONTAINER(window), vbox);

	table = gtk_table_new(9 ,9,FALSE);   // 14 rows 9 columns
	gtk_box_pack_start(GTK_BOX(vbox),table, TRUE,TRUE,0);

	vbox = gtk_vbox_new(FALSE, 0);
	gtk_table_attach_defaults(GTK_TABLE(table), vbox, 0,9, 0, 4);  // column 0-9, row 0-4
	if (!create_trial_handler_gui(vbox, trial_types_data, trial_stats, trials_history, msgs_gui_2_trial_hand))
		print_message(ERROR_MSG ,"BMIExpController", "Gui", "create_gui", "create_trial_handler_gui().");

	vbox = gtk_vbox_new(TRUE, 0);
	gtk_table_attach_defaults(GTK_TABLE(table), vbox, 0,9, 4, 5);  
        gtk_box_pack_start(GTK_BOX(vbox),gtk_hseparator_new(), TRUE,TRUE, 5);  // column 0-9, row 4-5

	vbox = gtk_vbox_new(TRUE, 0);
	gtk_table_attach_defaults(GTK_TABLE(table), vbox, 0,4, 5, 9);  
	if (!create_exp_envi_handler_gui(vbox))
		print_message(ERROR_MSG ,"BMIExpController", "Gui", "create_gui", "create_exp_envi_handler_gui().");

	vbox = gtk_vbox_new(TRUE, 0);
	gtk_table_attach_defaults(GTK_TABLE(table), vbox, 5, 9, 5, 9);  
	if (!create_mov_obj_handler_gui(vbox))
		print_message(ERROR_MSG ,"BMIExpController", "Gui", "create_gui", "create_mov_obj_handler_gui().");

	hbox = gtk_hbox_new(TRUE, 0);
	gtk_table_attach_defaults(GTK_TABLE(table), hbox, 4, 5, 5, 9);  
        gtk_box_pack_start(GTK_BOX(hbox),gtk_vseparator_new(), TRUE,TRUE,5);

	gtk_widget_show_all(window);
}

