#include "GuiMovObjHandler.h"

static Gui2MovObjHandMsg *static_msgs_gui_2_mov_obj_hand;    


bool create_mov_obj_handler_tab(GtkWidget *tabs, Gui2MovObjHandMsg *msgs_gui_2_mov_obj_hand)
{
	GtkWidget *frame, *frame_label, *hbox, *lbl, *table, *vbox;

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

	////////   LAST COLUMN
	vbox = gtk_vbox_new(FALSE, 0);
	gtk_table_attach_defaults(GTK_TABLE(table), vbox, 5,6, 0, 6);  // column 5-6, row 0-6

	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	lbl = gtk_label_new("data load save");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, TRUE, TRUE, 0);

	return TRUE;
}

