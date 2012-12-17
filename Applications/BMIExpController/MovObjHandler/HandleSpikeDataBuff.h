#ifndef HANDLE_SPIKE_DATA_BUFF_H
#define HANDLE_SPIKE_DATA_BUFF_H


#include "MovObjHandlerConfig.h"
#include "../../../Library/Status/MovObjStatus.h"
#include "../../../Library/MovObjData/MovObjData.h"
#include "../../../Library/TrialsData/TrialTypes.h"
#include "../../../../IzNeuronSimulators/Library/SpikeData/SpikeData.h"

bool handle_spike_data_buff(MovObjStatus mov_obj_status, TimeStamp current_time, SpikeData *scheduled_spike_data);
bool handle_spike_data_buff_for_bin(MovObjData *mov_obj_data, SpikeData *scheduled_spike_data, TimeStamp current_time, TrialType mov_obj_trial_type_status, MovObjLocationType current_location);



#endif
