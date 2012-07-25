#include "GuiMovObjHandler.h"

static RtTasksData *static_rt_tasks_data = NULL;

static Gui2MovObjHandMsg *static_msgs_gui_2_mov_obj_hand;    

static GtkWidget *btn_submit_threshold;
static GtkWidget *entry_threshold;
static void submit_threshold_button_func(void);

bool create_mov_obj_handler_tab(GtkWidget *tabs, RtTasksData *rt_tasks_data, Gui2MovObjHandMsg *msgs_gui_2_mov_obj_hand)
{
	GtkWidget *frame, *frame_label, *hbox, *lbl, *table, *vbox;

	static_rt_tasks_data = rt_tasks_data;

	static_msgs_gui_2_mov_obj_hand = msgs_gui_2_mov_obj_hand;

        frame = gtk_frame_new ("");
        frame_label = gtk_label_new ("     Mov Obj Handler    ");      
   
        gtk_notebook_append_page (GTK_NOTEBOOK (tabs), frame, frame_label);  

 	hbox = gtk_hbox_new(TRUE, 0);
        gtk_container_add (GTK_CONTAINER (frame), hbox);

	table = gtk_table_new(2 ,6,TRUE);   // 2 rows 6 columns
	gtk_box_pack_start(GTK_BOX(hbox),table, TRUE,TRUE,0);

	vbox = gtk_vbox_new(FALSE, 0);
	gtk_table_attach_defaults(GTK_TABLE(table), vbox, 0,1, 0, 6);  // column 0-1, row 0-6

	hbox = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	btn_submit_threshold = gtk_button_new_with_label("Submit Threshold");
	gtk_box_pack_start (GTK_BOX (hbox), btn_submit_threshold, FALSE, FALSE, 0);

	entry_threshold =  gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(hbox), entry_threshold, FALSE,FALSE,0);
	gtk_widget_set_size_request(entry_threshold, 50, 25);	

	////////   LAST COLUMN
	vbox = gtk_vbox_new(FALSE, 0);
	gtk_table_attach_defaults(GTK_TABLE(table), vbox, 5,6, 0, 6);  // column 5-6, row 0-6

	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	lbl = gtk_label_new("data load save");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, TRUE, TRUE, 0);

	g_signal_connect(G_OBJECT(btn_submit_threshold), "clicked", G_CALLBACK(submit_threshold_button_func), NULL);

	return TRUE;
}

static void submit_threshold_button_func(void)
{
	double threshold = atof(gtk_entry_get_text(GTK_ENTRY(entry_threshold)));
	if (threshold <= 0)
		return (void)print_message(ERROR_MSG ,"BMIExpController", "GuiMovObjHandler", "submit_threshold_button_func", "threshold <= 0.");		
	if (! write_to_gui_2_mov_obj_hand_msg_buffer(static_msgs_gui_2_mov_obj_hand, static_rt_tasks_data->current_system_time, GUI_2_MOV_OBJ_HAND_MSG_SET_THRESHOLD, threshold))
		return (void)print_message(ERROR_MSG ,"BMIExpController", "GuiMovObjHandler", "submit_threshold_button_func", "! write_to_gui_2_mov_obj_hand_msg_buffer().");		
	return;
}

