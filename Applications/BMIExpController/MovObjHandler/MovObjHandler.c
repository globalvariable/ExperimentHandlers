#include "MovObjHandler.h"

static ThreeDofRobot 	*robot_arm = NULL;
static Ellipsoid *ellipsoid_threshold = NULL;

int main( int argc, char *argv[])
{
	RtTasksData *rt_tasks_data = NULL;
	Gui2MovObjHandMsg *msgs_gui_2_mov_obj_hand = NULL; 
   	MovObjHand2GuiMsg *msgs_mov_obj_hand_2_gui = NULL; 

   	rt_tasks_data = rtai_malloc(SHM_NUM_RT_TASKS_DATA, 0);
	if (rt_tasks_data == NULL) 
		return print_message(ERROR_MSG ,"MovObjHandler", "MovObjHandler", "main", "rt_tasks_data == NULL.");

	robot_arm = g_new0(ThreeDofRobot, 1);
	init_three_dof_robot_arm(robot_arm);
	submit_arm_length_vals(robot_arm, 14.60, 19.4, 1.1);
	submit_arm_security_limits(robot_arm, -19.0, 14.0, -20.0, 20.0, 3.0, 35.0, M_PI*(1.0/12.0), M_PI*(11.0/12.0));
	submit_3_dof_arm_trajectory_history_buffer_size(robot_arm, 1000);

	init_servo_pulse(&(robot_arm->servos[BASE_SERVO]), 1430);
	init_servo_pulse(&(robot_arm->servos[SHOULDER_SERVO]), 1600);
	init_servo_pulse(&(robot_arm->servos[ELBOW_SERVO]), 1600);

	write_servo_pw_adc_ranges(&(robot_arm->servos[BASE_SERVO]), 879, 1430, 358, 615);
	write_servo_pw_adc_ranges(&(robot_arm->servos[SHOULDER_SERVO]), 956, 1431, 415, 654);
	write_servo_pw_adc_ranges(&(robot_arm->servos[ELBOW_SERVO]), 904, 1391, 428, 666);

	ellipsoid_threshold = g_new0(Ellipsoid, 1);

	msgs_gui_2_mov_obj_hand = allocate_gui_2_mov_obj_hand_msg_buffer(msgs_gui_2_mov_obj_hand);
	msgs_mov_obj_hand_2_gui = allocate_mov_obj_hand_2_gui_msg_buffer(msgs_mov_obj_hand_2_gui);

	if(! create_mov_obj_handler_rt_thread(rt_tasks_data, robot_arm, msgs_gui_2_mov_obj_hand,  msgs_mov_obj_hand_2_gui, ellipsoid_threshold))
		return print_message(ERROR_MSG ,"MovObjHandler", "MovObjHandler", "main", "create_mov_obj_handler_rt_thread().");
	gtk_init(&argc, &argv);
	create_gui_handler(rt_tasks_data, msgs_gui_2_mov_obj_hand, msgs_mov_obj_hand_2_gui, robot_arm, ellipsoid_threshold);
	gtk_main();
	return 0;
}	
