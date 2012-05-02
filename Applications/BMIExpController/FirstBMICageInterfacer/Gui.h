#ifndef GUI_H
#define GUI_H


#include <gtk/gtk.h>
#include <stdbool.h>
#include <stdlib.h>
#include "GuiCageInterfacer.h"
#include "../../../Library/Messages/Gui2ExpEnviInterf.h"
#include "../../../Library/Messages/Gui2MovObjInterf.h"

// Functions
void create_gui_handler(Gui2ExpEnviInterfMsg *msgs_gui_2_exp_envi_interf, Gui2MovObjInterfMsg *msgs_gui_2_mov_obj_interf);



#endif
