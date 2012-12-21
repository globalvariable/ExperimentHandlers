#ifndef HANDLE_MOV_OBJ_DUR_HAND_2_MOV_OBJ_HAND_MSGS_H
#define HANDLE_MOV_OBJ_DUR_HAND_2_MOV_OBJ_HAND_MSGS_H


#include <gtk/gtk.h>
#include <stdbool.h>
#include "HandleSpikeDataBuff.h"
#include "../../../Library/Status/MovObjStatus.h"
#include "../../../Library/Status/MovObjDurStatus.h"
#include "../../../Library/MovObjData/MovObjData.h"
#include "../../../Library/Messages/MovObjDurHand2MovObjHand.h"
#include "../../../Library/Messages/MovObjHand2MovObjDurHand.h"
#include "../../../Library/Messages/MovObjHand2TrialHand.h"
#include "../../../Library/Messages/MovObjHand2NeuralNet.h"
#include "../../../Library/Robot/ThreeDofRobot.h"
#include "../../../../BlueSpike/Library/LogBuffer/MessageLogBuffer.h"
#include "HandleRS232Buffers.h"
#include "../../../Library/ExpParadigm/ParadigmRobotReach/MovObjHandParadigm.h"


bool handle_mov_obj_dur_handler_to_mov_obj_handler_msg(ThreeDofRobot *robot_arm, TimeStamp current_time, MovObjDurHand2MovObjHandMsg *msgs_mov_obj_dur_hand_2_mov_obj_hand, MovObjHand2TrialHandMsg *msgs_mov_obj_hand_2_trial_hand, MovObjHand2MovObjDurHandMsg *msgs_mov_obj_hand_2_mov_obj_dur_hand, MovObjHand2NeuralNetMsgMultiThread *msgs_mov_obj_hand_2_neural_net_multi_thread, SpikeData *scheduled_spike_data, MovObjLocationType current_location, MessageLogBuffer *message_log, MovObjHandParadigmRobotReach *mov_obj_paradigm);



#endif
