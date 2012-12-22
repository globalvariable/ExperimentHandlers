#include "ExpEnviDurStatus.h"


bool get_exp_envi_dur_status_type_string(ExpEnviDurationStatus exp_envi_dur_status_type, char *str)   // pass NULL if you only want checking (to be faster) 
{
	switch (exp_envi_dur_status_type)
	{
		case EXP_ENVI_INPUTS_MIN_DUR_STATUS_TIMER_ON:
			if (str != NULL)
				strcpy(str, "EXP_ENVI_INPUTS_MIN_DUR_STATUS_TIMER_ON");
			return TRUE;
		case EXP_ENVI_INPUTS_MIN_DUR_STATUS_TIMER_OFF:
			if (str != NULL)
				strcpy(str, "EXP_ENVI_INPUTS_MIN_DUR_STATUS_TIMER_OFF");
			return TRUE;
		case EXP_ENVI_INPUTS_MAX_DUR_STATUS_TIMER_ON:
			if (str != NULL)
				strcpy(str, "EXP_ENVI_INPUTS_MIN_DUR_STATUS_TIMER_ON");
			return TRUE;
		case EXP_ENVI_INPUTS_MAX_DUR_STATUS_TIMER_OFF:
			if (str != NULL)
				strcpy(str, "EXP_ENVI_INPUTS_MIN_DUR_STATUS_TIMER_OFF");
			return TRUE;
		case EXP_ENVI_OUTPUTS_DUR_STATUS_TIMER_ON:
			if (str != NULL)
				strcpy(str, "EXP_ENVI_OUTPUTS_DUR_STATUS_TIMER_ON");
			return TRUE;
		case EXP_ENVI_OUTPUTS_DUR_STATUS_TIMER_OFF:
			if (str != NULL)
				strcpy(str, "EXP_ENVI_OUTPUTS_DUR_STATUS_TIMER_OFF");
			return TRUE;
/////////////////////////		
		case EXP_ENVI_DUR_STATUS_NULL:
			if (str != NULL)
				strcpy(str, "EXP_ENVI_DUR_STATUS_NULL");
			return FALSE;
		default:
			if (str != NULL)
				strcpy(str, "EXP_ENVI_DUR_STATUS_INVALID");
			return FALSE;
	}
}

