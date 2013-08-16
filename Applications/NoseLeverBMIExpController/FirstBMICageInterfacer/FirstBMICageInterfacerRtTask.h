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
#include "HandleRS232Hand2RS232DurHandMsgs.h"
#include "HandleRS232DurHand2RS232HandMsgs.h"
#include "../../../Library/RS232/RS232Data.h"
#include "../../../Library/Messages/ExpEnviHand2ExpEnviInterf.h"
#include "../../../Library/Messages/ExpEnviInterf2ExpEnviHand.h"
#include "../../../Library/Messages/MovObjHand2MovObjInterf.h"
#include "../../../Library/Messages/MovObjInterf2MovObjHand.h"
#include "../../../Library/Messages/RS232Hand2RS232DurHand.h"
#include "../../../Library/Messages/RS232DurHand2RS232Hand.h"

bool create_cage_interfacer_rt_thread(RtTasksData *rt_tasks_data, RS232Data *rs_232_data);
bool kill_cage_interfacer_rt_thread(void);




#endif
