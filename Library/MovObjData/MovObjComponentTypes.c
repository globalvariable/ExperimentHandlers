#include "MovObjComponentTypes.h"


bool get_mov_obj_component_type_string(MovObjCompType mov_obj_comp_type, char *str)
{
	switch (mov_obj_comp_type)
	{
		case MOV_OBJ_COMPONENT_1D_ACTUATOR:
			if (str != NULL)
				strcpy(str, "MOV_OBJ_COMPONENT_1D_ACTUATOR");
			return TRUE;	
		case MOV_OBJ_COMPONENT_2D_ACTUATOR:
			if (str != NULL)
				strcpy(str, "MOV_OBJ_COMPONENT_2D_ACTUATOR");
			return TRUE;	
		case MOV_OBJ_COMPONENT_3D_ACTUATOR:
			if (str != NULL)
				strcpy(str, "MOV_OBJ_COMPONENT_3D_ACTUATOR");
			return TRUE;		

//////////////
		case MOV_OBJ_COMPONENT_SHOULDER_FLEXOR:
			if (str != NULL)
				strcpy(str, "MOV_OBJ_COMPONENT_SHOULDER_FLEXOR");
			return TRUE;	
		case MOV_OBJ_COMPONENT_SHOULDER_ROTATOR:
			if (str != NULL)
				strcpy(str, "MOV_OBJ_COMPONENT_SHOULDER_ROTATOR");
			return TRUE;		
		case MOV_OBJ_COMPONENT_ELBOW_FLEXOR:
			if (str != NULL)
				strcpy(str, "MOV_OBJ_COMPONENT_ELBOW_FLEXOR");
			return TRUE;	
		case MOV_OBJ_COMPONENT_WRIST_ROTATOR:
			if (str != NULL)
				strcpy(str, "MOV_OBJ_COMPONENT_WRIST_ROTATOR");
			return TRUE;	
		case MOV_OBJ_COMPONENT_WRIST_FLEXOR:
			if (str != NULL)
				strcpy(str, "MOV_OBJ_COMPONENT_WRIST_FLEXOR");
			return TRUE;	
/////////////////////////		
		case MOV_OBJ_COMPONENT_NULL:
 			strcpy(str, "MOV_OBJ_COMPONENT_NULL");
			return FALSE;
		default:
 			strcpy(str, "MOV_OBJ_COMPONENT_INVALID");
			return FALSE;
	}
}
