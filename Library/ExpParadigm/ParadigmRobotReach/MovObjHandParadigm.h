#ifndef MOV_OBJ_HAND_PARADIGM_H
#define MOV_OBJ_HAND_PARADIGM_H

#include "../../../BlueSpike/System/TimeStamp/TimeStamp.h"
#include "../../../BlueSpike/Library/Thresholding/Thresholding.h"
#include "../../Coordinate/Cartesian.h"
#include "../../Robot/ThreeDofRobot.h"

typedef struct 
{
	TimeStamp				stay_at_start_duration;
	TimeStamp				stay_at_target_duration;	
	TimeStamp				send_pw_command_wait_period;
	TimeStamp				receive_position_wait_period;
	ThreeDofRobotServoPulse	move_to_target_position_pulse;		//  pulse width value of starting position or target. Trial Handler provides this info before resetting position to start position or target position. 
	EllipsoidThreshold			target_threshold;
} MovObjHandParadigmRobotReach;



#endif
