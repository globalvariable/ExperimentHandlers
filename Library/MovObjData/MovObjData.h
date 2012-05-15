#ifndef MOV_OBJ_DATA_H
#define MOV_OBJ_DATA_H

typedef struct __MovObjConstraints MovObjConstraints;
typedef struct __MovObjCompTypeData MovObjCompTypeData;
typedef struct __MovObjData MovObjData;

#include <gtk/gtk.h>
#include <stdbool.h>
#include <string.h>
#include "../../../BlueSpike/TimeStamp.h"
#include "../../../BlueSpike/Library/Misc/Misc.h"
#include "MovObjComponentTypes.h"

struct __MovObjConstraints
{
	TimeStamp			stay_at_start_duration;
	TimeStamp			stay_at_target_duration;		
	double				initial_threshold;	// for rewarding
	double				threshold_increment_amount;			
};

struct __MovObjCompTypeData
{
	MovObjCompType		type;
	MovObjConstraints		constraints;
};

struct __MovObjData
{
	MovObjCompTypeData		*comp_types;
	unsigned int				num_of_comps;
};

MovObjData* allocate_mov_obj_data(MovObjData* data);
MovObjData* deallocate_mov_obj_data(MovObjData* data);

bool get_component_type_idx_in_mov_obj_data(MovObjData *data, MovObjCompType comp_type, unsigned int *idx);
bool add_component_type_to_mov_obj_data(MovObjData *data, MovObjCompType comp_type, TimeStamp	stay_at_start_duration, TimeStamp stay_at_target_duration, double initial_threshold, double threshold_increment_amount);
bool is_mov_obj_component_type_used(MovObjData* data, MovObjCompType comp_type, bool *used);

#endif
