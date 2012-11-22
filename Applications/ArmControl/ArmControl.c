#include "ArmControl.h"

static ThreeDofRobot 	*robot_arm = NULL;

static SEM *exp_envi_rx_buff_sem = NULL;
static SEM *exp_envi_tx_buff_sem = NULL;
static unsigned char *exp_envi_rx_buff = NULL;
static unsigned char *exp_envi_tx_buff = NULL;

int main( int argc, char *argv[])
{
	RtTasksData *rt_tasks_data = NULL;
   	rt_tasks_data = rtai_malloc(nam2num(RT_TASKS_DATA_SHM_NAME), 0);
	if (rt_tasks_data == NULL) 
		return print_message(ERROR_MSG ,"FirstBMICageManager", "FirstBMICageManager", "main", "rt_tasks_data == NULL.");
	robot_arm = g_new0(ThreeDofRobot, 1);
	submit_arm_length_vals(robot_arm, 14.50, 23.9);
	robot_arm->servos[BASE_SERVO].pulse_command.pulse_width = 65535 - BASE_SERVO_INIT_PULSE;
	robot_arm->servos[SHOULDER_SERVO].pulse_command.pulse_width = 65535 - SHOULDER_SERVO_INIT_PULSE;
	robot_arm->servos[ELBOW_SERVO].pulse_command.pulse_width = 65535 - ELBOW_SERVO_INIT_PULSE;
	if (! init_rs232_com1(115200))
 		return print_message(ERROR_MSG ,"ServoControl", "ServoControl", "main", "! init_rs232_com1().");	
	if (! init_exp_envi_rx_buffer_semaphore(&exp_envi_rx_buff_sem))
		return print_message(ERROR_MSG ,"ServoControl", "ServoControl", "main", "! init_exp_envi_rx_buffer_semaphore().");	
	if (! init_exp_envi_tx_buffer_semaphore(&exp_envi_tx_buff_sem))
		return print_message(ERROR_MSG ,"ServoControl", "ServoControl", "main", "! init_exp_envi_tx_buffer_semaphore().");	
	if (! init_exp_envi_tx_buffer_shm(&exp_envi_tx_buff, EXP_ENVI_CMD_MSG_LEN) )
		return print_message(ERROR_MSG ,"ServoControl", "ServoControl", "main", "! init_exp_envi_tx_buffer_shm().");	
	if (! init_exp_envi_rx_buffer_shm(&exp_envi_rx_buff, EXP_ENVI_STATUS_MSG_LEN) )
		return print_message(ERROR_MSG ,"ServoControl", "ServoControl", "main", "! init_exp_envi_rx_buffer_shm().");	

	if(! create_servo_control_rt_thread(rt_tasks_data, exp_envi_rx_buff_sem, exp_envi_tx_buff_sem, exp_envi_rx_buff, exp_envi_tx_buff, robot_arm))
		return print_message(ERROR_MSG ,"ServoControl", "ServoControl", "main", "create_servo_control_rt_thread().");

	gtk_init(&argc, &argv);
	create_gui(robot_arm);
	gtk_main();
	return 0;
}	
