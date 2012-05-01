#ifndef HANDLE_MOV_OBJ_HAND_2_TRIAL_HAND_MSGS_H
#define HANDLE_MOV_OBJ_HAND_2_TRIAL_HAND_MSGS_H


#include <gtk/gtk.h>
#include <stdbool.h>
#include "../../../Library/Messages/MovObjHand2TrialHand.h"
#include "../../../Library/Status/TrialStatus.h"


bool handle_mov_obj_handler_to_trial_handler_msg(TrialStatus *trial_status, TimeStamp current_time, MovObjHand2TrialHandMsg *msgs_mov_obj_hand_2_trial_hand);





#endif
