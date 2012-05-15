#ifndef HANDLE_MOV_OBJ_INTERF_2_MOV_OBJ_HAND_MSGS_H
#define HANDLE_MOV_OBJ_INTERF_2_MOV_OBJ_HAND_MSGS_H


#include <gtk/gtk.h>
#include <stdbool.h>
#include "../../../Library/Status/MovObjStatus.h"
#include "../../../Library/MovObjData/MovObjData.h"
#include "../../../Library/Messages/MovObjInterf2MovObjHand.h"

bool handle_mov_obj_interf_to_mov_obj_handler_msg(MovObjData *mov_obj_data, MovObjStatus *mov_obj_status, TimeStamp current_time, MovObjInterf2MovObjHandMsg *msgs_mov_obj_interf_2_mov_obj_hand);



#endif