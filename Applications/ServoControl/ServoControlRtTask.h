#ifndef SERVO_CONTROL_RT_TASK_H
#define SERVO_CONTROL_RT_TASK_H


#include <gtk/gtk.h>
#include <stdbool.h>
#include <rtai_shm.h>
#include <rtai_nam2num.h>
#include "ServoControl.h"
#include "../../../BlueSpike/RtTasksData.h"
#include "../../../BlueSpike/Library/RtTaskStats/RtTaskStats.h"
#include "../../Library/RS232/RS232Handler.h"

bool create_servo_control_rt_thread(RtTasksData *rt_tasks_data);

#endif
