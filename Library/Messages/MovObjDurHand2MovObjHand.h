#ifndef MOV_OBJ_DUR_HAND_2_MOV_OBJ_HAND_H
#define MOV_OBJ_DUR_HAND_2_MOV_OBJ_HAND_H

//  MESSAGES FROM MOV OBJ DURATION HANDLER TO MOV OBJ HANDLER

typedef struct __MovObjDurHand2MovObjHandMsg MovObjDurHand2MovObjHandMsg;
typedef struct __MovObjDurHand2MovObjHandMsgItem MovObjDurHand2MovObjHandMsgItem;
typedef unsigned int MovObjDurHand2MovObjHandMsgType;
typedef unsigned int MovObjDurHand2MovObjHandMsgAdditional;


#define MOV_OBJ_DUR_HAND_2_MOV_OBJ_HAND_MSG_STRING_LENGTH					100

#define MOV_OBJ_DUR_HAND_2_MOV_OBJ_HAND_MSG_NULL							0
#define MOV_OBJ_DUR_HAND_2_MOV_OBJ_HAND_MSG_TIMEOUT						1




#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>
#include "MessageBuffersConfig.h"
#include "../../../BlueSpike/System/TimeStamp/TimeStamp.h"
#include "../../../BlueSpike/Library/Misc/Misc.h"

struct __MovObjDurHand2MovObjHandMsgItem
{
	TimeStamp 								msg_time;		
	MovObjDurHand2MovObjHandMsgType				msg_type;
	MovObjDurHand2MovObjHandMsgAdditional			additional_data;
};

struct __MovObjDurHand2MovObjHandMsg	
{
	MovObjDurHand2MovObjHandMsgItem		buff[MOV_OBJ_DUR_HAND_2_MOV_OBJ_HAND_MSG_BUFF_SIZE];
	unsigned int						buff_write_idx;	// only one message sender can write into this buffer and edit this write index
	unsigned int						buff_read_idx;	// only one request handler can edit this read index
};

bool get_mov_obj_dur_hand_2_mov_obj_hand_msg_type_string(MovObjDurHand2MovObjHandMsgType msg_type, char *str);

// Messaging through allocated memory (in same program) 
MovObjDurHand2MovObjHandMsg* allocate_mov_obj_dur_hand_2_mov_obj_hand_msg_buffer(MovObjDurHand2MovObjHandMsg* msg_buffer);
MovObjDurHand2MovObjHandMsg* deallocate_mov_obj_dur_hand_2_mov_obj_hand_msg_buffer(MovObjDurHand2MovObjHandMsg* msg_buffer);
bool write_to_mov_obj_dur_hand_2_mov_obj_hand_msg_buffer(MovObjDurHand2MovObjHandMsg* msg_buffer, TimeStamp msg_time, MovObjDurHand2MovObjHandMsgType msg_type, MovObjDurHand2MovObjHandMsgAdditional additional_data);
bool get_next_mov_obj_dur_hand_2_mov_obj_hand_msg_buffer_item(MovObjDurHand2MovObjHandMsg* msg_buffer, MovObjDurHand2MovObjHandMsgItem *msg_item);	// take care of static read_idx value //only request buffer handler uses

#endif
