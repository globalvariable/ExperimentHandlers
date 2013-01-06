#include "ThreeDofRobot.h"

void init_three_dof_robot_arm(ThreeDofRobot *robot_arm)
{
	unsigned int i;
	pthread_mutex_init(&(robot_arm->mutex), NULL);	
	pthread_mutex_lock(&(robot_arm->mutex));
	for (i = 0; i < THREE_DOF_ROBOT_NUM_OF_SERVOS; i++)
		init_servo_data(&(robot_arm->servos[i]));
	pthread_mutex_unlock(&(robot_arm->mutex));
}

void submit_arm_length_vals(ThreeDofRobot *robot_arm, double length_humerus, double length_ulna, double height_ulna)
{
	robot_arm->size.length_humerus = length_humerus;
	robot_arm->size.length_ulna = length_ulna;
	robot_arm->size.height_ulna = height_ulna;
}

void submit_3_dof_arm_trajectory_history_buffer_size(ThreeDofRobot *robot_arm, unsigned int buff_size)
{
	robot_arm->trajectory_history.buffer = g_new0(ThreeDofRobotPosition, buff_size);
	robot_arm->trajectory_history.buffer_size = buff_size;
	robot_arm->trajectory_history.write_idx = 0;
}

bool write_to_3_dof_arm_trajectory_history(ThreeDofRobot *robot_arm,  double height, double depth, double lateral)
{
	ThreeDofRobotPosition *item = &(robot_arm->trajectory_history.buffer[robot_arm->trajectory_history.write_idx]);
	item->height = height;
	item->depth = depth;
	item->lateral = lateral;
	if ((robot_arm->trajectory_history.write_idx+1) == robot_arm->trajectory_history.read_idx)
		return print_message(ERROR_MSG ,"ExperimentHandlers", "ThreeDofRobot", "write_to_3_dof_arm_trajectory_history", "BUFFER FULL!!!");
	if ((robot_arm->trajectory_history.write_idx+1) == robot_arm->trajectory_history.buffer_size)
		robot_arm->trajectory_history.write_idx = 0;
	else
		robot_arm->trajectory_history.write_idx++;	
	return TRUE;	
}

void evaluate_three_dof_robot_arm_pw_command(ThreeDofRobot *robot_arm)
{
	unsigned int i;
	pthread_mutex_lock(&(robot_arm->mutex));
	for (i = 0; i < THREE_DOF_ROBOT_NUM_OF_SERVOS; i++)
		evaluate_servo_pw_command(&(robot_arm->servos[i]));
	pthread_mutex_unlock(&(robot_arm->mutex));
}

void calculate_forward_kinematics(ThreeDofRobot *robot_arm)
{
	ServoData *servo;
	ThreeDofRobotPosition *tip_position;
	ThreeDofRobotSize *size;
	double R;
	double beta_minus_alpha;
	double alpha;
	double theta;
	pthread_mutex_lock(&(robot_arm->mutex));
	servo = &(robot_arm->servos[BASE_SERVO]);
	servo->current_angle = (servo->position.position - servo->range.position_0_degree) * servo->range.radian_per_pos_quanta;
	servo = &(robot_arm->servos[SHOULDER_SERVO]);
	servo->current_angle = (servo->position.position - servo->range.position_0_degree) * servo->range.radian_per_pos_quanta;
	servo = &(robot_arm->servos[ELBOW_SERVO]);
	servo->current_angle = (servo->position.position - servo->range.position_0_degree) * servo->range.radian_per_pos_quanta;
	pthread_mutex_unlock(&(robot_arm->mutex));
	tip_position = &(robot_arm->tip_position);
	alpha = robot_arm->servos[SHOULDER_SERVO].current_angle;
	beta_minus_alpha = robot_arm->servos[ELBOW_SERVO].current_angle - alpha;
	size = &(robot_arm->size);
	R = size->length_humerus*cos(alpha) + size->length_ulna*cos(beta_minus_alpha) + size->height_ulna*sin(beta_minus_alpha);
	tip_position->height = size->length_humerus*sin(alpha) - size->length_ulna*sin(beta_minus_alpha) + size->height_ulna*cos(beta_minus_alpha);
	theta = robot_arm->servos[BASE_SERVO].current_angle;
	tip_position->depth = R*sin(theta);
	tip_position->lateral = R*cos(theta); 
}

void submit_arm_security_limits(ThreeDofRobot *robot_arm, double depth_min, double depth_max, double lateral_min, double lateral_max, double height_min, double height_max, double joint_angle_base_lower_limit, double joint_angle_base_upper_limit, double joint_angle_shoulder_lower_limit, double joint_angle_shoulder_upper_limit, double joint_angle_elbow_lower_limit, double joint_angle_elbow_upper_limit)
{
	robot_arm->cartesian_security_limits.depth_min = depth_min;
	robot_arm->cartesian_security_limits.depth_max = depth_max;
	robot_arm->cartesian_security_limits.lateral_min = lateral_min;
	robot_arm->cartesian_security_limits.lateral_max = lateral_max;
	robot_arm->cartesian_security_limits.height_min = height_min;
	robot_arm->cartesian_security_limits.height_max = height_max;
	robot_arm->servos[BASE_SERVO].angular_security_limit.min = joint_angle_base_lower_limit;
	robot_arm->servos[BASE_SERVO].angular_security_limit.max = joint_angle_base_upper_limit;
	robot_arm->servos[SHOULDER_SERVO].angular_security_limit.min = joint_angle_shoulder_lower_limit;
	robot_arm->servos[SHOULDER_SERVO].angular_security_limit.max = joint_angle_shoulder_upper_limit;
	robot_arm->servos[ELBOW_SERVO].angular_security_limit.min = joint_angle_elbow_lower_limit;
	robot_arm->servos[ELBOW_SERVO].angular_security_limit.max = joint_angle_elbow_upper_limit;
}

bool check_three_dof_robot_security_limits(ThreeDofRobot *robot_arm)
{
	ThreeDofRobotPosition *tip_position =&(robot_arm->tip_position);
	ThreeDofRobotCartesianLimit	*cart_security_limits = &(robot_arm->cartesian_security_limits);

	unsigned int i;
	if ((cart_security_limits->depth_min > tip_position->depth) || (cart_security_limits->depth_max < tip_position->depth))
		return false;
	if ((cart_security_limits->lateral_min > tip_position->lateral) || (cart_security_limits->lateral_max < tip_position->lateral))
		return false;
	if ((cart_security_limits->height_min > tip_position->height) || (cart_security_limits->height_max < tip_position->height))
		return false;
	for (i = 0; i < THREE_DOF_ROBOT_NUM_OF_SERVOS; i++)
	{
		if ((robot_arm->servos[i].angular_security_limit.min > robot_arm->servos[i].current_angle) || (robot_arm->servos[i].angular_security_limit.max < robot_arm->servos[i].current_angle))
			return false;
	}
	return true;
}


