#ifndef EXP_ENVI_DUR_STATUS_H
#define EXP_ENVI_DUR_STATUS_H

typedef unsigned int ExpEnviDurationStatus;

#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>

#define	EXP_ENVI_DUR_STATUS_MAX_STRING_LENGTH			100
#define	EXP_ENVI_DUR_STATUS_NULL							0
#define	EXP_ENVI_INPUTS_MIN_DUR_STATUS_TIMER_ON			1
#define	EXP_ENVI_INPUTS_MIN_DUR_STATUS_TIMER_OFF			2
#define	EXP_ENVI_INPUTS_MAX_DUR_STATUS_TIMER_ON			3
#define	EXP_ENVI_INPUTS_MAX_DUR_STATUS_TIMER_OFF			4
#define	EXP_ENVI_OUTPUTS_DUR_STATUS_TIMER_ON				5
#define	EXP_ENVI_OUTPUTS_DUR_STATUS_TIMER_OFF			6


bool get_exp_envi_dur_status_type_string(ExpEnviDurationStatus exp_envi_dur_status_type, char *str);   // pass NULL if you only want checking (to be faster) 

#endif
