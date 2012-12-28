#ifndef GUI_TRIAL_HANDLER_H
#define GUI_TRIAL_HANDLER_H

#include "../../../Library/Messages/Gui2TrialHand.h"
#include "../../../../BlueSpike/Library/Misc/Misc.h"
#include "../../../../BlueSpike/System/RtTasksData/RtTasksData.h"
#include "TrialHandlerRtTask.h"
#include "../../../Library/ExpParadigm/ParadigmRobotReach/TrialHistory.h"

bool create_trial_handler_tab(GtkWidget *tabs, RtTasksData *rt_tasks_data, Gui2TrialHandMsg *msgs_gui_2_trial_hand, TrialHandParadigmRobotReach *trial_hand_paradigm, TrialHistory *trial_history);


#endif
