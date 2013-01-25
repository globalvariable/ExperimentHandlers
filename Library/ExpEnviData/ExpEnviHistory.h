#ifndef EXP_ENVI_HISTORY_H
#define EXP_ENVI_HISTORY_H


typedef struct __ExpEnviInputStatusHistoryItem ExpEnviInputStatusHistoryItem;
typedef struct __ExpEnviOutputStatusHistoryItem ExpEnviOutputStatusHistoryItem;
typedef struct __ExpEnviInputStatusHistory ExpEnviInputStatusHistory;
typedef struct __ExpEnviOutputStatusHistory ExpEnviOutputStatusHistory;

#include "ExpEnviComponentTypes.h"
#include "../Status/ExpEnviComponentStatus.h"
#include "../../../BlueSpike/System/TimeStamp/TimeStamp.h"
#include "../../../BlueSpike/Library/Misc/Misc.h"

struct __ExpEnviInputStatusHistoryItem
{
	TimeStamp			time;
	ExpEnviInputCompNum	comp_num;
	ExpEnviCompStatus	new_status;
};

struct __ExpEnviOutputStatusHistoryItem
{
	TimeStamp				time;
	ExpEnviOutputCompNum	comp_num;
	ExpEnviCompStatus		new_status;
};


struct __ExpEnviInputStatusHistory
{
	ExpEnviInputStatusHistoryItem 	*history;
	unsigned int 					buff_write_idx;  
	unsigned int 					buff_read_idx;  
	unsigned int 					buffer_size;
};

struct __ExpEnviOutputStatusHistory
{
	ExpEnviOutputStatusHistoryItem	 	*history;
	unsigned int 					buff_write_idx;
  	unsigned int 					buff_read_idx;
	unsigned int 					buffer_size;
};

ExpEnviInputStatusHistory* allocate_exp_envi_input_status_history(ExpEnviInputStatusHistory* hist, unsigned int buffer_size); 
ExpEnviInputStatusHistory* deallocate_exp_envi_input_status_history(ExpEnviInputStatusHistory* hist); 
bool write_to_exp_envi_input_status_history(ExpEnviInputStatusHistory* hist, TimeStamp time, ExpEnviInputCompNum comp_num, ExpEnviCompStatus new_status);
bool get_next_exp_envi_input_status_history_item(ExpEnviInputStatusHistory* hist, ExpEnviInputStatusHistoryItem *item);	

ExpEnviOutputStatusHistory* allocate_exp_envi_output_status_history(ExpEnviOutputStatusHistory* hist, unsigned int buffer_size); 
ExpEnviOutputStatusHistory* deallocate_exp_envi_output_status_history(ExpEnviOutputStatusHistory* hist); 
bool write_to_exp_envi_output_status_history(ExpEnviOutputStatusHistory* hist, TimeStamp time, ExpEnviOutputCompNum comp_num, ExpEnviCompStatus new_status);
bool get_next_exp_envi_output_status_history_item(ExpEnviOutputStatusHistory* hist, ExpEnviOutputStatusHistoryItem *item);	

#endif
