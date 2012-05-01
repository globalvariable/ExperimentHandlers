#include "TrialStatus.h"


bool get_trial_status_type_string(TrialStatus trial_status_type, char *str)   // pass NULL if you only want checking (to be faster) 
{
	switch (trial_status_type)
	{
		case TRIAL_STATUS_TRIALS_DISABLED:
			if (str != NULL)
				strcpy(str, "TRIAL_STATUS_TRIALS_DISABLED");
			return TRUE;		
		case TRIAL_STATUS_IN_TRIAL:
			if (str != NULL)
				strcpy(str, "TRIAL_STATUS_IN_TRIAL");
			return TRUE;
		case TRIAL_STATUS_IN_REFRACTORY:
			if (str != NULL)
				strcpy(str, "TRIAL_STATUS_IN_REFRACTORY");	
			return TRUE;
		case TRIAL_STATUS_START_TRIAL_AVAILABLE:
			if (str != NULL)
				strcpy(str, "TRIAL_STATUS_START_TRIAL_AVAILABLE");
			return TRUE;
/////////////////////////		
		case TRIAL_STATUS_NULL:
			if (str != NULL)
				strcpy(str, "TRIAL_STATUS_NULL");
			return FALSE;
		default:
			if (str != NULL)
				strcpy(str, "TRIAL_STATUS_TYPE_INVALID");
			return FALSE;
	}
}

