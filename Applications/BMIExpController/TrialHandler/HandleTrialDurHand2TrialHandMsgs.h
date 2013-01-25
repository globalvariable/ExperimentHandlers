#ifndef HANDLE_TRIAL_DUR_HAND_2_TRIAL_HAND_MSGS_H
#define HANDLE_TRIAL_DUR_HAND_2_TRIAL_HAND_MSGS_H


#include <gtk/gtk.h>
#include <stdbool.h>
#include "../../../Library/Messages/TrialDurHand2TrialHand.h"
#include "../../../Library/Messages/TrialHand2TrialDurHand.h"
#include "../../../Library/Messages/TrialHand2ExpEnviHand.h"
#include "../../../Library/Messages/TrialHand2MovObjHand.h"
#include "../../../Library/Messages/TrialHand2NeuralNet.h"
#include "../../../Library/Messages/TrialHand2SpikeGen.h"
#include "../../../Library/Status/TrialStatus.h"
#include "../../../Library/ExpParadigm/ParadigmRobotReach/TrialHistory.h"
#include "../../../Library/ExpParadigm/ParadigmRobotReach/TrialHandParadigm.h"
#include "../../../Library/Messages/TrialHand2Gui.h"
#include "../../../Library/Status/TrialStatusHistory.h"

bool handle_trial_dur_handler_to_trial_handler_msg(TrialStatus *trial_status, TimeStamp current_time, TrialDurHand2TrialHandMsg *msgs_trial_dur_hand_2_trial_hand, TrialHand2TrialDurHandMsg *msgs_trial_hand_2_trial_dur_hand, TrialHand2ExpEnviHandMsg *msgs_trial_hand_2_exp_envi_hand, TrialHand2MovObjHandMsg *msgs_trial_hand_2_mov_obj_hand, TrialHand2NeuralNetMsg *msgs_trial_hand_2_neural_net, TrialHand2SpikeGenMsg *msgs_trial_hand_2_spike_gen, ClassifiedTrialHistory* classified_history, TrialHandParadigmRobotReach *paradigm, TrialHand2GuiMsg *msgs_trial_hand_2_gui, TrialStatusHistory *trial_status_history);





#endif
