#include "ExpEnviEvaluate.h"

bool time_out_success_for_input_comp(ExpEnviInputCompTypeData *comp_data, bool *has_response)
{
	char str[EXP_ENVI_COMP_STATUS_MAX_STRING_LENGTH];
	*has_response = FALSE;

	switch (comp_data->status)
	{
		case EXP_ENVI_COMP_STATUS_LOW:			
			if (comp_data->enabled)
			{	
				comp_data->status = EXP_ENVI_COMP_STATUS_LOW_SUCCESS;
				comp_data->high_2_low_switch_success++;
			}
			else
			{	
				comp_data->low_2_high_switch_success = 0;
				comp_data->high_2_low_switch_success = 0;
			}
			break;			
		case EXP_ENVI_COMP_STATUS_LOW_SUCCESS:
			return print_message(BUG_MSG ,"ExperimentHandlers", "ExpEnviEvaluate", "time_out_success_for_input_comp", "comp_data->status == EXP_ENVI_COMP_STATUS_LOW_SUCCESS");	
		case EXP_ENVI_COMP_STATUS_HIGH:
			if (comp_data->enabled)
			{	
				comp_data->status = EXP_ENVI_COMP_STATUS_HIGH_SUCCESS;
				comp_data->low_2_high_switch_success++;
			}
			else
			{
				comp_data->low_2_high_switch_success = 0;
				comp_data->high_2_low_switch_success = 0;
			}
			break;			
		case EXP_ENVI_COMP_STATUS_HIGH_SUCCESS:
			return print_message(BUG_MSG ,"ExperimentHandlers", "ExpEnviEvaluate", "time_out_success_for_input_comp", "comp_data->status == EXP_ENVI_COMP_STATUS_HIGH_SUCCESS");
		case EXP_ENVI_COMP_STATUS_READY_FOR_SWITCHING:
			break;
		default:
			get_exp_envi_comp_status_type_string(comp_data->status, str);   
			return print_message(BUG_MSG ,"ExperimentHandlers", "ExpEnviEvaluate", "time_out_success_for_input_comp", str);	
	}
	if ((comp_data->low_2_high_switch_success == comp_data->constraints.num_of_low_2_high_switch ) && (comp_data->high_2_low_switch_success == comp_data->constraints.num_of_high_2_low_switch ))
	{
		*has_response = TRUE;
		comp_data->low_2_high_switch_success = 0;
		comp_data->high_2_low_switch_success = 0;
		switch (comp_data->status)
		{
			case EXP_ENVI_COMP_STATUS_LOW:			
				return print_message(BUG_MSG ,"ExperimentHandlers", "ExpEnviEvaluate", "time_out_success_for_input_comp", "comp_data->status == EXP_ENVI_COMP_STATUS_LOW");			
			case EXP_ENVI_COMP_STATUS_LOW_SUCCESS:
				comp_data->status = EXP_ENVI_COMP_STATUS_LOW;
				break;
			case EXP_ENVI_COMP_STATUS_HIGH:
				return print_message(BUG_MSG ,"ExperimentHandlers", "ExpEnviEvaluate", "time_out_success_for_input_comp", "comp_data->status == EXP_ENVI_COMP_STATUS_HIGH");			
				break;			
			case EXP_ENVI_COMP_STATUS_HIGH_SUCCESS:
				comp_data->status = EXP_ENVI_COMP_STATUS_HIGH;
			case EXP_ENVI_COMP_STATUS_READY_FOR_SWITCHING:
				break;
			default:
				get_exp_envi_comp_status_type_string(comp_data->status, str);   
				return print_message(BUG_MSG ,"ExperimentHandlers", "ExpEnviEvaluate", "time_out_success_for_input_comp", str);	
		}
	}
	return TRUE;
}

bool exp_envi_input_low_2_high_event(ExpEnviInputCompTypeData *comp_data, bool *cancellation_reqiured_for_low_status_timer, bool *setting_required_for_high_status_timer)
{
	char str[EXP_ENVI_COMP_STATUS_MAX_STRING_LENGTH];
	*cancellation_reqiured_for_low_status_timer = FALSE;
	*setting_required_for_high_status_timer = FALSE;
	switch (comp_data->status)
	{
		case EXP_ENVI_COMP_STATUS_LOW:	///  could not become successfull to keep it at low long enough
			if (comp_data->enabled)
			{
				comp_data->status = EXP_ENVI_COMP_STATUS_READY_FOR_SWITCHING;	
				comp_data->low_2_high_switch_success = 0;
				comp_data->high_2_low_switch_success = 0;	
				*cancellation_reqiured_for_low_status_timer  = TRUE;
			}
			else
			{
				comp_data->status = EXP_ENVI_COMP_STATUS_READY_FOR_SWITCHING;	// burada status LOW iken low_2_high event gelmiş, dolayısıyla burada switching oluşmuş. input component, disable iken switching yapıyorsa READY_FOR_SWITCHING yap (başa al). ama  STATUS_READY_FOR_SWITCHING iken switching yapıyorsa bunu kabul et (aşağıda "case EXP_ENVI_COMP_STATUS_READY_FOR_SWITCHING:" de handle ediliyor.). 
/// böylece enable_with_NO_status_reset ile enable ederken kaldığı yerden devam edebilir. (mesela robot target yaklaşmakta iken lever disable olur ama lever pressi alır. robot target varınca lever enable olur ve timer  başlar. robot target a ulaştıktan sonra yeterli süre lever basılı kalmışsa ödül gelir .)
				*cancellation_reqiured_for_low_status_timer = TRUE;
			}
			break;			
		case EXP_ENVI_COMP_STATUS_LOW_SUCCESS:	
			if (comp_data->enabled)
			{
				comp_data->status = EXP_ENVI_COMP_STATUS_HIGH;
				*setting_required_for_high_status_timer = TRUE;
			}
			else
			{
				comp_data->status = EXP_ENVI_COMP_STATUS_HIGH;
				*setting_required_for_high_status_timer = FALSE;
			}
			break;	
		case EXP_ENVI_COMP_STATUS_HIGH:
			return print_message(BUG_MSG ,"ExperimentHandlers", "ExpEnviEvaluate", "exp_envi_input_low_2_high_event", "comp_data->status == EXP_ENVI_COMP_STATUS_HIGH");	
		case EXP_ENVI_COMP_STATUS_HIGH_SUCCESS:
			return print_message(BUG_MSG ,"ExperimentHandlers", "ExpEnviEvaluate", "exp_envi_input_low_2_high_event", "comp_data->status == EXP_ENVI_COMP_STATUS_HIGH_SUCCESS");
		case EXP_ENVI_COMP_STATUS_READY_FOR_SWITCHING:
			if (comp_data->constraints.required_status_to_initiate_switching == EXP_ENVI_COMP_STATUS_LOW)
			{
				comp_data->status = EXP_ENVI_COMP_STATUS_HIGH;
				if (comp_data->enabled)
					*setting_required_for_high_status_timer = TRUE;
				else
					*setting_required_for_high_status_timer = FALSE;
			}
			break;	
		default:
			get_exp_envi_comp_status_type_string(comp_data->status, str);   
			return print_message(BUG_MSG ,"ExperimentHandlers", "ExpEnviEvaluate", "exp_envi_input_low_2_high_event", str);	
	}
	return TRUE;
}

bool exp_envi_input_high_2_low_event(ExpEnviInputCompTypeData *comp_data, bool *cancellation_reqiured_for_high_status_timer, bool *setting_required_for_low_status_timer)
{
	char str[EXP_ENVI_COMP_STATUS_MAX_STRING_LENGTH];
	*cancellation_reqiured_for_high_status_timer = FALSE;
	*setting_required_for_low_status_timer = FALSE;
	switch (comp_data->status)
	{
		case EXP_ENVI_COMP_STATUS_LOW:	
			return print_message(BUG_MSG ,"ExperimentHandlers", "ExpEnviEvaluate", "exp_envi_input_high_2_low_event", "comp_data->status == EXP_ENVI_COMP_STATUS_LOW");	
		case EXP_ENVI_COMP_STATUS_LOW_SUCCESS:	
			return print_message(BUG_MSG ,"ExperimentHandlers", "ExpEnviEvaluate", "exp_envi_input_high_2_low_event", "comp_data->status == EXP_ENVI_COMP_STATUS_LOW_SUCCESS");	
		case EXP_ENVI_COMP_STATUS_HIGH:    ///  could not become successfull to keep it at high long enough
			if (comp_data->enabled)
			{
				comp_data->status = EXP_ENVI_COMP_STATUS_READY_FOR_SWITCHING;	
				comp_data->low_2_high_switch_success = 0;
				comp_data->high_2_low_switch_success = 0;	
				*cancellation_reqiured_for_high_status_timer  = TRUE;
			}
			else
			{
				comp_data->status = EXP_ENVI_COMP_STATUS_READY_FOR_SWITCHING;	// burada status HIGH iken high_2_low event gelmiş, dolayısıyla burada switching oluşmuş. input component, disable iken switching yapıyorsa READY_FOR_SWITCHING yap (başa al). ama  STATUS_READY_FOR_SWITCHING iken switching yapıyorsa bunu kabul et (aşağıda "case EXP_ENVI_COMP_STATUS_READY_FOR_SWITCHING:" de handle ediliyor.). 
/// böylece enable_with_NO_status_reset ile enable ederken kaldığı yerden devam edebilir. (mesela robot target yaklaşmakta iken lever disable olur ama lever pressi kabul eder. robot target varınca lever enable olur ve timer  başlar. robot target a ulaştıktan sonra yeterli süre lever basılı kalmışsa ödül gelir .)
				*cancellation_reqiured_for_high_status_timer = TRUE;
			}
			break;		
		case EXP_ENVI_COMP_STATUS_HIGH_SUCCESS:	
			if (comp_data->enabled)
			{
				comp_data->status = EXP_ENVI_COMP_STATUS_LOW;
				*setting_required_for_low_status_timer = TRUE;
			}
			else
			{
				comp_data->status = EXP_ENVI_COMP_STATUS_LOW;
				*setting_required_for_low_status_timer = FALSE;
			}
			break;	
		case EXP_ENVI_COMP_STATUS_READY_FOR_SWITCHING:
			if (comp_data->constraints.required_status_to_initiate_switching == EXP_ENVI_COMP_STATUS_HIGH)
			{
				comp_data->status = EXP_ENVI_COMP_STATUS_LOW;
				if (comp_data->enabled)
					*setting_required_for_low_status_timer = TRUE;
				else
					*setting_required_for_low_status_timer = FALSE;
			}
			break;	
		default:
			get_exp_envi_comp_status_type_string(comp_data->status, str);   
			return print_message(BUG_MSG ,"ExperimentHandlers", "ExpEnviEvaluate", "exp_envi_input_high_2_low_event", str);	
	}
	return TRUE;
}

bool enable_exp_envi_input_with_status_reset(ExpEnviInputCompTypeData *comp_data, bool *cancellation_required_for_status_timer)   // eğer enable edildiğinde sil baştan low/high veya high/low sıralaması gerekiyorsa. 
{
	if (comp_data->enabled)
		return print_message(BUG_MSG ,"ExperimentHandlers", "ExpEnviEvaluate", "enable_exp_envi_input_with_status_reset", "Component is already enabled.");
	comp_data->enabled = TRUE;
	comp_data->low_2_high_switch_success = 0;
	comp_data->high_2_low_switch_success = 0;	
	comp_data->status = EXP_ENVI_COMP_STATUS_READY_FOR_SWITCHING;
	*cancellation_required_for_status_timer = TRUE;   // it is a reminder for the programmer to cancel the previously set timer.

	return TRUE;
}

bool enable_exp_envi_input_with_no_status_reset(ExpEnviInputCompTypeData *comp_data, bool *timer_restart_reqiured_for_low_status, bool *timer_restart_reqiured_for_high_status)  // eğer enable edildiğinde, disable iken EXP_ENVI_COMP_STATUS_READY_FOR_SWITCHING' den  comp_data->constraints.required_status_to_initiate_switching' e uygun olarak swtiching yapmışsa bu fonksiyon çağrılarak kalınan yerden devam edilebilir. 
//(mesela robot target yaklaşmakta iken lever disable olur ama lever pressi kabul eder. robot target'a varınca lever enable olur ve timer başlar. robot target a ulaştıktan sonra yeterli süre lever basılı kalmışsa ödül gelir .)
{
	char str[EXP_ENVI_COMP_STATUS_MAX_STRING_LENGTH];
	if (comp_data->enabled)
		return print_message(BUG_MSG ,"ExperimentHandlers", "ExpEnviEvaluate", "enable_exp_envi_input_with_status_saving", "Component is already enabled.");
	comp_data->enabled = TRUE;
	*timer_restart_reqiured_for_low_status = FALSE;
	*timer_restart_reqiured_for_high_status = FALSE;
	comp_data->low_2_high_switch_success = 0;
	comp_data->high_2_low_switch_success = 0;
	switch (comp_data->status)
	{
		case EXP_ENVI_COMP_STATUS_LOW:	
			*timer_restart_reqiured_for_low_status = TRUE;
			break;			
		case EXP_ENVI_COMP_STATUS_LOW_SUCCESS:	
			comp_data->status = EXP_ENVI_COMP_STATUS_LOW;
			*timer_restart_reqiured_for_low_status = TRUE;
			break;	
		case EXP_ENVI_COMP_STATUS_HIGH:
			*timer_restart_reqiured_for_high_status = TRUE;
			break;
		case EXP_ENVI_COMP_STATUS_HIGH_SUCCESS:
			comp_data->status = EXP_ENVI_COMP_STATUS_HIGH;
			*timer_restart_reqiured_for_high_status = TRUE;
			break;
		case EXP_ENVI_COMP_STATUS_READY_FOR_SWITCHING:
			break;	
		default:
			get_exp_envi_comp_status_type_string(comp_data->status, str);   
			return print_message(BUG_MSG ,"ExperimentHandlers", "ExpEnviEvaluate", "exp_envi_input_low_2_high_event", str);	
	}
	return TRUE;
}

bool disable_exp_envi_input_with_status_reset(ExpEnviInputCompTypeData *comp_data,  bool *cancellation_required_for_status_timer)   // status saving li disable yok.     sadece enable ederken status u reset leyen veya resetlemeyen var. yani status disable edilmeden önceki status korunamaz. fakat disable iken "comp_data->constraints.required_status_to_initiate_switching" e uygun event gelirse bu handle edilir ve saklanır. 
// enable_exp_envi_input_with_no_status_reset()  bu status'u dikkate alır;
// enable_exp_envi_input_with_status_reset()  bu status'u clear eder(status'u = EXP_ENVI_COMP_STATUS_READY_FOR_SWITCHING yapar);
// eğer disable etmeden önceki status bilgisine ihtiyacın varsa bu input component e hiç disable etme. ama exp_envi_status' ta bir status belirle, o status' a göre bunun outputunu handle et.
{
	if (! comp_data->enabled)
		return print_message(BUG_MSG ,"ExperimentHandlers", "ExpEnviEvaluate", "enable_exp_envi_input_with_status_reset", "Component is already disabled.");
	comp_data->enabled = 0;
	comp_data->low_2_high_switch_success = 0;
	comp_data->high_2_low_switch_success = 0;	
	comp_data->status = EXP_ENVI_COMP_STATUS_READY_FOR_SWITCHING;
	*cancellation_required_for_status_timer = TRUE;   // it is a reminder for the programmer to cancel the previously set timer.
	return TRUE;
}


bool reset_exp_envi_input_with_status_reset(ExpEnviInputCompTypeData *comp_data, bool *timer_cancellation_required)
{
	comp_data->low_2_high_switch_success = 0;
	comp_data->high_2_low_switch_success = 0;	
	comp_data->status = EXP_ENVI_COMP_STATUS_READY_FOR_SWITCHING;
	*timer_cancellation_required = TRUE;   // it is a reminder for the programmer to cancel the previously set timer.
	return TRUE;
}

bool reset_exp_envi_input_with_status_saving(ExpEnviInputCompTypeData *comp_data, bool *timer_cancellation_required)
{
	char str[EXP_ENVI_COMP_STATUS_MAX_STRING_LENGTH];
	comp_data->low_2_high_switch_success = 0;
	comp_data->high_2_low_switch_success = 0;	
	*timer_cancellation_required = TRUE;   // it is a reminder for the programmer to cancel the previously set timer.
	switch (comp_data->status)
	{
		case EXP_ENVI_COMP_STATUS_LOW:	
			break;			
		case EXP_ENVI_COMP_STATUS_LOW_SUCCESS:	
			comp_data->status = EXP_ENVI_COMP_STATUS_LOW;
			break;	
		case EXP_ENVI_COMP_STATUS_HIGH:
			break;
		case EXP_ENVI_COMP_STATUS_HIGH_SUCCESS:
			comp_data->status = EXP_ENVI_COMP_STATUS_HIGH;
			break;
		case EXP_ENVI_COMP_STATUS_READY_FOR_SWITCHING:
			break;	
		default:
			get_exp_envi_comp_status_type_string(comp_data->status, str);   
			return print_message(BUG_MSG ,"ExperimentHandlers", "ExpEnviEvaluate", "exp_envi_input_low_2_high_event", str);	
	}
	return TRUE;
}
