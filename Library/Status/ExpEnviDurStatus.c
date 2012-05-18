#include "ExpEnviDurStatus.h"


bool get_exp_envi_input_min_dur_status_type_string(ExpEnviInputsMinDurationStatus exp_envi_inputs_min_dur_status_type, char *str);   // pass NULL if you only want checking (to be faster) 
{
	switch (exp_envi_inputs_min_dur_status_type)
	{
		case EXP_ENVI_INPUTS_MIN_DUR_STATUS_TIMER_ON:
			if (str != NULL)
				strcpy(str, "EXP_ENVI_INPUTS_MIN_DUR_STATUS_TIMER_ON");
			return TRUE;
		case EXP_ENVI_INPUTS_MIN_DUR_STATUS_TIMER_OFF:
			if (str != NULL)
				strcpy(str, "EXP_ENVI_INPUTS_MIN_DUR_STATUS_TIMER_OFF");
			return TRUE;
/////////////////////////		
		case EXP_ENVI_INPUTS_MIN_DUR_STATUS_NULL:
			if (str != NULL)
				strcpy(str, "EXP_ENVI_INPUTS_MIN_DUR_STATUS_NULL");
			return FALSE;
		default:
			if (str != NULL)
				strcpy(str, "EXP_ENVI_INPUTS_MIN_DUR_STATUS_INVALID");
			return FALSE;
	}
}
bool get_exp_envi_input_max_dur_status_type_string(ExpEnviInputsMaxDurationStatus exp_envi_inputs_max_dur_status_type, char *str);   // pass NULL if you only want checking (to be faster) 
{
	switch (exp_envi_inputs_max_dur_status_type)
	{
		case EXP_ENVI_INPUTS_MAX_DUR_STATUS_TIMER_ON:
			if (str != NULL)
				strcpy(str, "EXP_ENVI_INPUTS_MAX_DUR_STATUS_TIMER_ON");
			return TRUE;
		case EXP_ENVI_INPUTS_MAX_DUR_STATUS_TIMER_OFF:
			if (str != NULL)
				strcpy(str, "EXP_ENVI_INPUTS_MAX_DUR_STATUS_TIMER_OFF");
			return TRUE;
/////////////////////////		
		case EXP_ENVI_INPUTS_MAX_DUR_STATUS_NULL:
			if (str != NULL)
				strcpy(str, "EXP_ENVI_INPUTS_MAX_DUR_STATUS_NULL");
			return FALSE;
		default:
			if (str != NULL)
				strcpy(str, "EXP_ENVI_INPUTS_MAX_DUR_STATUS_INVALID");
			return FALSE;
	}
}
bool get_exp_envi_output_dur_status_type_string(ExpEnviOutputsDurationStatus exp_envi_outputs_dur_status_type, char *str)   // pass NULL if you only want checking (to be faster) 
{
	switch (exp_envi_outputs_dur_status_type)
	{
		case EXP_ENVI_OUTPUTS_DUR_STATUS_TIMER_ON:
			if (str != NULL)
				strcpy(str, "EXP_ENVI_OUTPUTS_DUR_STATUS_TIMER_ON");
			return TRUE;
		case EXP_ENVI_OUTPUTS_DUR_STATUS_TIMER_OFF:
			if (str != NULL)
				strcpy(str, "EXP_ENVI_OUTPUTS_DUR_STATUS_TIMER_OFF");
			return TRUE;
/////////////////////////		
		case EXP_ENVI_OUTPUTS_DUR_STATUS_NULL:
			if (str != NULL)
				strcpy(str, "EXP_ENVI_OUTPUTS_DUR_STATUS_NULL");
			return FALSE;
		default:
			if (str != NULL)
				strcpy(str, "EXP_ENVI_OUTPUTS_DUR_STATUS_INVALID");
			return FALSE;
	}
}
