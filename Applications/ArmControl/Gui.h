#ifndef GUI_H
#define GUI_H


#include <gtk/gtk.h>
#include <stdbool.h>
#include <stdlib.h>
#include "ArmControl.h"
#include "../../../BlueSpike/Library/Misc/Misc.h"
#include "../../Library/Robot/ThreeDofRobot.h"

// Functions
void create_gui(ThreeDofRobot *robot_arm);


#endif
