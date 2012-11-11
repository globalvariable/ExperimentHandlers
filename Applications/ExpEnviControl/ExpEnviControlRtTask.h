#ifndef EXP_ENVI_CONTROL_RT_TASK_H
#define EXP_ENVI_CONTROL_RT_TASK_H


#include <gtk/gtk.h>
#include <stdbool.h>
#include <rtai_shm.h>
#include <rtai_nam2num.h>
#include "ExpEnviControl.h"
#include "../../../BlueSpike/RtTasksData.h"
#include "../../../BlueSpike/Library/RtTaskStats/RtTaskStats.h"
#include "../../Library/RS232/RS232Handler.h"

bool create_exp_envi_control_rt_thread(RtTasksData *rt_tasks_data, SEM* exp_envi_rx_buff_sem, SEM *exp_envi_tx_buff_sem, unsigned char *exp_envi_rx_buff, unsigned char *exp_envi_tx_buff);

#endif
