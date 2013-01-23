#ifndef GUI_TRIAL_HANDLER_H
#define GUI_TRIAL_HANDLER_H

#include "../../../Library/Messages/Gui2TrialHand.h"
#include "../../../Library/Messages/TrialHand2Gui.h"
#include "../../../../BlueSpike/Library/Misc/Misc.h"
#include "../../../../BlueSpike/System/RtTasksData/RtTasksData.h"
#include "TrialHandlerRtTask.h"
#include "../../../Library/ExpParadigm/ParadigmRobotReach/TrialHistory.h"
#include "DataHandling/DataHandling.h"

bool create_trial_handler_tab(GtkWidget *tabs, RtTasksData *rt_tasks_data, Gui2TrialHandMsg *msgs_gui_2_trial_hand, TrialHandParadigmRobotReach *trial_hand_paradigm, ClassifiedTrialHistory* classified_trial_history, TrialHand2GuiMsg *msgs_trial_hand_2_gui);


#endif
