#ifndef MOV_OBJ_DUR_STATUS_H
#define MOV_OBJ_DUR_STATUS_H


#include <stdbool.h>
#include "../../../BlueSpike/System/TimeStamp/TimeStamp.h"

#define	MOV_OBJ_DUR_STATUS_ITEM_STAY_AT_CURRENT_POSITION		0
#define	MOV_OBJ_DUR_STATUS_ITEM_SEND_PULSE_WIDTH				1
#define	MOV_OBJ_DUR_STATUS_ITEM_SEND_AD_CONVERSION				2
#define	MOV_OBJ_DUR_STATUS_ITEM_READ_POSITION						3
#define	MOV_OBJ_DUR_STATUS_NUM_OF_ITEMS							4


typedef struct 
{
	bool 		active;
	TimeStamp	schedule;
} MovObjScheduleItem; 

typedef struct 
{
	MovObjScheduleItem	items[MOV_OBJ_DUR_STATUS_NUM_OF_ITEMS];
} MovObjSchedule;


#endif
