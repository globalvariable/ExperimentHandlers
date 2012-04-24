#ifndef TRIAL_DATA

typedef struct __TrialData TrialData;
typedef struct __TrialDataHistory TrialDataHistory;



struct __TrialData
{
	TimeStamp	trial_start_time;   
	TimeStamp	trial_end_time;	// this is set before trial start during simulations. behaviors determines this during in vivo experiments.
	TrialType		trial_type;	// left, right, tracjectroy right etc. 
	bool		rewarded;
	unsigned int	rewarding_threshold;
};


struct __TrialDataHistory
{
	TrialData				history[TRIAL_DATA_HISTORY_SIZE];
	unsigned int 			buff_write_idx;
};
