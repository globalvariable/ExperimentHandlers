#include "MovObjHandler.h"



int main( int argc, char *argv[])
{
	RtTasksData *rt_tasks_data = NULL;
	Gui2MovObjHandMsg *msgs_gui_2_mov_obj_hand = NULL;    
	MovObjData *mov_obj_data = NULL;

   	rt_tasks_data = rtai_malloc(nam2num(RT_TASKS_DATA_SHM_NAME), 0);
	if (rt_tasks_data == NULL) 
		return print_message(ERROR_MSG ,"MovObjHandler", "MovObjHandler", "main", "rt_tasks_data == NULL.");

	mov_obj_data = allocate_mov_obj_data(mov_obj_data);
	if (!add_component_type_to_mov_obj_data(mov_obj_data, MOV_OBJ_COMPONENT_1D_ACTUATOR, 100000000, 500000000, 40, 5))  // 40 mm initial threshold
		return print_message(ERROR_MSG ,"MovObjHandler", "MovObjHandler", "main", "! add_component_type_to_mov_obj_data().");
	if (!set_global_constraints_mov_obj_data(mov_obj_data, 100000000, 500000000, 40, 5, 80.0))  // 40 mm initial threshold
		return print_message(ERROR_MSG ,"MovObjHandler", "MovObjHandler", "main", "! set_global_constraints_mov_obj_data().");
	msgs_gui_2_mov_obj_hand = allocate_gui_2_mov_obj_hand_msg_buffer(msgs_gui_2_mov_obj_hand);

	if(! create_mov_obj_handler_rt_thread(rt_tasks_data, mov_obj_data, msgs_gui_2_mov_obj_hand))
		return print_message(ERROR_MSG ,"MovObjHandler", "MovObjHandler", "main", "create_mov_obj_handler_rt_thread().");
	gtk_init(&argc, &argv);
	create_gui_handler(rt_tasks_data, msgs_gui_2_mov_obj_hand);
	gtk_main();
	return 0;
}	
