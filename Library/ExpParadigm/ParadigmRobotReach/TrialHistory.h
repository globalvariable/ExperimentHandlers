#ifndef TRIAL_HISTORY_H
#define TRIAL_HISTORY_H


typedef struct __TrialHistory TrialHistory;
typedef struct __ClassifiedTrialHistory ClassifiedTrialHistory;

#include <math.h>
#include "TrialData.h"

struct __TrialHistory    
{
	TrialData				*history;
	unsigned int 			buff_write_idx;    ///   IT IS USED AS TRIAL NUMBER AS WELL: SO THAT THE TRIAL HANDLING CAPACITY OF THE SYSTEM IS LIMITED BY BUFFER SIZE
	unsigned int 			buffer_size;
};

struct __ClassifiedTrialHistory
{
	TrialHistory			*all_trials;
	TrialHistory			***trial_types;
	unsigned int num_of_start_positions;
	unsigned int num_of_target_positions;
};


TrialHistory* allocate_trial_history(TrialHistory* hist, unsigned int buffer_size); 
TrialHistory* deallocate_trial_history(TrialHistory* hist); 

ClassifiedTrialHistory* allocate_classified_trial_history(ClassifiedTrialHistory* classified_hist, unsigned int buffer_size, unsigned int num_of_start_positions, unsigned int num_of_target_positions);
ClassifiedTrialHistory* deallocate_classified_trial_history(ClassifiedTrialHistory* classified_hist);
bool write_trial_data_to_classified_trial_history(ClassifiedTrialHistory* classified_history, unsigned int robot_start_position_idx, unsigned int robot_target_position_idx, TrialData *trial_data);

double get_abs_mean_of_reward_of_previous_trials(TrialHistory* hist, unsigned int num_of_past_trials);
TimeStamp get_previous_trial_type_trial_length(ClassifiedTrialHistory* hist, unsigned int start_position_idx, unsigned int target_position_idx);
double get_previous_trial_type_remained_distance_to_target(ClassifiedTrialHistory* hist, unsigned int start_position_idx, unsigned int target_position_idx);
double calculate_and_get_windowed_binary_reward_average(ClassifiedTrialHistory* hist, TrialData *trial_data, unsigned int window_size);
TimeStamp calculate_and_get_trial_length_windowed_average(ClassifiedTrialHistory* hist, TrialData *trial_data, unsigned int window_size);
#endif
