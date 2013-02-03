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
#include "../ExpParadigm/TrialHandParadigm.h"
#include "../../../../BlueSpike/Library/Misc/Randn.h"
#include "../ExpParadigm/TrialHistory.h"
#include "../../../Library/Status/TrialStatusHistory.h"
#include "Compile.h"

#ifdef	SIMULATION_MODE
void initialize_exp_envi_handler_to_trial_handler_msg_params(TrialStatus *arg_trial_status, ExpEnviHand2TrialHandMsg *arg_msgs_exp_envi_hand_2_trial_hand, TrialHand2TrialDurHandMsg *arg_msgs_trial_hand_2_trial_dur_hand, TrialHand2ExpEnviHandMsg *arg_msgs_trial_hand_2_exp_envi_hand, TrialHand2MovObjHandMsg *arg_msgs_trial_hand_2_mov_obj_hand, TrialHand2NeuralNetMsg *arg_msgs_trial_hand_2_neural_net, TrialHand2SpikeGenMsg *arg_msgs_trial_hand_2_spike_gen, TrialHandParadigmRobotReach *arg_paradigm, ClassifiedTrialHistory *arg_classified_history, TrialHand2GuiMsg *arg_msgs_trial_hand_2_gui, TrialStatusHistory *arg_trial_status_history);
#endif
#ifdef	IN_VIVO_MODE
void initialize_exp_envi_handler_to_trial_handler_msg_params(TrialStatus *arg_trial_status, ExpEnviHand2TrialHandMsg *arg_msgs_exp_envi_hand_2_trial_hand, TrialHand2TrialDurHandMsg *arg_msgs_trial_hand_2_trial_dur_hand, TrialHand2ExpEnviHandMsg *arg_msgs_trial_hand_2_exp_envi_hand, TrialHand2MovObjHandMsg *arg_msgs_trial_hand_2_mov_obj_hand, TrialHand2NeuralNetMsg *arg_msgs_trial_hand_2_neural_net, TrialHandParadigmRobotReach *arg_paradigm, ClassifiedTrialHistory *arg_classified_history, TrialHand2GuiMsg *arg_msgs_trial_hand_2_gui, TrialStatusHistory *arg_trial_status_history);
#endif

bool handle_exp_envi_handler_to_trial_handler_msg(TimeStamp current_time);





#endif
