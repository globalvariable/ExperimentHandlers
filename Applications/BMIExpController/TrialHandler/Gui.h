#ifndef GUI_H
#define GUI_H


#include <gtk/gtk.h>
#include <stdbool.h>
#include <stdlib.h>
#include "GuiTrialHandler.h"
#include "GuiExpEnviHandler.h"
#include "GuiMovObjHandler.h"
#include "../../../Library/TrialsData/TrialStats.h"
#include "../../../Library/Messages/Gui2TrialHand.h"

// Functions
void create_gui_handler(TrialTypesData *trial_types_data, TrialStatsData *trial_stats, TrialsHistory *trials_history, Gui2TrialHandMsg *msgs_gui_2_trial_hand);



#endif
