#ifndef TRIAL_HAND_PARADIGM_H
#define TRIAL_HAND_PARADIGM_H

#include "../../../BlueSpike/System/TimeStamp/TimeStamp.h"
#include "../../Coordinate/Cartesian.h"
#include "../../Robot/ThreeDofRobot.h"



typedef struct 
{
	unsigned int				selected_robot_start_position_idx;
	unsigned int				selected_robot_target_position_idx;
	unsigned int				num_of_robot_start_positions;
	unsigned int				num_of_robot_target_positions;
	TimeStamp				max_trial_length;			
	TimeStamp				trial_refractory;	
} TrialHandParadigmRobotReach;


#endif
