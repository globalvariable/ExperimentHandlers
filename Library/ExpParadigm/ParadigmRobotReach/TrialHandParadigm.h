#ifndef TRIAL_HAND_PARADIGM_H
#define TRIAL_HAND_PARADIGM_H

#include "../../../BlueSpike/System/TimeStamp/TimeStamp.h"
#include "../../Coordinate/Cartesian.h"
#include "../../Robot/ThreeDofRobot.h"
#include "../../../BlueSpike/Library/Thresholding/Thresholding.h"
#include "TrialData.h"

typedef struct 
{
	unsigned int				num_of_robot_start_positions;
	unsigned int				num_of_robot_target_positions;
	unsigned int				*target_led_component_indexes_list;
	unsigned int				num_of_target_led_components;
	TimeStamp				max_trial_length;			
	TimeStamp				min_trial_refractory;	
	TimeStamp				max_extra_trial_refractory;
	EllipsoidThreshold			min_target_reach_threshold;
	EllipsoidThreshold			max_target_reach_threshold;
	double					target_reach_threshold_change_rate;
//	Selected values for a trial:
	TrialData					current_trial_data;
} TrialHandParadigmRobotReach;


#endif
