#ifndef HANDLE_EXP_ENVI_HAND_2_TRIAL_HAND_MSGS_H
#define HANDLE_EXP_ENVI_HAND_2_TRIAL_HAND_MSGS_H


#include <gtk/gtk.h>
#include <stdbool.h>
#include "../../../Library/Messages/ExpEnviHand2TrialHand.h"
#include "../../../Library/Messages/TrialHand2TrialDurHand.h"
#include "../../../Library/Messages/TrialHand2ExpEnviHand.h"
#include "../../../Library/Messages/TrialHand2MovObjHand.h"
#include "../../../Library/Status/TrialStatus.h"
#include "../../../Library/TrialsData/TrialTypes.h"
#include "../../../Library/TrialsData/TrialData.h"


bool handle_exp_envi_handler_to_trial_handler_msg(TrialTypesData *trial_types_data, TrialsHistory *trials_history, TrialStatus *trial_status, TimeStamp current_time, ExpEnviHand2TrialHandMsg *msgs_exp_envi_hand_2_trial_hand, TrialHand2TrialDurHandMsg *msgs_trial_hand_2_trial_dur_hand, TrialHand2ExpEnviHandMsg *msgs_trial_hand_2_exp_envi_hand, TrialHand2MovObjHandMsg *msgs_trial_hand_2_mov_obj_hand);





#endif
