#ifndef GUI_CAGE_INTERFACER_H
#define GUI_CAGE_INTERFACER_H

#include "../../../Library/Messages/Gui2ExpEnviInterf.h"
#include "../../../Library/Messages/Gui2MovObjInterf.h"
#include "../../../../BlueSpike/Library/Misc/Misc.h"
#include "../../../../BlueSpike/SharedMemory.h"



bool create_cage_interfacer_tab(GtkWidget *tabs, Gui2ExpEnviInterfMsg *msgs_gui_2_exp_envi_interf, Gui2MovObjInterfMsg *msgs_gui_2_mov_obj_interf);


#endif
