#ifndef GUI_2_MOV_OBJ_INTERF_H
#define GUI_2_MOV_OBJ_INTERF_H

//  MESSAGES FROM MOV OBJ INTERFACER GUI TO MOV OBJ INTERFACER

typedef struct __Gui2MovObjInterfMsg Gui2MovObjInterfMsg;
typedef struct __Gui2MovObjInterfMsgItem Gui2MovObjInterfMsgItem;
typedef unsigned int Gui2MovObjInterfMsgType;
typedef unsigned int Gui2MovObjInterfMsgAdditional;


#define GUI_2_MOV_OBJ_INTERF_MSG_STRING_LENGTH		50

#define GUI_2_MOV_OBJ_INTERF_MSG_NULL				0


#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>
#include "MessageBuffersConfig.h"
#include "../../../BlueSpike/TimeStamp.h"
#include "../../../BlueSpike/Library/Misc/Misc.h"

struct __Gui2MovObjInterfMsgItem
{
	TimeStamp 								msg_time;		
	Gui2MovObjInterfMsgType					msg_type;
	Gui2MovObjInterfMsgAdditional				additional_data;
};

struct __Gui2MovObjInterfMsg		// Requests to TrialControllers
{
	Gui2MovObjInterfMsgItem		buff[GUI_2_MOV_OBJ_INTERF_MSG_BUFFER_SIZE];
	unsigned int					buff_write_idx;	// only one message sender can write into this buffer and edit this write index
	unsigned int					buff_read_idx;	// only one mesasge handler can edit this read index
};

Gui2MovObjInterfMsg* allocate_gui_2_mov_obj_interf_msg_buffer(Gui2MovObjInterfMsg* msg_buffer);
Gui2MovObjInterfMsg* deallocate_gui_2_mov_obj_interf_msg_buffer(Gui2MovObjInterfMsg* msg_buffer);
bool get_gui_2_mov_obj_interf_msg_type_string(Gui2MovObjInterfMsgType msg_type, char *str);
bool write_to_gui_2_mov_obj_interf_msg_buffer(Gui2MovObjInterfMsg* msg_buffer, TimeStamp msg_time, Gui2MovObjInterfMsgType msg_type, Gui2MovObjInterfMsgAdditional additional_data);
bool get_next_gui_2_mov_obj_interf_msg_buffer_item(Gui2MovObjInterfMsg* msg_buffer, Gui2MovObjInterfMsgItem **msg_item);	// take care of static read_idx value //only request buffer handler uses
#endif
