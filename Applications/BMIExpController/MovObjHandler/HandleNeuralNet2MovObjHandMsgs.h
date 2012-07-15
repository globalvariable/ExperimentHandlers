#ifndef HAND_NEURAL_NET_2_MOV_OBJ_HAND_MSGS_H
#define HAND_NEURAL_NET_2_MOV_OBJ_HAND_MSGS_H



#include <gtk/gtk.h>
#include <stdbool.h>
#include "../../../Library/Status/MovObjStatus.h"
#include "../../../Library/MovObjData/MovObjData.h"
#include "../../../Library/Messages/NeuralNet2MovObjHand.h"
#include "../../../Library/Messages/MovObjHand2MovObjInterf.h"

bool handle_neural_net_to_mov_obj_handler_msg(MovObjData *mov_obj_data, TimeStamp current_time, NeuralNet2MovObjHandMsgMultiThread *msgs_neural_net_2_mov_obj_hand_multi_thread, SpikeData *scheduled_spike_data);





#endif
