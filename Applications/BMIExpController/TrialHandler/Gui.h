#ifndef GUI_H
#define GUI_H


#include <gtk/gtk.h>
#include <stdbool.h>
#include <stdlib.h>
#include "GuiTrialHandler.h"
#include "../../../Library/Messages/Gui2TrialHand.h"

// Functions
void create_gui_handler(RtTasksData *rt_tasks_data, Gui2TrialHandMsg *msgs_gui_2_trial_hand, TrialHandParadigmRobotReach *trial_hand_paradigm, TrialHistory *trial_history);



#endif
