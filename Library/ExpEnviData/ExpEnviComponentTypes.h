#ifndef EXP_ENVI_COMPONENT_TYPES_H
#define EXP_ENVI_COMPONENT_TYPES_H


#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>

typedef unsigned int ExpEnviInputCompNum;		
typedef unsigned int ExpEnviOutputCompNum;				

#define EXP_ENVI_INPUT_STATUS_HIGH	TRUE
#define EXP_ENVI_INPUT_STATUS_LOW	FALSE
#define EXP_ENVI_OUTPUT_STATUS_HIGH	TRUE
#define EXP_ENVI_OUTPUT_STATUS_LOW	FALSE


typedef unsigned int ExpEnviInputCompType;					

#define	EXP_ENVI_INPUT_COMPONENT_TYPE_MAX_STRING_LENGTH		100

#define	EXP_ENVI_INPUT_COMPONENT_NULL								0
#define	EXP_ENVI_INPUT_COMPONENT_IR_BEAM_NOSE_POKE				1
#define	EXP_ENVI_INPUT_COMPONENT_LEFT_LEVER						2
#define	EXP_ENVI_INPUT_COMPONENT_RIGHT_LEVER						3


typedef unsigned int ExpEnviOutputCompType;					

#define	EXP_ENVI_OUTPUT_COMPONENT_TYPE_MAX_STRING_LENGTH		100

#define	EXP_ENVI_OUTPUT_COMPONENT_LEFT_TARGET_LED				0
#define	EXP_ENVI_OUTPUT_COMPONENT_RIGHT_TARGET_LED				1
#define	EXP_ENVI_OUTPUT_COMPONENT_VALVE_CENTER					2



bool get_exp_envi_input_component_type_string(ExpEnviInputCompType component_type, char *str);
bool get_exp_envi_output_component_type_string(ExpEnviOutputCompType component_type, char *str);















#endif