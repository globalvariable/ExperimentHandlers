#include "TrialStatusHistory.h"

TrialStatusHistory* allocate_trial_status_history(TrialStatusHistory* hist, unsigned int buffer_size)
{
	if (hist != NULL)
	{
		hist = deallocate_trial_status_history(hist);
		hist = allocate_trial_status_history(hist, buffer_size);
		return hist;
	}  
	hist = g_new0(TrialStatusHistory,1);
	hist->history = g_new0(TrialStatusHistoryItem, buffer_size);
	hist->buffer_size = buffer_size;	
	print_message(INFO_MSG ,"ExperimentHandler", "TrialStatusHistory", "allocate_trial_status_history", "Created TrialStatusHistory.");
	return hist;
}
TrialStatusHistory* deallocate_trial_status_history(TrialStatusHistory* hist)
{
	if (hist == NULL)
		return (TrialStatusHistory*)print_message(BUG_MSG ,"ExperimentHandler", "TrialStatusHistory", "deallocate_trial_status_history", "TrialStatusHistory == NULL.");    
	g_free(hist->history);
	g_free(hist);
	print_message(INFO_MSG ,"ExperimentHandler", "TrialStatusHistory", "deallocate_trial_status_history", "Destroyed TrialStatusHistory.");
	return NULL;
}

bool write_to_trial_status_history(TrialStatusHistory* hist, TimeStamp time, TrialStatus new_status)
{
	unsigned int *idx = &(hist->buff_write_idx);
	TrialStatusHistoryItem *item = &(hist->history[hist->buff_write_idx]);
	item->time = time;
	item->new_status = new_status;
	if ((*idx + 1) == hist->buffer_size)
		*idx = 0;
	else
		(*idx)++;
	if ((*idx) == hist->buff_read_idx)
		return print_message(BUG_MSG ,"ExperimentHandlers", "TrialStatusHistory", "write_to_trial_status_history", "BUFFER IS FULL!!!.");    		
	return TRUE;
}

bool get_next_trial_status_history_item(TrialStatusHistory* hist, TrialStatusHistoryItem *item)
{
	unsigned int *idx;
	if (hist->buff_read_idx == hist->buff_write_idx)
		return FALSE;
	idx = &(hist->buff_read_idx);
	memcpy(item, &(hist->history[*idx]), sizeof(TrialStatusHistoryItem));
	if ((*idx + 1) == hist->buffer_size)
		*idx = 0;
	else
		(*idx)++;	
	return TRUE;	
}
