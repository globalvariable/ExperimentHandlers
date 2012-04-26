#include "TrialStats.h"

TrialStatsData* allocate_trial_stats_data(TrialStatsData* data)
{
	if (data != NULL)
	{
		data = deallocate_trial_stats_data(data);
		data = allocate_trial_stats_data(data);
		return data;
	}  
	data = g_new0(TrialStatsData,1);
	print_message(INFO_MSG ,"ExperimentHandlers", "TrialStats", "allocate_trial_stats_data", "Created trial_stats_data.");
	return data;	
}

TrialStatsData* deallocate_trial_stats_data(TrialStatsData* data)
{
	if (data == NULL)
		return (TrialStatsData*)print_message(BUG_MSG ,"ExperimentHandlers", "TrialStats", "deallocate_trial_stats_data", "trial_stats_data == NULL.");    
	g_free(data->trial_type_stats);
	g_free(data);
	print_message(INFO_MSG ,"ExperimentHandlers", "TrialStats", "deallocate_stats_data", "Destroyed trial_stats_data.");
	return NULL;
}

bool add_trial_type_to_trial_stats_data(TrialTypesData* trial_types_data, TrialStatsData* trial_stats_data)
{
	unsigned int i;
	TrialTypeStats *lcl_trial_type_stats;
	lcl_trial_type_stats = g_new0(TrialTypeStats, trial_types_data->num_of_trial_types + 1);
	for (i = 0; i < trial_types_data->num_of_trial_types; i++)
		lcl_trial_type_stats[i] = trial_stats_data->trial_type_stats[i];
	g_free(trial_stats_data->trial_type_stats);
	trial_stats_data->trial_type_stats = lcl_trial_type_stats;
	print_message(INFO_MSG ,"ExperimentHandlers", "TrialStats", "add_trial_type_to_trial_stats_data", "Added new trial type stats for new trial type added to trial_types_data.");	
	return TRUE;
}
