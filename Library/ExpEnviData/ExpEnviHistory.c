#include "ExpEnviHistory.h"


ExpEnviInputStatusHistory* allocate_exp_envi_input_status_history(ExpEnviInputStatusHistory* hist, unsigned int buffer_size)
{
	if (hist != NULL)
	{
		hist = deallocate_exp_envi_input_status_history(hist);
		hist = allocate_exp_envi_input_status_history(hist, buffer_size);
		return hist;
	}  
	hist = g_new0(ExpEnviInputStatusHistory,1);
	hist->history = g_new0(ExpEnviInputStatusHistoryItem, buffer_size);
	hist->buffer_size = buffer_size;	
	print_message(INFO_MSG ,"ExperimentHandler", "ExpEnviHistory", "allocate_exp_envi_input_status_history", "Created ExpEnviInputStatusHistory.");
	return hist;
}
ExpEnviInputStatusHistory* deallocate_exp_envi_input_status_history(ExpEnviInputStatusHistory* hist)
{
	if (hist == NULL)
		return (ExpEnviInputStatusHistory*)print_message(BUG_MSG ,"ExperimentHandler", "ExpEnviHistory", "deallocate_exp_envi_input_status_history", "ExpEnviInputStatusHistory == NULL.");    
	g_free(hist->history);
	g_free(hist);
	print_message(INFO_MSG ,"ExperimentHandler", "ExpEnviHistory", "deallocate_exp_envi_input_status_history", "Destroyed ExpEnviInputStatusHistory.");
	return NULL;
}

bool write_to_exp_envi_input_status_history(ExpEnviInputStatusHistory* hist, TimeStamp time, ExpEnviInputCompNum comp_num, ExpEnviCompStatus new_status)
{
	unsigned int *idx = &(hist->buff_write_idx);
	ExpEnviInputStatusHistoryItem *item = &(hist->history[hist->buff_write_idx]);
	item->time = time;
	item->comp_num = comp_num;
	item->new_status = new_status;
	if ((*idx + 1) == hist->buffer_size)
		*idx = 0;
	else
		(*idx)++;
	if ((*idx) == hist->buff_read_idx)
		return print_message(BUG_MSG ,"ExperimentHandlers", "ExpEnviHistory", "write_to_exp_envi_input_status_history", "BUFFER IS FULL!!!.");    		
	return TRUE;
}

bool get_next_exp_envi_input_status_history_item(ExpEnviInputStatusHistory* hist, ExpEnviInputStatusHistoryItem *item)
{
	unsigned int *idx;
	if (hist->buff_read_idx == hist->buff_write_idx)
		return FALSE;
	idx = &(hist->buff_read_idx);
	memcpy(item, &(hist->history[*idx]), sizeof(ExpEnviInputStatusHistoryItem));
	if ((*idx + 1) == hist->buffer_size)
		*idx = 0;
	else
		(*idx)++;	
	return TRUE;	
}

ExpEnviOutputStatusHistory* allocate_exp_envi_output_status_history(ExpEnviOutputStatusHistory* hist, unsigned int buffer_size)
{
	if (hist != NULL)
	{
		hist = deallocate_exp_envi_output_status_history(hist);
		hist = allocate_exp_envi_output_status_history(hist, buffer_size);
		return hist;
	}  
	hist = g_new0(ExpEnviOutputStatusHistory,1);
	hist->history = g_new0(ExpEnviOutputStatusHistoryItem, buffer_size);
	hist->buffer_size = buffer_size;	
	print_message(INFO_MSG ,"ExperimentHandler", "ExpEnviHistory", "allocate_exp_envi_output_status_history", "Created ExpEnviOutputStatusHistory.");
	return hist;
}
ExpEnviOutputStatusHistory* deallocate_exp_envi_output_status_history(ExpEnviOutputStatusHistory* hist)
{
	if (hist == NULL)
		return (ExpEnviOutputStatusHistory*)print_message(BUG_MSG ,"ExperimentHandler", "ExpEnviHistory", "deallocate_exp_envi_input_status_history", "ExpEnviOutputStatusHistory == NULL.");    
	g_free(hist->history);
	g_free(hist);
	print_message(INFO_MSG ,"ExperimentHandler", "ExpEnviHistory", "deallocate_exp_envi_input_status_history", "Destroyed ExpEnviOutputStatusHistory.");
	return NULL;
}
bool write_to_exp_envi_output_status_history(ExpEnviOutputStatusHistory* hist, TimeStamp time, ExpEnviOutputCompNum comp_num, ExpEnviCompStatus new_status)
{
	unsigned int *idx = &(hist->buff_write_idx);
	ExpEnviOutputStatusHistoryItem *item = &(hist->history[hist->buff_write_idx]);
	item->time = time;
	item->comp_num = comp_num;
	item->new_status = new_status;
	if ((*idx + 1) == hist->buffer_size)
		*idx = 0;
	else
		(*idx)++;
	if ((*idx) == hist->buff_read_idx)
		return print_message(BUG_MSG ,"ExperimentHandlers", "ExpEnviHistory", "write_to_exp_envi_output_status_history", "BUFFER IS FULL!!!.");    		
	return TRUE;
}
bool get_next_exp_envi_output_status_history_item(ExpEnviOutputStatusHistory* hist, ExpEnviOutputStatusHistoryItem *item)
{
	unsigned int *idx;
	if (hist->buff_read_idx == hist->buff_write_idx)
		return FALSE;
	idx = &(hist->buff_read_idx);
	memcpy(item, &(hist->history[*idx]), sizeof(ExpEnviOutputStatusHistoryItem));
	if ((*idx + 1) == hist->buffer_size)
		*idx = 0;
	else
		(*idx)++;	
	return TRUE;
}
