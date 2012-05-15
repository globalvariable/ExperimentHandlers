#ifndef MOV_OBJ_DURATION_HANDLER_RT_TASK_H
#define MOV_OBJ_DURATION_HANDLER_RT_TASK_H

#include <gtk/gtk.h>
#include <stdbool.h>
#include <rtai_shm.h>
#include <rtai_nam2num.h>
#include "../../../../BlueSpike/Library/Misc/Misc.h"
#include "../../../Library/Messages/MovObjDurHand2MovObjHand.h"
#include "../../../Library/Messages/MovObjHand2MovObjDurHand.h"
#include "../../../Library/Status/MovObjDurStatus.h"
#include "../../../../BlueSpike/RtTasksData.h"
#include "../../../../BlueSpike/Library/RtTaskStats/RtTaskStats.h"
#include "HandleMovObjHand2MovObjDurHandMsgs.h"
#include "HandleMovObjHandDur.h"

bool create_mov_obj_duration_handler_rt_thread(MovObjDurHand2MovObjHandMsg *msgs_mov_obj_dur_hand_2_mov_obj_hand, MovObjHand2MovObjDurHandMsg *msgs_mov_obj_hand_2_mov_obj_dur_hand);
bool kill_mov_obj_duration_handler_rt_thread(void);









#endif
