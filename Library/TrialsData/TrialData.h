#ifndef TRIALS_DATA_H
#define TRIALS_DATA_H

typedef struct __TrialData TrialData;
typedef struct __TrialsHistory TrialsHistory;

#include "../../../BlueSpike/TimeStamp.h"
#include "TrialTypes.h"

struct __TrialData
{
	TimeStamp	trial_start_time;   
	TimeStamp	trial_end_time;	// this is set before trial start during simulations. behaviors determines this during in vivo experiments.
	TrialType		trial_type;	// left, right, tracjectroy right etc. 
	bool		rewarded;
	unsigned int	rewarding_threshold;
};


struct __TrialsHistory
{
	TrialData				*history;
	unsigned int 			buff_write_idx;
	unsigned int 			buffer_size;
};

TrialsHistory* allocate_trials_history(TrialsHistory* hist, unsigned int buffer_size); 
TrialsHistory* deallocate_trials_history(TrialsHistory* hist); 
void increment_trials_history_write_idx(TrialsHistory* hist);

#endif
