#include "ResetExpEnviMovObjRS232.h"


int main( int argc, char *argv[])
{
	int i;
	if (! init_rs232_com1(115200, TRUE))
		print_message(ERROR_MSG ,"ResetRS232", "ResetRS232", "main", "! init_rs232_com1().");
	if (! init_exp_envi_mov_obj_rs232_com1_shm())
		print_message(ERROR_MSG ,"ResetRS232", "ResetRS232", "main", "! init_exp_envi_mov_obj_rs232_com1_shm().");
	printf("Press any key to exit.\n");

	scanf("%d",&i);

	return 0;
}
