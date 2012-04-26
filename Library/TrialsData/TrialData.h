#ifndef TRIAL_DATA

typedef struct __TrialData TrialData;
typedef struct __TrialsHistory TrialsHistory;



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

#endif
