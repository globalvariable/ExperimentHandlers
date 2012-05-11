#ifndef EXP_ENVI_HANDLER_RT_TASK_H
#define EXP_ENVI_HANDLER_RT_TASK_H


#include <gtk/gtk.h>
#include <stdbool.h>
#include <rtai_shm.h>
#include <rtai_nam2num.h>
#include "../../../Library/Messages/Gui2ExpEnviHand.h"
#include "../../../Library/Messages/TrialHand2ExpEnviHand.h"
#include "../../../Library/Messages/ExpEnviDurHand2ExpEnviHand.h"
#include "../../../Library/Messages/ExpEnviHand2ExpEnviDurHand.h"
#include "../../../../BlueSpike/RtTasksData.h"
#include "../../../../BlueSpike/Library/RtTaskStats/RtTaskStats.h"
#include "ExpEnviDurationHandlerRtTask.h"

bool create_exp_envi_handler_rt_thread(Gui2ExpEnviHandMsg *msgs_gui_2_exp_envi_hand);
bool kill_exp_envi_handler_rt_thread(void);



#endif
