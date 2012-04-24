#ifndef TRIAL_HAND_STATUS_H
#define TRIAL_HAND_STATUS_H


typedef unsigned int TrialStatus;

#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>

#define	TRIAL_STATUS_MAX_STRING_LENGTH			50

#define	TRIAL_STATUS_NULL							0
#define	TRIAL_STATUS_TRIALS_DISABLED				1
#define	TRIAL_STATUS_IN_TRIAL						2
#define	TRIAL_STATUS_IN_REFRACTORY				3
#define	TRIAL_STATUS_START_TRIAL_AVAILABLE		4


bool get_trial_status_type_string(TrialStatus trial_status_type, char *str);   // pass NULL if you only want checking (to be faster) 


#endif
