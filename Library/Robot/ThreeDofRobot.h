#ifndef THREE_DOF_ROBOT_H
#define THREE_DOF_ROBOT_H


#define THREE_DOF_ROBOT_NUM_OF_SERVOS	3

#define BASE_SERVO			0
#define SHOULDER_SERVO	1
#define ELBOW_SERVO		2

#include "../Servo/Servo.h"

typedef struct 
{
	double depth_min;
	double depth_max;
	double lateral_min;
	double lateral_max;
	double height_min;
	double height_max;
} ThreeDofRobotLimit;

typedef struct 
{
	double	height;
	double	depth;
	double	lateral;
} ThreeDofRobotPosition;	

typedef struct 
{
	ServoData	servos[THREE_DOF_ROBOT_NUM_OF_SERVOS];
	ThreeDofRobotLimit	security_limits;
	ThreeDofRobotPosition	tip_position;
	ThreeDofRobotPosition	elbow_position;
	double		length_humerus;
	double		length_ulna;
	double		height_ulna;
} ThreeDofRobot;	// X PointOneMicrosec

void submit_arm_length_vals(ThreeDofRobot *robot_arm, double length_humerus, double length_ulna, double height_ulna);
void calculate_forward_kinematics(ThreeDofRobot *robot_arm);
void submit_arm_security_limits(ThreeDofRobot *robot_arm, double depth_min, double depth_max, double lateral_min, double lateral_max, double height_min, double height_max);
bool check_three_dof_robot_out_of_security_limits(ThreeDofRobot *robot_arm);

#endif
