#include "ExpEnviHandler.h"



int main( int argc, char *argv[])
{
	RtTasksData *rt_tasks_data = NULL;
	Gui2ExpEnviHandMsg *msgs_gui_2_exp_envi_hand = NULL;    
	ExpEnviData *exp_envi_data = NULL;

   	rt_tasks_data = rtai_malloc(SHM_NUM_RT_TASKS_DATA, 0);
	if (rt_tasks_data == NULL) 
		return print_message(ERROR_MSG ,"ExpEnviHandler", "ExpEnviHandler", "main", "rt_tasks_data == NULL.");
	exp_envi_data = allocate_exp_envi_data(exp_envi_data);


//     Order of addition of components is important. Add them according to ConfigExpEnviComponentNums.h
	if (! add_input_component_type_to_exp_envi_data(exp_envi_data, EXP_ENVI_INPUT_COMPONENT_IR_BEAM_NOSE_POKE, 0, 1000000000, 0, 1000000000, 2, 1, EXP_ENVI_COMP_STATUS_LOW)) /// 2 nose poke
		return print_message(ERROR_MSG ,"ExpEnviHandler", "ExpEnviHandler", "main", "! add_input_component_type_to_exp_envi_data().");
//     Order of addition of components is important. Add them according to ConfigExpEnviComponentNums.h
	if (! add_input_component_type_to_exp_envi_data(exp_envi_data, EXP_ENVI_INPUT_COMPONENT_LEFT_LEVER, 100000000, 1000000000, 100000000, 1000000000, 1, 0, EXP_ENVI_COMP_STATUS_LOW))  /// 100 ms lever press
		return print_message(ERROR_MSG ,"ExpEnviHandler", "ExpEnviHandler", "main", "! add_input_component_type_to_exp_envi_data().");
//     Order of addition of components is important. Add them according to ConfigExpEnviComponentNums.h
	if (! add_input_component_type_to_exp_envi_data(exp_envi_data, EXP_ENVI_INPUT_COMPONENT_RIGHT_LEVER, 100000000, 1000000000, 100000000, 1000000000, 1, 0, EXP_ENVI_COMP_STATUS_LOW))  /// 100 ms lever press
		return print_message(ERROR_MSG ,"ExpEnviHandler", "ExpEnviHandler", "main", "! add_input_component_type_to_exp_envi_data().");
//     Order of addition of components is important. Add them according to ConfigExpEnviComponentNums.h
	if (! add_output_component_type_to_exp_envi_data(exp_envi_data, EXP_ENVI_OUTPUT_COMPONENT_VALVE_CENTER, 1000000000))
		return print_message(ERROR_MSG ,"ExpEnviHandler", "ExpEnviHandler", "main", "! add_output_component_type_to_exp_envi_data().");
//     Order of addition of components is important. Add them according to ConfigExpEnviComponentNums.h
	if (! add_output_component_type_to_exp_envi_data(exp_envi_data, EXP_ENVI_OUTPUT_COMPONENT_BUZZER, 1000000000))
		return print_message(ERROR_MSG ,"ExpEnviHandler", "ExpEnviHandler", "main", "! add_output_component_type_to_exp_envi_data().");
//     Order of addition of components is important. Add them according to ConfigExpEnviComponentNums.h
	if (! add_output_component_type_to_exp_envi_data(exp_envi_data, EXP_ENVI_OUTPUT_COMPONENT_LEFT_TARGET_LED, 7000000000))
		return print_message(ERROR_MSG ,"ExpEnviHandler", "ExpEnviHandler", "main", "! add_output_component_type_to_exp_envi_data().");
//     Order of addition of components is important. Add them according to ConfigExpEnviComponentNums.h
	if (! add_output_component_type_to_exp_envi_data(exp_envi_data, EXP_ENVI_OUTPUT_COMPONENT_RIGHT_TARGET_LED, 7000000000))
		return print_message(ERROR_MSG ,"ExpEnviHandler", "ExpEnviHandler", "main", "! add_output_component_type_to_exp_envi_data().");
//     Order of addition of components is important. Add them according to ConfigExpEnviComponentNums.h
	if (! add_output_component_type_to_exp_envi_data(exp_envi_data, EXP_ENVI_OUTPUT_COMPONENT_GUIDE_LED, 7000000000))
		return print_message(ERROR_MSG ,"ExpEnviHandler", "ExpEnviHandler", "main", "! add_output_component_type_to_exp_envi_data().");
//     Order of addition of components is important. Add them according to ConfigExpEnviComponentNums.h
	if (! add_output_component_type_to_exp_envi_data(exp_envi_data, EXP_ENVI_OUTPUT_COMPONENT_LEVER_SOLENOID, 7000000000))
		return print_message(ERROR_MSG ,"ExpEnviHandler", "ExpEnviHandler", "main", "! add_output_component_type_to_exp_envi_data().");

	msgs_gui_2_exp_envi_hand = allocate_gui_2_exp_envi_hand_msg_buffer(msgs_gui_2_exp_envi_hand);

	if(! create_exp_envi_handler_rt_thread(rt_tasks_data, exp_envi_data, msgs_gui_2_exp_envi_hand))
		return print_message(ERROR_MSG ,"ExpEnviHandler", "ExpEnviHandler", "main", "create_exp_envi_handler_rt_thread().");
	gtk_init(&argc, &argv);
	create_gui_handler(rt_tasks_data, msgs_gui_2_exp_envi_hand);
	gtk_main();
	return 0;
}	
