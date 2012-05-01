#ifndef GUI_TRIAL_HANDLER_H
#define GUI_TRIAL_HANDLER_H

#include "../../../Library/Combos/TrialTypesCombo.h"
#include "../../../Library/TrialsData/TrialStats.h"
#include "../../../Library/TrialsData/TrialData.h"
#include "../../../Library/Messages/Gui2TrialHand.h"
#include "../../../../BlueSpike/Library/Misc/Misc.h"
#include "../../../../BlueSpike/SharedMemory.h"



bool create_trial_handler_tab(GtkWidget *tabs, TrialTypesData *trial_types_data, TrialStatsData *trial_stats, TrialsHistory *trials_history, Gui2TrialHandMsg *msgs_gui_2_trial_hand);


#endif
