#ifndef EXP_ENVI_DUR_STATUS_H
#define EXP_ENVI_DUR_STATUS_H


typedef unsigned int ExpEnviInputsMinDurationStatus;   // !!!ONLY!!! exp_envi_duration handler can change this.
 typedef unsigned int ExpEnviInputsMaxDurationStatus;   // !!!ONLY!!! exp_envi_duration handler can change this.
typedef unsigned int ExpEnviOutputsDurationStatus;   // !!!ONLY!!! exp_envi_duration handler can change this. 

#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>

#define	EXP_ENVI_INPUTS_MIN_DUR_STATUS_MAX_STRING_LENGTH			100
#define	EXP_ENVI_INPUTS_MIN_DUR_STATUS_NULL							0
#define	EXP_ENVI_INPUTS_MIN_DUR_STATUS_TIMER_ON						1
#define	EXP_ENVI_INPUTS_MIN_DUR_STATUS_TIMER_OFF						2

#define	EXP_ENVI_INPUTS_MAX_DUR_STATUS_MAX_STRING_LENGTH			100
#define	EXP_ENVI_INPUTS_MAX_DUR_STATUS_NULL							0
#define	EXP_ENVI_INPUTS_MAX_DUR_STATUS_TIMER_ON						1
#define	EXP_ENVI_INPUTS_MAX_DUR_STATUS_TIMER_OFF						2

#define	EXP_ENVI_OUTPUTS_DUR_STATUS_MAX_STRING_LENGTH			100
#define	EXP_ENVI_OUTPUTS_DUR_STATUS_NULL							0
#define	EXP_ENVI_OUTPUTS_DUR_STATUS_TIMER_ON						1
#define	EXP_ENVI_OUTPUTS_DUR_STATUS_TIMER_OFF					2


bool get_exp_envi_input_min_dur_status_type_string(ExpEnviInputsMinDurationStatus exp_envi_inputs_min_dur_status_type, char *str);   // pass NULL if you only want checking (to be faster) 
bool get_exp_envi_input_max_dur_status_type_string(ExpEnviInputsMaxDurationStatus exp_envi_inputs_max_dur_status_type, char *str);   // pass NULL if you only want checking (to be faster) 
bool get_exp_envi_output_dur_status_type_string(ExpEnviOutputsDurationStatus exp_envi_outputs_dur_status_type, char *str);   // pass NULL if you only want checking (to be faster) 

#endif
