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
		case TRIAL_STATUS_GET_READY_TO_START:
			if (str != NULL)
				strcpy(str, "TRIAL_STATUS_GET_READY_TO_START");
			return TRUE;
		case TRIAL_STATUS_WAIT_FOR_LEVER_PRESS:
			if (str != NULL)
				strcpy(str, "TRIAL_STATUS_WAIT_FOR_LEVER_PRESS");
			return TRUE;
		case TRIAL_STATUS_WAIT_FOR_NOSE_RETRACT:
			if (str != NULL)
				strcpy(str, "TRIAL_STATUS_WAIT_FOR_NOSE_RETRACT");
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
{	// IT IS ESPECIALLY FOR GRAPHS TO INDICATE THE TRIAL STATUS CHANGE TIMES
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
void schedule_trial_status_event(TrialStatusEvents* trial_status_events, TimeStamp trial_status_start_time, TrialHand2NeuralNetTrialStatusMsgAdd trial_status_change_msg_add)   // it can have multiple readers. so no read_idx defined.
{
	unsigned int *idx;
	idx = &(trial_status_events->buff_write_idx);
	TrialStatusEventItem *buff = trial_status_events->buff;

	buff[*idx].status_start_time = trial_status_start_time + trial_status_events->status_change_latency;
	buff[*idx].trial_status = trial_status_change_msg_add.new_trial_status;
	buff[*idx].selected_robot_target_idx_in_trial_hand_paradigm = trial_status_change_msg_add.new_robot_target_position_idx;

	if ((*idx + 1) == trial_status_events->buffer_size)
		*idx = 0;
	else
		(*idx)++;
	return ;	
}
bool get_next_trial_status_events_buffer_item(TrialStatusEvents* trial_status_events, unsigned int *read_idx, TrialStatusEventItem *event_item)
{
	TrialStatusEventItem *buff_item;
	if (*read_idx == trial_status_events->buff_write_idx)
		return FALSE;
	buff_item = &(trial_status_events->buff[*read_idx]);	
	event_item->status_start_time = buff_item->status_start_time;   
	event_item->trial_status = buff_item->trial_status;   
	event_item->selected_robot_target_idx_in_trial_hand_paradigm = buff_item->selected_robot_target_idx_in_trial_hand_paradigm;
	if ((*read_idx + 1) == trial_status_events->buffer_size)
		*read_idx = 0;
	else
		(*read_idx)++;
	return TRUE;
}
TrialStatusEventItem get_last_trial_status_events_buffer_item(TrialStatusEvents* trial_status_events)
{
	if  (trial_status_events->buff_write_idx == 0)
		return trial_status_events->buff[trial_status_events->buffer_size-1];
	else
		return trial_status_events->buff[trial_status_events->buff_write_idx-1];
}
