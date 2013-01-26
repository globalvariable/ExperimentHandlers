#include "MovObjStatusHistory.h"

MovObjStatusHistory* allocate_mov_obj_status_history(MovObjStatusHistory* hist, unsigned int buffer_size)
{
	if (hist != NULL)
	{
		hist = deallocate_mov_obj_status_history(hist);
		hist = allocate_mov_obj_status_history(hist, buffer_size);
		return hist;
	}  
	hist = g_new0(MovObjStatusHistory,1);
	hist->history = g_new0(MovObjStatusHistoryItem, buffer_size);
	hist->buffer_size = buffer_size;	
	print_message(INFO_MSG ,"ExperimentHandler", "MovObjStatusHistory", "allocate_mov_obj_status_history", "Created MovObjStatusHistory.");
	return hist;
}
MovObjStatusHistory* deallocate_mov_obj_status_history(MovObjStatusHistory* hist)
{
	if (hist == NULL)
		return (MovObjStatusHistory*)print_message(BUG_MSG ,"ExperimentHandler", "MovObjStatusHistory", "deallocate_mov_obj_status_history", "MovObjStatusHistory == NULL.");    
	g_free(hist->history);
	g_free(hist);
	print_message(INFO_MSG ,"ExperimentHandler", "MovObjStatusHistory", "deallocate_mov_obj_status_history", "Destroyed MovObjStatusHistory.");
	return NULL;
}

bool write_to_mov_obj_status_history(MovObjStatusHistory* hist, TimeStamp time, MovObjStatus new_status)
{
	unsigned int *idx = &(hist->buff_write_idx);
	MovObjStatusHistoryItem *item = &(hist->history[hist->buff_write_idx]);
	item->time = time;
	item->new_status = new_status;
	if ((*idx + 1) == hist->buffer_size)
		*idx = 0;
	else
		(*idx)++;
	if ((*idx) == hist->buff_read_idx)
		return print_message(BUG_MSG ,"ExperimentHandlers", "MovObjStatusHistory", "write_to_mov_obj_status_history", "BUFFER IS FULL!!!.");    		
	return TRUE;
}

bool get_next_mov_obj_status_history_item(MovObjStatusHistory* hist, MovObjStatusHistoryItem *item)
{
	unsigned int *idx;
	if (hist->buff_read_idx == hist->buff_write_idx)
		return FALSE;
	idx = &(hist->buff_read_idx);
	memcpy(item, &(hist->history[*idx]), sizeof(MovObjStatusHistoryItem));
	if (((*idx) + 1) == hist->buffer_size)
		*idx = 0;
	else
		(*idx)++;	
	return TRUE;	
}
