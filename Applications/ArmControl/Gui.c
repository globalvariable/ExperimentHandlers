#include "Gui.h"

static ThreeDofRobot *static_robot_arm = NULL;

static GtkWidget *entry_base_pulse_width;
static GtkWidget *entry_shoulder_pulse_width;
static GtkWidget *entry_elbow_pulse_width;
static GtkWidget *btn_submit_pulse_width;
static GtkWidget *entry_base_pulse_width_change;
static GtkWidget *entry_shoulder_pulse_width_change;
static GtkWidget *entry_elbow_pulse_width_change;
static GtkWidget *btn_increment_base_pulse_width;
static GtkWidget *btn_decrement_base_pulse_width;
static GtkWidget *lbl_base_0_degree_quanta;
static GtkWidget *btn_set_base_0_degree;
static GtkWidget *lbl_base_90_degree_quanta;
static GtkWidget *btn_set_base_90_degree;
static GtkWidget *lbl_base_degree_per_pos_quanta;
static GtkWidget *lbl_base_angle;
static GtkWidget *btn_increment_shoulder_pulse_width;
static GtkWidget *btn_decrement_shoulder_pulse_width;
static GtkWidget *lbl_shoulder_0_degree_quanta;
static GtkWidget *btn_set_shoulder_0_degree;
static GtkWidget *lbl_shoulder_90_degree_quanta;
static GtkWidget *btn_set_shoulder_90_degree;
static GtkWidget *lbl_shoulder_degree_per_pos_quanta;
static GtkWidget *lbl_shoulder_angle;
static GtkWidget *btn_increment_elbow_pulse_width;
static GtkWidget *btn_decrement_elbow_pulse_width;
static GtkWidget *lbl_elbow_0_degree_quanta;
static GtkWidget *btn_set_elbow_0_degree;
static GtkWidget *lbl_elbow_90_degree_quanta;
static GtkWidget *btn_set_elbow_90_degree;
static GtkWidget *lbl_elbow_degree_per_pos_quanta;
static GtkWidget *lbl_elbow_angle;

static gboolean timeout_callback(gpointer none);

static void submit_pulse_width_button_func(void);
static void increment_base_pulse_width_button_func(void);
static void decrement_base_pulse_width_button_func(void);
static void set_base_0_degree_button_func(void);
static void set_base_90_degree_button_func(void);
static void increment_shoulder_pulse_width_button_func(void);
static void decrement_shoulder_pulse_width_button_func(void);
static void set_shoulder_0_degree_button_func(void);
static void set_shoulder_90_degree_button_func(void);
static void increment_elbow_pulse_width_button_func(void);
static void decrement_elbow_pulse_width_button_func(void);
static void set_elbow_0_degree_button_func(void);
static void set_elbow_90_degree_button_func(void);

void create_gui(ThreeDofRobot 	*robot_arm)
{
	GtkWidget *window, *vbox, *hbox, *lbl, *table;

	static_robot_arm = robot_arm;

 	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  	gtk_window_set_default_size(GTK_WINDOW(window), 100, 100);
  	gtk_window_set_title(GTK_WINDOW(window), "ArmControl");
  	gtk_container_set_border_width(GTK_CONTAINER(window), 10);

  	vbox = gtk_vbox_new(TRUE, 0);
	gtk_container_add(GTK_CONTAINER(window), vbox);

  	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);       

	table = gtk_table_new(2 ,6,TRUE);   // 2 rows 6 columns
	gtk_box_pack_start(GTK_BOX(hbox),table, TRUE,TRUE,0);

	vbox = gtk_vbox_new(FALSE, 0);
	gtk_table_attach_defaults(GTK_TABLE(table), vbox, 0,1, 0, 6);  // column 0-1, row 0-6

	hbox = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	lbl = gtk_label_new("Base PW\t\t: ");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);
        entry_base_pulse_width = gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(hbox),entry_base_pulse_width, FALSE,FALSE,0);
	gtk_entry_set_text(GTK_ENTRY(entry_base_pulse_width), "1500");
	gtk_widget_set_size_request(entry_base_pulse_width, 50, 30) ;	
	lbl = gtk_label_new("us");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);

        entry_base_pulse_width_change = gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(hbox),entry_base_pulse_width_change, FALSE,FALSE,0);
	gtk_entry_set_text(GTK_ENTRY(entry_base_pulse_width_change), "100");
	gtk_widget_set_size_request(entry_base_pulse_width_change, 50, 30) ;	

	btn_increment_base_pulse_width = gtk_button_new_with_label("+");
	gtk_box_pack_start (GTK_BOX (hbox), btn_increment_base_pulse_width, FALSE, FALSE, 0);
	gtk_widget_set_size_request(btn_increment_base_pulse_width, 30, 30) ;	
	btn_decrement_base_pulse_width = gtk_button_new_with_label("-");
	gtk_box_pack_start (GTK_BOX (hbox), btn_decrement_base_pulse_width, FALSE, FALSE, 0);
	gtk_widget_set_size_request(btn_decrement_base_pulse_width, 30, 30) ;	

	gtk_box_pack_start (GTK_BOX (hbox), gtk_vseparator_new(), FALSE, FALSE, 10);

	lbl_base_0_degree_quanta = gtk_label_new("0");
        gtk_box_pack_start(GTK_BOX(hbox),lbl_base_0_degree_quanta, FALSE,FALSE,0);
	gtk_widget_set_size_request(lbl_base_0_degree_quanta, 50, 30) ;	
	btn_set_base_0_degree = gtk_button_new_with_label("0°");
	gtk_box_pack_start (GTK_BOX (hbox), btn_set_base_0_degree, FALSE, FALSE, 0);
	gtk_widget_set_size_request(btn_set_base_0_degree, 40, 30) ;	
	lbl_base_90_degree_quanta = gtk_label_new("0");
        gtk_box_pack_start(GTK_BOX(hbox),lbl_base_90_degree_quanta, FALSE,FALSE,0);
	gtk_widget_set_size_request(lbl_base_90_degree_quanta, 50, 30) ;	
	btn_set_base_90_degree = gtk_button_new_with_label("90°");
	gtk_box_pack_start (GTK_BOX (hbox), btn_set_base_90_degree, FALSE, FALSE, 0);
	gtk_widget_set_size_request(btn_set_base_90_degree, 40, 30) ;	

	lbl_base_degree_per_pos_quanta = gtk_label_new("0°");
        gtk_box_pack_start(GTK_BOX(hbox),lbl_base_degree_per_pos_quanta, FALSE,FALSE,0);
	gtk_widget_set_size_request(lbl_base_degree_per_pos_quanta, 50, 30) ;	

	gtk_box_pack_start (GTK_BOX (hbox), gtk_vseparator_new(), FALSE, FALSE, 10);

	lbl_base_angle = gtk_label_new("0°");
        gtk_box_pack_start(GTK_BOX(hbox),lbl_base_angle, FALSE,FALSE,0);
	gtk_widget_set_size_request(lbl_base_angle, 60, 30) ;	

  	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);       

	lbl = gtk_label_new("Shoulder PW\t: ");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);
        entry_shoulder_pulse_width= gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(hbox),entry_shoulder_pulse_width, FALSE,FALSE,0);
	gtk_entry_set_text(GTK_ENTRY(entry_shoulder_pulse_width), "1500");
	gtk_widget_set_size_request(entry_shoulder_pulse_width, 50, 30) ;	
	lbl = gtk_label_new("us");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);

        entry_shoulder_pulse_width_change = gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(hbox),entry_shoulder_pulse_width_change, FALSE,FALSE,0);
	gtk_entry_set_text(GTK_ENTRY(entry_shoulder_pulse_width_change), "100");
	gtk_widget_set_size_request(entry_shoulder_pulse_width_change, 50, 30) ;	

	btn_increment_shoulder_pulse_width = gtk_button_new_with_label("+");
	gtk_box_pack_start (GTK_BOX (hbox), btn_increment_shoulder_pulse_width, FALSE, FALSE, 0);
	gtk_widget_set_size_request(btn_increment_shoulder_pulse_width, 30, 30) ;	
	btn_decrement_shoulder_pulse_width = gtk_button_new_with_label("-");
	gtk_box_pack_start (GTK_BOX (hbox), btn_decrement_shoulder_pulse_width, FALSE, FALSE, 0);
	gtk_widget_set_size_request(btn_decrement_shoulder_pulse_width, 30, 30) ;	

	gtk_box_pack_start (GTK_BOX (hbox), gtk_vseparator_new(), FALSE, FALSE, 10);

	lbl_shoulder_0_degree_quanta = gtk_label_new("0");
        gtk_box_pack_start(GTK_BOX(hbox),lbl_shoulder_0_degree_quanta, FALSE,FALSE,0);
	gtk_widget_set_size_request(lbl_shoulder_0_degree_quanta, 50, 30) ;	
	btn_set_shoulder_0_degree = gtk_button_new_with_label("0°");
	gtk_box_pack_start (GTK_BOX (hbox), btn_set_shoulder_0_degree, FALSE, FALSE, 0);
	gtk_widget_set_size_request(btn_set_shoulder_0_degree, 40, 30) ;	
	lbl_shoulder_90_degree_quanta = gtk_label_new("0");
        gtk_box_pack_start(GTK_BOX(hbox),lbl_shoulder_90_degree_quanta, FALSE,FALSE,0);
	gtk_widget_set_size_request(lbl_shoulder_90_degree_quanta, 50, 30) ;	
	btn_set_shoulder_90_degree = gtk_button_new_with_label("90°");
	gtk_box_pack_start (GTK_BOX (hbox), btn_set_shoulder_90_degree, FALSE, FALSE, 0);
	gtk_widget_set_size_request(btn_set_shoulder_90_degree, 40, 30) ;	

	lbl_shoulder_degree_per_pos_quanta = gtk_label_new("0°");
        gtk_box_pack_start(GTK_BOX(hbox),lbl_shoulder_degree_per_pos_quanta, FALSE,FALSE,0);
	gtk_widget_set_size_request(lbl_shoulder_degree_per_pos_quanta, 50, 30) ;	

	gtk_box_pack_start (GTK_BOX (hbox), gtk_vseparator_new(), FALSE, FALSE, 10);

	lbl_shoulder_angle = gtk_label_new("0°");
        gtk_box_pack_start(GTK_BOX(hbox),lbl_shoulder_angle, FALSE,FALSE,0);
	gtk_widget_set_size_request(lbl_shoulder_angle, 60, 30) ;		

  	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);       

	lbl = gtk_label_new("Elbow PW\t: ");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);
        entry_elbow_pulse_width= gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(hbox),entry_elbow_pulse_width, FALSE,FALSE,0);
	gtk_entry_set_text(GTK_ENTRY(entry_elbow_pulse_width), "1500");
	gtk_widget_set_size_request(entry_elbow_pulse_width, 50, 30) ;	
	lbl = gtk_label_new("us");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);

        entry_elbow_pulse_width_change = gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(hbox),entry_elbow_pulse_width_change, FALSE,FALSE,0);
	gtk_entry_set_text(GTK_ENTRY(entry_elbow_pulse_width_change), "100");
	gtk_widget_set_size_request(entry_elbow_pulse_width_change, 50, 30) ;	

	btn_increment_elbow_pulse_width = gtk_button_new_with_label("+");
	gtk_box_pack_start (GTK_BOX (hbox), btn_increment_elbow_pulse_width, FALSE, FALSE, 0);
	gtk_widget_set_size_request(btn_increment_elbow_pulse_width, 30, 30) ;	
	btn_decrement_elbow_pulse_width = gtk_button_new_with_label("-");
	gtk_box_pack_start (GTK_BOX (hbox), btn_decrement_elbow_pulse_width, FALSE, FALSE, 0);
	gtk_widget_set_size_request(btn_decrement_elbow_pulse_width, 30, 30) ;	

	gtk_box_pack_start (GTK_BOX (hbox), gtk_vseparator_new(), FALSE, FALSE, 10);

	lbl_elbow_0_degree_quanta = gtk_label_new("0");
        gtk_box_pack_start(GTK_BOX(hbox),lbl_elbow_0_degree_quanta, FALSE,FALSE,0);
	gtk_widget_set_size_request(lbl_elbow_0_degree_quanta, 50, 30) ;	
	btn_set_elbow_0_degree = gtk_button_new_with_label("0°");
	gtk_box_pack_start (GTK_BOX (hbox), btn_set_elbow_0_degree, FALSE, FALSE, 0);
	gtk_widget_set_size_request(btn_set_elbow_0_degree, 40, 30) ;
	lbl_elbow_90_degree_quanta = gtk_label_new("0");
        gtk_box_pack_start(GTK_BOX(hbox),lbl_elbow_90_degree_quanta, FALSE,FALSE,0);
	gtk_widget_set_size_request(lbl_elbow_90_degree_quanta, 50, 30) ;		
	btn_set_elbow_90_degree = gtk_button_new_with_label("90°");
	gtk_box_pack_start (GTK_BOX (hbox), btn_set_elbow_90_degree, FALSE, FALSE, 0);
	gtk_widget_set_size_request(btn_set_elbow_90_degree, 40, 30) ;	

	lbl_elbow_degree_per_pos_quanta = gtk_label_new("0°");
        gtk_box_pack_start(GTK_BOX(hbox),lbl_elbow_degree_per_pos_quanta, FALSE,FALSE,0);
	gtk_widget_set_size_request(lbl_elbow_degree_per_pos_quanta, 50, 30) ;	

	gtk_box_pack_start (GTK_BOX (hbox), gtk_vseparator_new(), FALSE, FALSE, 10);

	lbl_elbow_angle = gtk_label_new("0°");
        gtk_box_pack_start(GTK_BOX(hbox),lbl_elbow_angle, FALSE,FALSE,0);
	gtk_widget_set_size_request(lbl_elbow_angle, 60, 30) ;		

  	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	btn_submit_pulse_width = gtk_button_new_with_label("Submit Pulse Width");
	gtk_box_pack_start (GTK_BOX (hbox), btn_submit_pulse_width, TRUE, TRUE, 0);

	gtk_widget_show_all(window);

  	g_signal_connect (G_OBJECT (window), "destroy", G_CALLBACK (gtk_main_quit), NULL);
      	g_signal_connect(G_OBJECT( btn_submit_pulse_width), "clicked", G_CALLBACK( submit_pulse_width_button_func), NULL);
      	g_signal_connect(G_OBJECT( btn_increment_base_pulse_width), "clicked", G_CALLBACK( increment_base_pulse_width_button_func), NULL);
      	g_signal_connect(G_OBJECT( btn_decrement_base_pulse_width), "clicked", G_CALLBACK( decrement_base_pulse_width_button_func), NULL);
      	g_signal_connect(G_OBJECT(btn_set_base_0_degree), "clicked", G_CALLBACK(set_base_0_degree_button_func), NULL);
      	g_signal_connect(G_OBJECT(btn_set_base_90_degree), "clicked", G_CALLBACK(set_base_90_degree_button_func), NULL);
      	g_signal_connect(G_OBJECT( btn_increment_shoulder_pulse_width), "clicked", G_CALLBACK( increment_shoulder_pulse_width_button_func), NULL);
      	g_signal_connect(G_OBJECT( btn_decrement_shoulder_pulse_width), "clicked", G_CALLBACK( decrement_shoulder_pulse_width_button_func), NULL);
      	g_signal_connect(G_OBJECT(btn_set_shoulder_0_degree), "clicked", G_CALLBACK(set_shoulder_0_degree_button_func), NULL);
      	g_signal_connect(G_OBJECT(btn_set_shoulder_90_degree), "clicked", G_CALLBACK(set_shoulder_90_degree_button_func), NULL);
      	g_signal_connect(G_OBJECT( btn_increment_elbow_pulse_width), "clicked", G_CALLBACK( increment_elbow_pulse_width_button_func), NULL);
      	g_signal_connect(G_OBJECT( btn_decrement_elbow_pulse_width), "clicked", G_CALLBACK( decrement_elbow_pulse_width_button_func), NULL);
      	g_signal_connect(G_OBJECT(btn_set_elbow_0_degree), "clicked", G_CALLBACK(set_elbow_0_degree_button_func), NULL);
      	g_signal_connect(G_OBJECT(btn_set_elbow_90_degree), "clicked", G_CALLBACK(set_elbow_90_degree_button_func), NULL);

	g_timeout_add(100, timeout_callback, NULL);
}

static gboolean timeout_callback(gpointer none)
{
	char temp[10];

	sprintf (temp, "%.2f°", static_robot_arm->servos[BASE_SERVO].angle_radian * (180.0 / M_PI));
 	gtk_label_set_text(GTK_LABEL(lbl_base_angle), temp);
	sprintf (temp, "%.2f°", static_robot_arm->servos[SHOULDER_SERVO].angle_radian * (180.0 / M_PI));
 	gtk_label_set_text(GTK_LABEL(lbl_shoulder_angle), temp);
	sprintf (temp, "%.2f°", static_robot_arm->servos[ELBOW_SERVO].angle_radian * (180.0 / M_PI));
 	gtk_label_set_text(GTK_LABEL(lbl_elbow_angle), temp);

	return TRUE;
} 

static void submit_pulse_width_button_func(void)
{
	unsigned short int base_pw, shoulder_pw, elbow_pw;
	
	base_pw = (unsigned short int)atof(gtk_entry_get_text(GTK_ENTRY(entry_base_pulse_width)));
	shoulder_pw = (unsigned short int)atof(gtk_entry_get_text(GTK_ENTRY(entry_shoulder_pulse_width)));
	elbow_pw = (unsigned short int)atof(gtk_entry_get_text(GTK_ENTRY(entry_elbow_pulse_width)));

	if (base_pw >= 2000)
		return (void)print_message(ERROR_MSG ,"ArmControl", "Gui", "submit_pulse_width_button_func", "base_pw >= 25000.");
	if (base_pw <= 500)
		return (void)print_message(ERROR_MSG ,"ArmControl", "Gui", "submit_pulse_width_button_func", "base_pw <= 5000.");
	if (shoulder_pw >= 2000)
		return (void)print_message(ERROR_MSG ,"ArmControl", "Gui", "submit_pulse_width_button_func", "shoulder_pw >= 25000.");
	if (shoulder_pw <= 500)
		return (void)print_message(ERROR_MSG ,"ArmControl", "Gui", "submit_pulse_width_button_func", "shoulder_pw <= 5000.");
	if (elbow_pw >= 2000)
		return (void)print_message(ERROR_MSG ,"ArmControl", "Gui", "submit_pulse_width_button_func", "elbow_pw >= 25000.");
	if (elbow_pw <= 500)
		return (void)print_message(ERROR_MSG ,"ArmControl", "Gui", "submit_pulse_width_button_func", "elbow_pw <= 5000.");
	
	static_robot_arm->servos[BASE_SERVO].pulse_command.pulse_width = (unsigned short int)65536 - (unsigned short int)((9216/10000.0)*10*base_pw);
	static_robot_arm->servos[SHOULDER_SERVO].pulse_command.pulse_width = (unsigned short int)65536 - (unsigned short int)((9216/10000.0)*10*shoulder_pw);
	static_robot_arm->servos[ELBOW_SERVO].pulse_command.pulse_width = (unsigned short int)65536 - (unsigned short int)((9216/10000.0)*10*elbow_pw);

	return;
}

static void increment_base_pulse_width_button_func(void)
{	
	unsigned short int base_pw, shoulder_pw, elbow_pw, change;
	char temp [50];
	base_pw = (unsigned short int)atof(gtk_entry_get_text(GTK_ENTRY(entry_base_pulse_width)));
	shoulder_pw = (unsigned short int)atof(gtk_entry_get_text(GTK_ENTRY(entry_shoulder_pulse_width)));
	elbow_pw = (unsigned short int)atof(gtk_entry_get_text(GTK_ENTRY(entry_elbow_pulse_width)));
	change = (unsigned short int)atof(gtk_entry_get_text(GTK_ENTRY(entry_base_pulse_width_change)));

	base_pw = base_pw + change;
	static_robot_arm->servos[BASE_SERVO].pulse_command.pulse_width = (unsigned short int)65536 - (unsigned short int)((9216/10000.0)*10*base_pw);	
	sprintf (temp, "%u", base_pw);
	gtk_entry_set_text(GTK_ENTRY(entry_base_pulse_width), temp);
}
static void decrement_base_pulse_width_button_func(void)
{
	unsigned short int base_pw, shoulder_pw, elbow_pw, change;
	char temp [50];
	base_pw = (unsigned short int)atof(gtk_entry_get_text(GTK_ENTRY(entry_base_pulse_width)));
	shoulder_pw = (unsigned short int)atof(gtk_entry_get_text(GTK_ENTRY(entry_shoulder_pulse_width)));
	elbow_pw = (unsigned short int)atof(gtk_entry_get_text(GTK_ENTRY(entry_elbow_pulse_width)));
	change = (unsigned short int)atof(gtk_entry_get_text(GTK_ENTRY(entry_base_pulse_width_change)));

	base_pw = base_pw - change;
	static_robot_arm->servos[BASE_SERVO].pulse_command.pulse_width = (unsigned short int)65536 - (unsigned short int)((9216/10000.0)*10*base_pw);	
	sprintf (temp, "%u", base_pw);
	gtk_entry_set_text(GTK_ENTRY(entry_base_pulse_width), temp);
}
static void set_base_0_degree_button_func(void)
{
	char temp[20];
	static_robot_arm->servos[BASE_SERVO].position_0_degree = static_robot_arm->servos[BASE_SERVO].position.position;
	if (static_robot_arm->servos[BASE_SERVO].position_90_degree == 0)
		static_robot_arm->servos[BASE_SERVO].position_90_degree = static_robot_arm->servos[BASE_SERVO].position_0_degree;

	static_robot_arm->servos[BASE_SERVO].radian_per_pos_quanta = M_PI_2 / (static_robot_arm->servos[BASE_SERVO].position_90_degree - static_robot_arm->servos[BASE_SERVO].position_0_degree);
	sprintf (temp, "%u", static_robot_arm->servos[BASE_SERVO].position_0_degree); 
 	gtk_label_set_text(GTK_LABEL(lbl_base_0_degree_quanta), temp);
	sprintf (temp, "%.2f°", static_robot_arm->servos[BASE_SERVO].radian_per_pos_quanta * (180.0 / M_PI) ); 
 	gtk_label_set_text(GTK_LABEL(lbl_base_degree_per_pos_quanta), temp);

}
static void set_base_90_degree_button_func(void)
{
	char temp[20];
	static_robot_arm->servos[BASE_SERVO].position_90_degree = static_robot_arm->servos[BASE_SERVO].position.position;
	if (static_robot_arm->servos[BASE_SERVO].position_0_degree == 0)
		static_robot_arm->servos[BASE_SERVO].position_0_degree = static_robot_arm->servos[BASE_SERVO].position_90_degree;
	
	static_robot_arm->servos[BASE_SERVO].radian_per_pos_quanta = M_PI_2 / (static_robot_arm->servos[BASE_SERVO].position_90_degree - static_robot_arm->servos[BASE_SERVO].position_0_degree);
	sprintf (temp, "%u", static_robot_arm->servos[BASE_SERVO].position_90_degree); 
 	gtk_label_set_text(GTK_LABEL(lbl_base_90_degree_quanta), temp);
	sprintf (temp, "%.2f°", static_robot_arm->servos[BASE_SERVO].radian_per_pos_quanta * (180.0 / M_PI) ); 
 	gtk_label_set_text(GTK_LABEL(lbl_base_degree_per_pos_quanta), temp);
}
static void increment_shoulder_pulse_width_button_func(void)
{
	unsigned short int base_pw, shoulder_pw, elbow_pw, change;
	char temp [50];
	base_pw = (unsigned short int)atof(gtk_entry_get_text(GTK_ENTRY(entry_base_pulse_width)));
	shoulder_pw = (unsigned short int)atof(gtk_entry_get_text(GTK_ENTRY(entry_shoulder_pulse_width)));
	elbow_pw = (unsigned short int)atof(gtk_entry_get_text(GTK_ENTRY(entry_elbow_pulse_width)));
	change = (unsigned short int)atof(gtk_entry_get_text(GTK_ENTRY(entry_shoulder_pulse_width_change)));

	shoulder_pw = shoulder_pw + change;
	static_robot_arm->servos[SHOULDER_SERVO].pulse_command.pulse_width = (unsigned short int)65536 - (unsigned short int)((9216/10000.0)*10*shoulder_pw);	
	sprintf (temp, "%u", shoulder_pw);
	gtk_entry_set_text(GTK_ENTRY(entry_shoulder_pulse_width), temp);
}
static void decrement_shoulder_pulse_width_button_func(void)
{
	unsigned short int base_pw, shoulder_pw, elbow_pw, change;
	char temp [50];
	base_pw = (unsigned short int)atof(gtk_entry_get_text(GTK_ENTRY(entry_base_pulse_width)));
	shoulder_pw = (unsigned short int)atof(gtk_entry_get_text(GTK_ENTRY(entry_shoulder_pulse_width)));
	elbow_pw = (unsigned short int)atof(gtk_entry_get_text(GTK_ENTRY(entry_elbow_pulse_width)));
	change = (unsigned short int)atof(gtk_entry_get_text(GTK_ENTRY(entry_shoulder_pulse_width_change)));

	shoulder_pw = shoulder_pw - change;
	static_robot_arm->servos[SHOULDER_SERVO].pulse_command.pulse_width = (unsigned short int)65536 - (unsigned short int)((9216/10000.0)*10*shoulder_pw);	
	sprintf (temp, "%u", shoulder_pw);
	gtk_entry_set_text(GTK_ENTRY(entry_shoulder_pulse_width), temp);
}
static void set_shoulder_0_degree_button_func(void)
{
	char temp[20];
	static_robot_arm->servos[SHOULDER_SERVO].position_0_degree = static_robot_arm->servos[SHOULDER_SERVO].position.position;
	if (static_robot_arm->servos[SHOULDER_SERVO].position_90_degree == 0)
		static_robot_arm->servos[SHOULDER_SERVO].position_90_degree = static_robot_arm->servos[SHOULDER_SERVO].position_0_degree;

	static_robot_arm->servos[SHOULDER_SERVO].radian_per_pos_quanta = M_PI_2 / (static_robot_arm->servos[SHOULDER_SERVO].position_90_degree - static_robot_arm->servos[SHOULDER_SERVO].position_0_degree);	
	sprintf (temp, "%u", static_robot_arm->servos[SHOULDER_SERVO].position_0_degree); 
 	gtk_label_set_text(GTK_LABEL(lbl_shoulder_0_degree_quanta), temp);
	sprintf (temp, "%.2f°", static_robot_arm->servos[SHOULDER_SERVO].radian_per_pos_quanta * (180.0 / M_PI) ); 
 	gtk_label_set_text(GTK_LABEL(lbl_shoulder_degree_per_pos_quanta), temp);
}
static void set_shoulder_90_degree_button_func(void)
{
	char temp[20];
	static_robot_arm->servos[SHOULDER_SERVO].position_90_degree = static_robot_arm->servos[SHOULDER_SERVO].position.position;
	if (static_robot_arm->servos[SHOULDER_SERVO].position_0_degree == 0)
		static_robot_arm->servos[SHOULDER_SERVO].position_0_degree = static_robot_arm->servos[SHOULDER_SERVO].position_90_degree;

	static_robot_arm->servos[SHOULDER_SERVO].radian_per_pos_quanta = M_PI_2 / (static_robot_arm->servos[SHOULDER_SERVO].position_90_degree - static_robot_arm->servos[SHOULDER_SERVO].position_0_degree);	
	sprintf (temp, "%u", static_robot_arm->servos[SHOULDER_SERVO].position_90_degree); 
 	gtk_label_set_text(GTK_LABEL(lbl_shoulder_90_degree_quanta), temp);
	sprintf (temp, "%.2f°", static_robot_arm->servos[SHOULDER_SERVO].radian_per_pos_quanta * (180.0 / M_PI) ); 
 	gtk_label_set_text(GTK_LABEL(lbl_shoulder_degree_per_pos_quanta), temp);
}
static void increment_elbow_pulse_width_button_func(void)
{
	unsigned short int base_pw, shoulder_pw, elbow_pw, change;
	char temp [50];
	base_pw = (unsigned short int)atof(gtk_entry_get_text(GTK_ENTRY(entry_base_pulse_width)));
	shoulder_pw = (unsigned short int)atof(gtk_entry_get_text(GTK_ENTRY(entry_shoulder_pulse_width)));
	elbow_pw = (unsigned short int)atof(gtk_entry_get_text(GTK_ENTRY(entry_elbow_pulse_width)));
	change = (unsigned short int)atof(gtk_entry_get_text(GTK_ENTRY(entry_elbow_pulse_width_change)));

	elbow_pw = elbow_pw + change;
	static_robot_arm->servos[ELBOW_SERVO].pulse_command.pulse_width = (unsigned short int)65536 - (unsigned short int)((9216/10000.0)*10*elbow_pw);	
	sprintf (temp, "%u", elbow_pw);
	gtk_entry_set_text(GTK_ENTRY(entry_elbow_pulse_width), temp);
}
static void decrement_elbow_pulse_width_button_func(void)
{
	unsigned short int base_pw, shoulder_pw, elbow_pw, change;
	char temp [50];
	base_pw = (unsigned short int)atof(gtk_entry_get_text(GTK_ENTRY(entry_base_pulse_width)));
	shoulder_pw = (unsigned short int)atof(gtk_entry_get_text(GTK_ENTRY(entry_shoulder_pulse_width)));
	elbow_pw = (unsigned short int)atof(gtk_entry_get_text(GTK_ENTRY(entry_elbow_pulse_width)));
	change = (unsigned short int)atof(gtk_entry_get_text(GTK_ENTRY(entry_elbow_pulse_width_change)));

	elbow_pw = elbow_pw - change;
	static_robot_arm->servos[ELBOW_SERVO].pulse_command.pulse_width = (unsigned short int)65536 - (unsigned short int)((9216/10000.0)*10*elbow_pw);	
	sprintf (temp, "%u", elbow_pw);
	gtk_entry_set_text(GTK_ENTRY(entry_elbow_pulse_width), temp);
}
static void set_elbow_0_degree_button_func(void)
{
	char temp[20];
	static_robot_arm->servos[ELBOW_SERVO].position_0_degree = static_robot_arm->servos[ELBOW_SERVO].position.position;
	if (static_robot_arm->servos[ELBOW_SERVO].position_90_degree == 0)
		static_robot_arm->servos[ELBOW_SERVO].position_90_degree = static_robot_arm->servos[ELBOW_SERVO].position_0_degree;

	static_robot_arm->servos[ELBOW_SERVO].radian_per_pos_quanta = M_PI_2 / (static_robot_arm->servos[ELBOW_SERVO].position_90_degree - static_robot_arm->servos[ELBOW_SERVO].position_0_degree);		
	sprintf (temp, "%u", static_robot_arm->servos[ELBOW_SERVO].position_0_degree); 
 	gtk_label_set_text(GTK_LABEL(lbl_elbow_0_degree_quanta), temp);
	sprintf (temp, "%.2f°", static_robot_arm->servos[ELBOW_SERVO].radian_per_pos_quanta * (180.0 / M_PI) ); 
 	gtk_label_set_text(GTK_LABEL(lbl_elbow_degree_per_pos_quanta), temp);
}
static void set_elbow_90_degree_button_func(void)
{
	char temp[20];
	static_robot_arm->servos[ELBOW_SERVO].position_90_degree = static_robot_arm->servos[ELBOW_SERVO].position.position;
	if (static_robot_arm->servos[ELBOW_SERVO].position_0_degree == 0)
		static_robot_arm->servos[ELBOW_SERVO].position_0_degree = static_robot_arm->servos[ELBOW_SERVO].position_90_degree;

	static_robot_arm->servos[ELBOW_SERVO].radian_per_pos_quanta = M_PI_2 / (static_robot_arm->servos[ELBOW_SERVO].position_90_degree - static_robot_arm->servos[ELBOW_SERVO].position_0_degree);		
	sprintf (temp, "%u", static_robot_arm->servos[ELBOW_SERVO].position_90_degree); 
 	gtk_label_set_text(GTK_LABEL(lbl_elbow_90_degree_quanta), temp);
	sprintf (temp, "%.2f°", static_robot_arm->servos[ELBOW_SERVO].radian_per_pos_quanta * (180.0 / M_PI) ); 
 	gtk_label_set_text(GTK_LABEL(lbl_elbow_degree_per_pos_quanta), temp);
}
