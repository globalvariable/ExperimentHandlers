#ifndef HANDLE_TRIAL_DUR_HAND_2_TRIAL_HAND_MSGS_H
#define HANDLE_TRIAL_DUR_HAND_2_TRIAL_HAND_MSGS_H


#include <gtk/gtk.h>
#include <stdbool.h>
#include "../../../Library/Messages/TrialDurHand2TrialHand.h"
#include "../../../Library/Status/TrialStatus.h"


bool handle_trial_dur_handler_to_trial_handler_msg(TrialStatus *trial_status, TimeStamp current_time, TrialDurHand2TrialHandMsg *msgs_trial_dur_hand_2_trial_hand);





#endif
