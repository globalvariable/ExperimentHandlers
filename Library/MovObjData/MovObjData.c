#include "MovObjData.h"


MovObjData* allocate_mov_obj_data(MovObjData* data, TimeStamp	neural_net_2_mov_obj_hand_delay, TimeStamp	HARD_MIN_NEURAL_NET_2_MOV_OBJ_HAND_EVENT_SCHEDULING_DELAY)
{
	if (neural_net_2_mov_obj_hand_delay < HARD_MIN_NEURAL_NET_2_MOV_OBJ_HAND_EVENT_SCHEDULING_DELAY)
		return (MovObjData*)print_message(BUG_MSG ,"ExperimentHandlers", "MovObjData", "deallocate_mov_obj_data", "neural_net_2_mov_obj_hand_delay < MINIMUM_NEURAL_NET_2_MOV_OBJ_HAND_SPIKE_SCHEDULING_DELAY.");    
	if (data != NULL)
	{
		data = deallocate_mov_obj_data(data);
		data = allocate_mov_obj_data(data, neural_net_2_mov_obj_hand_delay, HARD_MIN_NEURAL_NET_2_MOV_OBJ_HAND_EVENT_SCHEDULING_DELAY);
		return data;
	}  
	data = g_new0(MovObjData,1);
	data->neural_net_2_mov_obj_hand_delay = neural_net_2_mov_obj_hand_delay;
	print_message(INFO_MSG ,"ExperimentHandlers", "MovObjData", "allocate_mov_obj_data", "Created mov_obj_data.");
	return data;	
}

MovObjData* deallocate_mov_obj_data(MovObjData* data)
{
	if (data == NULL)
		return (MovObjData*)print_message(BUG_MSG ,"ExperimentHandlers", "MovObjData", "deallocate_mov_obj_data", "mov_obj_data == NULL.");    
	g_free(data->comp_types);
	g_free(data);
	print_message(INFO_MSG ,"ExperimentHandlers", "MovObjData", "deallocate_mov_obj_data", "Destroyed mov_obj_data.");
	return NULL;
}

bool get_component_type_idx_in_mov_obj_data(MovObjData *data, MovObjCompType comp_type, unsigned int *idx)
{
	unsigned int i;
	unsigned int num_of_comps = data->num_of_comps;
	MovObjCompTypeData	*comp_types = data->comp_types;
	*idx = num_of_comps; 

	for (i = 0; i < num_of_comps; i++)
	{
		if (comp_type == comp_types[i].type)
		{
			*idx = i;
			return TRUE;
		}
	}
	return FALSE;	
}
bool add_component_type_to_mov_obj_data(MovObjData *data, MovObjCompType comp_type, TimeStamp	stay_at_start_duration, TimeStamp stay_at_target_duration, double initial_threshold, double threshold_increment_amount, MovObjLocationType target_location, TimeStamp motor_command_delivery_interval, TimeStamp	HARD_MIN_NEURAL_NET_2_MOV_OBJ_HAND_EVENT_SCHEDULING_DELAY)
{
	unsigned int i;
	bool comp_type_used;
	char temp[MOV_OBJ_COMPONENT_TYPE_MAX_STRING_LENGTH];
	MovObjCompTypeData	*lcl_comp_types;
	if (stay_at_start_duration < HARD_MIN_NEURAL_NET_2_MOV_OBJ_HAND_EVENT_SCHEDULING_DELAY)
		return print_message(ERROR_MSG ,"ExperimentHandlers", "MovObjData", "add_component_type_to_mov_obj_data", "stay_at_start_duration < MINIMUM_NEURAL_NET_2_MOV_OBJ_HAND_SPIKE_SCHEDULING_DELAY.");	
	if (!is_mov_obj_component_type_used(data, comp_type, &comp_type_used))
		return print_message(ERROR_MSG ,"ExperimentHandlers", "MovObjData", "add_component_type_to_mov_obj_data", "! is_component_type_used()");	
	if (comp_type_used)
		return print_message(ERROR_MSG ,"ExperimentHandlers", "MovObjData", "add_component_type_to_mov_obj_data", "comp_type_used");	
	if (!get_mov_obj_component_type_string(comp_type, temp))    // is trial type valid ?
		return print_message(ERROR_MSG ,"ExperimentHandlers", "MovObjData", "add_component_type_to_mov_obj_data", "!get_mov_obj_component_type_string()");
	lcl_comp_types = g_new0(MovObjCompTypeData, data->num_of_comps + 1);
	for (i = 0; i < data->num_of_comps; i++)
		lcl_comp_types[i] = data->comp_types[i];
	g_free(data->comp_types);
	data->comp_types = lcl_comp_types;
	data->comp_types[data->num_of_comps].type = comp_type;
	data->comp_types[data->num_of_comps].comp_constraints.stay_at_start_duration = stay_at_start_duration;
	data->comp_types[data->num_of_comps].comp_constraints.stay_at_target_duration = stay_at_target_duration;
	data->comp_types[data->num_of_comps].comp_constraints.initial_threshold = initial_threshold;
	data->comp_types[data->num_of_comps].comp_constraints.current_threshold = initial_threshold;
	data->comp_types[data->num_of_comps].comp_constraints.threshold_increment_amount = threshold_increment_amount;
	data->comp_types[data->num_of_comps].comp_constraints.target_location = target_location;
	data->comp_types[data->num_of_comps].comp_constraints.motor_command_delivery_interval = motor_command_delivery_interval;
	data->num_of_comps++;
	print_message(INFO_MSG ,"ExperimentHandlers", "MovObjData", "add_component_type_to_mov_obj_data", temp);	
	return TRUE;
}
bool is_mov_obj_component_type_used(MovObjData* data, MovObjCompType comp_type, bool *used)
{
	unsigned int i;
	char temp[MOV_OBJ_COMPONENT_TYPE_MAX_STRING_LENGTH];
	*used = FALSE;
	
	if (!get_mov_obj_component_type_string(comp_type, temp))    // is comp type valid ?
		return print_message(ERROR_MSG ,"ExperimentHandlers", "MovObjData", "is_component_type_used", "!get_mov_obj_component_type_string()");

	for (i = 0; i < data->num_of_comps; i++)
	{
		if (comp_type == data->comp_types[i].type)
		{
			*used = TRUE;
			return TRUE;
		}
	}
	return TRUE;
}
bool set_global_constraints_mov_obj_data(MovObjData *data, TimeStamp stay_at_start_duration, TimeStamp stay_at_target_duration, MovObjLocationType initial_threshold, MovObjLocationType threshold_increment_amount, MovObjLocationType target_location, TimeStamp motor_command_delivery_interval, TimeStamp	HARD_MIN_NEURAL_NET_2_MOV_OBJ_HAND_EVENT_SCHEDULING_DELAY)
{
	if (stay_at_start_duration < HARD_MIN_NEURAL_NET_2_MOV_OBJ_HAND_EVENT_SCHEDULING_DELAY)
		return print_message(ERROR_MSG ,"ExperimentHandlers", "MovObjData", "set_global_constraints_mov_obj_data", "stay_at_start_duration < MINIMUM_NEURAL_NET_2_MOV_OBJ_HAND_SPIKE_SCHEDULING_DELAY.");	
	data->glo_constraints.stay_at_start_duration = stay_at_start_duration;
	data->glo_constraints.stay_at_target_duration = stay_at_target_duration;
	data->glo_constraints.initial_threshold = initial_threshold;
	data->glo_constraints.current_threshold = initial_threshold;
	data->glo_constraints.threshold_increment_amount = threshold_increment_amount;	
	data->glo_constraints.target_location = target_location;	
	data->glo_constraints.motor_command_delivery_interval = motor_command_delivery_interval;	
	return TRUE;
}


