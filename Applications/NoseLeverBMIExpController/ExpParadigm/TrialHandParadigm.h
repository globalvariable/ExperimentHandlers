#ifndef TRIAL_HAND_PARADIGM_H
#define TRIAL_HAND_PARADIGM_H

#include "../../../BlueSpike/System/TimeStamp/TimeStamp.h"
#include "../../../Library/Coordinate/Cartesian.h"
#include "../../../Library/Robot/ThreeDofRobot.h"
#include "../../../BlueSpike/Library/Thresholding/Thresholding.h"
#include "TrialData.h"

#define REWARD_AVERAGING_WINDOW 1
#define DISTANCE_AVERAGING_WINDOW 1
#define ALPHA 80.0
#define BETA 270.0
#define MU 8.0


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
	unsigned int				max_num_of_sessions;
//	Selected values for a trial:
	TrialData					current_trial_data;
	TimeStamp				max_lever_press_interval;
} TrialHandParadigmRobotReach;


#endif
