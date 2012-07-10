#ifndef MOV_OBJ_HANDLER_RT_TASK_H
#define MOV_OBJ__HANDLER_RT_TASK_H


#include <gtk/gtk.h>
#include <stdbool.h>
#include <rtai_shm.h>
#include <rtai_nam2num.h>
#include "../../../Library/Messages/Gui2MovObjHand.h"
#include "../../../Library/Messages/TrialHand2MovObjHand.h"
#include "../../../Library/Messages/MovObjHand2TrialHand.h"
#include "../../../Library/Messages/MovObjHand2MovObjInterf.h"
#include "../../../Library/Messages/MovObjInterf2MovObjHand.h"
#include "../../../Library/Messages/MovObjDurHand2MovObjHand.h"
#include "../../../Library/Messages/MovObjHand2MovObjDurHand.h"
#include "../../../Library/Messages/MovObjHand2NeuralNet.h"
#include "../../../Library/Messages/NeuralNet2MovObjHand.h"
#include "../../../../BlueSpike/RtTasksData.h"
#include "../../../../BlueSpike/Library/RtTaskStats/RtTaskStats.h"
#include "../../../Library/MovObjData/MovObjData.h"
#include "HandleGui2MovObjHandMsgs.h"
#include "HandleMovObjDurHand2MovObjHandMsgs.h"
#include "HandleMovObjHand2MovObjDurHandMsgs.h"
#include "HandleTrialHand2MovObjHandMsgs.h"
#include "HandleMovObjInterf2MovObjHandMsgs.h"
#include "HandleNeuralNet2MovObjHandMsgs.h"
#include "HandleSpikeDataBuff.h"

bool create_mov_obj_handler_rt_thread(RtTasksData *rt_tasks_data, MovObjData *mov_obj_data, Gui2MovObjHandMsg *msgs_gui_2_mov_obj_hand);
bool kill_mov_obj_handler_rt_thread(void);



#endif
