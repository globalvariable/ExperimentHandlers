#include "ExpEnviData.h"


ExpEnviData* allocate_exp_envi_data(ExpEnviData* data)
{
	if (data != NULL)
	{
		data = deallocate_exp_envi_data(data);
		data = allocate_exp_envi_data(data);
		return data;
	}  
	data = g_new0(ExpEnviData,1);
	print_message(INFO_MSG ,"ExperimentHandlers", "ExpEnviData", "allocate_exp_envi_data", "Created exp_envi_data.");
	return data;	
}

ExpEnviData* deallocate_exp_envi_data(ExpEnviData* data)
{
	if (data == NULL)
		return (ExpEnviData*)print_message(BUG_MSG ,"ExperimentHandlers", "ExpEnviData", "deallocate_exp_envi_data", "exp_envi_data == NULL.");    
	g_free(data->inp_comp_types);
	g_free(data->outp_comp_types);
	g_free(data);
	print_message(INFO_MSG ,"ExperimentHandlers", "ExpEnviData", "deallocate_exp_envi_data", "Destroyed exp_envi_data.");
	return NULL;
}

bool get_input_component_type_idx_in_exp_envi_data(ExpEnviData *data, ExpEnviInputCompType comp_type, unsigned int *idx)
{
	unsigned int i;
	unsigned int num_of_inp_comps = data->num_of_inp_comps;
	ExpEnviInputCompTypeData	*inp_comp_types = data->inp_comp_types;
	*idx = num_of_inp_comps; 

	for (i = 0; i < num_of_inp_comps; i++)
	{
		if (comp_type == inp_comp_types[i].type)
		{
			*idx = i;
			return TRUE;
		}
	}
	return FALSE;	
}
bool add_input_component_type_to_exp_envi_data(ExpEnviData *data, ExpEnviInputCompType comp_type, TimeStamp min_high_status_duration, TimeStamp max_high_status_duration, TimeStamp min_low_status_duration, TimeStamp max_low_status_duration, unsigned int num_of_low_2_high_switch, unsigned int num_of_high_2_low_switch, ExpEnviCompStatus required_status_to_initiate_switching, bool enabled)
{
	unsigned int i;
	bool comp_type_used;
	char temp[EXP_ENVI_INPUT_COMPONENT_TYPE_MAX_STRING_LENGTH];
	ExpEnviInputCompTypeData	*lcl_inp_comp_types;
	if ((min_high_status_duration + 100000000) >= max_high_status_duration)  // should be 100msec diff to be robust
		return print_message(ERROR_MSG ,"ExperimentHandlers", "ExpEnviData", "add_input_component_type_to_exp_envi_data", "Inconvenient min_high_status_duration & max_high_status_duration");	
	if ((min_low_status_duration + 100000000) >= max_low_status_duration)  // should be 100msec diff to be robust
		return print_message(ERROR_MSG ,"ExperimentHandlers", "ExpEnviData", "add_input_component_type_to_exp_envi_data", "Inconvenient min_low_status_duration & max_low_status_duration");	
	if (!is_input_component_type_used(data, comp_type, &comp_type_used))
		return print_message(ERROR_MSG ,"ExperimentHandlers", "ExpEnviData", "add_input_component_type_to_exp_envi_data", "! is_input_component_type_used()");	
	if (comp_type_used)
		return print_message(ERROR_MSG ,"ExperimentHandlers", "ExpEnviData", "add_input_component_type_to_exp_envi_data", "comp_type_used");	
	if (!get_exp_envi_input_component_type_string(comp_type, temp))    // is trial type valid ?
		return print_message(ERROR_MSG ,"ExperimentHandlers", "ExpEnviData", "add_input_component_type_to_exp_envi_data", "!get_exp_envi_input_component_type_string()");
	lcl_inp_comp_types = g_new0(ExpEnviInputCompTypeData, data->num_of_inp_comps + 1);
	for (i = 0; i < data->num_of_inp_comps; i++)
		lcl_inp_comp_types[i] = data->inp_comp_types[i];
	g_free(data->inp_comp_types);
	data->inp_comp_types = lcl_inp_comp_types;
	data->inp_comp_types[data->num_of_inp_comps].type = comp_type;
	data->inp_comp_types[data->num_of_inp_comps].status = EXP_ENVI_COMP_STATUS_READY_FOR_SWITCHING;
	data->inp_comp_types[data->num_of_inp_comps].enabled = enabled;
	data->inp_comp_types[data->num_of_inp_comps].constraints.max_high_status_duration = max_high_status_duration;
	data->inp_comp_types[data->num_of_inp_comps].constraints.min_high_status_duration = min_high_status_duration;
	data->inp_comp_types[data->num_of_inp_comps].constraints.max_low_status_duration = max_low_status_duration;
	data->inp_comp_types[data->num_of_inp_comps].constraints.min_low_status_duration = min_low_status_duration;
	data->inp_comp_types[data->num_of_inp_comps].constraints.num_of_low_2_high_switch = num_of_low_2_high_switch;
	data->inp_comp_types[data->num_of_inp_comps].constraints.num_of_high_2_low_switch = num_of_high_2_low_switch;
	data->inp_comp_types[data->num_of_inp_comps].constraints.required_status_to_initiate_switching = required_status_to_initiate_switching;
	data->num_of_inp_comps++;
	print_message(INFO_MSG ,"ExperimentHandlers", "ExpEnviData", "add_input_component_type_to_exp_envi_data", temp);	
	return TRUE;
}

bool submit_new_time_params_for_input_component_type(ExpEnviData *data, ExpEnviInputCompType comp_type, TimeStamp min_high_status_duration, TimeStamp max_high_status_duration, TimeStamp min_low_status_duration, TimeStamp max_low_status_duration)
{
	unsigned int idx;
	if (! get_input_component_type_idx_in_exp_envi_data(data, comp_type, &idx))
		return print_message(ERROR_MSG ,"ExperimentHandlers", "ExpEnviData", "submit_new_time_params_for_input_component_type", "! get_input_component_type_idx_in_exp_envi_data()");	

	if ((min_high_status_duration + 100000000) >= max_high_status_duration)  // should be 100msec diff to be robust
		return print_message(ERROR_MSG ,"ExperimentHandlers", "ExpEnviData", "submit_new_time_params_for_input_component_type", "Inconvenient min_high_status_duration & max_high_status_duration");	
	if ((min_low_status_duration + 100000000) >= max_low_status_duration)  // should be 100msec diff to be robust
		return print_message(ERROR_MSG ,"ExperimentHandlers", "ExpEnviData", "submit_new_time_params_for_input_component_type", "Inconvenient min_low_status_duration & max_low_status_duration");	

	data->inp_comp_types[idx].constraints.max_high_status_duration = max_high_status_duration;
	data->inp_comp_types[idx].constraints.min_high_status_duration = min_high_status_duration;
	data->inp_comp_types[idx].constraints.max_low_status_duration = max_low_status_duration;
	data->inp_comp_types[idx].constraints.min_low_status_duration = min_low_status_duration;
	return TRUE;
}
bool is_input_component_type_used(ExpEnviData* data, ExpEnviInputCompType comp_type, bool *used)
{
	unsigned int i;
	char temp[EXP_ENVI_INPUT_COMPONENT_TYPE_MAX_STRING_LENGTH];
	*used = FALSE;
	
	if (!get_exp_envi_input_component_type_string(comp_type, temp))    // is trial type valid ?
		return print_message(ERROR_MSG ,"ExperimentHandlers", "ExpEnviData", "is_input_component_type_used", "!get_exp_envi_input_component_type_string()");

	for (i = 0; i < data->num_of_inp_comps; i++)
	{
		if (comp_type == data->inp_comp_types[i].type)
		{
			*used = TRUE;
			return TRUE;
		}
	}
	return TRUE;
}

bool get_output_component_type_idx_in_exp_envi_data(ExpEnviData *data, ExpEnviOutputCompType comp_type, unsigned int *idx)
{
	unsigned int i;
	unsigned int num_of_outp_comps = data->num_of_outp_comps;
	ExpEnviOutputCompTypeData	*outp_comp_types = data->outp_comp_types;
	*idx = num_of_outp_comps; 

	for (i = 0; i < num_of_outp_comps; i++)
	{
		if (comp_type == outp_comp_types[i].type)
		{
			*idx = i;
			return TRUE;
		}
	}
	return FALSE;	
}
bool add_output_component_type_to_exp_envi_data(ExpEnviData *data, ExpEnviOutputCompType comp_type, TimeStamp high_status_duration)
{
	unsigned int i;
	bool comp_type_used;
	char temp[EXP_ENVI_OUTPUT_COMPONENT_TYPE_MAX_STRING_LENGTH];
	ExpEnviOutputCompTypeData	*lcl_outp_comp_types;
	if (!is_output_component_type_used(data, comp_type, &comp_type_used))
		return print_message(ERROR_MSG ,"ExperimentHandlers", "ExpEnviData", "add_output_component_type_to_exp_envi_data", "! is_output_component_type_used()");	
	if (comp_type_used)
		return print_message(ERROR_MSG ,"ExperimentHandlers", "ExpEnviData", "add_output_component_type_to_exp_envi_data", "comp_type_used");	
	if (!get_exp_envi_output_component_type_string(comp_type, temp))    // is trial type valid ?
		return print_message(ERROR_MSG ,"ExperimentHandlers", "ExpEnviData", "add_output_component_type_to_exp_envi_data", "!get_exp_envi_output_component_type_string()");
	lcl_outp_comp_types = g_new0(ExpEnviOutputCompTypeData, data->num_of_outp_comps + 1);
	for (i = 0; i < data->num_of_outp_comps; i++)
		lcl_outp_comp_types[i] = data->outp_comp_types[i];
	g_free(data->outp_comp_types);
	data->outp_comp_types = lcl_outp_comp_types;
	data->outp_comp_types[data->num_of_outp_comps].type = comp_type;
	data->outp_comp_types[data->num_of_outp_comps].status = EXP_ENVI_COMP_STATUS_LOW;
	data->outp_comp_types[data->num_of_outp_comps].high_status_duration = high_status_duration;
	data->num_of_outp_comps++;
	print_message(INFO_MSG ,"ExperimentHandlers", "ExpEnviData", "add_output_component_type_to_exp_envi_data", temp);	
	return TRUE;
}
bool is_output_component_type_used(ExpEnviData* data, ExpEnviOutputCompType comp_type, bool *used)
{
	unsigned int i;
	char temp[EXP_ENVI_OUTPUT_COMPONENT_TYPE_MAX_STRING_LENGTH];
	*used = FALSE;
	
	if (!get_exp_envi_output_component_type_string(comp_type, temp))    // is trial type valid ?
		return print_message(ERROR_MSG ,"ExperimentHandlers", "ExpEnviData", "is_output_component_type_used", "!get_exp_envi_output_component_type_string()");

	for (i = 0; i < data->num_of_outp_comps; i++)
	{
		if (comp_type == data->outp_comp_types[i].type)
		{
			*used = TRUE;
			return TRUE;
		}
	}
	return TRUE;	
}
