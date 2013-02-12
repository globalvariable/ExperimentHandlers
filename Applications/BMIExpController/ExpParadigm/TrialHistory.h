#ifndef TRIAL_HISTORY_H
#define TRIAL_HISTORY_H


typedef struct __TrialHistory TrialHistory;
typedef struct __ClassifiedTrialHistory ClassifiedTrialHistory;

#include <math.h>
#include "TrialData.h"

struct __TrialHistory    
{
	TrialData				*history;
	unsigned int 			buff_write_idx;    
	unsigned int 			buffer_size;	
};

struct __ClassifiedTrialHistory
{
	TrialHistory			*all_trials;
	TrialHistory			***trial_types;	
	TrialHistory			****trial_types_sessions;   // num_of_sessions * num_of_start_positions * num_of_target_positions
	unsigned int num_of_start_positions;   //GET RID OF THIS in when you have multi starting point. reward is related to target, not starting position.
	unsigned int num_of_target_positions;
	unsigned int num_of_sessions;
};


TrialHistory* allocate_trial_history(TrialHistory* hist, unsigned int buffer_size); 
TrialHistory* deallocate_trial_history(TrialHistory* hist); 

ClassifiedTrialHistory* allocate_classified_trial_history(ClassifiedTrialHistory* classified_hist, unsigned int buffer_size, unsigned int num_of_start_positions, unsigned int num_of_target_positions, unsigned int num_of_sessions);
ClassifiedTrialHistory* deallocate_classified_trial_history(ClassifiedTrialHistory* classified_hist);
bool write_trial_data_to_classified_trial_history(ClassifiedTrialHistory* classified_history, TrialData *trial_data);

double get_abs_mean_of_reward_of_previous_trials(TrialHistory* hist, unsigned int num_of_past_trials);
TimeStamp get_previous_trial_type_trial_length(ClassifiedTrialHistory* hist, unsigned int start_position_idx, unsigned int target_position_idx);
double get_previous_trial_type_remained_distance_to_target(ClassifiedTrialHistory* hist, unsigned int start_position_idx, unsigned int target_position_idx);
double calculate_and_get_windowed_binary_reward_average(ClassifiedTrialHistory* hist, TrialData *trial_data, unsigned int window_size);
TimeStamp calculate_and_get_trial_length_windowed_average(ClassifiedTrialHistory* hist, TrialData *trial_data, unsigned int window_size);
double calculate_and_get_remained_distance_to_target_windowed_average(ClassifiedTrialHistory* hist, TrialData *trial_data, unsigned int window_size);
TrialData* get_previous_trial_history_data_ptr(TrialHistory* hist);
#endif
