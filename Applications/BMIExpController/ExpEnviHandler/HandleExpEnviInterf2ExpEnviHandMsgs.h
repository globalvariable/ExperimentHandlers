#ifndef HANDLE_EXP_ENVI_INTERF_2_EXP_ENVI_HAND_MSGS_H
#define HANDLE_EXP_ENVI_INTERF_2_EXP_ENVI_HAND_MSGS_H


#include <gtk/gtk.h>
#include <stdbool.h>
#include "../../../Library/Status/ExpEnviStatus.h"
#include "../../../Library/ExpEnviData/ExpEnviData.h"
#include "../../../Library/Messages/ExpEnviInterf2ExpEnviHand.h"

bool handle_exp_envi_interf_to_exp_envi_handler_msg(ExpEnviData *exp_envi_data, ExpEnviStatus *exp_envi_status, TimeStamp current_time, ExpEnviInterf2ExpEnviHandMsg *msgs_exp_envi_interf_2_exp_envi_hand);



#endif
