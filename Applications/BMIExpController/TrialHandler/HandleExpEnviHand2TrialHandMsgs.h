#ifndef HANDLE_EXP_ENVI_HAND_2_TRIAL_HAND_MSGS_H
#define HANDLE_EXP_ENVI_HAND_2_TRIAL_HAND_MSGS_H


#include <gtk/gtk.h>
#include <stdbool.h>
#include "../../../Library/Messages/ExpEnviHand2TrialHand.h"
#include "../../../Library/Status/TrialStatus.h"


bool handle_exp_envi_handler_to_trial_handler_msg(TrialStatus *trial_status, TimeStamp current_time, ExpEnviHand2TrialHandMsg *msgs_exp_envi_hand_2_trial_hand);





#endif
