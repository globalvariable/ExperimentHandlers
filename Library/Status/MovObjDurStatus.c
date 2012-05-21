#include "MovObjDurStatus.h"


bool get_mov_obj_dur_status_type_string(MovObjDurationStatus mov_obj_dur_status_type, char *str)   // pass NULL if you only want checking (to be faster) 
{
	switch (mov_obj_dur_status_type)
	{
		case MOV_OBJ_DUR_STATUS_TIMER_ON:
			if (str != NULL)
				strcpy(str, "MOV_OBJ_DUR_STATUS_TIMER_ON");
			return TRUE;
		case MOV_OBJ_DUR_STATUS_TIMER_OFF:
			if (str != NULL)
				strcpy(str, "MOV_OBJ_DUR_STATUS_TIMER_OFF");
			return TRUE;
/////////////////////////		
		case MOV_OBJ_DUR_STATUS_NULL:
			if (str != NULL)
				strcpy(str, "MOV_OBJ_DUR_STATUS_NULL");
			return FALSE;
		default:
			if (str != NULL)
				strcpy(str, "MOV_OBJ_DUR_STATUS_INVALID");
			return FALSE;
	}
}
