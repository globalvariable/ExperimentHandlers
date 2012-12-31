#include "TrialHistory.h"



TrialHistory* allocate_trial_history(TrialHistory* hist, unsigned int buffer_size)
{
	if (hist != NULL)
	{
		hist = deallocate_trial_history(hist);
		hist = allocate_trial_history(hist, buffer_size);
		return hist;
	}  
	hist = g_new0(TrialHistory,1);
	hist->history = g_new0(TrialData, buffer_size);
	hist->buffer_size = buffer_size;	
	print_message(INFO_MSG ,"ExperimentHandler", "TrialData", "allocate_trials_history", "Created trials_history.");
	return hist;

} 

TrialHistory* deallocate_trial_history(TrialHistory* hist)
{
	if (hist == NULL)
		return (TrialHistory*)print_message(BUG_MSG ,"ExperimentHandler", "TrialData", "allocate_trials_history", "trials_history == NULL.");    
	g_free(hist->history);
	g_free(hist);
	print_message(INFO_MSG ,"TrialControllers", "TrialsData", "deallocate_trials_data", "Destroyed trials_data.");
	return NULL;
}

double get_abs_mean_of_reward_of_previous_trials(TrialHistory* hist, unsigned int num_of_past_trials)
{
	unsigned int start_idx;
	double sum = 0;

	if (hist->buff_write_idx < num_of_past_trials) 
		start_idx = hist->buff_write_idx + hist->buffer_size - num_of_past_trials;
	else
		start_idx = hist->buff_write_idx - num_of_past_trials;
		
	while (start_idx != hist->buff_write_idx)
	{
		sum += fabs(hist->history[start_idx].reward_amount);
		if ((start_idx + 1) == hist->buffer_size)
			start_idx = 0;
		else
			start_idx++;
	} 
	return sum/((double)num_of_past_trials);
}
