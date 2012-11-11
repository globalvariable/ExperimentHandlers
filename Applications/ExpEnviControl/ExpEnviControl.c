#include "ExpEnviControl.h"

static SEM *exp_envi_rx_buff_sem = NULL;
static SEM *exp_envi_tx_buff_sem = NULL;
static unsigned char *exp_envi_rx_buff = NULL;
static unsigned char *exp_envi_tx_buff = NULL;

int main( int argc, char *argv[])
{
	RtTasksData *rt_tasks_data = NULL;
   	rt_tasks_data = rtai_malloc(nam2num(RT_TASKS_DATA_SHM_NAME), 0);
	if (rt_tasks_data == NULL) 
		return print_message(ERROR_MSG ,"ExpEnviControl", "ExpEnviControl", "main", "rt_tasks_data == NULL.");

	if (! bind_to_exp_envi_rx_buffer_semaphore(&exp_envi_rx_buff_sem))
		return print_message(ERROR_MSG ,"ExpEnviControl", "ExpEnviControl", "main", "! bind_to_exp_envi_rx_buffer_semaphore().");	
	if (! bind_to_exp_envi_tx_buffer_semaphore(&exp_envi_tx_buff_sem))
		return print_message(ERROR_MSG ,"ExpEnviControl", "ExpEnviControl", "main", "! bind_to_exp_envi_tx_buffer_semaphore().");	
	if (! bind_to_exp_envi_tx_buffer_shm(&exp_envi_tx_buff) )
		return print_message(ERROR_MSG ,"ExpEnviControl", "ExpEnviControl", "main", "! bind_to_exp_envi_tx_buffer_shm().");	
	if (! bind_to_exp_envi_rx_buffer_shm(&exp_envi_rx_buff) )
		return print_message(ERROR_MSG ,"ExpEnviControl", "ExpEnviControl", "main", "! bind_to_exp_envi_rx_buffer_shm().");	

	if(! create_exp_envi_control_rt_thread(rt_tasks_data, exp_envi_rx_buff_sem, exp_envi_tx_buff_sem, exp_envi_rx_buff, exp_envi_tx_buff))
		return print_message(ERROR_MSG ,"ExpEnviControl", "ExpEnviControl", "main", "create_exp_envi_control_rt_thread().");

	gtk_init(&argc, &argv);
	create_gui();
	gtk_main();
	return 0;
}	
