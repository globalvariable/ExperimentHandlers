#ifndef HANDLE_TRIAL_HAND_2_EXP_ENVI_HAND_MSGS_H
#define HANDLE_TRIAL_HAND_2_EXP_ENVI_HAND_MSGS_H

#include <gtk/gtk.h>
#include <stdbool.h>
#include "../../../Library/Status/ExpEnviStatus.h"
#include "../../../Library/ExpEnviData/ExpEnviData.h"
#include "../../../Library/Messages/TrialHand2ExpEnviHand.h"
#include "../../../Library/Messages/ExpEnviHand2ExpEnviInterf.h"
#include "../../../Library/Messages/ExpEnviHand2ExpEnviDurHand.h"
#include "../../../Library/TrialsData/TrialTypes.h"
#include "ConfigExpEnviComponentNums.h"

bool handle_trial_handler_to_exp_envi_handler_msg(ExpEnviData *exp_envi_data, ExpEnviStatus *exp_envi_status, TimeStamp current_time, TrialHand2ExpEnviHandMsg *msgs_trial_hand_2_exp_envi_hand, ExpEnviHand2ExpEnviInterfMsg *msgs_exp_envi_hand_2_exp_envi_interf, ExpEnviHand2ExpEnviDurHandMsg *msgs_exp_envi_hand_2_exp_envi_dur_hand);












#endif
