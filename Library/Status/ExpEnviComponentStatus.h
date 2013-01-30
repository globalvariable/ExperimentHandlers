
#ifndef EXP_ENVI_COMPONENT_STATUS_H
#define EXP_ENVI_COMPONENT_STATUS_H


typedef unsigned int ExpEnviCompStatus;   

#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>

#define	EXP_ENVI_COMP_STATUS_MAX_STRING_LENGTH			100

#define	EXP_ENVI_COMP_STATUS_NULL						0
#define	EXP_ENVI_COMP_STATUS_LOW						1
#define	EXP_ENVI_COMP_STATUS_LOW_SUCCESS				2
#define	EXP_ENVI_COMP_STATUS_HIGH						3
#define	EXP_ENVI_COMP_STATUS_HIGH_SUCCESS			4
#define	EXP_ENVI_COMP_STATUS_READY_FOR_SWITCHING	5


bool get_exp_envi_comp_status_type_string(ExpEnviCompStatus exp_envi_comp_status_type, char *str);   // pass NULL if you only want checking (to be faster) 

#endif
