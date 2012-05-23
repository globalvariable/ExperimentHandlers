#ifndef GUI_MOV_OBJ_HANDLER_H
#define GUI_MOV_OBJ_HANDLER_H

#include "../../../Library/Messages/Gui2MovObjHand.h"
#include "../../../../BlueSpike/Library/Misc/Misc.h"
#include "../../../../BlueSpike/RtTasksData.h"



bool create_mov_obj_handler_tab(GtkWidget *tabs, RtTasksData *rt_tasks_data, Gui2MovObjHandMsg *msgs_gui_2_mov_obj_hand);


#endif
