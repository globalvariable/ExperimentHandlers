#ifndef MOV_OBJ_DUR_STATUS_H
#define MOV_OBJ_DUR_STATUS_H


typedef unsigned int MovObjDurationStatus;   // !!!ONLY!!! mov_obj_duration handler can change this. 

#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>

#define	MOV_OBJ_DUR_STATUS_MAX_STRING_LENGTH			100

#define	MOV_OBJ_DUR_STATUS_NULL							0
#define	MOV_OBJ_DUR_STATUS_TIMER_ON						1
#define	MOV_OBJ_DUR_STATUS_TIMER_OFF						2


bool get_mov_obj_dur_status_type_string(MovObjDurationStatus mov_obj_dur_status_type, char *str);   // pass NULL if you only want checking (to be faster) 


#endif
