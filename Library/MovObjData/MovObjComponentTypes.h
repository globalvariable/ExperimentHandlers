#ifndef MOV_OBJ_COMPONENT_TYPES_H
#define MOV_OBJ_COMPONENT_TYPES_H


#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>


typedef unsigned int MovObjCompNum;				


typedef unsigned int MovObjCompType;					

#define	MOV_OBJ_COMPONENT_TYPE_MAX_STRING_LENGTH		100

#define	MOV_OBJ_COMPONENT_NULL								0
#define	MOV_OBJ_COMPONENT_1D_ACTUATOR					1	
#define	MOV_OBJ_COMPONENT_2D_ACTUATOR					2	
#define	MOV_OBJ_COMPONENT_3D_ACTUATOR					3	


#define	MOV_OBJ_COMPONENT_SHOULDER_FLEXOR				31
#define	MOV_OBJ_COMPONENT_SHOULDER_ROTATOR				32
#define	MOV_OBJ_COMPONENT_ELBOW_FLEXOR					33
#define	MOV_OBJ_COMPONENT_WRIST_ROTATOR					34
#define	MOV_OBJ_COMPONENT_WRIST_FLEXOR					35


bool get_mov_obj_component_type_string(MovObjCompType mov_obj_comp_type, char *str);

#endif
