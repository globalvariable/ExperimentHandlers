#include "BMIExpController.h"


int main( int argc, char *argv[])
{
   	shared_memory = (SharedMemStruct*)rtai_malloc(nam2num(SHARED_MEM_NAME), SHARED_MEM_SIZE);
	if (shared_memory == NULL) {
		print_message(ERROR_MSG ,"BMISimulationTrialController", "BMISimulationTrialController", "main", "shared_memory == NULL.");	return -1; }
	gtk_init(&argc, &argv);
	create_gui();
	gtk_main();
	return 0;
}	


