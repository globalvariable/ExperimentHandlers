#ifndef GUI_H
#define GUI_H


#include <gtk/gtk.h>
#include <stdbool.h>
#include <stdlib.h>
#include "GuiExpEnviHandler.h"
#include "../../../Library/Messages/Gui2ExpEnviHand.h"

// Functions
void create_gui_handler(RtTasksData *rt_tasks_data, Gui2ExpEnviHandMsg *msgs_gui_2_exp_envi_hand);



#endif
