#ifndef EXP_ENVI_HAND_DUR_H
#define EXP_ENVI_HAND_DUR_H


#include <gtk/gtk.h>
#include <stdbool.h>
#include "../../../Library/Messages/ExpEnviDurHand2ExpEnviHand.h"
#include "../../../Library/Status/ExpEnviDurStatus.h"

bool handle_exp_envi_handler_duration(ExpEnviInputsDurationStatus *exp_envi_inputs_duration_status, TimeStamp current_time, TimeStamp *inputs_handling_end_time, unsigned int num_of_input_components, ExpEnviDurHand2ExpEnviHandMsg *msgs_exp_envi_dur_hand_2_exp_envi_hand);



#endif
