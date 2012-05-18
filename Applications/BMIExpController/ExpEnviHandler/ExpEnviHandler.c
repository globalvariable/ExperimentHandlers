#include "ExpEnviHandler.h"



int main( int argc, char *argv[])
{
	Gui2ExpEnviHandMsg *msgs_gui_2_exp_envi_hand = NULL;    
	ExpEnviData *exp_envi_data = NULL;

  	shared_memory = (SharedMemStruct*)rtai_malloc(nam2num(SHARED_MEM_NAME), SHARED_MEM_SIZE);
	if (shared_memory == NULL) 
		return print_message(ERROR_MSG ,"BMIExpController", "ExpEnviHandler", "main", "shared_memory == NULL.");
	exp_envi_data = allocate_exp_envi_data(exp_envi_data);
	if (! add_input_component_type_to_exp_envi_data(exp_envi_data, EXP_ENVI_INPUT_COMPONENT_IR_BEAM_NOSE_POKE, 0, 1000000000, 0, 1000000000, 2, 1, EXP_ENVI_COMP_STATUS_LOW)) /// 2 nose poke
		return print_message(ERROR_MSG ,"BMIExpController", "ExpEnviHandler", "main", "! add_input_component_type_to_exp_envi_data().");
	if (! add_input_component_type_to_exp_envi_data(exp_envi_data, EXP_ENVI_INPUT_COMPONENT_LEFT_LEVER, 100000000, 1000000000, 0, 0, 1, 0, EXP_ENVI_COMP_STATUS_LOW))  /// 100 ms lever press
		return print_message(ERROR_MSG ,"BMIExpController", "ExpEnviHandler", "main", "! add_input_component_type_to_exp_envi_data().");
	if (! add_input_component_type_to_exp_envi_data(exp_envi_data, EXP_ENVI_INPUT_COMPONENT_RIGHT_LEVER, 100000000, 1000000000, 0, 0, 1, 0, EXP_ENVI_COMP_STATUS_LOW))  /// 100 ms lever press
		return print_message(ERROR_MSG ,"BMIExpController", "ExpEnviHandler", "main", "! add_input_component_type_to_exp_envi_data().");

	msgs_gui_2_exp_envi_hand = allocate_gui_2_exp_envi_hand_msg_buffer(msgs_gui_2_exp_envi_hand);

	if(! create_exp_envi_handler_rt_thread(exp_envi_data, msgs_gui_2_exp_envi_hand))
		return print_message(ERROR_MSG ,"BMIExpController", "ExpEnviHandler", "main", "create_exp_envi_handler_rt_thread().");
	gtk_init(&argc, &argv);
	create_gui_handler(msgs_gui_2_exp_envi_hand);
	gtk_main();
	return 0;
}	
