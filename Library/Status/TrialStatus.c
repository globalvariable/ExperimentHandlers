#include "TrialStatus.h"


bool get_trial_status_type_string(TrialStatus trial_status_type, char *str)   // pass NULL if you only want checking (to be faster) 
{
	switch (trial_status_type)
	{
		case TRIAL_STATUS_TRIALS_DISABLED:
			if (str != NULL)
				strcpy(str, "TRIAL_STATUS_TRIALS_DISABLED");
			return TRUE;		
		case TRIAL_STATUS_IN_TRIAL:
			if (str != NULL)
				strcpy(str, "TRIAL_STATUS_IN_TRIAL");
			return TRUE;
		case TRIAL_STATUS_IN_REFRACTORY:
			if (str != NULL)
				strcpy(str, "TRIAL_STATUS_IN_REFRACTORY");	
			return TRUE;
		case TRIAL_STATUS_START_TRIAL_AVAILABLE:
			if (str != NULL)
				strcpy(str, "TRIAL_STATUS_START_TRIAL_AVAILABLE");
			return TRUE;
/////////////////////////		
		case TRIAL_STATUS_NULL:
			if (str != NULL)
				strcpy(str, "TRIAL_STATUS_NULL");
			return FALSE;
		default:
			if (str != NULL)
				strcpy(str, "TRIAL_STATUS_TYPE_INVALID");
			return FALSE;
	}
}

TrialStatusEvents* allocate_trial_status_events_buffer(TrialStatusEvents* trial_status_events, unsigned int buffer_size, TimeStamp status_change_latency)
{
	if (trial_status_events != NULL)
	{
		trial_status_events = deallocate_trial_status_events_buffer(trial_status_events);
		trial_status_events = allocate_trial_status_events_buffer(trial_status_events, buffer_size, status_change_latency);
		return trial_status_events;
	}  
	trial_status_events = g_new0(TrialStatusEvents,1);
	trial_status_events->buff = g_new0(TrialStatusEventItem, buffer_size);
	trial_status_events->buffer_size = buffer_size;
	trial_status_events->status_change_latency	= status_change_latency;
	print_message(INFO_MSG ,"ExperimentHandlers", "TrialStatus", "allocate_trial_status_events", "Created trial_status_events.");
	return trial_status_events;
}
TrialStatusEvents* deallocate_trial_status_events_buffer(TrialStatusEvents* trial_status_events)
{
	if (trial_status_events == NULL)
		return (TrialStatusEvents*)print_message(BUG_MSG ,"ExperimentHandlers", "TrialStatus", "deallocate_trial_status_events", "trial_status_events == NULL.");    
	g_free(trial_status_events->buff);
	g_free(trial_status_events);
	print_message(INFO_MSG ,"ExperimentHandlers", "TrialStatus", "allocate_trial_status_events", "Destroyed trial_status_events.");
	return NULL;
}
void write_to_trial_status_events_buffer(TrialStatusEvents* trial_status_events, TimeStamp trial_status_start_time, TrialStatus trial_status, TrialType trial_type)   // it can have multiple readers. so no read_idx defined.
{
	unsigned int *idx;
	idx = &(trial_status_events->buff_write_idx);
	TrialStatusEventItem *buff = trial_status_events->buff;
	buff[*idx].trial_status_start_time = trial_status_start_time + trial_status_events->status_change_latency;
	buff[*idx].trial_status = trial_status;
	buff[*idx].trial_type = trial_type;
	if ((*idx + 1) == trial_status_events->buffer_size)
		*idx = 0;
	else
		(*idx)++;
	return ;	
}
bool get_next_trial_status_events_buffer_item(TrialStatusEvents* trial_status_events, unsigned int *read_idx, TrialStatusEventItem **event_item)
{
	if (*read_idx == trial_status_events->buff_write_idx)
		return FALSE;
	*event_item = &(trial_status_events->buff[*read_idx]);	
	if ((*read_idx + 1) == trial_status_events->buffer_size)
		*read_idx = 0;
	else
		(*read_idx)++;
	return TRUE;
}

