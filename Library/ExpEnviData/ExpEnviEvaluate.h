#ifndef EXP_ENVI_EVALUATE_H
#define EXP_ENVI_EVALUATE_H


#include "ExpEnviData.h"

bool time_out_success_for_input_comp(ExpEnviInputCompTypeData *comp_data, bool *has_response);
bool exp_envi_input_low_2_high_event(ExpEnviInputCompTypeData *comp_data, bool *cancellation_reqiured_for_low_status_timer, bool *setting_required_for_high_status_timer);
bool exp_envi_input_high_2_low_event(ExpEnviInputCompTypeData *comp_data, bool *cancellation_reqiured_for_high_status_timer, bool *setting_required_for_low_status_timer);
bool enable_exp_envi_input_with_status_reset(ExpEnviInputCompTypeData *comp_data, bool *cancellation_required_for_status_timer);
bool enable_exp_envi_input_with_no_status_reset(ExpEnviInputCompTypeData *comp_data, bool *timer_restart_reqiured_for_low_status, bool *timer_restart_reqiured_for_high_status) ;
bool disable_exp_envi_input_with_status_reset(ExpEnviInputCompTypeData *comp_data,  bool *cancellation_required_for_status_timer) ;
bool reset_exp_envi_input_with_status_reset(ExpEnviInputCompTypeData *comp_data, bool *timer_cancellation_required);
bool reset_exp_envi_input_with_status_saving(ExpEnviInputCompTypeData *comp_data, bool *timer_cancellation_required);



#endif
