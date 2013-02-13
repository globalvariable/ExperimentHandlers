#ifndef MOV_OBJ_HAND_PARADIGM_H
#define MOV_OBJ_HAND_PARADIGM_H

#include "../../../BlueSpike/System/TimeStamp/TimeStamp.h"
#include "../../../BlueSpike/Library/Thresholding/Thresholding.h"
#include "../../../Library/Coordinate/Cartesian.h"
#include "../../../Library/Robot/ThreeDofRobot.h"

typedef struct 
{
	unsigned int				selected_position_idx;	
	unsigned int				num_of_positions;
	CartesianCoordinates		*cart_coordinates;
	ThreeDofRobotServoPulse	*robot_pulse_widths;
} RobotSpacePoints;

typedef struct 
{
	EllipsoidThreshold			point_reach_threshold;
}
MovObjThreshold;


typedef struct 
{
	TimeStamp					stay_at_start_duration;
	TimeStamp					stay_at_target_duration;	
	TimeStamp					send_pw_command_wait_period;
	TimeStamp					receive_position_wait_period;
	double						spike_2_pulse_width_multiplier;
	ServoPulseChange			max_pulse_width_change;   // for servo control in handle spike data buff. It determines max servo speed.
	MovObjThreshold				threshold;
	RobotSpacePoints				start_info;
	RobotSpacePoints				target_info;
	ThreeDofRobotCartesianLimit	cartesian_space_limits;	// interrupt pulsing servos, robot goes to somewhere dangerous
	ServoAngularLimit				polar_space_limits[THREE_DOF_ROBOT_NUM_OF_SERVOS];
} MovObjHandParadigmRobotReach;

bool submit_cartesian_robotic_space_borders(ThreeDofRobot *robot_arm, MovObjHandParadigmRobotReach *paradigm, double depth_min, double depth_max, double lateral_min, double lateral_max, double height_min, double height_max);
bool submit_polar_robotic_space_borders(ThreeDofRobot *robot_arm, MovObjHandParadigmRobotReach *paradigm, double joint_angle_base_lower_limit, double joint_angle_base_upper_limit, double joint_angle_shoulder_lower_limit, double joint_angle_shoulder_upper_limit, double joint_angle_elbow_lower_limit, double joint_angle_elbow_upper_limit);
bool check_robot_space_borders(ThreeDofRobot *robot_arm, MovObjHandParadigmRobotReach *paradigm);

#endif
