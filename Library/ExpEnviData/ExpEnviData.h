#ifndef EXP_ENVI_DATA_H
#define EXP_ENVI_DATA_H

typedef struct __ExpEnviInputCompTypeConstraints ExpEnviInputCompTypeConstraints;
typedef struct __ExpEnviInputCompTypeData ExpEnviInputCompTypeData;
typedef struct __ExpEnviOutputCompTypeData ExpEnviOutputCompTypeData;
typedef struct __ExpEnviData ExpEnviData;

#include <gtk/gtk.h>
#include <stdbool.h>
#include <string.h>
#include "../../../BlueSpike/System/TimeStamp/TimeStamp.h"
#include "../../../BlueSpike/Library/Misc/Misc.h"
#include "ExpEnviComponentTypes.h"
#include "../Status/ExpEnviComponentStatus.h"

struct __ExpEnviInputCompTypeConstraints
{
	ExpEnviCompStatus	required_status_to_initiate_switching;		// high - low
	TimeStamp			max_high_status_duration;		
	TimeStamp			min_high_status_duration;	
	TimeStamp			max_low_status_duration;			
	TimeStamp			min_low_status_duration;		
	unsigned int			num_of_low_2_high_switch;
	unsigned int			num_of_high_2_low_switch;
};

struct __ExpEnviInputCompTypeData
{
	ExpEnviInputCompType					type;
	ExpEnviCompStatus					status;		// high - low
	unsigned int							low_2_high_switch_success;
	unsigned int							high_2_low_switch_success;
	ExpEnviInputCompTypeConstraints		constraints;
	bool 								enabled;
};

struct __ExpEnviOutputCompTypeData
{
	ExpEnviOutputCompType				type;
	ExpEnviCompStatus					status;		// high - low
	TimeStamp							high_status_duration;		
};

struct __ExpEnviData   // DO NOT BRING EXP ENVI STATUS HERE. IT IS KIND OF PRIVATE WHICH CAN BE CHANGED BY EXP ENVI HANDLER
{
	ExpEnviInputCompTypeData		*inp_comp_types;
	unsigned int					num_of_inp_comps;
	ExpEnviOutputCompTypeData	*outp_comp_types;
	unsigned int					num_of_outp_comps;
};

ExpEnviData* allocate_exp_envi_data(ExpEnviData* data);
ExpEnviData* deallocate_exp_envi_data(ExpEnviData* data);

bool get_input_component_type_idx_in_exp_envi_data(ExpEnviData *data, ExpEnviInputCompType comp_type, unsigned int *idx);
bool add_input_component_type_to_exp_envi_data(ExpEnviData *data, ExpEnviInputCompType comp_type, TimeStamp min_high_status_duration, TimeStamp max_high_status_duration, TimeStamp min_low_status_duration, TimeStamp max_low_status_duration, unsigned int num_of_low_2_high_switch, unsigned int num_of_high_2_low_switch, ExpEnviCompStatus required_status_to_initiate_switching, bool enabled);
bool is_input_component_type_used(ExpEnviData* data, ExpEnviInputCompType comp_type, bool *used);
bool submit_new_time_params_for_input_component_type(ExpEnviData *data, ExpEnviInputCompType comp_type, TimeStamp min_high_status_duration, TimeStamp max_high_status_duration, TimeStamp min_low_status_duration, TimeStamp max_low_status_duration);

bool submit_new_min_low_status_duration_for_input_component_type(ExpEnviData *data, ExpEnviInputCompType comp_type, TimeStamp min_low_status_duration);
bool submit_new_max_low_status_duration_for_input_component_type(ExpEnviData *data, ExpEnviInputCompType comp_type, TimeStamp max_low_status_duration);
bool submit_new_min_high_status_duration_for_input_component_type(ExpEnviData *data, ExpEnviInputCompType comp_type, TimeStamp min_high_status_duration);
bool submit_new_max_high_status_duration_for_input_component_type(ExpEnviData *data, ExpEnviInputCompType comp_type, TimeStamp max_high_status_duration);

bool get_output_component_type_idx_in_exp_envi_data(ExpEnviData *data, ExpEnviOutputCompType comp_type, unsigned int *idx);
bool add_output_component_type_to_exp_envi_data(ExpEnviData *data, ExpEnviOutputCompType comp_type, TimeStamp high_status_duration);
bool is_output_component_type_used(ExpEnviData* data, ExpEnviOutputCompType comp_type, bool *used);





#endif
