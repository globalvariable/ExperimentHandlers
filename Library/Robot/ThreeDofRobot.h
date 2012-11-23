#ifndef THREE_DOF_ROBOT_H
#define THREE_DOF_ROBOT_H


#define THREE_DOF_ROBOT_NUM_OF_SERVOS	3

#define BASE_SERVO			0
#define SHOULDER_SERVO	1
#define ELBOW_SERVO		2

#define BASE_SERVO_INIT_PULSE			15000
#define SHOULDER_SERVO_INIT_PULSE	15000
#define ELBOW_SERVO_INIT_PULSE		15000

#include <math.h>
#include "../Servo/Servo.h"

typedef struct 
{
	ServoData	servos[THREE_DOF_ROBOT_NUM_OF_SERVOS];
	double		tip_height;
	double		tip_depth;
	double		tip_lateral;
	double		elbow_height;
	double		elbow_depth;
	double		elbow_lateral;
	double		length_humerus;
	double		length_ulna;
	double		height_ulna;
} ThreeDofRobot;	// X PointOneMicrosec

void submit_arm_length_vals(ThreeDofRobot *robot_arm, double length_humerus, double length_ulna, double height_ulna);
void calculate_forward_kinematics(ThreeDofRobot *robot_arm);

#endif
