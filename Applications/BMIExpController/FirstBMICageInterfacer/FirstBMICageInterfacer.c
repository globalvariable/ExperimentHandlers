#include "FirstBMICageInterfacer.h"



int main( int argc, char *argv[])
{
	Gui2ExpEnviInterfMsg *msgs_gui_2_exp_envi_interf = NULL;    
	Gui2MovObjInterfMsg *msgs_gui_2_mov_obj_interf = NULL;    
   	shared_memory = (SharedMemStruct*)rtai_malloc(nam2num(SHARED_MEM_NAME), SHARED_MEM_SIZE);
	if (shared_memory == NULL) 
		return print_message(ERROR_MSG ,"BMIExpController", "FirstBMICageManager", "main", "shared_memory == NULL.");

	msgs_gui_2_exp_envi_interf = allocate_gui_2_exp_envi_interf_msg_buffer(msgs_gui_2_exp_envi_interf);
	msgs_gui_2_mov_obj_interf = allocate_gui_2_mov_obj_interf_msg_buffer(msgs_gui_2_mov_obj_interf);
	if(! create_cage_interfacer_rt_thread(msgs_gui_2_exp_envi_interf, msgs_gui_2_mov_obj_interf))
		return print_message(ERROR_MSG ,"BMIExpController", "FirstBMICageManager", "main", "create_cage_interfacer_rt_thread().");
	gtk_init(&argc, &argv);
	create_gui_handler(msgs_gui_2_exp_envi_interf, msgs_gui_2_mov_obj_interf);
	gtk_main();
	return 0;
}	
