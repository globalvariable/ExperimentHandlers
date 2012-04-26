#include "TrialHandler.h"

#define MAX_TRIAL_LENGTH		10000000000UL	// 10 seconds
#define MAX_TRIAL_REFRACTORY	4000000000UL	// 4 seconds

static TrialStatus trial_status = TRIAL_STATUS_NULL;   // Only trial handler can change trial status. 

static TrialTypesData *trial_types_data;	// IN SHARED MEMO  only trial handler can write here, only trial handler gui can read. For SpikeGenerator redefine it
static TrialsHistory *trials_history;   // only trial handler can write here, others can read.
static TrialStats *trial_stats; // only trial handler can write here, others can read.

TrialTypesData *get_trial_types_data(void)
{
	return trial_types_data;
}

int main( int argc, char *argv[])
{
   	shared_memory = (SharedMemStruct*)rtai_malloc(nam2num(SHARED_MEM_NAME), SHARED_MEM_SIZE);
	if (shared_memory == NULL) {
		print_message(ERROR_MSG ,"BMISimulationTrialController", "BMISimulationTrialController", "main", "shared_memory == NULL.");	return -1; }
	initialize_trial_handler();
	gtk_init(&argc, &argv);
	create_gui();
	gtk_main();
	return 0;
}	

bool initialize_trial_handler(void)
{
	trial_status = TRIAL_STATUS_TRIALS_DISABLED;

	trial_types_data = g_new0(TrialTypesData, 1);
	trials_history = g_new0(TrialsHistory, 1);
	trial_stats = g_new0(TrialStats, 1);

	if (! add_trial_type_to_trial_types_data(trial_types_data, TRIAL_TYPE_IN_VIVO_BMI_LEFT_TARGET, MAX_TRIAL_LENGTH, MAX_TRIAL_REFRACTORY)) 
		return print_message(ERROR_MSG ,"BMIExpController", "TrialHandler", "initialize_trial_handler", "! add_trial_type_to_trial_types_data().");
	if (! add_trial_type_to_trial_types_data(trial_types_data, TRIAL_TYPE_IN_VIVO_BMI_RIGHT_TARGET, MAX_TRIAL_LENGTH, MAX_TRIAL_REFRACTORY)) 
		return print_message(ERROR_MSG ,"BMIExpController", "TrialHandler", "initialize_trial_handler", "! add_trial_type_to_trial_types_data().");
	
	return TRUE;
}



