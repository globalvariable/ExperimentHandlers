#ifndef HANDLE_GUI_2_TRIAL_HAND_MSGS_H
#define HANDLE_GUI_2_TRIAL_HAND_MSGS_H

#include <gtk/gtk.h>
#include <stdbool.h>
#include "../../../Library/Messages/Gui2TrialHand.h"
#include "../../../Library/Status/TrialStatus.h"

bool handle_gui_to_trial_handler_msg(TrialStatus *trial_status, TimeStamp current_time, Gui2TrialHandMsg *msgs_gui_2_trial_hand);




#endif
