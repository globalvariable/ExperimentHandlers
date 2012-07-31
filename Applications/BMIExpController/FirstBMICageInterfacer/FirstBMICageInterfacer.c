#include "FirstBMICageInterfacer.h"



int main( int argc, char *argv[])
{
	RtTasksData *rt_tasks_data = NULL;
	RS232Data *rs_232_data = NULL;
   	rt_tasks_data = rtai_malloc(nam2num(RT_TASKS_DATA_SHM_NAME), 0);
	if (rt_tasks_data == NULL) 
		return print_message(ERROR_MSG ,"FirstBMICageManager", "FirstBMICageManager", "main", "rt_tasks_data == NULL.");

	if (! enable_rs232_com1_9600_baud()) 
		return print_message(ERROR_MSG ,"BMIExpController", "FirstBMICageManager", "main", "! enable_rs232_com1_9600_baud().");

	rs_232_data = allocate_rs232_data(rs_232_data);
	if (! add_component_to_rs232_data(rs_232_data, 12000000, 8000000))   // 12 ms for TX, 10 ms for RX which is set by TX timeout.  // 4800 baud rate sends 5 byte data in 1 ms. So 5 ms seems secure. This leads 5 ms jittter in sending commands to motor controller. i.e. MovObjHandler sends every 100 ms, motor controller receives it every 100+-5 ms
		return print_message(ERROR_MSG ,"BMIExpController", "FirstBMICageManager", "main", "! add_component_to_rs232_data().");
	if(! create_cage_interfacer_rt_thread(rt_tasks_data, rs_232_data))
		return print_message(ERROR_MSG ,"BMIExpController", "FirstBMICageManager", "main", "create_cage_interfacer_rt_thread().");
	gtk_init(&argc, &argv);
	create_gui_handler(rt_tasks_data);
	gtk_main();
	return 0;
}	
