#include "TrialTypes.h"

bool get_trial_type_string(TrialType trial_type, char *str)  // pass NULL for only check trial type validity.
{
	switch (trial_type)
	{
////            RT_TRIALS    (REAL_TIME)
		case TRIAL_TYPE_IN_VIVO_BMI_LEFT_TARGET:
			if (str != NULL)
				strcpy(str, "TRIAL_TYPE_IN_VIVO_BMI_LEFT_TARGET");
			return TRUE;
		case TRIAL_TYPE_IN_VIVO_BMI_RIGHT_TARGET:
			if (str != NULL)
				strcpy(str, "TRIAL_TYPE_IN_VIVO_BMI_RIGHT_TARGET");	
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

TrialTypesData* allocate_trial_types_data(TrialTypesData* data)
{
	if (data != NULL)
	{
		data = deallocate_trial_types_data(data);
		data = allocate_trial_types_data(data);
		return data;
	}  
	data = g_new0(TrialTypesData,1);
	print_message(INFO_MSG ,"ExperimentHandlers", "TrialTypes", "allocate_trial_types_data", "Created trial_types_data.");
	return data;	
}

TrialTypesData* deallocate_trial_types_data(TrialTypesData* data)
{
	if (data == NULL)
		return (TrialTypesData*)print_message(BUG_MSG ,"ExperimentHandlers", "TrialTypes", "deallocate_trial_types_data", "trial_types_data == NULL.");    
	g_free(data->types);
	g_free(data);
	print_message(INFO_MSG ,"ExperimentHandlers", "TrialTypes", "deallocate_trials_data", "Destroyed trial_types_data.");
	return NULL;
}


bool get_trial_type_idx_in_trial_types_data(TrialTypesData* trial_types_data, TrialType trial_type, unsigned int *idx)
{
	unsigned int i;
	*idx = trial_types_data->num_of_trial_types; 

	for (i = 0; i < trial_types_data->num_of_trial_types; i++)
	{
		if (trial_type == trial_types_data->types[i].type)
		{
			*idx = i;
			return TRUE;
		}
	}
	return FALSE;	
}
bool add_trial_type_to_trial_types_data(TrialTypesData* trial_types_data, TrialType trial_type, TimeStamp max_trial_length, TimeStamp trial_refractory)
{
	unsigned int i;
	bool trial_type_used;
	char temp[200];
	TrialTypeData	*lcl_types;
	if (!is_trial_type_used(trial_types_data, trial_type, &trial_type_used))
		return print_message(ERROR_MSG ,"ExperimentHandlers", "TrialTypes", "add_trial_type_to_trial_types_data", "! is_trial_type_used()");	
	if (trial_type_used)
		return print_message(ERROR_MSG ,"ExperimentHandlers", "TrialTypes", "add_trial_type_to_trial_types_data", "trial_type_used");	
	if (!get_trial_type_string(trial_type, temp))    // is trial type valid ?
		return print_message(ERROR_MSG ,"ExperimentHandlers", "TrialTypes", "add_trial_type_to_trial_types_data", "!get_trial_type_string()");
	lcl_types = g_new0(TrialTypeData, trial_types_data->num_of_trial_types + 1);
	for (i = 0; i < trial_types_data->num_of_trial_types; i++)
		lcl_types[i] = trial_types_data->types[i];
	g_free(trial_types_data->types);
	trial_types_data->types = lcl_types;
	trial_types_data->types[trial_types_data->num_of_trial_types].type = trial_type;
	trial_types_data->types[trial_types_data->num_of_trial_types].constraints.max_trial_length = max_trial_length;
	trial_types_data->types[trial_types_data->num_of_trial_types].constraints.trial_refractory = trial_refractory;
	trial_types_data->num_of_trial_types++;
	print_message(INFO_MSG ,"ExperimentHandlers", "TrialTypes", "add_trial_type_to_trial_types_data", temp);	
	return TRUE;
}
bool is_trial_type_used(TrialTypesData* trial_types_data, TrialType trial_type, bool *used)
{
	unsigned int i;
	char temp[TRIAL_TYPE_MAX_STRING_LENGTH];
	*used = FALSE;
	
	if (!get_trial_type_string(trial_type, temp))  // is trial type valid ?
		return print_message(ERROR_MSG ,"ExperimentHandlers", "TrialTypes", "add_trial_type_to_trials_data", "! get_trial_type_string.");

	for (i = 0; i < trial_types_data->num_of_trial_types; i++)
	{
		if (trial_type == trial_types_data->types[i].type)
		{
			*used = TRUE;
			return TRUE;
		}
	}
	return TRUE;
}


