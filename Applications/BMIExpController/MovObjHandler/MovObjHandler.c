#include "MovObjHandler.h"

static pthread_t logging_thread;
void *logging_thread_function( void *message_log );

#define BASE_SERVO_0_DEGREE_PULSE		879
#define BASE_SERVO_90_DEGREE_PULSE		1430
#define BASE_SERVO_0_DEGREE_ADC_VAL		358
#define BASE_SERVO_90_DEGREE_ADC_VAL	615

#define SHOULDER_SERVO_0_DEGREE_PULSE		956
#define SHOULDER_SERVO_90_DEGREE_PULSE		1431
#define SHOULDER_SERVO_0_DEGREE_ADC_VAL	415
#define SHOULDER_SERVO_90_DEGREE_ADC_VAL	654

#define ELBOW_SERVO_0_DEGREE_PULSE		904
#define ELBOW_SERVO_90_DEGREE_PULSE		1391
#define ELBOW_SERVO_0_DEGREE_ADC_VAL	428
#define ELBOW_SERVO_90_DEGREE_ADC_VAL	666

#define BASE_SERVO_INIT_PULSE				BASE_SERVO_90_DEGREE_PULSE   
#define SHOULDER_SERVO_INIT_PULSE		1531
#define ELBOW_SERVO_INIT_PULSE			1344

int main( int argc, char *argv[])
{
	RtTasksData *rt_tasks_data = NULL;
	ThreeDofRobot 	*robot_arm = NULL;
	MovObjHandParadigmRobotReach *mov_obj_paradigm = NULL;
	MessageLogBuffer *message_log = NULL;
	Gui2MovObjHandMsg *msgs_gui_2_mov_obj_hand = NULL; 
   	MovObjHand2GuiMsg *msgs_mov_obj_hand_2_gui = NULL; 
	MovObjStatusHistory* mov_obj_status_history = NULL;
	ThreeDofRobotAngleHistory *robot_angle_history = NULL;
	ThreeDofRobotPulseHistory *robot_pulse_history = NULL;
	unsigned int i;

   	rt_tasks_data = rtai_malloc(SHM_NUM_RT_TASKS_DATA, 0);
	if (rt_tasks_data == NULL) 
		return print_message(ERROR_MSG ,"MovObjHandler", "MovObjHandler", "main", "rt_tasks_data == NULL.");

	robot_arm = g_new0(ThreeDofRobot, 1);
	mov_obj_paradigm = g_new0(MovObjHandParadigmRobotReach, 1);

	init_three_dof_robot_arm(robot_arm);
	submit_arm_length_vals(robot_arm, 14.60, 19.4, 1.1);
	submit_arm_security_limits(robot_arm, -19.0, 16.0, -20.0, 20.0, 3.0, 35.0, (M_PI*0.0)/12.0, (M_PI*12.0)/12.0, -(M_PI*0.5)/12.0, (M_PI*12.0)/12.0,  (M_PI*0.0)/12.0, (M_PI*12.0)/12.0);
	if (! submit_cartesian_robotic_space_borders(robot_arm, mov_obj_paradigm, -18.0, 15.5, -19.0, 19.0, 4.0, 34.0))
		return print_message(ERROR_MSG ,"MovObjHandler", "MovObjHandler", "main", "! submit_cartesian_robotic_space_borders().");
	if (! submit_polar_robotic_space_borders(robot_arm, mov_obj_paradigm, (M_PI*2.5)/12.0, (M_PI*9.5)/12.0, (M_PI*0.0)/12.0, (M_PI*10.0)/12.0, (M_PI*1.0)/12.0, (M_PI*11.0)/12.0))
		return print_message(ERROR_MSG ,"MovObjHandler", "MovObjHandler", "main", "! submit_polar_robotic_space_borders().");

	write_servo_pw_adc_ranges(&(robot_arm->servos[BASE_SERVO]), BASE_SERVO_0_DEGREE_PULSE, BASE_SERVO_90_DEGREE_PULSE, BASE_SERVO_0_DEGREE_ADC_VAL, BASE_SERVO_90_DEGREE_ADC_VAL);
	write_servo_pw_adc_ranges(&(robot_arm->servos[SHOULDER_SERVO]), SHOULDER_SERVO_0_DEGREE_PULSE, SHOULDER_SERVO_90_DEGREE_PULSE, SHOULDER_SERVO_0_DEGREE_ADC_VAL, SHOULDER_SERVO_90_DEGREE_ADC_VAL);
	write_servo_pw_adc_ranges(&(robot_arm->servos[ELBOW_SERVO]), ELBOW_SERVO_0_DEGREE_PULSE, ELBOW_SERVO_90_DEGREE_PULSE, ELBOW_SERVO_0_DEGREE_ADC_VAL, ELBOW_SERVO_90_DEGREE_ADC_VAL);

	init_servo_pulse(&(robot_arm->servos[BASE_SERVO]), BASE_SERVO_INIT_PULSE);
	init_servo_pulse(&(robot_arm->servos[SHOULDER_SERVO]), SHOULDER_SERVO_INIT_PULSE);
	init_servo_pulse(&(robot_arm->servos[ELBOW_SERVO]), ELBOW_SERVO_INIT_PULSE);

	init_servo_angles_for_sample_averaging(&(robot_arm->servos[BASE_SERVO]), ((BASE_SERVO_INIT_PULSE-BASE_SERVO_0_DEGREE_PULSE)/(BASE_SERVO_90_DEGREE_PULSE-BASE_SERVO_0_DEGREE_PULSE))*M_PI_2, 3);  // it is required for check_three_dof_robot_security_limits(). Too weird initialization cannot pass check security limits.
	init_servo_angles_for_sample_averaging(&(robot_arm->servos[SHOULDER_SERVO]), ((SHOULDER_SERVO_INIT_PULSE-SHOULDER_SERVO_0_DEGREE_PULSE)/(SHOULDER_SERVO_90_DEGREE_PULSE-SHOULDER_SERVO_0_DEGREE_PULSE))*M_PI_2, 3);
	init_servo_angles_for_sample_averaging(&(robot_arm->servos[ELBOW_SERVO]), ((ELBOW_SERVO_INIT_PULSE-ELBOW_SERVO_0_DEGREE_PULSE)/(ELBOW_SERVO_90_DEGREE_PULSE-ELBOW_SERVO_0_DEGREE_PULSE))*M_PI_2, 3);  // it is required for check_three_dof_robot_security_limits(). Too weird initialization cannot pass check security limits.


	mov_obj_paradigm->stay_at_target_duration = 200000000;
	mov_obj_paradigm->send_pw_command_wait_period = 25000000;
	mov_obj_paradigm->receive_position_wait_period = 5000000;
	mov_obj_paradigm->stay_at_start_duration = 400000000;   

	mov_obj_paradigm->spike_2_servo_degree_multiplier = 1.0;
	mov_obj_paradigm->max_servo_angle_change = 3.0;

	mov_obj_paradigm->target_info.cart_coordinates = g_new0(CartesianCoordinates, 2);
	mov_obj_paradigm->target_info.robot_pulse_widths = g_new0(ThreeDofRobotServoPulse, 2);
	mov_obj_paradigm->target_info.num_of_positions = 2;

//	POSITIONS ACCORDING TO TARGET LEDS
/*	mov_obj_paradigm->target_info.cart_coordinates[0].height = 18.5 ;
	mov_obj_paradigm->target_info.cart_coordinates[0].depth = 12.5;
	mov_obj_paradigm->target_info.cart_coordinates[0].lateral = -8.0;
	mov_obj_paradigm->target_info.robot_pulse_widths[0].pulse[BASE_SERVO] = 1624;
	mov_obj_paradigm->target_info.robot_pulse_widths[0].pulse[SHOULDER_SERVO] = 1511;
	mov_obj_paradigm->target_info.robot_pulse_widths[0].pulse[ELBOW_SERVO] = 1424;
	mov_obj_paradigm->target_info.cart_coordinates[1].height = 18.5 ;
	mov_obj_paradigm->target_info.cart_coordinates[1].depth = 12.5;
	mov_obj_paradigm->target_info.cart_coordinates[1].lateral = 8.0;
	mov_obj_paradigm->target_info.robot_pulse_widths[1].pulse[BASE_SERVO] = 1226;
	mov_obj_paradigm->target_info.robot_pulse_widths[1].pulse[SHOULDER_SERVO] = 1511;
	mov_obj_paradigm->target_info.robot_pulse_widths[1].pulse[ELBOW_SERVO] = 1424;
*/
	mov_obj_paradigm->target_info.cart_coordinates[0].height = 17.7;
	mov_obj_paradigm->target_info.cart_coordinates[0].depth = 11.85;
	mov_obj_paradigm->target_info.cart_coordinates[0].lateral = -8.2;
	mov_obj_paradigm->target_info.robot_pulse_widths[0].pulse[BASE_SERVO] = 1645;
	mov_obj_paradigm->target_info.robot_pulse_widths[0].pulse[SHOULDER_SERVO] = 1531;
	mov_obj_paradigm->target_info.robot_pulse_widths[0].pulse[ELBOW_SERVO] = 1444;
	mov_obj_paradigm->target_info.cart_coordinates[1].height = 17.7 ;
	mov_obj_paradigm->target_info.cart_coordinates[1].depth = 11.85;
	mov_obj_paradigm->target_info.cart_coordinates[1].lateral = 8.2;
	mov_obj_paradigm->target_info.robot_pulse_widths[1].pulse[BASE_SERVO] = 1215;
	mov_obj_paradigm->target_info.robot_pulse_widths[1].pulse[SHOULDER_SERVO] = 1531;
	mov_obj_paradigm->target_info.robot_pulse_widths[1].pulse[ELBOW_SERVO] = 1444;

	mov_obj_paradigm->start_info.cart_coordinates = g_new0(CartesianCoordinates, 16);
	mov_obj_paradigm->start_info.robot_pulse_widths = g_new0(ThreeDofRobotServoPulse, 16);
	mov_obj_paradigm->start_info.num_of_positions = 10;

//	POSITIONS ACCORDING TO MIDLINE 
/*	mov_obj_paradigm->start_info.cart_coordinates[0].height = 18.2 ;
	mov_obj_paradigm->start_info.cart_coordinates[0].depth = 14.3;		
	mov_obj_paradigm->start_info.cart_coordinates[0].lateral = 0.0;
	mov_obj_paradigm->start_info.robot_pulse_widths[0].pulse[BASE_SERVO] = 1430;
	mov_obj_paradigm->start_info.robot_pulse_widths[0].pulse[SHOULDER_SERVO] = 1531;
	mov_obj_paradigm->start_info.robot_pulse_widths[0].pulse[ELBOW_SERVO] = 1444;
*/

	for (i = 0; i < mov_obj_paradigm->start_info.num_of_positions; i++)
	{
		mov_obj_paradigm->start_info.robot_pulse_widths[i].pulse[BASE_SERVO] = mov_obj_paradigm->target_info.robot_pulse_widths[0].pulse[BASE_SERVO]  - (ServoPulse)((((i+1) * (mov_obj_paradigm->target_info.robot_pulse_widths[0].pulse[BASE_SERVO] - mov_obj_paradigm->target_info.robot_pulse_widths[1].pulse[BASE_SERVO])) / ((double)(mov_obj_paradigm->start_info.num_of_positions + 1))));
		mov_obj_paradigm->start_info.robot_pulse_widths[i].pulse[SHOULDER_SERVO] = 1531;
		mov_obj_paradigm->start_info.robot_pulse_widths[i].pulse[ELBOW_SERVO] = 1444;		
	}

	mov_obj_paradigm->threshold.outer_threshold.r_x = 16;  //height
	mov_obj_paradigm->threshold.outer_threshold.r_y = 46; // depth    ->>>  to provide a circle with radius of ~12 cm at the frontal surface of the cage
	mov_obj_paradigm->threshold.outer_threshold.r_z = 16; // lateral

	mov_obj_paradigm->threshold.point_reach_threshold.r_x = 1;
	mov_obj_paradigm->threshold.point_reach_threshold.r_y = 1;
	mov_obj_paradigm->threshold.point_reach_threshold.r_z = 1;

	msgs_gui_2_mov_obj_hand = allocate_gui_2_mov_obj_hand_msg_buffer(msgs_gui_2_mov_obj_hand);
	msgs_mov_obj_hand_2_gui = allocate_mov_obj_hand_2_gui_msg_buffer(msgs_mov_obj_hand_2_gui);

	mov_obj_status_history = allocate_mov_obj_status_history(mov_obj_status_history, 50); 
	robot_angle_history = allocate_three_dof_robot_angle_history(robot_angle_history, 1000);
	robot_pulse_history = allocate_three_dof_robot_pulse_history(robot_pulse_history, 1000);

	initialize_data_read_write_handlers();

	message_log = allocate_message_log_buffer(message_log, 200);
    	pthread_create( &logging_thread, NULL, logging_thread_function, (void*)message_log);

	if(! create_mov_obj_handler_rt_thread(rt_tasks_data, robot_arm, msgs_gui_2_mov_obj_hand,  msgs_mov_obj_hand_2_gui, mov_obj_paradigm, message_log, mov_obj_status_history, robot_angle_history, robot_pulse_history))
		return print_message(ERROR_MSG ,"MovObjHandler", "MovObjHandler", "main", "create_mov_obj_handler_rt_thread().");
	gtk_init(&argc, &argv);
	create_gui_handler(rt_tasks_data, msgs_gui_2_mov_obj_hand, msgs_mov_obj_hand_2_gui, robot_arm, mov_obj_paradigm, mov_obj_status_history, robot_angle_history, robot_pulse_history);
	gtk_main();
	return 0;
}	

void *logging_thread_function( void *message_log )
{
	while (1)
	{
		if (!print_message_log_buffer(message_log, 50))
			return (void*)print_message(ERROR_MSG ,"MovObjHandler", "MovObjHandler", "logging_thread_function", "! print_message_log_buffer().");
		sleep(1);
	}
	return NULL;	
}
