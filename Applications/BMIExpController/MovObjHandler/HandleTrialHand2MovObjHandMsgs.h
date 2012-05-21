#ifndef HANDLE_TRIAL_HAND_2_MOV_OBJ_HAND_MSGS_H
#define HANDLE_TRIAL_HAND_2_MOV_OBJ_HAND_MSGS_H

#include <gtk/gtk.h>
#include <stdbool.h>
#include "../../../Library/Status/MovObjStatus.h"
#include "../../../Library/MovObjData/MovObjData.h"
#include "../../../Library/Messages/TrialHand2MovObjHand.h"
#include "../../../Library/Messages/MovObjHand2MovObjDurHand.h"
#include "../../../Library/TrialsData/TrialTypes.h"

bool handle_trial_handler_to_mov_obj_handler_msg(MovObjData *mov_obj_data, MovObjStatus *mov_obj_status, TrialType *mov_obj_trial_type_status, TimeStamp current_time, TrialHand2MovObjHandMsg *msgs_trial_hand_2_mov_obj_hand, MovObjHand2MovObjDurHandMsg *msgs_mov_obj_hand_2_mov_obj_dur_hand);












#endif
