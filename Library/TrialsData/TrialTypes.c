#include "TrialTypes.h"

bool get_trial_type_string(TrialType trial_type, char *str)  // pass NULL for only check trial type validity.
{
	switch (trial_type)
	{
////            RT_TRIALS    (REAL_TIME)
		case TRIAL_TYPE_RT_BMI_LEFT_TARGET:
			if (str != NULL)
				strcpy(str, "TRIAL_TYPE_RT_BMI_LEFT_TARGET");
			return TRUE;
		case TRIAL_TYPE_RT_BMI_RIGHT_TARGET:
			if (str != NULL)
				strcpy(str, "TRIAL_TYPE_RT_BMI_RIGHT_TARGET");	
			return TRUE;
									
////            RAT_TRAINING_TRIALS   
		case TRIAL_TYPE_RAT_TRAINING_ROBOT_TO_LEFT:
			if (str != NULL)
				strcpy(str, "TRIAL_TYPE_RAT_TRAINING_ROBOT_TO_LEFT");
			return TRUE;
		case TRIAL_TYPE_RAT_TRAINING_ROBOT_TO_RIGHT:
			if (str != NULL)
				strcpy(str, "TRIAL_TYPE_RAT_TRAINING_ROBOT_TO_RIGHT");	
			return TRUE;	
						
			
/////////////////////////		
		case TRIAL_TYPE_NULL:
 			strcpy(str, "TRIAL_TYPE_NULL");
			return FALSE;
		default:
 			strcpy(str, "TRIAL_TYPE_INVALID");
			return FALSE;
	}
}

bool get_trial_type_idx_in_trial_types_data(TrialTypesData* trial_types_data, TrialType trial_type, unsigned int *idx)
{
	unsigned int i;
	*idx = NUM_OF_TRIAL_TYPES; 

	for (i = 0; i < NUM_OF_TRIAL_TYPES; i++)
	{
		if (trial_type == trial_types_data->types[i].type)
		{
			*idx = i;
			return TRUE;
		}
	}
	return FALSE;	
}
bool add_trial_type_to_trial_types_data(TrialTypesData* trial_types_data, TrialType trial_type, unsigned int trial_type_idx, TimeStamp max_trial_length, TimeStamp trial_refractory)
{
	bool trial_type_used;
	char temp[TRIAL_TYPE_MAX_STRING_LENGTH];
	if (!is_trial_type_used(trial_types_data, trial_type, &trial_type_used))
		return print_message(ERROR_MSG ,"ExperimentHandlers", "TrialTypes", "add_trial_type_to_trials_data", "! is_trial_type_used.");	
	if (trial_type_used)
		return print_message(ERROR_MSG ,"ExperimentHandlers", "TrialTypes", "add_trial_type_to_trials_data", "trial_type_used.");	
	if (!get_trial_type_string(trial_type, temp))    // is trial type valid ?
		return print_message(ERROR_MSG ,"ExperimentHandlers", "TrialTypes", "add_trial_type_to_trials_data", "! get_trial_type_string.");	
	if (trial_type_idx >= NUM_OF_TRIAL_TYPES) 
		return print_message(ERROR_MSG ,"ExperimentHandlers", "TrialTypes", "add_trial_type_to_trials_data", "trial_type_idx >= NUM_OF_TRIAL_TYPES.");	
	trial_types_data->types[trial_type_idx].type = trial_type;
	trial_types_data->types[trial_type_idx].constraints.max_trial_length = max_trial_length;
	trial_types_data->types[trial_type_idx].constraints.trial_refractory = trial_refractory;
	print_message(INFO_MSG ,"ExperimentHandlers", "TrialTypes", "add_trial_type_to_trials_data", temp);	
	return TRUE;
}
bool is_trial_type_used(TrialTypesData* trial_types_data, TrialType trial_type, bool *used)
{
	unsigned int i;
	char temp[TRIAL_TYPE_MAX_STRING_LENGTH];
	*used = FALSE;
	
	if (!get_trial_type_string(trial_type, temp))  // is trial type valid ?
		return print_message(ERROR_MSG ,"ExperimentHandlers", "TrialTypes", "add_trial_type_to_trials_data", "! get_trial_type_string.");

	for (i = 0; i < NUM_OF_TRIAL_TYPES; i++)
	{
		if (trial_type == trial_types_data->types[i].type)
		{
			*used = TRUE;
			return TRUE;
		}
	}
	return TRUE;
}


