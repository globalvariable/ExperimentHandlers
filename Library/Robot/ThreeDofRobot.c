#include "ThreeDofRobot.h"


void submit_arm_length_vals(ThreeDofRobot *robot_arm, double length_humerus, double length_ulna)
{
	robot_arm->length_humerus = length_humerus;
	robot_arm->length_ulna = length_ulna;
}

void calculate_forward_kinematics(ThreeDofRobot *robot_arm)
{
	ServoData *servo;
	double R;
	servo = &(robot_arm->servos[BASE_SERVO]);
	servo->angle_radian = (servo->position.position - servo->position_0_degree) * servo->radian_per_pos_quanta;
	servo = &(robot_arm->servos[SHOULDER_SERVO]);
	servo->angle_radian = (servo->position.position - servo->position_0_degree) * servo->radian_per_pos_quanta;
	servo = &(robot_arm->servos[ELBOW_SERVO]);
	servo->angle_radian = (servo->position.position - servo->position_0_degree) * servo->radian_per_pos_quanta;
	R = robot_arm->length_humerus*cos(robot_arm->servos[SHOULDER_SERVO].angle_radian) + robot_arm->length_ulna*sin(robot_arm->servos[SHOULDER_SERVO].angle_radian+M_PI_2-robot_arm->servos[ELBOW_SERVO].angle_radian);
	robot_arm->tip_height = robot_arm->length_humerus*sin(robot_arm->servos[SHOULDER_SERVO].angle_radian) - robot_arm->length_ulna*cos(robot_arm->servos[SHOULDER_SERVO].angle_radian+M_PI_2-robot_arm->servos[ELBOW_SERVO].angle_radian);
	robot_arm->tip_depth = R*sin(robot_arm->servos[BASE_SERVO].angle_radian);
	robot_arm->tip_lateral = R*cos(robot_arm->servos[BASE_SERVO].angle_radian); 
}
