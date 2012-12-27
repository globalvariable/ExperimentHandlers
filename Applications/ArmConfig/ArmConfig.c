#include "ArmConfig.h"

static ThreeDofRobot 	*robot_arm = NULL;



int main( int argc, char *argv[])
{
	RtTasksData *rt_tasks_data = NULL;
	ServoPosition position_0_degree, position_90_degree;
	ServoPulse pulse_width_0_degree, pulse_width_90_degree;

   	rt_tasks_data = rtai_malloc(SHM_NUM_RT_TASKS_DATA, 0);
	if (rt_tasks_data == NULL) 
		return print_message(ERROR_MSG ,"ArmConfig", "ArmConfig", "main", "rt_tasks_data == NULL.");
	robot_arm = g_new0(ThreeDofRobot, 1);
	init_three_dof_robot_arm(robot_arm);
	submit_arm_length_vals(robot_arm, 14.60, 19.4, 1.1);
	submit_arm_security_limits(robot_arm, -19.0, 14.5, -20.0, 20.0, 3.0, 35.0, M_PI*(1.0/12.0), M_PI*(11.0/12.0));

	init_servo_pulse(&(robot_arm->servos[BASE_SERVO]), 1425);
	init_servo_pulse(&(robot_arm->servos[SHOULDER_SERVO]), 1431);
	init_servo_pulse(&(robot_arm->servos[ELBOW_SERVO]), 1014);

	pulse_width_0_degree = 879;
	pulse_width_90_degree = 1430;
	position_0_degree = 358;
	position_90_degree = 615;
	write_servo_pw_adc_ranges(&(robot_arm->servos[BASE_SERVO]), pulse_width_0_degree, pulse_width_90_degree, position_0_degree, position_90_degree);

	pulse_width_0_degree = 956;
	pulse_width_90_degree = 1431;
	position_0_degree = 415;
	position_90_degree = 654;
	write_servo_pw_adc_ranges(&(robot_arm->servos[SHOULDER_SERVO]), pulse_width_0_degree, pulse_width_90_degree, position_0_degree, position_90_degree);

	pulse_width_0_degree = 904;
	pulse_width_90_degree = 1391;
	position_0_degree = 428;
	position_90_degree = 666;
	write_servo_pw_adc_ranges(&(robot_arm->servos[ELBOW_SERVO]), pulse_width_0_degree, pulse_width_90_degree, position_0_degree, position_90_degree);

	if (! init_rs232_com1(115200))
 		return print_message(ERROR_MSG ,"ArmConfig", "ArmConfig", "main", "! init_rs232_com1().");	

	if(! create_servo_control_rt_thread(rt_tasks_data, robot_arm))
		return print_message(ERROR_MSG ,"ArmConfig", "ArmConfig", "main", "create_servo_control_rt_thread().");

	gtk_init(&argc, &argv);
	create_gui(robot_arm);
	gtk_main();
	return 0;
}	
