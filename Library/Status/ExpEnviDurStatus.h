#ifndef EXP_ENVI_DUR_STATUS_H
#define EXP_ENVI_DUR_STATUS_H


typedef unsigned int ExpEnviDurationStatus;   // !!!ONLY!!! exp_envi_duration handler can change this. 

#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>

#define	EXP_ENVI_DUR_STATUS_MAX_STRING_LENGTH			100

#define	EXP_ENVI_DUR_STATUS_NULL							0



bool get_exp_envi_dur_status_type_string(ExpEnviDurationStatus exp_envi_dur_status_type, char *str);   // pass NULL if you only want checking (to be faster) 


#endif
