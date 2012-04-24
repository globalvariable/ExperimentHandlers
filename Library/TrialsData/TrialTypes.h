#ifndef TRIAL_TYPES_H
#define TRIAL_TYPES_H

typedef struct __TrialTypeConstraints TrialTypeConstraints;
typedef struct __TrialTypeData TrialTypeData;
typedef TrialTypeData TrialTypesData[NUM_OF_TRIAL_TYPES];

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

















#endif
