

typedef struct __TrialStats TrialStats;
typedef struct __TrialTypeStats TrialTypeStats;

struct __TrialTypeStats
{
	unsigned int					num_of_trials;  
	unsigned int					num_of_rewarded_trials;
};

struct __TrialStats
{
	unsigned int 					num_of_trials;	
	unsigned int					num_of_rewarded_trials;
	TrialTypeStats				*trial_type_stats;    // num_of_trial_types in trial types data
};
