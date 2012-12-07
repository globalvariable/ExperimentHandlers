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
	ThreeDofRobotPosition *tip_position;
	double R;
	double beta_minus_alpha;
	double alpha;
	double theta;
	servo = &(robot_arm->servos[BASE_SERVO]);
	servo->current_angle = (servo->position.position - servo->range.position_0_degree.position) * servo->range.radian_per_pos_quanta;
	servo = &(robot_arm->servos[SHOULDER_SERVO]);
	servo->current_angle = (servo->position.position - servo->range.position_0_degree.position) * servo->range.radian_per_pos_quanta;
	servo = &(robot_arm->servos[ELBOW_SERVO]);
	servo->current_angle = (servo->position.position - servo->range.position_0_degree.position) * servo->range.radian_per_pos_quanta;
	tip_position = &(robot_arm->tip_position);
	alpha = robot_arm->servos[SHOULDER_SERVO].current_angle;
	beta_minus_alpha = robot_arm->servos[ELBOW_SERVO].current_angle - alpha;
	R = robot_arm->length_humerus*cos(alpha) + robot_arm->length_ulna*cos(beta_minus_alpha) + robot_arm->height_ulna*sin(beta_minus_alpha);
	tip_position->height = robot_arm->length_humerus*sin(alpha) - robot_arm->length_ulna*sin(beta_minus_alpha) + robot_arm->height_ulna*cos(beta_minus_alpha);
	theta = robot_arm->servos[BASE_SERVO].current_angle;
	tip_position->depth = R*sin(theta);
	tip_position->lateral = R*cos(theta); 
}

void submit_arm_security_limits(ThreeDofRobot *robot_arm, double depth_min, double depth_max, double lateral_min, double lateral_max, double height_min, double height_max)
{
	robot_arm->security_limits.depth_min = depth_min;
	robot_arm->security_limits.depth_max = depth_max;
	robot_arm->security_limits.lateral_min = lateral_min;
	robot_arm->security_limits.lateral_max = lateral_max;
	robot_arm->security_limits.height_min = height_min;
	robot_arm->security_limits.height_max = height_max;
}

bool check_three_dof_robot_out_of_security_limits(ThreeDofRobot *robot_arm)
{
	ThreeDofRobotPosition *tip_position =&(robot_arm->tip_position);
	ThreeDofRobotLimit	*security_limits = &(robot_arm->security_limits);
	if ((security_limits->depth_min > tip_position->depth) || (security_limits->depth_max < tip_position->depth))
		return false;
	if ((security_limits->lateral_min > tip_position->lateral) || (security_limits->lateral_max < tip_position->lateral))
		return false;
	if ((security_limits->height_min > tip_position->height) || (security_limits->height_max < tip_position->height))
		return false;
	return true;
}
