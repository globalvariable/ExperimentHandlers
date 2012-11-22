#include "ThreeDofRobot.h"


void submit_arm_length_vals(ThreeDofRobot *robot_arm, double length_humerus, double length_ulna)
{
	robot_arm->length_humerus = length_humerus;
	robot_arm->length_ulna = length_ulna;
}

void calculate_forward_kinematics(ThreeDofRobot *robot_arm)
{
	ServoData *servo;
	servo = &(robot_arm->servos[BASE_SERVO]);
	servo->angle_radian = (servo->position.position - servo->position_0_degree) * servo->radian_per_pos_quanta;
	servo = &(robot_arm->servos[SHOULDER_SERVO]);
	servo->angle_radian = (servo->position.position - servo->position_0_degree) * servo->radian_per_pos_quanta;
	servo = &(robot_arm->servos[ELBOW_SERVO]);
	servo->angle_radian = (servo->position.position - servo->position_0_degree) * servo->radian_per_pos_quanta;
}
