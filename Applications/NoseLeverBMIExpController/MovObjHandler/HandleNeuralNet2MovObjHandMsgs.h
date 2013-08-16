#ifndef HAND_NEURAL_NET_2_MOV_OBJ_HAND_MSGS_H
#define HAND_NEURAL_NET_2_MOV_OBJ_HAND_MSGS_H



#include <gtk/gtk.h>
#include <stdbool.h>
#include "../../../Library/Status/MovObjStatus.h"
#include "../../../Library/MovObjData/MovObjData.h"
#include "../../../Library/Messages/NeuralNet2MovObjHand.h"
#include "../../../Library/Messages/NeuralNet2MovObjHand.h"
#include "../../../Library/Robot/ThreeDofRobot.h"
#include "../../../IzNeuronSimulators/Library/SpikeData/SpikeData.h"

bool handle_neural_net_to_mov_obj_handler_msg(ThreeDofRobot *robot_arm, TimeStamp current_time, NeuralNet2MovObjHandMsgMultiThread *msgs_neural_net_2_mov_obj_hand_multi_thread, SpikeData *scheduled_spike_data);





#endif
