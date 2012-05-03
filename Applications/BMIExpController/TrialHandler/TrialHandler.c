#include "TrialHandler.h"



int main( int argc, char *argv[])
{
	TrialTypesData *trial_types_data = NULL;	
	TrialsHistory *trials_history = NULL; 
	TrialStatsData *trial_stats_data = NULL;

   	shared_memory = (SharedMemStruct*)rtai_malloc(nam2num(SHARED_MEM_NAME), SHARED_MEM_SIZE);
	if (shared_memory == NULL) 
		return print_message(ERROR_MSG ,"BMIExpController", "TrialHandler", "main", "shared_memory == NULL.");
	trial_types_data = allocate_trial_types_data(trial_types_data);
	trial_stats_data = allocate_trial_stats_data(trial_stats_data);
	trials_history = allocate_trials_history(trials_history, 1000);
	if (! add_trial_type_to_trial_types_data(trial_types_data, TRIAL_TYPE_IN_VIVO_BMI_LEFT_TARGET, 5000000000, 4000000000)) 
		return print_message(ERROR_MSG ,"BMIExpController", "TrialHandler", "main", "! add_trial_type_to_trial_types_data().");
	if (! add_trial_type_to_trial_stats_data(trial_types_data, trial_stats_data))
		return print_message(ERROR_MSG ,"BMIExpController", "TrialHandler", "main", "! add_trial_type_to_stats_types_data().");
	if (! add_trial_type_to_trial_types_data(trial_types_data, TRIAL_TYPE_IN_VIVO_BMI_RIGHT_TARGET, 5000000000, 4000000000)) 
		return print_message(ERROR_MSG ,"BMIExpController", "TrialHandler", "main", "! add_trial_type_to_trial_types_data().");
	if (! add_trial_type_to_trial_stats_data(trial_types_data, trial_stats_data))
		return print_message(ERROR_MSG ,"BMIExpController", "TrialHandler", "main", "! add_trial_type_to_stats_types_data().");

	gtk_init(&argc, &argv);
	create_gui_handler(trial_types_data, trial_stats_data, trials_history);
	gtk_main();
	return 0;
}	



