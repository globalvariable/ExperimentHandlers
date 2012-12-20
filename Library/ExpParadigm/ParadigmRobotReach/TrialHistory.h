#ifndef TRIAL_HISTORY_H
#define TRIAL_HISTORY_H


typedef struct __TrialsHistory TrialsHistory;

#include "TrialData.h"

struct __TrialHistory
{
	TrialData				*history;
	unsigned int 			buff_write_idx;
	unsigned int 			buffer_size;
};

TrialsHistory* allocate_trials_history(TrialsHistory* hist, unsigned int buffer_size); 
TrialsHistory* deallocate_trials_history(TrialsHistory* hist); 


#endif
