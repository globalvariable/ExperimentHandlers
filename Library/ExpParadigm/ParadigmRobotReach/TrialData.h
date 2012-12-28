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
	unsigned int			target_led_component_list_idx;
	unsigned int			robot_start_position_idx;
	unsigned int			robot_target_position_idx;
	double				reward_amount;
	EllipsoidThreshold		rewarding_threshold;
};





#endif
