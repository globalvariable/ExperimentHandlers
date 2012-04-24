#include "GuiExpEnviHandler.h"


bool create_exp_envi_handler_gui(GtkWidget *vbox)
{
	GtkWidget *hbox, *lbl;

	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	lbl = gtk_label_new("Experiment Environment Handler");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);

	return TRUE;

}
