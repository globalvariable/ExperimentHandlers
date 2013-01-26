#ifndef MOV_OBJ_STATUS_HISTORY_H
#define MOV_OBJ_STATUS_HISTORY_H


typedef struct __MovObjStatusHistoryItem MovObjStatusHistoryItem;
typedef struct __MovObjStatusHistory MovObjStatusHistory;

#include "MovObjStatus.h"
#include "../../../BlueSpike/System/TimeStamp/TimeStamp.h"
#include "../../../BlueSpike/Library/Misc/Misc.h"

struct __MovObjStatusHistoryItem
{
	TimeStamp			time;
	MovObjStatus			new_status;
};

struct __MovObjStatusHistory
{
	MovObjStatusHistoryItem 	*history;
	unsigned int 			buff_write_idx;  
	unsigned int 			buff_read_idx;  
	unsigned int 			buffer_size;
};

MovObjStatusHistory* allocate_mov_obj_status_history(MovObjStatusHistory* hist, unsigned int buffer_size); 
MovObjStatusHistory* deallocate_mov_obj_status_history(MovObjStatusHistory* hist); 
bool write_to_mov_obj_status_history(MovObjStatusHistory* hist, TimeStamp time, MovObjStatus new_status);
bool get_next_mov_obj_status_history_item(MovObjStatusHistory* hist, MovObjStatusHistoryItem *item);	



#endif
