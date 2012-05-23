#include "FirstBMICageInterfacer.h"



int main( int argc, char *argv[])
{
	RtTasksData *rt_tasks_data = NULL;

   	rt_tasks_data = rtai_malloc(nam2num(RT_TASKS_DATA_SHM_NAME), 0);
	if (rt_tasks_data == NULL) 
		return print_message(ERROR_MSG ,"FirstBMICageManager", "FirstBMICageManager", "main", "rt_tasks_data == NULL.");

	if (! enable_rs232_com1_9600_baud()) 
		return print_message(ERROR_MSG ,"BMIExpController", "FirstBMICageManager", "main", "! enable_rs232_com1_9600_baud().");

	if(! create_cage_interfacer_rt_thread(rt_tasks_data))
		return print_message(ERROR_MSG ,"BMIExpController", "FirstBMICageManager", "main", "create_cage_interfacer_rt_thread().");
	gtk_init(&argc, &argv);
	create_gui_handler(rt_tasks_data);
	gtk_main();
	return 0;
}	
