#include"TrialData.h"


TrialsHistory* allocate_trials_history(TrialsHistory* hist, unsigned int buffer_size)
{
	if (hist != NULL)
	{
		hist = deallocate_trials_history(hist);
		hist = allocate_trials_history(hist, buffer_size);
		return hist;
	}  
	hist = g_new0(TrialsHistory,1);
	hist->history = g_new0(TrialData, buffer_size);
	hist->buffer_size = buffer_size;	
	print_message(INFO_MSG ,"ExperimentHandler", "TrialData", "allocate_trials_history", "Created trials_history.");
	return hist;

} 

TrialsHistory* deallocate_trials_history(TrialsHistory* hist)
{
	if (hist == NULL)
		return (TrialsHistory*)print_message(BUG_MSG ,"ExperimentHandler", "TrialData", "allocate_trials_history", "trials_history == NULL.");    
	g_free(hist->history);
	g_free(hist);
	print_message(INFO_MSG ,"TrialControllers", "TrialsData", "deallocate_trials_data", "Destroyed trials_data.");
	return NULL;
}
