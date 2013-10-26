#ifndef HANDLE_TRIAL_HAND_2_MOV_OBJ_HAND_MSGS_H
#define HANDLE_TRIAL_HAND_2_MOV_OBJ_HAND_MSGS_H

#include <gtk/gtk.h>
#include <stdbool.h>
#include "ConfigMovObjHandler.h"
#include "../../../Library/Status/MovObjStatus.h"
#include "../../../Library/Status/MovObjDurStatus.h"
#include "../../../Library/MovObjData/MovObjData.h"
#include "../../../Library/Messages/TrialHand2MovObjHand.h"
#include "../../../Library/Messages/MovObjHand2MovObjDurHand.h"
#include "../../../Library/Messages/MovObjHand2TrialHand.h"
#include "../../../Library/Messages/MovObjHand2Gui.h"
#include "../../../Library/Robot/ThreeDofRobot.h"
#include "../../../Library/Coordinate/Cartesian.h"
#include "../ExpParadigm/MovObjHandParadigm.h"
#include "../../../../BlueSpike/Library/LogBuffer/MessageLogBuffer.h"
#include "../../../Library/Status/MovObjStatusHistory.h"
#include "../../../Library/Messages/MovObjHand2NeuralNet.h"

bool handle_trial_handler_to_mov_obj_handler_msg(ThreeDofRobot *robot_arm, MovObjStatus *mov_obj_status, TimeStamp current_time, TrialHand2MovObjHandMsg *msgs_trial_hand_2_mov_obj_hand, MovObjHand2MovObjDurHandMsg *msgs_mov_obj_hand_2_mov_obj_dur_hand, MovObjHand2TrialHandMsg *msgs_mov_obj_hand_2_trial_hand, MovObjHandParadigmRobotReach *mov_obj_paradigm, MessageLogBuffer *message_log, MovObjStatusHistory* mov_obj_status_history, MovObjHand2GuiMsg *msgs_mov_obj_hand_2_gui, MovObjHand2NeuralNetMsgMultiThread *msgs_mov_obj_hand_2_neural_net_multi_thread);












#endif
