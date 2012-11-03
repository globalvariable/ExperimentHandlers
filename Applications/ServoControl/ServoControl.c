#include "ServoControl.h"


int main( int argc, char *argv[])
{
	RtTasksData *rt_tasks_data = NULL;
   	rt_tasks_data = rtai_malloc(nam2num(RT_TASKS_DATA_SHM_NAME), 0);
	if (rt_tasks_data == NULL) 
		return print_message(ERROR_MSG ,"FirstBMICageManager", "FirstBMICageManager", "main", "rt_tasks_data == NULL.");

	if (NUM_OF_SERVOS>MAX_NUM_OF_SERVOS)  // check for config error
		return print_message(ERROR_MSG ,"FirstBMICageManager", "FirstBMICageManager", "main", "NUM_OF_SERVOS>MAX_NUM_OF_SERVOS.");

	rx_position_len = (2*NUM_OF_SERVOS) ; // Two adc value byte for each servo (2 bytes msg check for 0x00 0x00 is made in lower  read_from_rs232_com1_mov_obj_with_semaphore()
	rx_buffer = g_new0(char, rx_position_len);

	tx_pw_command_len = (2*NUM_OF_SERVOS) + 3; // Two pulse width byte for each servo + 'P' + 2 bytes for 0x02 0x03 check by PIC18F4520
	tx_adc_command_len = 3;    //  'A' + 2 bytes for 0x00 0x01 check by PIC18F4520
	tx_buffer_adc_command = g_new0(char, tx_adc_command_len);
	tx_buffer_pw_command = g_new0(char, tx_pw_command_len);

	servos[BASE_SERVO].pulse_command.pulse_width = 65536 - BASE_SERVO_INIT_PULSE;
	servos[SHOULDER_SERVO].pulse_command.pulse_width = 65536 - SHOULDER_SERVO_INIT_PULSE;
	servos[ELBOW_SERVO].pulse_command.pulse_width = 65536 - ELBOW_SERVO_INIT_PULSE;

	if (! bind_to_rs232_com1_semaphore())
		return print_message(ERROR_MSG ,"ServoControl", "ServoControl", "main", "! bind_to_rs232_com1_semaphore().");	

	if (! bind_to_exp_envi_mov_obj_rs232_com1_shm())
		return print_message(ERROR_MSG ,"ServoControl", "ServoControl", "main", "! bind_to_exp_envi_mov_obj_rs232_com1_shm().");		

	if(! create_servo_control_rt_thread(rt_tasks_data))
		return print_message(ERROR_MSG ,"ServoControl", "ServoControl", "main", "create_servo_control_rt_thread().");

	gtk_init(&argc, &argv);
	create_gui();
	gtk_main();
	return 0;
}	
