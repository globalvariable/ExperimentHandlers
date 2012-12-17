#ifndef HANDLE_EXP_ENVI_INTERF_2_EXP_ENVI_HAND_MSGS_H
#define HANDLE_EXP_ENVI_INTERF_2_EXP_ENVI_HAND_MSGS_H


#include <gtk/gtk.h>
#include <stdbool.h>
#include "../../../Library/Status/ExpEnviStatus.h"
#include "../../../Library/ExpEnviData/ExpEnviData.h"
#include "../../../Library/ExpEnviData/ExpEnviEvaluate.h"
#include "../../../Library/Messages/ExpEnviHand2ExpEnviDurHand.h"
#include "ConfigExpEnviComponentNums.h"

bool handle_exp_envi_interf_to_exp_envi_handler_msg(ExpEnviData *exp_envi_data, TimeStamp current_time, ExpEnviHand2ExpEnviDurHandMsg *msgs_exp_envi_hand_2_exp_envi_dur_hand);



#endif
