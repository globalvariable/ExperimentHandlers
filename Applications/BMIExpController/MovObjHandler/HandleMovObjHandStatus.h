#ifndef HAND_MOV_OBJ_HAND_STATUS_H
#define HAND_MOV_OBJ_HAND_STATUS_H



#include <gtk/gtk.h>
#include <stdbool.h>
#include "../../../Library/Messages/MovObjHand2MovObjInterf.h"
#include "../../../Library/Status/MovObjStatus.h"
#include "../../../Library/TrialsData/TrialTypes.h"
#include "ConfigMovObjComponentNums.h"

bool handle_mov_obj_handler_status(MovObjStatus mov_obj_status, TrialType mov_obj_trial_type_status, TimeStamp current_time, MovObjHand2MovObjInterfMsg *msgs_mov_obj_hand_2_mov_obj_interf);




#endif
