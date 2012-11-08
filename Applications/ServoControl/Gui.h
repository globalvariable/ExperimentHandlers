#ifndef GUI_H
#define GUI_H


#include <gtk/gtk.h>
#include <stdbool.h>
#include <stdlib.h>
#include "ServoControl.h"
#include "../../../BlueSpike/Library/Misc/Misc.h"
#include "../../Library/Servo/Servo.h"

// Functions
void create_gui(ServoData *servos);


#endif
