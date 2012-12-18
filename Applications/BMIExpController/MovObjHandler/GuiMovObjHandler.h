#ifndef GUI_MOV_OBJ_HANDLER_H
#define GUI_MOV_OBJ_HANDLER_H


#include <stdlib.h>
#include "../../../Library/Messages/Gui2MovObjHand.h"
#include "../../../Library/Messages/MovObjHand2Gui.h"
#include "../../../Library/Graphs/LocationGraph.h"
#include "../../../../BlueSpike/Library/Misc/Misc.h"
#include "../../../../BlueSpike/System/RtTasksData/RtTasksData.h"
#include "../../../Library/Robot/ThreeDofRobot.h"
#include "../../../Library/ExpParadigm/ParadigmRobotReach/MovObjHandParadigm.h"
#include "../../../../BlueSpike/Library/Thresholding/Thresholding.h"


bool create_mov_obj_handler_tab(GtkWidget *tabs, RtTasksData *rt_tasks_data, Gui2MovObjHandMsg *msgs_gui_2_mov_obj_hand, MovObjHand2GuiMsg *msgs_mov_obj_hand_2_gui, ThreeDofRobot *robot_arm, MovObjHandParadigmRobotReach *mov_obj_paradigm);


#endif
