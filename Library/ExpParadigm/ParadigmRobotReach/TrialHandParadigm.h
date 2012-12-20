#ifndef TRIAL_HAND_PARADIGM_H
#define TRIAL_HAND_PARADIGM_H

#include "../../../BlueSpike/System/TimeStamp/TimeStamp.h"
#include "../../Coordinate/Cartesian.h"
#include "../../Robot/ThreeDofRobot.h"

typedef struct 
{
	unsigned int				num_of_positions;
	CartesianCoordinates		*cart_coordinates;
	ThreeDofRobotServoPulse	*robot_pulse_widths;
} RobotReachStart;

typedef struct 
{
	unsigned int				num_of_positions;
	CartesianCoordinates		*cart_coordinates;
	ThreeDofRobotServoPulse	*robot_pulse_widths;
	unsigned int				*target_led_comp_idx;   //  ExpEnviOutputCompTypeData index in ExpEnviData  // TrialHandler sends this index when a trial starts
} RobotReachTarget;

typedef struct 
{
	RobotReachStart			start_info;
	RobotReachTarget			target_info;
	unsigned int				current_trial_start_position_idx;
	unsigned int				current_trial_target_position_idx;
	TimeStamp				max_trial_length;			
	TimeStamp				trial_refractory;	
} TrialHandParadigmRobotReach;

TrialHandParadigmRobotReach *allocate_trial_hand_paradigm(unsigned int num_of_start_positions, unsigned int num_of_target_positions);

#endif
