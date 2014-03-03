#ifndef EXP_ENVI_HAND_PARADIGM_H
#define EXP_ENVI_HAND_PARADIGM_H


#include "../../../BlueSpike/System/TimeStamp/TimeStamp.h"

typedef struct 
{
	unsigned int				selected_target_led_component_list_idx;
	unsigned int				*target_led_component_indexes_list;
	unsigned int				num_of_target_led_components;
	TimeStamp				min_low_status_duration_for_nose_poke; 
	TimeStamp				max_extra_low_status_duration_for_nose_poke;
} ExpEnviHandParadigmRobotReach;


#endif
