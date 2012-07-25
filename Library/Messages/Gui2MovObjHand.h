#ifndef GUI_2_MOV_OBJ_HAND_H
#define GUI_2_MOV_OBJ_HAND_H

//  MESSAGES FROM MOV OBJ HANDLER GUI TO MOV OBJ HANDLER

typedef struct __Gui2MovObjHandMsg Gui2MovObjHandMsg;
typedef struct __Gui2MovObjHandMsgItem Gui2MovObjHandMsgItem;
typedef unsigned int Gui2MovObjHandMsgType;
typedef double Gui2MovObjHandMsgAdditional;


#define GUI_2_MOV_OBJ_HAND_MSG_STRING_LENGTH		50

#define GUI_2_MOV_OBJ_HAND_MSG_NULL					0
#define GUI_2_MOV_OBJ_HAND_MSG_SET_THRESHOLD		1

#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>
#include "MessageBuffersConfig.h"
#include "../../../BlueSpike/TimeStamp.h"
#include "../../../BlueSpike/Library/Misc/Misc.h"

struct __Gui2MovObjHandMsgItem
{
	TimeStamp 								msg_time;		
	Gui2MovObjHandMsgType					msg_type;
	Gui2MovObjHandMsgAdditional				additional_data;
};

struct __Gui2MovObjHandMsg		// Requests to TrialControllers
{
	Gui2MovObjHandMsgItem		buff[GUI_2_MOV_OBJ_HAND_MSG_BUFFER_SIZE];
	unsigned int					buff_write_idx;	// only one message sender can write into this buffer and edit this write index
	unsigned int					buff_read_idx;	// only one request handler can edit this read index
};

Gui2MovObjHandMsg* allocate_gui_2_mov_obj_hand_msg_buffer(Gui2MovObjHandMsg* msg_buffer);
Gui2MovObjHandMsg* deallocate_gui_2_mov_obj_hand_msg_buffer(Gui2MovObjHandMsg* msg_buffer);
bool get_gui_2_mov_obj_hand_msg_type_string(Gui2MovObjHandMsgType msg_type, char *str);
bool write_to_gui_2_mov_obj_hand_msg_buffer(Gui2MovObjHandMsg* msg_buffer, TimeStamp msg_time, Gui2MovObjHandMsgType msg_type, Gui2MovObjHandMsgAdditional additional_data);
bool get_next_gui_2_mov_obj_hand_msg_buffer_item(Gui2MovObjHandMsg* msg_buffer, Gui2MovObjHandMsgItem *msg_item);	// take care of static read_idx value //only request buffer handler uses
#endif
