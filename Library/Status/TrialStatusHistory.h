#ifndef TRIAL_STATUS_HISTORY_H
#define TRIAL_STATUS_HISTORY_H


typedef struct __TrialStatusHistoryItem TrialStatusHistoryItem;
typedef struct __TrialStatusHistory TrialStatusHistory;

#include "TrialStatus.h"
#include "../../../BlueSpike/System/TimeStamp/TimeStamp.h"
#include "../../../BlueSpike/Library/Misc/Misc.h"

struct __TrialStatusHistoryItem
{
	TimeStamp			time;
	TrialStatus			new_status;
};

struct __TrialStatusHistory
{
	TrialStatusHistoryItem 	*history;
	unsigned int 			buff_write_idx;  
	unsigned int 			buff_read_idx;  
	unsigned int 			buffer_size;
};

TrialStatusHistory* allocate_trial_status_history(TrialStatusHistory* hist, unsigned int buffer_size); 
TrialStatusHistory* deallocate_trial_status_history(TrialStatusHistory* hist); 
bool write_to_trial_status_history(TrialStatusHistory* hist, TimeStamp time, TrialStatus new_status);
bool get_next_trial_status_history_item(TrialStatusHistory* hist, TrialStatusHistoryItem *item);	



#endif
