#ifndef FIRST_BMI_CAGE_INTERFACER_RT_TASK_H
#define FIRST_BMI_CAGE_INTERFACER_RT_TASK_H


#include <gtk/gtk.h>
#include <stdbool.h>
#include <rtai_shm.h>
#include <rtai_nam2num.h>
#include "../../../Library/Messages/Gui2ExpEnviInterf.h"
#include "../../../Library/Messages/Gui2MovObjInterf.h"
#include "../../../../BlueSpike/RtTasksData.h"
#include "../../../../BlueSpike/Library/RtTaskStats/RtTaskStats.h"

bool create_cage_interfacer_rt_thread(Gui2ExpEnviInterfMsg *msgs_gui_2_exp_envi_interf, Gui2MovObjInterfMsg *msgs_gui_2_mov_obj_interf);
bool kill_cage_interfacer_rt_thread(void);




#endif
