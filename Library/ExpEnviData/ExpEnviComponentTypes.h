#ifndef EXP_ENVI_COMPONENT_TYPES_H
#define EXP_ENVI_COMPONENT_TYPES_H


#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>

#define EXP_ENVI_COMP_NUM_NULL	0xFFFFFFFF	

typedef unsigned int ExpEnviCompNum;
typedef ExpEnviCompNum ExpEnviInputCompNum;	
typedef ExpEnviCompNum ExpEnviOutputCompNum;				

typedef unsigned int ExpEnviInputCompType;					

#define	EXP_ENVI_INPUT_COMPONENT_TYPE_MAX_STRING_LENGTH		100

#define	EXP_ENVI_INPUT_COMPONENT_NULL								0
#define	EXP_ENVI_INPUT_COMPONENT_IR_BEAM_NOSE_POKE				1
#define	EXP_ENVI_INPUT_COMPONENT_LEFT_LEVER						2
#define	EXP_ENVI_INPUT_COMPONENT_RIGHT_LEVER						3
#define	EXP_ENVI_INPUT_COMPONENT_NOSE_RETRACT_IR				4
#define	EXP_ENVI_INPUT_COMPONENT_LEVER							5
#define	EXP_ENVI_INPUT_COMPONENT_RESTRAIN_SWITCH				6

typedef unsigned int ExpEnviOutputCompType;					

#define	EXP_ENVI_OUTPUT_COMPONENT_TYPE_MAX_STRING_LENGTH		100

#define	EXP_ENVI_OUTPUT_COMPONENT_VALVE_CENTER					0
#define	EXP_ENVI_OUTPUT_COMPONENT_BUZZER							1
#define	EXP_ENVI_OUTPUT_COMPONENT_LEFT_TARGET_LED				2
#define	EXP_ENVI_OUTPUT_COMPONENT_RIGHT_TARGET_LED				3
#define	EXP_ENVI_OUTPUT_COMPONENT_GUIDE_LED						4
#define	EXP_ENVI_OUTPUT_COMPONENT_LEVER_SOLENOID				5
#define	EXP_ENVI_OUTPUT_COMPONENT_TRIAL_AVAILABLE_LED			6
#define	EXP_ENVI_OUTPUT_COMPONENT_GET_READY_LED				7


bool get_exp_envi_input_component_type_string(ExpEnviInputCompType component_type, char *str);
bool get_exp_envi_output_component_type_string(ExpEnviOutputCompType component_type, char *str);















#endif
