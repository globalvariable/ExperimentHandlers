#ifndef NEURAL_NET_2_MOV_OBJ_HAND_SCHED_H
#define NEURAL_NET_2_MOV_OBJ_HAND_SCHED_H


// SHOULD schedule the spike to spike data buff to be handled by mov obj handler. Otherwise, spike time cannot be binned correctly by MovObjHandler . 

#include "../../../BlueSpike/System/RtTasksData/RtTasksData.h"
#define MINIMUM_NEURAL_NET_2_MOV_OBJ_HAND_SPIKE_SCHEDULING_DELAY MOV_OBJ_HANDLER_PERIOD+IZ_PS_NETWORK_SIM_PERIOD+1000000   // 1 ms delay for prospective  jitter



#include "../../../IzNeuronSimulators/Library/SpikeData/SpikeData.h"
#include "../Messages/NeuralNet2MovObjHand.h"
#include "../MovObjData/MovObjData.h"

bool schedule_neural_net_spikes_to_mov_obj_hand(MovObjData *mov_obj_data, NeuralNet2MovObjHandMsgItem *msg_item, SpikeData *scheduled_spike_data);









#endif
