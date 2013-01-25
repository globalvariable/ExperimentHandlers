#ifndef GUI_EXP_ENVI_HANDLER_H
#define GUI_EXP_ENVI_HANDLER_H

#include "../../../Library/Messages/Gui2ExpEnviHand.h"
#include "../../../Library/Messages/ExpEnviHand2Gui.h"
#include "../../../../BlueSpike/Library/Misc/Misc.h"
#include "../../../../BlueSpike/System/RtTasksData/RtTasksData.h"
#include "DataHandling/DataHandling.h"
#include "../../../Library/ExpEnviData/ExpEnviHistory.h"

bool create_exp_envi_handler_tab(GtkWidget *tabs, RtTasksData *rt_tasks_data, Gui2ExpEnviHandMsg *msgs_gui_2_exp_envi_hand, ExpEnviHand2GuiMsg *msgs_exp_envi_hand_2_gui, ExpEnviInputStatusHistory *exp_envi_input_status_history, ExpEnviOutputStatusHistory *exp_envi_output_status_history);


#endif
