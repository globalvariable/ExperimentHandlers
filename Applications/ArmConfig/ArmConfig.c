#include "ArmConfig.h"

static ThreeDofRobot 	*robot_arm = NULL;

static SEM *exp_envi_rx_buff_sem = NULL;
static SEM *exp_envi_tx_buff_sem = NULL;
static unsigned char *exp_envi_rx_buff = NULL;
static unsigned char *exp_envi_tx_buff = NULL;

int main( int argc, char *argv[])
{
	RtTasksData *rt_tasks_data = NULL;
	ServoPosition position_0_degree, position_90_degree;
	ServoPulse pulse_width_0_degree, pulse_width_90_degree;
	ServoPulse init_pulse;
   	rt_tasks_data = rtai_malloc(nam2num(RT_TASKS_DATA_SHM_NAME), 0);
	if (rt_tasks_data == NULL) 
		return print_message(ERROR_MSG ,"ArmConfig", "ArmConfig", "main", "rt_tasks_data == NULL.");
	robot_arm = g_new0(ThreeDofRobot, 1);
	submit_arm_length_vals(robot_arm, 14.60, 18.7, 1.1);
	submit_arm_security_limits(robot_arm, -19.0, 14.0, -20.0, 20.0, 2.0, 35.0);

	if (! init_rs232_com1(115200))
 		return print_message(ERROR_MSG ,"ArmConfig", "ArmConfig", "main", "! init_rs232_com1().");	
	if (! init_exp_envi_rx_buffer_semaphore(&exp_envi_rx_buff_sem))
		return print_message(ERROR_MSG ,"ArmConfig", "ArmConfig", "main", "! init_exp_envi_rx_buffer_semaphore().");	
	if (! init_exp_envi_tx_buffer_semaphore(&exp_envi_tx_buff_sem))
		return print_message(ERROR_MSG ,"ArmConfig", "ArmConfig", "main", "! init_exp_envi_tx_buffer_semaphore().");	
	if (! init_exp_envi_tx_buffer_shm(&exp_envi_tx_buff, EXP_ENVI_CMD_MSG_LEN) )
		return print_message(ERROR_MSG ,"ArmConfig", "ArmConfig", "main", "! init_exp_envi_tx_buffer_shm().");	
	if (! init_exp_envi_rx_buffer_shm(&exp_envi_rx_buff, EXP_ENVI_STATUS_MSG_LEN) )
		return print_message(ERROR_MSG ,"ArmConfig", "ArmConfig", "main", "! init_exp_envi_rx_buffer_shm().");	

	init_pulse.pulse_width = 1430;
	write_servo_pw_val(&(robot_arm->servos[BASE_SERVO]), init_pulse);
	init_pulse.pulse_width = 1600;
	write_servo_pw_val(&(robot_arm->servos[SHOULDER_SERVO]), init_pulse);
	init_pulse.pulse_width = 1600;
	write_servo_pw_val(&(robot_arm->servos[ELBOW_SERVO]), init_pulse);

	pulse_width_0_degree.pulse_width = 879;
	pulse_width_90_degree.pulse_width = 1430;
	position_0_degree.position = 358;
	position_90_degree.position = 615;
	write_servo_pw_adc_ranges(&(robot_arm->servos[BASE_SERVO]), pulse_width_0_degree, pulse_width_90_degree, position_0_degree, position_90_degree);

	pulse_width_0_degree.pulse_width = 956;
	pulse_width_90_degree.pulse_width = 1431;
	position_0_degree.position = 415;
	position_90_degree.position = 654;
	write_servo_pw_adc_ranges(&(robot_arm->servos[SHOULDER_SERVO]), pulse_width_0_degree, pulse_width_90_degree, position_0_degree, position_90_degree);

	pulse_width_0_degree.pulse_width = 904;
	pulse_width_90_degree.pulse_width = 1391;
	position_0_degree.position = 428;
	position_90_degree.position = 666;
	write_servo_pw_adc_ranges(&(robot_arm->servos[ELBOW_SERVO]), pulse_width_0_degree, pulse_width_90_degree, position_0_degree, position_90_degree);


	if(! create_servo_control_rt_thread(rt_tasks_data, exp_envi_rx_buff_sem, exp_envi_tx_buff_sem, exp_envi_rx_buff, exp_envi_tx_buff, robot_arm))
		return print_message(ERROR_MSG ,"ArmConfig", "ArmConfig", "main", "create_servo_control_rt_thread().");

	gtk_init(&argc, &argv);
	create_gui(robot_arm);
	gtk_main();
	return 0;
}	
