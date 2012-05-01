#include "MovObjHandler.h"



int main( int argc, char *argv[])
{
	Gui2MovObjHandMsg *msgs_gui_2_mov_obj_hand = NULL;    
   	shared_memory = (SharedMemStruct*)rtai_malloc(nam2num(SHARED_MEM_NAME), SHARED_MEM_SIZE);
	if (shared_memory == NULL) 
		return print_message(ERROR_MSG ,"BMIExpController", "MovObjHandler", "main", "shared_memory == NULL.");

	msgs_gui_2_mov_obj_hand = allocate_gui_2_mov_obj_hand_msg_buffer(msgs_gui_2_mov_obj_hand);

	if(! create_mov_obj_handler_rt_thread(msgs_gui_2_mov_obj_hand))
		return print_message(ERROR_MSG ,"BMIExpController", "MovObjHandler", "main", "create_mov_obj_handler_rt_thread().");
	gtk_init(&argc, &argv);
	create_gui_handler(msgs_gui_2_mov_obj_hand);
	gtk_main();
	return 0;
}	
