#ifndef GUI_EXP_ENVI_HANDLER_H
#define GUI_EXP_ENVI_HANDLER_H

#include "../../../Library/Messages/Gui2ExpEnviHand.h"
#include "../../../../BlueSpike/Library/Misc/Misc.h"
#include "../../../../BlueSpike/System/RtTasksData/RtTasksData.h"



bool create_exp_envi_handler_tab(GtkWidget *tabs, RtTasksData *rt_tasks_data, Gui2ExpEnviHandMsg *msgs_gui_2_exp_envi_hand);


#endif
