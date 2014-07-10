#ifndef MOV_OBJ_DATA_H
#define MOV_OBJ_DATA_H

typedef struct __MovObjConstraints MovObjConstraints;
typedef struct __MovObjCompTypeData MovObjCompTypeData;
typedef struct __MovObjData MovObjData;
typedef struct __MovObjStats MovObjStats;

#include <gtk/gtk.h>
#include <stdbool.h>
#include <string.h>
#include "../../../BlueSpike/System/TimeStamp/TimeStamp.h"
#include "../../../BlueSpike/Library/Misc/Misc.h"
#include "MovObjComponentTypes.h"
#include "MovObjLocationType.h"
#include "../Messages/NeuralNet2MovObjHand.h"


struct __MovObjStats
{
	double		 	trajectory_success;		///  saves the information about how good the mov obj followed the target trajectory
	unsigned int		num_of_actions;		
	double			trajectory_success_ratio;		
};

struct __MovObjConstraints
{
	TimeStamp			stay_at_start_duration;
	TimeStamp			stay_at_target_duration;		
	MovObjLocationType	initial_threshold;	// for rewarding // millimeters
	MovObjLocationType	threshold_increment_amount;	
	MovObjLocationType	current_threshold;		
	MovObjLocationType	target_location;
	TimeStamp			motor_command_delivery_interval;
};

struct __MovObjCompTypeData
{
	MovObjCompType		type;
	MovObjConstraints		comp_constraints;
	MovObjStats			comp_stats;
};

struct __MovObjData
{
	MovObjCompTypeData		*comp_types;
	unsigned int				num_of_comps;
	MovObjConstraints			glo_constraints;
	TimeStamp				neural_net_2_mov_obj_hand_delay;   // move this into neural_net_2_mov_obj_hand when you have spare time.
	MovObjStats				main_stats;
};

MovObjData* allocate_mov_obj_data(MovObjData* data, TimeStamp	neural_net_2_mov_obj_hand_delay, TimeStamp	HARD_MIN_NEURAL_NET_2_MOV_OBJ_HAND_EVENT_SCHEDULING_DELAY);
MovObjData* deallocate_mov_obj_data(MovObjData* data);

bool get_component_type_idx_in_mov_obj_data(MovObjData *data, MovObjCompType comp_type, unsigned int *idx);
bool add_component_type_to_mov_obj_data(MovObjData *data, MovObjCompType comp_type, TimeStamp	stay_at_start_duration, TimeStamp stay_at_target_duration, double initial_threshold, double threshold_increment_amount, MovObjLocationType target_location, TimeStamp motor_command_delivery_interval, TimeStamp	HARD_MIN_NEURAL_NET_2_MOV_OBJ_HAND_EVENT_SCHEDULING_DELAY);
bool set_global_constraints_mov_obj_data(MovObjData *data, TimeStamp stay_at_start_duration, TimeStamp stay_at_target_duration, MovObjLocationType initial_threshold, MovObjLocationType threshold_increment_amount, MovObjLocationType target_location, TimeStamp motor_command_delivery_interval, TimeStamp	HARD_MIN_NEURAL_NET_2_MOV_OBJ_HAND_EVENT_SCHEDULING_DELAY);
bool is_mov_obj_component_type_used(MovObjData* data, MovObjCompType comp_type, bool *used);

#endif
