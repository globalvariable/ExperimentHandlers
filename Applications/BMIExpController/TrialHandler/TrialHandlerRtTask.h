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
#include "../../../Library/Messages/ExpEnviHand2TrialHand.h"
#include "../../../Library/Messages/MovObjHand2TrialHand.h"
#include "../../../Library/Messages/TrialHand2ExpEnviHand.h"
#include "../../../Library/Messages/TrialHand2MovObjHand.h"
#include "../../../Library/Messages/TrialHand2NeuralNet.h"
#include "../../../Library/Messages/NeuralNet2TrialHand.h"
#include "../../../Library/Messages/TrialHand2SpikeGen.h"
#include "../../../Library/Messages/SpikeGen2TrialHand.h"
#include "../../../../BlueSpike/Library/Misc/Misc.h"
#include "../../../../BlueSpike/System/RtTasksData/RtTasksData.h"
#include "../../../../BlueSpike/Library/RtTaskStats/RtTaskStats.h"
#include "HandleGui2TrialHandMsgs.h"
#include "HandleTrialDurHand2TrialHandMsgs.h"
#include "HandleExpEnviHand2TrialHandMsgs.h"
#include "HandleMovObjHand2TrialHandMsgs.h"

bool create_trial_handler_rt_thread(RtTasksData *rt_tasks_data, TrialTypesData *trial_types_data, TrialStatsData *trial_stats, TrialsHistory *trials_history, Gui2TrialHandMsg *msgs_gui_2_trial_hand);
bool kill_trial_handler_rt_thread(void);









#endif
