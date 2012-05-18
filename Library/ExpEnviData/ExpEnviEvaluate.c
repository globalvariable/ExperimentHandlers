#include "ExpEnviEvaluate.h"

bool time_out_success_for_input_comp(ExpEnviInputCompTypeData *comp_data, bool *has_response)
{
	char str[EXP_ENVI_COMP_STATUS_MAX_STRING_LENGTH];
	*has_response = FALSE;

	switch (comp_data->status)
	{
		case EXP_ENVI_COMP_STATUS_LOW:	
			comp_data->status = EXP_ENVI_COMP_STATUS_LOW_SUCCESS;
			comp_data->high_2_low_switch_success++;
			break;			
		case EXP_ENVI_COMP_STATUS_LOW_SUCCESS:	
			return print_message(BUG_MSG ,"ExperimentHandlers", "ExpEnviEvaluate", "time_out_success_for_input_comp", "comp_data->status == EXP_ENVI_COMP_STATUS_LOW_SUCCESS");	
		case EXP_ENVI_COMP_STATUS_HIGH:
			comp_data->status = EXP_ENVI_COMP_STATUS_HIGH_SUCCESS;
			comp_data->low_2_high_switch_success++;
			break;			
		case EXP_ENVI_COMP_STATUS_HIGH_SUCCESS:
			return print_message(BUG_MSG ,"ExperimentHandlers", "ExpEnviEvaluate", "time_out_success_for_input_comp", "comp_data->status == EXP_ENVI_COMP_STATUS_HIGH_SUCCESS");
		case EXP_ENVI_COMP_STATUS_IDLE:
			return print_message(BUG_MSG ,"ExperimentHandlers", "ExpEnviEvaluate", "time_out_success_for_input_comp", "comp_data->status == EXP_ENVI_COMP_STATUS_IDLE");
		default:
			get_exp_envi_comp_status_type_string(comp_data->status, str);   
			return print_message(BUG_MSG ,"ExperimentHandlers", "ExpEnviEvaluate", "time_out_success_for_input_comp", str);	
	}
	if ((comp_data->low_2_high_switch_success == comp_data->constraints.num_of_low_2_high_switch ) && (comp_data->high_2_low_switch_success == comp_data->constraints.num_of_high_2_low_switch ))
	{
		*has_response = TRUE;
		comp_data->low_2_high_switch_success = 0;
		comp_data->high_2_low_switch_success = 0;
		comp_data->status = EXP_ENVI_COMP_STATUS_IDLE;
	}
	return TRUE;
}

bool time_out_fail_for_input_comp(ExpEnviInputCompTypeData *comp_data)
{
	char str[EXP_ENVI_COMP_STATUS_MAX_STRING_LENGTH];
	switch (comp_data->status)
	{
		case EXP_ENVI_COMP_STATUS_LOW:	
			break;
		case EXP_ENVI_COMP_STATUS_LOW_SUCCESS:	
			comp_data->low_2_high_switch_success = 0;
			comp_data->high_2_low_switch_success = 0;	
			comp_data->status = EXP_ENVI_COMP_STATUS_IDLE;
			break;
		case EXP_ENVI_COMP_STATUS_HIGH:
			break;
		case EXP_ENVI_COMP_STATUS_HIGH_SUCCESS:
			comp_data->low_2_high_switch_success = 0;
			comp_data->high_2_low_switch_success = 0;	
			comp_data->status = EXP_ENVI_COMP_STATUS_IDLE;
			break;
		case EXP_ENVI_COMP_STATUS_IDLE:
			break;
		default:
			get_exp_envi_comp_status_type_string(comp_data->status, str);   
			return print_message(BUG_MSG ,"ExperimentHandlers", "ExpEnviEvaluate", "time_out_fail_for_input_comp", str);	
	}
	return TRUE;
}

void reset_exp_envi_input_comp(ExpEnviInputCompTypeData *comp_data)
{
	comp_data->low_2_high_switch_success = 0;
	comp_data->high_2_low_switch_success = 0;	
	comp_data->status = EXP_ENVI_COMP_STATUS_IDLE;
	return;
}

bool exp_envi_input_low_2_high_event(ExpEnviInputCompTypeData *comp_data, bool *valid)
{
	char str[EXP_ENVI_COMP_STATUS_MAX_STRING_LENGTH];
	*valid = FALSE;
	switch (comp_data->status)
	{
		case EXP_ENVI_COMP_STATUS_LOW:	
			comp_data->status = EXP_ENVI_COMP_STATUS_IDLE;
			comp_data->low_2_high_switch_success = 0;
			comp_data->high_2_low_switch_success = 0;	
			*valid = FALSE;
			break;			
		case EXP_ENVI_COMP_STATUS_LOW_SUCCESS:	
			comp_data->status = EXP_ENVI_COMP_STATUS_HIGH;
			*valid = TRUE;
			break;	
		case EXP_ENVI_COMP_STATUS_HIGH:
			return print_message(BUG_MSG ,"ExperimentHandlers", "ExpEnviEvaluate", "exp_envi_input_low_2_high_event", "comp_data->status == EXP_ENVI_COMP_STATUS_HIGH");	
		case EXP_ENVI_COMP_STATUS_HIGH_SUCCESS:
			return print_message(BUG_MSG ,"ExperimentHandlers", "ExpEnviEvaluate", "exp_envi_input_low_2_high_event", "comp_data->status == EXP_ENVI_COMP_STATUS_HIGH_SUCCESS");
		case EXP_ENVI_COMP_STATUS_IDLE:
			if (comp_data->constraints.initial_status == EXP_ENVI_COMP_STATUS_LOW)
			{
				comp_data->status = EXP_ENVI_COMP_STATUS_HIGH;		
				*valid = TRUE;
			}
			break;	
		default:
			get_exp_envi_comp_status_type_string(comp_data->status, str);   
			return print_message(BUG_MSG ,"ExperimentHandlers", "ExpEnviEvaluate", "exp_envi_input_low_2_high_event", str);	
	}
	return TRUE;
}

bool exp_envi_input_high_2_low_event(ExpEnviInputCompTypeData *comp_data, bool *valid)
{
	char str[EXP_ENVI_COMP_STATUS_MAX_STRING_LENGTH];
	*valid = FALSE;
	switch (comp_data->status)
	{
		case EXP_ENVI_COMP_STATUS_LOW:	
			return print_message(BUG_MSG ,"ExperimentHandlers", "ExpEnviEvaluate", "exp_envi_input_high_2_low_event", "comp_data->status == EXP_ENVI_COMP_STATUS_LOW");	
		case EXP_ENVI_COMP_STATUS_LOW_SUCCESS:	
			return print_message(BUG_MSG ,"ExperimentHandlers", "ExpEnviEvaluate", "exp_envi_input_high_2_low_event", "comp_data->status == EXP_ENVI_COMP_STATUS_LOW_SUCCESS");	
		case EXP_ENVI_COMP_STATUS_HIGH:
			comp_data->status = EXP_ENVI_COMP_STATUS_IDLE;
			comp_data->low_2_high_switch_success = 0;
			comp_data->high_2_low_switch_success = 0;	
			*valid = FALSE;
			break;		
		case EXP_ENVI_COMP_STATUS_HIGH_SUCCESS:	
			comp_data->status = EXP_ENVI_COMP_STATUS_LOW;
			*valid = TRUE;
			break;	
		case EXP_ENVI_COMP_STATUS_IDLE:
			if (comp_data->constraints.initial_status == EXP_ENVI_COMP_STATUS_HIGH)
			{
				comp_data->status = EXP_ENVI_COMP_STATUS_LOW;
				*valid = TRUE;
			}
			break;	
		default:
			get_exp_envi_comp_status_type_string(comp_data->status, str);   
			return print_message(BUG_MSG ,"ExperimentHandlers", "ExpEnviEvaluate", "exp_envi_input_high_2_low_event", str);	
	}
	return TRUE;
}
