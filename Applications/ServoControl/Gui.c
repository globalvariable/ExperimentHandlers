#include "Gui.h"

static GtkWidget *entry_base_pulse_width;
static GtkWidget *entry_shoulder_pulse_width;
static GtkWidget *entry_elbow_pulse_width;
static GtkWidget *btn_submit_pulse_width;

static void submit_pulse_width_button_func(void);

void create_gui(void)
{
	GtkWidget *window, *vbox, *hbox, *lbl;

 	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  	gtk_window_set_default_size(GTK_WINDOW(window), 100, 100);
  	gtk_window_set_title(GTK_WINDOW(window), "ServoControl");
  	gtk_container_set_border_width(GTK_CONTAINER(window), 10);

  	vbox = gtk_vbox_new(TRUE, 0);
	gtk_container_add(GTK_CONTAINER(window), vbox);

  	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);       

	lbl = gtk_label_new("Base PW\t\t: ");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);
        entry_base_pulse_width = gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(hbox),entry_base_pulse_width, FALSE,FALSE,0);
	gtk_entry_set_text(GTK_ENTRY(entry_base_pulse_width), "15000");
	gtk_widget_set_size_request(entry_base_pulse_width, 50, 30) ;	
	lbl = gtk_label_new(" x 0.1us");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);

  	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);       

	lbl = gtk_label_new("Shoulder PW\t: ");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);
        entry_shoulder_pulse_width= gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(hbox),entry_shoulder_pulse_width, FALSE,FALSE,0);
	gtk_entry_set_text(GTK_ENTRY(entry_shoulder_pulse_width), "15000");
	gtk_widget_set_size_request(entry_shoulder_pulse_width, 50, 30) ;	
	lbl = gtk_label_new(" x 0.1us");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);

  	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);       

	lbl = gtk_label_new("Elbow PW\t: ");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);
        entry_elbow_pulse_width= gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(hbox),entry_elbow_pulse_width, FALSE,FALSE,0);
	gtk_entry_set_text(GTK_ENTRY(entry_elbow_pulse_width), "15000");
	gtk_widget_set_size_request(entry_elbow_pulse_width, 50, 30) ;	
	lbl = gtk_label_new(" x 0.1us");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);

  	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	btn_submit_pulse_width = gtk_button_new_with_label("Submit Pulse Width");
	gtk_box_pack_start (GTK_BOX (hbox), btn_submit_pulse_width, TRUE, TRUE, 0);

	gtk_widget_show_all(window);

  	g_signal_connect (G_OBJECT (window), "destroy", G_CALLBACK (gtk_main_quit), NULL);
      	g_signal_connect(G_OBJECT( btn_submit_pulse_width), "clicked", G_CALLBACK( submit_pulse_width_button_func), NULL);

}

static void submit_pulse_width_button_func(void)
{
	unsigned int base_pw, shoulder_pw, elbow_pw;
	
	base_pw = (unsigned int)atof(gtk_entry_get_text(GTK_ENTRY(entry_base_pulse_width)));
	shoulder_pw = (unsigned int)atof(gtk_entry_get_text(GTK_ENTRY(entry_shoulder_pulse_width)));
	elbow_pw = (unsigned int)atof(gtk_entry_get_text(GTK_ENTRY(entry_elbow_pulse_width)));

	if (base_pw >= 25000)
		return (void)print_message(ERROR_MSG ,"ServoControl", "ServoControlRtTask", "submit_pulse_width_button_func", "base_pw >= 25000.");
	if (base_pw <= 5000)
		return (void)print_message(ERROR_MSG ,"ServoControl", "ServoControlRtTask", "submit_pulse_width_button_func", "base_pw <= 5000.");
	if (shoulder_pw >= 25000)
		return (void)print_message(ERROR_MSG ,"ServoControl", "ServoControlRtTask", "submit_pulse_width_button_func", "shoulder_pw >= 25000.");
	if (shoulder_pw <= 5000)
		return (void)print_message(ERROR_MSG ,"ServoControl", "ServoControlRtTask", "submit_pulse_width_button_func", "shoulder_pw <= 5000.");
	if (elbow_pw >= 25000)
		return (void)print_message(ERROR_MSG ,"ServoControl", "ServoControlRtTask", "submit_pulse_width_button_func", "elbow_pw >= 25000.");
	if (elbow_pw <= 5000)
		return (void)print_message(ERROR_MSG ,"ServoControl", "ServoControlRtTask", "submit_pulse_width_button_func", "elbow_pw <= 5000.");
	
	servos[BASE_SERVO].pulse_command.pulse_width = 65536 - base_pw;
	servos[SHOULDER_SERVO].pulse_command.pulse_width = 65536 - shoulder_pw;
	servos[ELBOW_SERVO].pulse_command.pulse_width = 65536 - elbow_pw;

	return;
}
