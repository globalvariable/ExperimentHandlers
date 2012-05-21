#include "FirstBMICageInterfacer.h"



int main( int argc, char *argv[])
{
   	shared_memory = (SharedMemStruct*)rtai_malloc(nam2num(SHARED_MEM_NAME), SHARED_MEM_SIZE);
	if (shared_memory == NULL) 
		return print_message(ERROR_MSG ,"BMIExpController", "FirstBMICageManager", "main", "shared_memory == NULL.");

	if (! enable_rs232_com1_9600_baud()) 
		return print_message(ERROR_MSG ,"BMIExpController", "FirstBMICageManager", "main", "! enable_rs232_com1_9600_baud().");

	if(! create_cage_interfacer_rt_thread())
		return print_message(ERROR_MSG ,"BMIExpController", "FirstBMICageManager", "main", "create_cage_interfacer_rt_thread().");
	gtk_init(&argc, &argv);
	create_gui_handler();
	gtk_main();
	return 0;
}	
