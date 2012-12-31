#ifndef TRIAL_HISTORY_H
#define TRIAL_HISTORY_H


typedef struct __TrialHistory TrialHistory;

#include <math.h>
#include "TrialData.h"

struct __TrialHistory
{
	TrialData				*history;
	unsigned int 			buff_write_idx;
	unsigned int 			buffer_size;
};

TrialHistory* allocate_trial_history(TrialHistory* hist, unsigned int buffer_size); 
TrialHistory* deallocate_trial_history(TrialHistory* hist); 
double get_abs_mean_of_reward_of_previous_trials(TrialHistory* hist, unsigned int num_of_past_trials);


#endif
