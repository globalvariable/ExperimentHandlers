#ifndef HANDLE_SPIKE_DATA_BUFF_H
#define HANDLE_SPIKE_DATA_BUFF_H


#include "../../../Library/Status/MovObjStatus.h"
#include "../../../Library/MovObjData/MovObjData.h"
#include "../../../../IzNeuronSimulators/Library/SpikeData/SpikeData.h"
#include "../../Library/Robot/ThreeDofRobot.h"
#include "../../../../IzNeuronSimulators/Applications/HybridNetRLBMI/HybridNetRLBMI.h"

bool handle_spike_data_buff(MovObjStatus mov_obj_status, TimeStamp current_time, SpikeData *scheduled_spike_data, ThreeDofRobot *robot);
bool handle_spike_data_buff_for_bin(MovObjData *mov_obj_data, SpikeData *scheduled_spike_data, TimeStamp current_time, MovObjLocationType current_location);



#endif
