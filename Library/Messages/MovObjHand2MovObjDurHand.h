#ifndef MOV_OBJ_HAND_2_MOV_OBJ_DUR_HAND_H
#define MOV_OBJ_HAND_2_MOV_OBJ_DUR_HAND_H

//  MESSAGES FROM MOV OBJ HANDLER TO MOV OBJ DURATION HANDLER

#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>
#include "MessageBuffersConfig.h"
#include "../../../BlueSpike/TimeStamp.h"
#include "../../../BlueSpike/Library/Misc/Misc.h"

typedef struct __MovObjHand2MovObjDurHandMsg MovObjHand2MovObjDurHandMsg;
typedef struct __MovObjHand2MovObjDurHandMsgItem MovObjHand2MovObjDurHandMsgItem;
typedef unsigned int MovObjHand2MovObjDurHandMsgType;
typedef TimeStamp MovObjHand2MovObjDurHandMsgAdditional;


#define MOV_OBJ_HAND_2_MOV_OBJ_DUR_HAND_MSG_STRING_LENGTH					100

#define MOV_OBJ_HAND_2_MOV_OBJ_DUR_HAND_MSG_NULL							0
#define MOV_OBJ_HAND_2_MOV_OBJ_DUR_HAND_MSG_START_TIMER					1
#define MOV_OBJ_HAND_2_MOV_OBJ_DUR_HAND_MSG_CANCEL_TIMER				2


struct __MovObjHand2MovObjDurHandMsgItem
{
	TimeStamp 								msg_time;		
	MovObjHand2MovObjDurHandMsgType				msg_type;
	MovObjHand2MovObjDurHandMsgAdditional			additional_data;
};

struct __MovObjHand2MovObjDurHandMsg		
{
	MovObjHand2MovObjDurHandMsgItem		buff[MOV_OBJ_HAND_2_MOV_OBJ_DUR_HAND_MSG_BUFF_SIZE];
	unsigned int						buff_write_idx;	// only one message sender can write into this buffer and edit this write index
	unsigned int						buff_read_idx;	// only one request handler can edit this read index
};

bool get_mov_obj_hand_2_mov_obj_dur_hand_msg_type_string(MovObjHand2MovObjDurHandMsgType msg_type, char *str);

// Messaging through allocated memory (in same program) 
MovObjHand2MovObjDurHandMsg* allocate_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer(MovObjHand2MovObjDurHandMsg* msg_buffer);
MovObjHand2MovObjDurHandMsg* deallocate_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer(MovObjHand2MovObjDurHandMsg* msg_buffer);
bool write_to_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer(MovObjHand2MovObjDurHandMsg* msg_buffer, TimeStamp msg_time, MovObjHand2MovObjDurHandMsgType msg_type, MovObjHand2MovObjDurHandMsgAdditional additional_data);
bool get_next_mov_obj_hand_2_mov_obj_dur_hand_msg_buffer_item(MovObjHand2MovObjDurHandMsg* msg_buffer, MovObjHand2MovObjDurHandMsgItem *msg_item);	// take care of static read_idx value //only request buffer handler uses

#endif
