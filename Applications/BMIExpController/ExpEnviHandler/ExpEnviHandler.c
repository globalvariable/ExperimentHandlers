#include "ExpEnviHandler.h"



int main( int argc, char *argv[])
{
	Gui2ExpEnviHandMsg *msgs_gui_2_exp_envi_hand = NULL;    
   	shared_memory = (SharedMemStruct*)rtai_malloc(nam2num(SHARED_MEM_NAME), SHARED_MEM_SIZE);
	if (shared_memory == NULL) 
		return print_message(ERROR_MSG ,"BMIExpController", "MovObjHandler", "main", "shared_memory == NULL.");

	msgs_gui_2_exp_envi_hand = allocate_gui_2_exp_envi_hand_msg_buffer(msgs_gui_2_exp_envi_hand);

	if(! create_exp_envi_handler_rt_thread(msgs_gui_2_exp_envi_hand))
		return print_message(ERROR_MSG ,"BMIExpController", "ExpEnviHandler", "main", "create_exp_envi_handler_rt_thread().");
	gtk_init(&argc, &argv);
	create_gui_handler(msgs_gui_2_exp_envi_hand);
	gtk_main();
	return 0;
}	
