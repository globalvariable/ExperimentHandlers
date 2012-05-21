#ifndef HANDLE_MOV_OBJ_DUR_HAND_2_MOV_OBJ_HAND_MSGS_H
#define HANDLE_MOV_OBJ_DUR_HAND_2_MOV_OBJ_HAND_MSGS_H


#include <gtk/gtk.h>
#include <stdbool.h>
#include "../../../Library/Status/MovObjStatus.h"
#include "../../../Library/MovObjData/MovObjData.h"
#include "../../../Library/Messages/MovObjDurHand2MovObjHand.h"
#include "../../../Library/Messages/MovObjHand2TrialHand.h"

bool handle_mov_obj_dur_handler_to_mov_obj_handler_msg(MovObjData *mov_obj_data, MovObjStatus *mov_obj_status, TimeStamp current_time, MovObjDurHand2MovObjHandMsg *msgs_mov_obj_dur_hand_2_mov_obj_hand, MovObjHand2TrialHandMsg *msgs_mov_obj_hand_2_trial_hand);



#endif
