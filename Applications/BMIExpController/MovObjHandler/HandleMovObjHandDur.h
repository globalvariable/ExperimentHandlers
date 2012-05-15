#ifndef MOV_OBJ_HAND_DUR_H
#define MOV_OBJ_HAND_DUR_H


#include <gtk/gtk.h>
#include <stdbool.h>
#include "../../../Library/Messages/MovObjDurHand2MovObjHand.h"
#include "../../../Library/Status/MovObjDurStatus.h"

bool handle_mov_obj_handler_duration(MovObjDurationStatus *mov_obj_duration_status, TimeStamp current_time, TimeStamp handling_end_time, MovObjDurHand2MovObjHandMsg *msgs_mov_obj_dur_hand_2_mov_obj_hand);



#endif
