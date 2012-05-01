#ifndef MOV_OBJ_HANDLER_RT_TASK_H
#define MOV_OBJ__HANDLER_RT_TASK_H


#include <gtk/gtk.h>
#include <stdbool.h>
#include <rtai_shm.h>
#include <rtai_nam2num.h>
#include "../../../Library/Messages/Gui2MovObjHand.h"
#include "../../../../BlueSpike/RtTasksData.h"
#include "../../../../BlueSpike/Library/RtTaskStats/RtTaskStats.h"

bool create_mov_obj_handler_rt_thread(Gui2MovObjHandMsg *msgs_gui_2_mov_obj_hand);
bool kill_mov_obj_handler_rt_thread(void);



#endif
