#ifndef TRIAL_HANDLER_RT_TASK_H
#define TRIAL_HANDLER_RT_TASK_H

#include <gtk/gtk.h>
#include <stdbool.h>
#include <rtai_shm.h>
#include <rtai_nam2num.h>
#include "TrialDurationHandlerRtTask.h"
#include "../../../Library/Status/TrialStatus.h"
#include "../../../Library/TrialsData/TrialTypes.h"
#include "../../../Library/TrialsData/TrialStats.h"
#include "../../../Library/TrialsData/TrialData.h"
#include "../../../Library/Messages/Gui2TrialHand.h"
#include "../../../Library/Messages/TrialDurHand2TrialHand.h"
#include "../../../Library/Messages/TrialHand2TrialDurHand.h"
#include "../../../../BlueSpike/Library/Misc/Misc.h"
#include "../../../../BlueSpike/SharedMemory.h"



bool create_trial_handler_rt_thread(TrialTypesData *trial_types_data, TrialStatsData *trial_stats, TrialsHistory *trials_history, Gui2TrialHandMsg *msgs_gui_2_trial_hand);
bool kill_trial_handler_rt_thread(void);









#endif
