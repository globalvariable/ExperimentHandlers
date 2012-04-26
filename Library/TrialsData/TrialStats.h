#ifndef TRIAL_STATS_H
#define TRIAL_STATS_H

typedef struct __TrialStatsData TrialStatsData;
typedef struct __TrialTypeStats TrialTypeStats;

#include <gtk/gtk.h>
#include <stdbool.h>
#include "TrialTypes.h"

struct __TrialTypeStats
{
	unsigned int					num_of_trials;  
	unsigned int					num_of_rewarded_trials;
};

struct __TrialStatsData
{
	unsigned int 					num_of_trials;	
	unsigned int					num_of_rewarded_trials;
	TrialTypeStats				*trial_type_stats;    // num_of_trial_types in trial types data
};


TrialStatsData* allocate_trial_stats_data(TrialStatsData* data);
TrialStatsData* deallocate_trial_stats_data(TrialStatsData* data);
bool add_trial_type_to_trial_stats_data(TrialTypesData* trial_types_data, TrialStatsData* trial_stats_data);

#endif
