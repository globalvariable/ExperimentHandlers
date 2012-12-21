#ifndef MOV_OBJ_HAND_PARADIGM_H
#define MOV_OBJ_HAND_PARADIGM_H

#include "../../../BlueSpike/System/TimeStamp/TimeStamp.h"
#include "../../../BlueSpike/Library/Thresholding/Thresholding.h"
#include "../../Coordinate/Cartesian.h"
#include "../../Robot/ThreeDofRobot.h"

typedef struct 
{
	unsigned int				selected_position_idx;	
	unsigned int				num_of_positions;
	CartesianCoordinates		*cart_coordinates;
	ThreeDofRobotServoPulse	*robot_pulse_widths;
} RobotSpacePoints;

typedef struct 
{
	EllipsoidThreshold			selected_target_threshold;
	EllipsoidThreshold			min_target_threshold;
	EllipsoidThreshold			max_target_threshold;
	double					target_threshold_change_rate;
	EllipsoidThreshold			point_threshold;
}
MovObjThreshold;


typedef struct 
{
	TimeStamp				stay_at_start_duration;
	TimeStamp				stay_at_target_duration;	
	TimeStamp				send_pw_command_wait_period;
	TimeStamp				receive_position_wait_period;
	MovObjThreshold			threshold;
	RobotSpacePoints			start_info;
	RobotSpacePoints			target_info;
} MovObjHandParadigmRobotReach;



#endif
