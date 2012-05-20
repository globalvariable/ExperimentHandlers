#ifndef EXP_ENVI_STATUS_H
#define EXP_ENVI_STATUS_H


typedef unsigned int ExpEnviStatus;   // !!!ONLY!!! exp_envi_duration handler can change this. 

#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>

#define	EXP_ENVI_STATUS_MAX_STRING_LENGTH			100

#define	EXP_ENVI_STATUS_NULL							0
#define	EXP_ENVI_STATUS_OUT_OF_TRIAL				1
#define	EXP_ENVI_STATUS_COMPONENTS_AVAILABLE		2



bool get_exp_envi_status_type_string(ExpEnviStatus exp_envi_status_type, char *str);   // pass NULL if you only want checking (to be faster) 


#endif
