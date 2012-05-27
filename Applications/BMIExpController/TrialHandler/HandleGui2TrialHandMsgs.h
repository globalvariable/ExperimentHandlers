#ifndef HANDLE_GUI_2_TRIAL_HAND_MSGS_H
#define HANDLE_GUI_2_TRIAL_HAND_MSGS_H

#include <gtk/gtk.h>
#include <stdbool.h>
#include "../../../Library/Messages/Gui2TrialHand.h"
#include "../../../Library/Messages/TrialHand2TrialDurHand.h"
#include "../../../Library/Messages/TrialHand2ExpEnviHand.h"
#include "../../../Library/Messages/TrialHand2MovObjHand.h"
#include "../../../Library/Messages/TrialHand2NeuralNet.h"
#include "../../../Library/Messages/TrialHand2SpikeGen.h"
#include "../../../Library/Status/TrialStatus.h"
#include "../../../Library/TrialsData/TrialTypes.h"

bool handle_gui_to_trial_handler_msg(TrialTypesData *trial_types_data, TrialStatus *trial_status, TimeStamp current_time, Gui2TrialHandMsg *msgs_gui_2_trial_hand, TrialHand2TrialDurHandMsg* msgs_trial_hand_2_trial_dur_hand, TrialHand2ExpEnviHandMsg *msgs_trial_hand_2_exp_envi_hand, TrialHand2MovObjHandMsg *msgs_trial_hand_2_mov_obj_hand, TrialHand2NeuralNetMsg *msgs_trial_hand_2_neural_net, TrialHand2SpikeGenMsg *msgs_trial_hand_2_spike_gen);




#endif
