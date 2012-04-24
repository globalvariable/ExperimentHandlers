#ifndef TRIAL_TYPES_H
#define TRIAL_TYPES_H



typedef struct __TrialTypeConstraints TrialTypeConstraints;
typedef struct __TrialTypeData TrialTypeData;
typedef struct __TrialTypesData TrialTypesData;
typedef unsigned int TrialType;

#include <gtk/gtk.h>
#include <stdbool.h>
#include <string.h>
#include "../../Config.h"
#include "../../../BlueSpike/TimeStamp.h"
#include "../../../BlueSpike/Library/Misc/Misc.h"



struct __TrialTypeConstraints
{
	TimeStamp			max_trial_length;			
	TimeStamp			trial_refractory;	
};

struct __TrialTypeData
{
	TrialType					type;
	TrialTypeConstraints		constraints;
};

struct __TrialTypesData
{
	TrialTypeData				types[NUM_OF_TRIAL_TYPES];
};





#define	TRIAL_TYPE_MAX_STRING_LENGTH	200

#define	TRIAL_TYPE_NULL									0

////            RT_TRIALS    (REAL_TIME)
#define	TRIAL_TYPE_RT_BMI_LEFT_TARGET		11
#define	TRIAL_TYPE_RT_BMI_RIGHT_TARGET		12


////            RAT_TRAINING_TRIALS   
#define	TRIAL_TYPE_RAT_TRAINING_ROBOT_TO_LEFT		3001
#define	TRIAL_TYPE_RAT_TRAINING_ROBOT_TO_RIGHT		3002


bool get_trial_type_string(TrialType trial_type, char *str);
bool get_trial_type_idx_in_trial_types_data(TrialTypesData* trial_types_data, TrialType trial_type, unsigned int *idx);
bool add_trial_type_to_trial_types_data(TrialTypesData* trial_types_data, TrialType trial_type, unsigned int trial_type_idx, TimeStamp max_trial_length, TimeStamp trial_refractory);
bool is_trial_type_used(TrialTypesData* trial_types_data, TrialType trial_type, bool *used);












#endif
