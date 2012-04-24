#include "TrialHandler.h"

#define MAX_TRIAL_LENGTH		10000000000UL	// 10 seconds
#define MAX_TRIAL_REFRACTORY	4000000000UL	// 4 seconds

static TrialStatus trial_status = TRIAL_STATUS_NULL;   // Only trial handler can change trial status. 

static TrialTypesData *trial_types_data;	// IN SHARED MEMO  only trial handler can write here, others can read.
static TrialsHistory *trials_history;   // only trial handler can write here, others can read.
static TrialStats *trial_stats; // only trial handler can write here, others can read.



bool initialize_trial_handler(void)
{
	trial_status = TRIAL_STATUS_TRIALS_DISABLED;
	trial_types_data = rtai_malloc(nam2num("TRIALTYPES"), sizeof(TrialTypesData));
	if (trial_types_data == NULL)
		print_message(ERROR_MSG ,"BMIExpController", "TrialHandler", "initialize_trial_handler", "trial_types_data == NULL.");
	trials_history = g_new0(TrialsHistory, 1);
	trial_stats = g_new0(TrialStats, 1);

	if (! add_trial_type_to_trial_types_data(trial_types_data, TRIAL_TYPE_RT_BMI_LEFT_TARGET, 0, MAX_TRIAL_LENGTH, MAX_TRIAL_REFRACTORY)) 
		return print_message(ERROR_MSG ,"BMIExpController", "TrialHandler", "initialize_trial_handler", "! add_trial_type_to_trial_types_data().");
	if (! add_trial_type_to_trial_types_data(trial_types_data, TRIAL_TYPE_RT_BMI_RIGHT_TARGET, 1, MAX_TRIAL_LENGTH, MAX_TRIAL_REFRACTORY)) 
		return print_message(ERROR_MSG ,"BMIExpController", "TrialHandler", "initialize_trial_handler", "! add_trial_type_to_trial_types_data().");
	
	return TRUE;
}

