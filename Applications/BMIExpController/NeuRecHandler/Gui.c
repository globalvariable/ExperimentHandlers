#include "Gui.h"


static GtkWidget *btn_select_directory_to_save;
static GtkWidget *btn_create_recording_folder;

static void create_recording_folder_button_func (void);

static void set_directory_btn_select_directory_to_save(void);


void create_gui_handler(GtkWidget *arg_btn_select_directory_to_save)
{
	GtkWidget *window, *hbox, *vbox, *table;

 	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  	gtk_window_set_default_size(GTK_WINDOW(window), 1000, 1000);
  	gtk_window_set_title(GTK_WINDOW(window), "BMIExpController - NeuRecHandler");
  	gtk_window_set_deletable(GTK_WINDOW(window), FALSE);
  	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
  	gtk_container_set_border_width(GTK_CONTAINER(window), 10);

  	vbox = gtk_vbox_new(TRUE, 0);
	gtk_container_add(GTK_CONTAINER(window), vbox);

	hbox = gtk_hbox_new(TRUE, 0);
	gtk_box_pack_start(GTK_BOX(vbox),hbox, TRUE,TRUE,0);

	table = gtk_table_new(2 ,3,TRUE);   // 2 rows 3 columns
	gtk_box_pack_start(GTK_BOX(hbox),table, TRUE,TRUE,0);

	vbox = gtk_vbox_new(FALSE, 0);
	gtk_table_attach_defaults(GTK_TABLE(table), vbox, 0,1, 0, 6);  // column 0-1, row 0-6

	hbox = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	////////   LAST COLUMN
	vbox = gtk_vbox_new(FALSE, 0);
	gtk_table_attach_defaults(GTK_TABLE(table), vbox, 2,3, 0, 6);  // column 2-3, row 0-6

	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

   	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE, 0);  	      

	btn_select_directory_to_save = arg_btn_select_directory_to_save;
        gtk_box_pack_start(GTK_BOX(hbox), btn_select_directory_to_save, TRUE,TRUE,0);
	set_directory_btn_select_directory_to_save();

   	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE, 0);  	     

	btn_create_recording_folder = gtk_button_new_with_label("Create Recording Folder");
	gtk_box_pack_start (GTK_BOX (hbox), btn_create_recording_folder, TRUE, TRUE, 0);

        gtk_box_pack_start(GTK_BOX(vbox),gtk_hseparator_new(), FALSE,FALSE, 5);

	g_signal_connect(G_OBJECT(btn_create_recording_folder), "clicked", G_CALLBACK(create_recording_folder_button_func), NULL);

	gtk_widget_show_all(window);
}

static void create_recording_folder_button_func (void)
{
	unsigned int path_len;
	char *path_temp = NULL, *path = NULL;
	path_temp = gtk_file_chooser_get_uri (GTK_FILE_CHOOSER (btn_select_directory_to_save));
	path = &path_temp[7];   // since     uri returns file:///home/....	
	path_len = strlen(path_temp);
	if (strcmp(&(path_temp[path_len-8]),"EXP_DATA") == 0)
		return (void)print_message(ERROR_MSG ,"NeuRecHandler", "Gui", "create_recording_folder_button_func", "Selected folder is /EXP_DATA main folder. Select a folder inside this folder.");				
	if ((*create_main_directory[MAX_NUMBER_OF_DATA_FORMAT_VER-1])(1, path))		// record in last format version
	{
		
	}
	else
		print_message(ERROR_MSG ,"NeuRecHandler", "Gui", "create_recording_folder_button_func", " *create_main_directory().");			
}


static void set_directory_btn_select_directory_to_save(void)
{
	char line[600];
	FILE *fp = NULL;
       	if ((fp = fopen("./path_initial_directory", "r")) == NULL)  
       	{ 
		print_message(ERROR_MSG ,"NeuRecHandler", "Gui", "set_directory_btn_select_directory_to_save", "Couldn't find file: ./path_initial_directory.");
		print_message(ERROR_MSG ,"NeuRecHandler", "Gui", "set_directory_btn_select_directory_to_save", "/home is loaded as initial direcoty to create data folder.");
		gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER (btn_select_directory_to_save),"/home");
       	}
       	else
       	{
		if (fgets(line, sizeof line, fp ) == NULL) 
		{ 
			print_message(ERROR_MSG ,"NeuRecHandler", "Gui", "set_directory_btn_select_directory_to_save", "Couldn' t read ./path_initial_directory.");
			print_message(ERROR_MSG ,"NeuRecHandler", "Gui", "set_directory_btn_select_directory_to_save", "/home is loaded as initial direcoty to create data folder.");
			gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER (btn_select_directory_to_save),"/home");
		}
		else
		{
			line[strlen(line)-16] = 0;   
			gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER (btn_select_directory_to_save),line);
		}
		fclose(fp); 		
	}  	 
}

