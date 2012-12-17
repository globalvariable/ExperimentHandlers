#ifndef TRIAL_TYPES_H
#define TRIAL_TYPES_H



typedef struct __TrialTypeConstraints TrialTypeConstraints;
typedef struct __TrialTypeData TrialTypeData;
typedef struct __TrialTypesData TrialTypesData;
typedef unsigned int TrialType;

#include <gtk/gtk.h>
#include <stdbool.h>
#include <string.h>
#include "../../../BlueSpike/System/TimeStamp/TimeStamp.h"
#include "../../../BlueSpike/Library/Misc/Misc.h"
#include "../../../BlueSpike/Library/Misc/Randn.h"


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
	TrialTypeData				*types;
	unsigned int				num_of_trial_types;
};





#define	TRIAL_TYPE_MAX_STRING_LENGTH					200

#define	TRIAL_TYPE_NULL									0

#define	TRIAL_TYPE_UNSPECIFIED							1	/// it is not like TRIAL_TYPE_NULL. it is unspecified for mov obj handler and exp envi handler, for instance during refractory.

#define	TRIAL_TYPE_IN_VIVO_BMI_LEFT_TARGET				2
#define	TRIAL_TYPE_IN_VIVO_BMI_RIGHT_TARGET				3
#define	TRIAL_TYPE_RAT_TRAINING_ROBOT_TO_LEFT			4
#define	TRIAL_TYPE_RAT_TRAINING_ROBOT_TO_RIGHT			5



TrialTypesData* allocate_trial_types_data(TrialTypesData* data);
TrialTypesData* deallocate_trial_types_data(TrialTypesData* data);
bool get_trial_type_string(TrialType trial_type, char *str);
bool get_trial_type_idx_in_trial_types_data(TrialTypesData* trial_types_data, TrialType trial_type, unsigned int *idx);
bool add_trial_type_to_trial_types_data(TrialTypesData* trial_types_data, TrialType trial_type, TimeStamp max_trial_length, TimeStamp trial_refractory);
bool is_trial_type_used(TrialTypesData* trial_types_data, TrialType trial_type, bool *used);
bool get_a_random_trial_type(TrialTypesData* trial_types_data, TrialType *trial_type);











#endif
