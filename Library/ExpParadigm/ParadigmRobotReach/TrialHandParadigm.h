#ifndef TRIAL_HAND_PARADIGM_H
#define TRIAL_HAND_PARADIGM_H

#include "../../../BlueSpike/System/TimeStamp/TimeStamp.h"
#include "../Coordinate/Cartesian.h"



typedef struct 
{
	unsigned int			num_of_reach_positions;
	unsigned int			num_of_start_positions;
	CartesianCoordinates	*target_positions;
	CartesianCoordinates	*start_positions;
	TimeStamp			max_trial_length;			
	TimeStamp			trial_refractory;	
} TrialHandParadigmRobotReach;



#endif
