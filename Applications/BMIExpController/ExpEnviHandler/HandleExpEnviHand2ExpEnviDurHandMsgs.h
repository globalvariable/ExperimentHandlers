#ifndef HANDLE_EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSGS_H
#define HANDLE_EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSGS_H

#include "../../../Library/Status/ExpEnviDurStatus.h"
#include "../../../Library/Messages/ExpEnviHand2ExpEnviDurHand.h"
#include "../../../../BlueSpike/Library/Misc/Misc.h"
#include "../../../../BlueSpike/TimeStamp.h"
#include "ConfigExpEnviComponentNums.h"

bool handle_exp_envi_handler_to_exp_envi_dur_handler_msg(ExpEnviInputsMinDurationStatus *exp_envi_inputs_min_dur_status, ExpEnviInputsMaxDurationStatus *exp_envi_inputs_max_dur_status, TimeStamp current_time, ExpEnviHand2ExpEnviDurHandMsg *msgs_exp_envi_hand_2_exp_envi_dur_hand, TimeStamp *inputs_handling_end_time_min, TimeStamp *inputs_handling_end_time_max);











#endif
