#include "ExpEnviComponentStatus.h"


bool get_exp_envi_comp_status_type_string(ExpEnviCompStatus exp_envi_comp_status_type, char *str)   // pass NULL if you only want checking (to be faster) 
{
	switch (exp_envi_comp_status_type)
	{
		case EXP_ENVI_COMP_STATUS_LOW:
			if (str != NULL)
				strcpy(str, "EXP_ENVI_COMP_STATUS_LOW");
			return TRUE;		
		case EXP_ENVI_COMP_STATUS_LOW_SUCCESS:
			if (str != NULL)
				strcpy(str, "EXP_ENVI_COMP_STATUS_LOW_SUCCESS");
			return TRUE;		
		case EXP_ENVI_COMP_STATUS_HIGH:
			if (str != NULL)
				strcpy(str, "EXP_ENVI_COMP_STATUS_HIGH");
			return TRUE;
		case EXP_ENVI_COMP_STATUS_HIGH_SUCCESS:
			if (str != NULL)
				strcpy(str, "EXP_ENVI_COMP_STATUS_HIGH_SUCCESS");
			return TRUE;	
		case EXP_ENVI_COMP_STATUS_IDLE:
			if (str != NULL)
				strcpy(str, "EXP_ENVI_COMP_STATUS_IDLE");
			return TRUE;
/////////////////////////		
		case EXP_ENVI_COMP_STATUS_NULL:
			if (str != NULL)
				strcpy(str, "EXP_ENVI_COMP_STATUS_NULL");
			return FALSE;
		default:
			if (str != NULL)
				strcpy(str, "EXP_ENVI_COMP_STATUS_INVALID");
			return FALSE;
	}
}
