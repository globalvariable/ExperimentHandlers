#ifndef HANDLE_EXP_ENVI_HAND_2_TRIAL_HAND_MSGS_H
#define HANDLE_EXP_ENVI_HAND_2_TRIAL_HAND_MSGS_H


#include <gtk/gtk.h>
#include <stdbool.h>
#include "../../../Library/Messages/TrialHand2Gui.h"
#include "../../../Library/Messages/ExpEnviHand2TrialHand.h"
#include "../../../Library/Messages/TrialHand2TrialDurHand.h"
#include "../../../Library/Messages/TrialHand2ExpEnviHand.h"
#include "../../../Library/Messages/TrialHand2MovObjHand.h"
#include "../../../Library/Messages/TrialHand2NeuralNet.h"
#include "../../../Library/Messages/TrialHand2SpikeGen.h"
#include "../../../Library/Status/TrialStatus.h"
#include "../../../Library/ExpParadigm/ParadigmRobotReach/TrialHandParadigm.h"
#include "../../../../BlueSpike/Library/Misc/Randn.h"
#include "../../../Library/ExpParadigm/ParadigmRobotReach/TrialHistory.h"
#include "../../../Library/Status/TrialStatusHistory.h"

bool handle_exp_envi_handler_to_trial_handler_msg(TrialStatus *trial_status, TimeStamp current_time, ExpEnviHand2TrialHandMsg *msgs_exp_envi_hand_2_trial_hand, TrialHand2TrialDurHandMsg *msgs_trial_hand_2_trial_dur_hand, TrialHand2ExpEnviHandMsg *msgs_trial_hand_2_exp_envi_hand, TrialHand2MovObjHandMsg *msgs_trial_hand_2_mov_obj_hand, TrialHand2NeuralNetMsg *msgs_trial_hand_2_neural_net, TrialHand2SpikeGenMsg *msgs_trial_hand_2_spike_gen, TrialHandParadigmRobotReach *paradigm, ClassifiedTrialHistory* classified_history, TrialHand2GuiMsg *msgs_trial_hand_2_gui, TrialStatusHistory *trial_status_history);





#endif
