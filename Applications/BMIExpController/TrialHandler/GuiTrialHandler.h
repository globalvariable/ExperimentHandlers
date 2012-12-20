#ifndef GUI_TRIAL_HANDLER_H
#define GUI_TRIAL_HANDLER_H

#include "../../../Library/Messages/Gui2TrialHand.h"
#include "../../../../BlueSpike/Library/Misc/Misc.h"
#include "../../../../BlueSpike/System/RtTasksData/RtTasksData.h"
#include "TrialHandlerRtTask.h"


bool create_trial_handler_tab(GtkWidget *tabs, RtTasksData *rt_tasks_data, Gui2TrialHandMsg *msgs_gui_2_trial_hand);


#endif
