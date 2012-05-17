#include "ExpEnviStatus.h"


bool get_exp_envi_status_type_string(ExpEnviStatus exp_envi_status_type, char *str)   // pass NULL if you only want checking (to be faster) 
{
	switch (exp_envi_status_type)
	{
		case EXP_ENVI_STATUS_OUT_OF_TRIAL:
			if (str != NULL)
				strcpy(str, "EXP_ENVI_STATUS_OUT_OF_TRIAL");
			return TRUE;
		case EXP_ENVI_STATUS_LEFT_TARGET_SELECTED:
			if (str != NULL)
				strcpy(str, "EXP_ENVI_STATUS_LEFT_TARGET_SELECTED");
			return TRUE;
		case EXP_ENVI_STATUS_RIGHT_TARGET_SELECTED:
			if (str != NULL)
				strcpy(str, "EXP_ENVI_STATUS_RIGHT_TARGET_SELECTED");
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
