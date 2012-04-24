

typedef struct __TrialStats TrialStats;

struct __TrialStats
{
	unsigned int 					num_of_trials;	// number of trials in linked list
	unsigned int					num_of_trials_in_trial_type[NUM_OF_TRIAL_TYPES];
	unsigned int					num_of_rewarded_trials;
	unsigned int					num_of_rewarded_trials_in_trial_type[NUM_OF_TRIAL_TYPES];
};
