#include "ThreeDofRobot.h"


void submit_arm_length_vals(ThreeDofRobot *robot_arm, double length_humerus, double length_ulna, double height_ulna)
{
	robot_arm->length_humerus = length_humerus;
	robot_arm->length_ulna = length_ulna;
	robot_arm->height_ulna = height_ulna;
}

void calculate_forward_kinematics(ThreeDofRobot *robot_arm)
{
	ServoData *servo;
	double R;
	double beta_minus_alpha;
	double alpha;
	double theta;
	servo = &(robot_arm->servos[BASE_SERVO]);
	servo->angle_radian = (servo->position.position - servo->position_0_degree) * servo->radian_per_pos_quanta;
	servo = &(robot_arm->servos[SHOULDER_SERVO]);
	servo->angle_radian = (servo->position.position - servo->position_0_degree) * servo->radian_per_pos_quanta;
	servo = &(robot_arm->servos[ELBOW_SERVO]);
	servo->angle_radian = (servo->position.position - servo->position_0_degree) * servo->radian_per_pos_quanta;
	alpha = robot_arm->servos[SHOULDER_SERVO].angle_radian;
	beta_minus_alpha = robot_arm->servos[ELBOW_SERVO].angle_radian - alpha;
	R = robot_arm->length_humerus*cos(alpha) + robot_arm->length_ulna*cos(beta_minus_alpha) + robot_arm->height_ulna*sin(beta_minus_alpha);
	robot_arm->tip_height = robot_arm->length_humerus*sin(alpha) - robot_arm->length_ulna*sin(beta_minus_alpha) + robot_arm->height_ulna*cos(beta_minus_alpha);
	theta = robot_arm->servos[BASE_SERVO].angle_radian;
	robot_arm->tip_depth = R*sin(theta);
	robot_arm->tip_lateral = R*cos(theta); 
}
