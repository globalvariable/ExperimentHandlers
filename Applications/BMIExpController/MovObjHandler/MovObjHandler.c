#include "MovObjHandler.h"

static pthread_t logging_thread;
void *logging_thread_function( void *message_log );

int main( int argc, char *argv[])
{
	RtTasksData *rt_tasks_data = NULL;
	ThreeDofRobot 	*robot_arm = NULL;
	MovObjHandParadigmRobotReach *mov_obj_paradigm = NULL;
	MessageLogBuffer *message_log = NULL;
	Gui2MovObjHandMsg *msgs_gui_2_mov_obj_hand = NULL; 
   	MovObjHand2GuiMsg *msgs_mov_obj_hand_2_gui = NULL; 

   	rt_tasks_data = rtai_malloc(SHM_NUM_RT_TASKS_DATA, 0);
	if (rt_tasks_data == NULL) 
		return print_message(ERROR_MSG ,"MovObjHandler", "MovObjHandler", "main", "rt_tasks_data == NULL.");

	robot_arm = g_new0(ThreeDofRobot, 1);
	init_three_dof_robot_arm(robot_arm);
	submit_arm_length_vals(robot_arm, 14.60, 19.4, 1.1);
	submit_arm_security_limits(robot_arm, -19.0, 14.5, -20.0, 20.0, 3.0, 35.0, M_PI*(1.0/12.0), M_PI*(11.0/12.0));
	if (! submit_robotic_space_borders(robot_arm, -18.0, 13.5, -19.0, 19.0, 4.0, 34.0, M_PI*(1.5/12.0) , M_PI*(10.5/12.0)))
		return print_message(ERROR_MSG ,"MovObjHandler", "MovObjHandler", "main", "! submit_robotic_space_borders().");

	submit_3_dof_arm_trajectory_history_buffer_size(robot_arm, 1000);

	init_servo_pulse(&(robot_arm->servos[BASE_SERVO]), 1425);
	init_servo_pulse(&(robot_arm->servos[SHOULDER_SERVO]), 1431);
	init_servo_pulse(&(robot_arm->servos[ELBOW_SERVO]), 1014);

	write_servo_pw_adc_ranges(&(robot_arm->servos[BASE_SERVO]), 879, 1430, 358, 615);
	write_servo_pw_adc_ranges(&(robot_arm->servos[SHOULDER_SERVO]), 956, 1431, 415, 654);
	write_servo_pw_adc_ranges(&(robot_arm->servos[ELBOW_SERVO]), 904, 1391, 428, 666);

	mov_obj_paradigm = g_new0(MovObjHandParadigmRobotReach, 1);
	mov_obj_paradigm->stay_at_start_duration = 200000000;
	mov_obj_paradigm->stay_at_target_duration = 200000000;
	mov_obj_paradigm->send_pw_command_wait_period = 25000000;
	mov_obj_paradigm->receive_position_wait_period = 5000000;


	mov_obj_paradigm->start_info.cart_coordinates = g_new0(CartesianCoordinates, 1);
	mov_obj_paradigm->start_info.robot_pulse_widths = g_new0(ThreeDofRobotServoPulse, 1);
	mov_obj_paradigm->start_info.num_of_positions = 1;

	mov_obj_paradigm->start_info.cart_coordinates[0].height = 18.9 ;
	mov_obj_paradigm->start_info.cart_coordinates[0].depth = 11.8;
	mov_obj_paradigm->start_info.cart_coordinates[0].lateral = 0.0;
	mov_obj_paradigm->start_info.robot_pulse_widths[0].pulse[BASE_SERVO] = 1425;
	mov_obj_paradigm->start_info.robot_pulse_widths[0].pulse[SHOULDER_SERVO] = 1581;
	mov_obj_paradigm->start_info.robot_pulse_widths[0].pulse[ELBOW_SERVO] = 1464;

	mov_obj_paradigm->target_info.cart_coordinates = g_new0(CartesianCoordinates, 2);
	mov_obj_paradigm->target_info.robot_pulse_widths = g_new0(ThreeDofRobotServoPulse, 2);
	mov_obj_paradigm->target_info.num_of_positions = 2;

	mov_obj_paradigm->target_info.cart_coordinates[0].height = 18.5 ;
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

	mov_obj_paradigm->threshold.min_target_reach_threshold.r_x = 1;  //height
	mov_obj_paradigm->threshold.min_target_reach_threshold.r_y = 1; // depth
	mov_obj_paradigm->threshold.min_target_reach_threshold.r_z = 1; // lateral

	mov_obj_paradigm->threshold.max_target_reach_threshold.r_x = 8;  //height   //  heigh be laterali non overlapping seç. aksi takdirde sıçan her iki target için ödül alabilir. dolayısıyla targetlara dikkat etmeden sadece trial başlatır ve guide led ve target led leri izlemez. 
	mov_obj_paradigm->threshold.max_target_reach_threshold.r_y = 4; // depth    
	mov_obj_paradigm->threshold.max_target_reach_threshold.r_z = 8; // lateral
	mov_obj_paradigm->threshold.target_reach_threshold_change_rate = 0.1;

	mov_obj_paradigm->threshold.outer_threshold.r_x = 16;  //height
	mov_obj_paradigm->threshold.outer_threshold.r_y = 46; // depth    ->>>  to provide a circle with radius of ~12 cm at the frontal surface of the cage
	mov_obj_paradigm->threshold.outer_threshold.r_z = 16; // lateral

	mov_obj_paradigm->threshold.point_reach_threshold.r_x = 1;
	mov_obj_paradigm->threshold.point_reach_threshold.r_y = 1;
	mov_obj_paradigm->threshold.point_reach_threshold.r_z = 1;

	mov_obj_paradigm->threshold.selected_target_reach_threshold = mov_obj_paradigm->threshold.max_target_reach_threshold;

	msgs_gui_2_mov_obj_hand = allocate_gui_2_mov_obj_hand_msg_buffer(msgs_gui_2_mov_obj_hand);
	msgs_mov_obj_hand_2_gui = allocate_mov_obj_hand_2_gui_msg_buffer(msgs_mov_obj_hand_2_gui);

	message_log = allocate_message_log_buffer(message_log, 200);
    	pthread_create( &logging_thread, NULL, logging_thread_function, (void*)message_log);

	if(! create_mov_obj_handler_rt_thread(rt_tasks_data, robot_arm, msgs_gui_2_mov_obj_hand,  msgs_mov_obj_hand_2_gui, mov_obj_paradigm, message_log))
		return print_message(ERROR_MSG ,"MovObjHandler", "MovObjHandler", "main", "create_mov_obj_handler_rt_thread().");
	gtk_init(&argc, &argv);
	create_gui_handler(rt_tasks_data, msgs_gui_2_mov_obj_hand, msgs_mov_obj_hand_2_gui, robot_arm, mov_obj_paradigm);
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
