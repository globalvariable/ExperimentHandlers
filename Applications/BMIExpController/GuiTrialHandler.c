#include "GuiTrialHandler.h"


static GtkWidget *btn_interrogate_trial_type;
static GtkWidget *btn_enable_trials;

bool create_trial_handler_gui(GtkWidget *vbox)
{
	GtkWidget *hbox;

	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	btn_interrogate_trial_type = gtk_button_new_with_label("Interrogate Trial Type");
	gtk_box_pack_start (GTK_BOX (hbox), btn_interrogate_trial_type, TRUE, TRUE, 0);

	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	btn_enable_trials = gtk_button_new_with_label("Trials: Disabled");
	gtk_box_pack_start (GTK_BOX (hbox), btn_enable_trials, TRUE, TRUE, 0);

	return TRUE;
}
