#ifndef TRIAL_DATA_H
#define TRIAL_DATA_H


typedef struct __TrialData TrialData;

#include <stdbool.h>
#include "../../../BlueSpike/System/TimeStamp/TimeStamp.h"
#include "../../../BlueSpike/Library/Thresholding/Thresholding.h"
#include "../../../BlueSpike/Library/Misc/Misc.h"

struct __TrialData
{
	TimeStamp			trial_start_time;   
	TimeStamp			trial_end_time;	// this is set before trial start during simulations. behaviors determines this during in vivo experiments.
	TimeStamp			trial_length;
	unsigned int			target_led_component_list_idx;
	unsigned int			robot_start_position_idx;
	unsigned int			robot_target_position_idx;
	double				reward_magnitude;
	bool				binary_reward; 
	double				binary_reward_windowed_average; 
	TimeStamp			trial_length_windowed_average; 
	double				remained_distance_to_target;
	double				initial_distance_to_target;
	EllipsoidThreshold		rewarding_threshold;
	unsigned int			gui_selected_target_position_idx;
	bool				auto_target_select_mode_on;
};





#endif
