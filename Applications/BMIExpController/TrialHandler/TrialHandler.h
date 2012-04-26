#ifndef TRIAL_HANDLER_H
#define TRIAL_HANDLER_H

#include <rtai_shm.h>
#include <rtai_nam2num.h>
#include "../../../../BlueSpike/Library/Misc/Misc.h"
#include "Gui.h"
#include "TrialHandlerRtTask.h"

TrialTypesData *get_trial_types_data(void);   // only trial handler gui can use this
bool initialize_trial_handler(void);





#endif
