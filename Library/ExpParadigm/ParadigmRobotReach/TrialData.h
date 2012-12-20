#ifndef TRIAL_DATA_H
#define TRIAL_DATA_H


typedef struct __TrialData TrialData;


#include "../../../BlueSpike/System/TimeStamp/TimeStamp.h"
#include "TrialTypes.h"

struct __TrialData
{
	TimeStamp			trial_start_time;   
	TimeStamp			trial_end_time;	// this is set before trial start during simulations. behaviors determines this during in vivo experiments.
	CartesianCoordinates	start_coordinates;
	CartesianCoordinates	target_coordinates;
	bool				rewarded;
	EllipsoidThreshold		rewarding_threshold;
};





#endif
