#include "ExpEnviComponentTypes.h"


bool get_exp_envi_input_component_type_string(ExpEnviInputCompType component_type, char *str)
{
	switch (component_type)
	{
		case EXP_ENVI_INPUT_COMPONENT_IR_BEAM_NOSE_POKE:
			if (str != NULL)
				strcpy(str, "EXP_ENVI_INPUT_COMPONENT_IR_BEAM_NOSE_POKE");
			return TRUE;	
		case EXP_ENVI_INPUT_COMPONENT_LEFT_LEVER:
			if (str != NULL)
				strcpy(str, "EXP_ENVI_INPUT_COMPONENT_LEFT_LEVER");
			return TRUE;	
		case EXP_ENVI_INPUT_COMPONENT_RIGHT_LEVER:
			if (str != NULL)
				strcpy(str, "EXP_ENVI_INPUT_COMPONENT_RIGHT_LEVER");
			return TRUE;	
/////////////////////////		
		default:
 			strcpy(str, "EXP_ENVI_INPUT_COMPONENT_INVALID");
			return FALSE;
	}
}

bool get_exp_envi_output_component_type_string(ExpEnviOutputCompType component_type, char *str)
{
	switch (component_type)
	{
		case EXP_ENVI_OUTPUT_COMPONENT_VALVE_CENTER:
			if (str != NULL)
				strcpy(str, "EXP_ENVI_OUTPUT_COMPONENT_VALVE_CENTER");
			return TRUE;	
		case EXP_ENVI_OUTPUT_COMPONENT_BUZZER:
			if (str != NULL)
				strcpy(str, "EXP_ENVI_OUTPUT_COMPONENT_BUZZER");
			return TRUE;	
		case EXP_ENVI_OUTPUT_COMPONENT_LEFT_TARGET_LED:
			if (str != NULL)
				strcpy(str, "EXP_ENVI_OUTPUT_COMPONENT_LEFT_TARGET_LED");
			return TRUE;	
		case EXP_ENVI_OUTPUT_COMPONENT_RIGHT_TARGET_LED:
			if (str != NULL)
				strcpy(str, "EXP_ENVI_OUTPUT_COMPONENT_RIGHT_TARGET_LED");
			return TRUE;	
		case EXP_ENVI_OUTPUT_COMPONENT_GUIDE_LED:
			if (str != NULL)
				strcpy(str, "EXP_ENVI_OUTPUT_COMPONENT_GUIDE_LED");
			return TRUE;
		case EXP_ENVI_OUTPUT_COMPONENT_LEVER_SOLENOID:
			if (str != NULL)
				strcpy(str, "EXP_ENVI_OUTPUT_COMPONENT_LEVER_SOLENOID");
			return TRUE;	


/////////////////////////	
	
		default:
 			strcpy(str, "EXP_ENVI_OUTPUT_COMPONENT_INVALID");
			return FALSE;
	}
}
