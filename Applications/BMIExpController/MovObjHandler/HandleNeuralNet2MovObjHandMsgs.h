#ifndef HAND_NEURAL_NET_2_MOV_OBJ_HAND_MSGS_H
#define HAND_NEURAL_NET_2_MOV_OBJ_HAND_MSGS_H



#include <gtk/gtk.h>
#include <stdbool.h>
#include "../../../Library/Status/MovObjStatus.h"
#include "../../../Library/MovObjData/MovObjData.h"
#include "../../../Library/Messages/NeuralNet2MovObjHand.h"
#include "../../../Library/Messages/MovObjHand2MovObjInterf.h"

bool handle_neural_net_to_mov_obj_handler_msg(MovObjStatus mov_obj_status, TimeStamp current_time, NeuralNet2MovObjHandMsg *msgs_neural_net_2_mov_obj_hand, MovObjHand2MovObjInterfMsg *msgs_mov_obj_hand_2_mov_obj_interf);





#endif
