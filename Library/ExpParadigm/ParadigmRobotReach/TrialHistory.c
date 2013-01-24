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
		return (TrialHistory*)print_message(BUG_MSG ,"ExperimentHandler", "TrialData", "deallocate_trials_history", "trials_history == NULL.");    
	g_free(hist->history);
	g_free(hist);
	print_message(INFO_MSG ,"TrialControllers", "TrialsData", "deallocate_trials_data", "Destroyed trials_data.");
	return NULL;
}

ClassifiedTrialHistory* allocate_classified_trial_history(ClassifiedTrialHistory* classified_hist, unsigned int buffer_size, unsigned int num_of_start_positions, unsigned int num_of_target_positions)
{
	unsigned int i, j;
	if (classified_hist != NULL)
	{
		classified_hist = deallocate_classified_trial_history(classified_hist);
		classified_hist = allocate_classified_trial_history(classified_hist, buffer_size, num_of_start_positions, num_of_target_positions);
		return classified_hist;
	}  
	classified_hist = g_new0(ClassifiedTrialHistory,1);
	classified_hist->all_trials = allocate_trial_history(classified_hist->all_trials, buffer_size);

	classified_hist->trial_types = g_new0(TrialHistory**, num_of_start_positions);
	for (i = 0; i < num_of_start_positions; i++)
	{
		classified_hist->trial_types[i] = g_new0(TrialHistory*, num_of_target_positions);
		for (j = 0; j < num_of_target_positions; j++)
		{
			classified_hist->trial_types[i][j] = allocate_trial_history(classified_hist->trial_types[i][j], buffer_size);
		}
	}
	
	classified_hist->num_of_start_positions = num_of_start_positions;	
	classified_hist->num_of_target_positions = num_of_target_positions;	

	print_message(INFO_MSG ,"ExperimentHandler", "TrialData", "allocate_classified_trial_history", "Created classified_trials_history.");
	return classified_hist;	

}
ClassifiedTrialHistory* deallocate_classified_trial_history(ClassifiedTrialHistory* classified_hist)
{
	unsigned int i, j;
	if (classified_hist == NULL)
		return (ClassifiedTrialHistory*)print_message(BUG_MSG ,"ExperimentHandler", "TrialData", "deallocate_classified_trial_history", "classified_trials_history == NULL.");    


	for (i = 0; i < classified_hist->num_of_start_positions; i++)
	{
		for (j = 0; j < classified_hist->num_of_target_positions; j++)
		{
			classified_hist->trial_types[i][j] = deallocate_trial_history(classified_hist->trial_types[i][j]);
		}
		g_free(classified_hist->trial_types[i]);
	}
	g_free(classified_hist->trial_types);
	g_free(classified_hist);

	print_message(INFO_MSG ,"TrialControllers", "TrialsData", "deallocate_trials_data", "Destroyed trials_data.");
	return NULL;	
}

bool write_trial_data_to_classified_trial_history(ClassifiedTrialHistory* classified_history, unsigned int robot_start_position_idx, unsigned int robot_target_position_idx, TrialData *trial_data)
{
	memcpy(&(classified_history->all_trials->history[classified_history->all_trials->buff_write_idx]), trial_data, sizeof(TrialData));
	memcpy(&(classified_history->trial_types[trial_data->robot_start_position_idx][trial_data->robot_target_position_idx]->history[classified_history->trial_types[trial_data->robot_start_position_idx][trial_data->robot_target_position_idx]->buff_write_idx]), trial_data, sizeof(TrialData));
	if ((classified_history->all_trials->buff_write_idx + 1) == classified_history->all_trials->buffer_size)   // do not expand this buffer. All design is realised according to its this. It is a NON CIRCULAR BUFFER.
		return print_message(ERROR_MSG ,"ExperimentHandler", "TrialData", "write_trial_data_to_classified_trial_history", "classified_history->all_trials->buffer is FULL!!!.");    	
	if ((classified_history->trial_types[trial_data->robot_start_position_idx][trial_data->robot_target_position_idx]->buff_write_idx + 1) == classified_history->trial_types[trial_data->robot_start_position_idx][trial_data->robot_target_position_idx]->buffer_size)   // do not expand this buffer. All design is realised according to its this. It is a NON CIRCULAR BUFFER.
		return print_message(ERROR_MSG ,"ExperimentHandler", "TrialData", "write_trial_data_to_classified_trial_history", "classified_history->trial_types[m][n]->buffer is FULL!!!.");  
	classified_history->all_trials->buff_write_idx++;
   	classified_history->trial_types[trial_data->robot_start_position_idx][trial_data->robot_target_position_idx]->buff_write_idx++; 
	return TRUE;
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
		sum += fabs(hist->history[start_idx].reward_magnitude);
		if ((start_idx + 1) == hist->buffer_size)
			start_idx = 0;
		else
			start_idx++;
	} 
	return sum/((double)num_of_past_trials);
}

TimeStamp get_previous_trial_type_trial_length(ClassifiedTrialHistory* hist, unsigned int start_position_idx, unsigned int target_position_idx)
{
	unsigned int idx; 
	if (hist->trial_types[start_position_idx][target_position_idx]->buff_write_idx == 0)
		 idx = hist->trial_types[start_position_idx][target_position_idx]->buffer_size - 1;
	else
		 idx = hist->trial_types[start_position_idx][target_position_idx]->buff_write_idx - 1;

	return hist->trial_types[start_position_idx][target_position_idx]->history[idx].trial_length;
}

double get_previous_trial_type_remained_distance_to_target(ClassifiedTrialHistory* hist, unsigned int start_position_idx, unsigned int target_position_idx)
{
	unsigned int idx; 
	if (hist->trial_types[start_position_idx][target_position_idx]->buff_write_idx == 0)
		 idx = hist->trial_types[start_position_idx][target_position_idx]->buffer_size - 1;
	else
		 idx = hist->trial_types[start_position_idx][target_position_idx]->buff_write_idx - 1;

	return hist->trial_types[start_position_idx][target_position_idx]->history[idx].remained_distance_to_target;
}

double calculate_and_get_windowed_binary_reward_average(ClassifiedTrialHistory* hist, TrialData *trial_data, unsigned int window_size)
{
	unsigned int write_idx_prev; 

	if (hist->trial_types[trial_data->robot_start_position_idx][trial_data->robot_target_position_idx]->buff_write_idx == 0)
		 write_idx_prev = hist->trial_types[trial_data->robot_start_position_idx][trial_data->robot_target_position_idx]->buffer_size - 1;
	else
		 write_idx_prev = hist->trial_types[trial_data->robot_start_position_idx][trial_data->robot_target_position_idx]->buff_write_idx - 1;	

	trial_data->binary_reward_windowed_average = ((hist->trial_types[trial_data->robot_start_position_idx][trial_data->robot_target_position_idx]->history[write_idx_prev].binary_reward_windowed_average * window_size) + ((double)trial_data->binary_reward)) / ((double)(window_size+1));

	return trial_data->binary_reward_windowed_average;
}

TimeStamp calculate_and_get_trial_length_windowed_average(ClassifiedTrialHistory* hist, TrialData *trial_data, unsigned int window_size)
{
	unsigned int write_idx_prev; 

	if ( hist->trial_types[trial_data->robot_start_position_idx][trial_data->robot_target_position_idx]->buff_write_idx == 0)
		 write_idx_prev = hist->trial_types[trial_data->robot_start_position_idx][trial_data->robot_target_position_idx]->buffer_size - 1;
	else
		 write_idx_prev = hist->trial_types[trial_data->robot_start_position_idx][trial_data->robot_target_position_idx]->buff_write_idx - 1;		

	trial_data->trial_length_windowed_average = ((hist->trial_types[trial_data->robot_start_position_idx][trial_data->robot_target_position_idx]->history[write_idx_prev].trial_length_windowed_average * window_size) + trial_data->trial_length) / (window_size+1);

	return trial_data->trial_length_windowed_average;
}
