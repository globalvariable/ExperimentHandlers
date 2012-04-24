#ifndef TRIAL_TYPES_COMBO_H
#define TRIAL_TYPES_COMBO_H


typedef struct __TrialTypesCombo TrialTypesCombo;

#include <stdbool.h>
#include <gtk/gtk.h>
#include "../../../../BlueSpike/Library/Misc/Misc.h"
#include "../TrialsData/TrialsData.h"


struct __TrialTypesCombo
{
	GtkWidget *combo;
	unsigned int num_of_texts;
};

TrialTypesCombo* allocate_trial_types_combo(void);
bool update_trial_types_combo(TrialsData *trials_data, TrialTypesCombo *combo);

#endif
