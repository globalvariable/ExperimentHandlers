#include "TrialTypesCombo.h"


TrialTypesCombo* allocate_trial_types_combo(void)
{
	TrialTypesCombo* combo;

	combo = g_new0(TrialTypesCombo, 1);
	combo->combo = gtk_combo_box_new_text();
	return combo;
}
bool update_trial_types_combo(TrialTypesData *trial_types_data, TrialTypesCombo *combo)
{
	unsigned int i;
	char temp[TRIAL_TYPE_MAX_STRING_LENGTH];

	if (combo == NULL)
		return print_message(ERROR_MSG ,"ExperimentHandlers", "TrialTypesCombo", "update_trial_types_combo", "combo == NULL.");		
	for (i = combo->num_of_texts; i >0 ; i--)
		gtk_combo_box_remove_text (GTK_COMBO_BOX(combo->combo), i-1);
	for (i=0; i < trial_types_data->num_of_trial_types; i++)
	{
		if (!get_trial_type_string(trial_types_data->types[i].type, temp))
			return print_message(ERROR_MSG ,"TrialControllers", "TrialTypesCombo", "update_trial_types_combo", "! get_trial_type_string.");
	 	gtk_combo_box_append_text(GTK_COMBO_BOX(combo->combo), &temp[11]);    // ignore uncessary string part
	} 
	combo->num_of_texts = trial_types_data->num_of_trial_types;
	gtk_combo_box_set_active (GTK_COMBO_BOX(combo->combo), 0);
	return TRUE;	
}



