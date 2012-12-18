#include "GuiMovObjHandler.h"

static RtTasksData *static_rt_tasks_data = NULL;

static Gui2MovObjHandMsg *static_msgs_gui_2_mov_obj_hand;    
static MovObjHand2GuiMsg *static_msgs_mov_obj_hand_2_gui;
static GtkWidget *btn_submit_threshold;
static GtkWidget *entry_threshold;

static bool display_paused = FALSE;
static LocationGraph *location_graph = NULL;

static ThreeDofRobot *static_robot_arm = NULL;
static MovObjHandParadigmRobotReach *static_mov_obj_paradigm = NULL;


static void submit_threshold_button_func(void);

static gboolean timeout_callback(gpointer graph);

bool create_mov_obj_handler_tab(GtkWidget *tabs, RtTasksData *rt_tasks_data, Gui2MovObjHandMsg *msgs_gui_2_mov_obj_hand, MovObjHand2GuiMsg *msgs_mov_obj_hand_2_gui, ThreeDofRobot *robot_arm, MovObjHandParadigmRobotReach *mov_obj_paradigm)
{
	GtkWidget *frame, *frame_label, *hbox, *lbl, *table, *vbox;

	static_rt_tasks_data = rt_tasks_data;

	static_robot_arm = robot_arm;
	static_mov_obj_paradigm = mov_obj_paradigm;

	static_msgs_gui_2_mov_obj_hand = msgs_gui_2_mov_obj_hand;
	static_msgs_mov_obj_hand_2_gui = msgs_mov_obj_hand_2_gui;

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

	////////   LOCATION GRAPH
	vbox = gtk_vbox_new(TRUE, 0);
	gtk_table_attach_defaults(GTK_TABLE(table), vbox, 1,5, 0, 6);  // column 0-1, row 0-6

	hbox = gtk_hbox_new(TRUE, 0);
	gtk_box_pack_start(GTK_BOX(vbox),hbox, TRUE,TRUE,0);
	gtk_widget_set_size_request(hbox, 500, 500);	

	location_graph = allocate_location_graph(hbox, location_graph);

	////////   LAST COLUMN
	vbox = gtk_vbox_new(FALSE, 0);
	gtk_table_attach_defaults(GTK_TABLE(table), vbox, 5,6, 0, 6);  // column 5-6, row 0-6

	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	lbl = gtk_label_new("data load save");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, TRUE, TRUE, 0);

	g_signal_connect(G_OBJECT(btn_submit_threshold), "clicked", G_CALLBACK(submit_threshold_button_func), NULL);

	g_timeout_add(50, timeout_callback, NULL);

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


static gboolean timeout_callback(gpointer graph)
{
	static float x = 0, y = 0, z = 0;
	MovObjCompType 	component;
	MovObjHand2GuiMsgItem msg_item;

	while (get_next_mov_obj_hand_2_gui_msg_buffer_item(static_msgs_mov_obj_hand_2_gui, &msg_item))
	{
		switch (msg_item.msg_type)
		{
			case MOV_OBJ_HAND_2_GUI_MSG_LOCATION:	
				component = msg_item.component;
				x = msg_item.additional_data_0;
				y = msg_item.additional_data_1;
				z = msg_item.additional_data_2;
				break;
			default:
				return print_message(BUG_MSG ,"BMIExpController", "GuiMovObjHandler", "gboolean timeout_callback", "switch (msg_item.msg_type) - default");
		}
	}
	if (!display_paused)
	{
		location_graph->x[0] = x;
		location_graph->y[0] = y;
		gtk_databox_set_total_limits (GTK_DATABOX (location_graph->databox), 0.1, -0.1, 0.1, -0.1);			
	}
	return TRUE;
} 
