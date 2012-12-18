#ifndef MOV_OBJ_HAND_PARADIGM_H
#define MOV_OBJ_HAND_PARADIGM_H

#include "../../../BlueSpike/System/TimeStamp/TimeStamp.h"
#include "../../../BlueSpike/Library/Thresholding/Thresholding.h"
#include "../../Coordinate/Cartesian.h"

typedef struct 
{
	TimeStamp			stay_at_start_duration;
	TimeStamp			stay_at_target_duration;	
	TimeStamp			send_command_wait_period;
	TimeStamp			receive_position_wait_period;
	ServoPulse			start_position_pulse[3];
	ServoPulse			target_position_pulse[3];
	EllipsoidThreshold		target_threshold;
} MovObjHandParadigmRobotReach;



#endif
