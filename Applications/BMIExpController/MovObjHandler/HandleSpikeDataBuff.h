#ifndef HANDLE_SPIKE_DATA_BUFF_H
#define HANDLE_SPIKE_DATA_BUFF_H


#include "../../../Library/Status/MovObjStatus.h"
#include "../../../Library/MovObjData/MovObjData.h"
#include "../../../../IzNeuronSimulators/Library/SpikeData/SpikeData.h"
#include "../../Library/Robot/ThreeDofRobot.h"
#include "../../../../IzNeuronSimulators/Applications/HybridNetRLBMI/HybridNetRLBMI.h"
#include "../ExpParadigm/MovObjHandParadigm.h"

bool handle_spike_data_buff(MovObjStatus mov_obj_status, TimeStamp current_time, SpikeData *scheduled_spike_data, ThreeDofRobot *robot, MovObjHandParadigmRobotReach *mov_obj_paradigm);


#endif
