#ifndef MOV_OBJ_STATUS_H
#define MOV_OBJ_STATUS_H


typedef unsigned int MovObjStatus;   // !!!ONLY!!! mov_obj_duration handler can change this. 

#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>

#define	MOV_OBJ_STATUS_MAX_STRING_LENGTH							100

#define	MOV_OBJ_STATUS_NULL											0
#define	MOV_OBJ_STATUS_OUT_OF_TRIAL								1
#define	MOV_OBJ_STATUS_STAYING_AT_START_POINT						2
#define	MOV_OBJ_STATUS_AVAILABLE_TO_CONTROL						3
#define	MOV_OBJ_STATUS_RESETTING_TO_TARGET_POINT					4
#define	MOV_OBJ_STATUS_REACHED_TARGET_POINT						5
#define	MOV_OBJ_STATUS_RESETTING_TO_START_POINT					6


bool get_mov_obj_status_type_string(MovObjStatus mov_obj_status_type, char *str);   // pass NULL if you only want checking (to be faster) 


#endif
