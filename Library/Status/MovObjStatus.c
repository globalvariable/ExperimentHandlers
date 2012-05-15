#include "MovObjStatus.h"


bool get_mov_obj_status_type_string(MovObjStatus mov_obj_status_type, char *str);   // pass NULL if you only want checking (to be faster) 
{
	switch (mov_obj_status_type)
	{
		case MOV_OBJ_STATUS_STAYING_AT_START_POINT:
			if (str != NULL)
				strcpy(str, "MOV_OBJ_STATUS_STAYING_AT_START_POINT");
			return TRUE;		
		case MOV_OBJ_STATUS_AVAILABLE_TO_CONTROL:
			if (str != NULL)
				strcpy(str, "MOV_OBJ_STATUS_AVAILABLE_TO_CONTROL");
			return TRUE;
		case MOV_OBJ_STATUS_RESETTING_TO_TARGET_POINT:
			if (str != NULL)
				strcpy(str, "MOV_OBJ_STATUS_RESETTING_TO_TARGET_POINT");
			return TRUE;
		case MOV_OBJ_STATUS_REACHED_TARGET_POINT:
			if (str != NULL)
				strcpy(str, "MOV_OBJ_STATUS_REACHED_TARGET_POINT");
			return TRUE;
		case MOV_OBJ_STATUS_RESETTING_TO_START_POINT:
			if (str != NULL)
				strcpy(str, "MOV_OBJ_STATUS_RESETTING_TO_START_POINT");
			return TRUE;
/////////////////////////		
		case MOV_OBJ_STATUS_NULL:
			if (str != NULL)
				strcpy(str, "MOV_OBJ_STATUS_NULL");
			return FALSE;
		default:
			if (str != NULL)
				strcpy(str, "MOV_OBJ_STATUS_INVALID");
			return FALSE;
	}
}
