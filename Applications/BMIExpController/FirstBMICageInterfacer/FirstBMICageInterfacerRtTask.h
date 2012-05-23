#ifndef FIRST_BMI_CAGE_INTERFACER_RT_TASK_H
#define FIRST_BMI_CAGE_INTERFACER_RT_TASK_H


#include <gtk/gtk.h>
#include <stdbool.h>
#include <rtai_shm.h>
#include <rtai_nam2num.h>
#include "../../../Library/Messages/ExpEnviHand2ExpEnviInterf.h"
#include "../../../Library/Messages/MovObjHand2MovObjInterf.h"
#include "../../../../BlueSpike/RtTasksData.h"
#include "../../../../BlueSpike/Library/RtTaskStats/RtTaskStats.h"
#include "HandleExpEnviHand2ExpEnviInterfMsgs.h"
#include "HandleMovObjHand2MovObjInterfMsgs.h"
#include "HandleExpEnviInterf2ExpEnviHandMsgs.h"
#include "HandleMovObjInterf2MovObjHandMsgs.h"
#include "../../../Library/RS232/RS232Handler.h"

bool create_cage_interfacer_rt_thread(RtTasksData *rt_tasks_data);
bool kill_cage_interfacer_rt_thread(void);




#endif
