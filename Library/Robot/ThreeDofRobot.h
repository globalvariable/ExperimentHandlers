#ifndef THREE_DOF_ROBOT_H
#define THREE_DOF_ROBOT_H


#define THREE_DOF_ROBOT_NUM_OF_SERVOS	3

#define BASE_SERVO			0
#define SHOULDER_SERVO	1
#define ELBOW_SERVO		2

#include "../Servo/Servo.h"
#include "../Coordinate/Cartesian.h"
#include "../../../BlueSpike/Library/Misc/Misc.h"

typedef struct 
{
	double depth_min;
	double depth_max;
	double lateral_min;
	double lateral_max;
	double height_min;
	double height_max;
} ThreeDofRobotCartesianLimit;

typedef CartesianCoordinates ThreeDofRobotPosition; 

typedef struct 
{
	double		length_humerus;
	double		length_ulna;
	double		height_ulna;
} ThreeDofRobotSize;

typedef struct 
{
	ThreeDofRobotPosition	*buffer;
	unsigned int			write_idx;
	unsigned int			read_idx;
	unsigned int			buffer_size;
} ThreeDofRobotTrajectory;

typedef struct 
{
	pthread_mutex_t 				mutex; 
	ServoData					servos[THREE_DOF_ROBOT_NUM_OF_SERVOS];
	ThreeDofRobotCartesianLimit	cartesian_security_limits;	// interrupt pulsing servos, robot goes to somewhere dangerous
	ThreeDofRobotPosition			tip_position;
	ThreeDofRobotPosition			tip_position_prev;
	ThreeDofRobotPosition			elbow_position;
	ThreeDofRobotSize			size;
	ThreeDofRobotTrajectory		trajectory_history; // for example in one trial
} ThreeDofRobot;	

typedef struct 
{
	ServoPulse		pulse[THREE_DOF_ROBOT_NUM_OF_SERVOS];	// pulse width to transmit
} ThreeDofRobotServoPulse;
	

void init_three_dof_robot_arm(ThreeDofRobot *robot_arm);
void submit_arm_length_vals(ThreeDofRobot *robot_arm, double length_humerus, double length_ulna, double height_ulna);
void submit_3_dof_arm_trajectory_history_buffer_size(ThreeDofRobot *robot_arm, unsigned int buff_size);
void evaluate_three_dof_robot_arm_pw_command(ThreeDofRobot *robot_arm);
void push_current_arm_position_to_previous(ThreeDofRobot *robot_arm);
void calculate_forward_kinematics(ThreeDofRobot *robot_arm);
void submit_arm_security_limits(ThreeDofRobot *robot_arm, double depth_min, double depth_max, double lateral_min, double lateral_max, double height_min, double height_max, double joint_angle_base_lower_limit, double joint_angle_base_upper_limit, double joint_angle_shoulder_lower_limit, double joint_angle_shoulder_upper_limit, double joint_angle_elbow_lower_limit, double joint_angle_elbow_upper_limit);
bool check_three_dof_robot_security_limits(ThreeDofRobot *robot_arm);


#endif
