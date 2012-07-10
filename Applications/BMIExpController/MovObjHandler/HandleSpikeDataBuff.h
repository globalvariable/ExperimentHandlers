#ifndef HANDLE_SPIKE_DATA_BUFF_H
#define HANDLE_SPIKE_DATA_BUFF_H


#include "MovObjHandlerConfig.h"
#include "../../../Library/Status/MovObjStatus.h"
#include "../../../Library/Messages/MovObjHand2MovObjInterf.h"
#include "../../../../IzNeuronSimulators/Library/SpikeData/SpikeData.h"

bool handle_spike_data_buff(MovObjStatus mov_obj_status, TimeStamp current_time, SpikeData *scheduled_spike_data);
bool handle_spike_data_buff_for_bin(SpikeData *scheduled_spike_data, TimeStamp current_time, MovObjHand2MovObjInterfMsg *msgs_mov_obj_hand_2_mov_obj_interf);



#endif
