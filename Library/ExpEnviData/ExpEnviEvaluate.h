#ifndef EXP_ENVI_EVALUATE_H
#define EXP_ENVI_EVALUATE_H


#include "ExpEnviData.h"

bool time_out_success_for_input_comp(ExpEnviInputCompTypeData *comp_data, bool *has_response);
bool time_out_fail_for_input_comp(ExpEnviInputCompTypeData *comp_data);
void reset_exp_envi_input_comp(ExpEnviInputCompTypeData *comp_data);
bool exp_envi_input_low_2_high_event(ExpEnviInputCompTypeData *comp_data, bool *valid);
bool exp_envi_input_high_2_low_event(ExpEnviInputCompTypeData *comp_data, bool *valid);





#endif
