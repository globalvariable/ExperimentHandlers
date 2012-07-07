#ifndef HANDLE_SPIKE_DATA_BUFF_H
#define HANDLE_SPIKE_DATA_BUFF_H

#include "../../../Library/Status/MovObjStatus.h"
#include "../../../Library/Messages/MovObjHand2MovObjInterf.h"
#include "../../../../IzNeuronSimulators/Library/SpikeData/SpikeData.h"

bool handle_spike_data_buff(MovObjStatus mov_obj_status, TimeStamp current_time, SpikeData *scheduled_spike_data, unsigned int *left_layer_spike_counter, unsigned int *right_layer_spike_counter );




#endif
