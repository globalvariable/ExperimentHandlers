#include "ExpEnviStatus.h"


bool get_exp_envi_status_type_string(ExpEnviStatus exp_envi_status_type, char *str)   // pass NULL if you only want checking (to be faster) 
{
	switch (exp_envi_status_type)
	{
		case EXP_ENVI_STATUS_COMPONENTS_UNAVAILABLE:
			if (str != NULL)
				strcpy(str, "EXP_ENVI_STATUS_COMPONENTS_UNAVAILABLE");
			return TRUE;
		case EXP_ENVI_STATUS_COMPONENTS_AVAILABLE:
			if (str != NULL)
				strcpy(str, "EXP_ENVI_STATUS_COMPONENTS_AVAILABLE");
			return TRUE;
/////////////////////////		
		case EXP_ENVI_STATUS_NULL:
			if (str != NULL)
				strcpy(str, "EXP_ENVI_STATUS_NULL");
			return FALSE;
		default:
			if (str != NULL)
				strcpy(str, "EXP_ENVI_STATUS_INVALID");
			return FALSE;
	}
}
