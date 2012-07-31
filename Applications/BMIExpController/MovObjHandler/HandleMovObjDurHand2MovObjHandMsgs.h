#ifndef HANDLE_MOV_OBJ_DUR_HAND_2_MOV_OBJ_HAND_MSGS_H
#define HANDLE_MOV_OBJ_DUR_HAND_2_MOV_OBJ_HAND_MSGS_H


#include <gtk/gtk.h>
#include <stdbool.h>
#include "HandleSpikeDataBuff.h"
#include "ConfigMovObjComponentNums.h"
#include "MovObjHandlerConfig.h"
#include "../../../Library/Status/MovObjStatus.h"
#include "../../../Library/TrialsData/TrialTypes.h"
#include "../../../Library/MovObjData/MovObjData.h"
#include "../../../Library/Messages/MovObjDurHand2MovObjHand.h"
#include "../../../Library/Messages/MovObjHand2MovObjDurHand.h"
#include "../../../Library/Messages/MovObjHand2TrialHand.h"
#include "../../../Library/Messages/MovObjHand2MovObjInterf.h"
#include "../../../Library/Messages/MovObjHand2NeuralNet.h"

bool handle_mov_obj_dur_handler_to_mov_obj_handler_msg(MovObjData *mov_obj_data, MovObjStatus *mov_obj_status, TrialType mov_obj_trial_type_status, TimeStamp current_time, MovObjDurHand2MovObjHandMsg *msgs_mov_obj_dur_hand_2_mov_obj_hand, MovObjHand2TrialHandMsg *msgs_mov_obj_hand_2_trial_hand, MovObjHand2MovObjDurHandMsg *msgs_mov_obj_hand_2_mov_obj_dur_hand, MovObjHand2MovObjInterfMsg *msgs_mov_obj_hand_2_mov_obj_interf, MovObjHand2NeuralNetMsgMultiThread *msgs_mov_obj_hand_2_neural_net_multi_thread, SpikeData *scheduled_spike_data, MovObjLocationType current_location);



#endif
