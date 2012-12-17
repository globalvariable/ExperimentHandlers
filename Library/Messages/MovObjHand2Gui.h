#ifndef MOV_OBJ_HAND_2_GUI_H
#define MOV_OBJ_HAND_2_GUI_H

//  MESSAGES FROM MOV OBJ HANDLER TO MOV OBJ HANDLER GUI

typedef struct __MovObjHand2GuiMsg MovObjHand2GuiMsg;
typedef struct __MovObjHand2GuiMsgItem MovObjHand2GuiMsgItem;
typedef unsigned int MovObjHand2GuiMsgType;
typedef double MovObjHand2GuiMsgAdditional;


#define MOV_OBJ_HAND_2_GUI_MSG_STRING_LENGTH		50

#define MOV_OBJ_HAND_2_GUI_MSG_NULL					0
#define MOV_OBJ_HAND_2_GUI_MSG_LOCATION				1

#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>
#include "MessageBuffersConfig.h"
#include "../../../BlueSpike/System/TimeStamp/TimeStamp.h"
#include "../MovObjData/MovObjComponentTypes.h"
#include "../../../BlueSpike/Library/Misc/Misc.h"

struct __MovObjHand2GuiMsgItem
{
	TimeStamp 						msg_time;		
	MovObjHand2GuiMsgType			msg_type;
	MovObjCompType 					component;
	MovObjHand2GuiMsgAdditional		additional_data_0;
	MovObjHand2GuiMsgAdditional		additional_data_1;
	MovObjHand2GuiMsgAdditional		additional_data_2;
};

struct __MovObjHand2GuiMsg		// Requests to TrialControllers
{
	MovObjHand2GuiMsgItem		buff[MOV_OBJ_HAND_2_GUI_MSG_BUFFER_SIZE];
	unsigned int					buff_write_idx;	// only one message sender can write into this buffer and edit this write index
	unsigned int					buff_read_idx;	// only one request handler can edit this read index
};

MovObjHand2GuiMsg* allocate_mov_obj_hand_2_gui_msg_buffer(MovObjHand2GuiMsg* msg_buffer);
MovObjHand2GuiMsg* deallocate_mov_obj_hand_2_gui_msg_buffer(MovObjHand2GuiMsg* msg_buffer);
bool get_mov_obj_hand_2_gui_msg_type_string(MovObjHand2GuiMsgType msg_type, char *str);
bool write_to_mov_obj_hand_2_gui_msg_buffer(MovObjHand2GuiMsg* msg_buffer, TimeStamp msg_time, MovObjHand2GuiMsgType msg_type, MovObjCompType component, MovObjHand2GuiMsgAdditional additional_data_0,  MovObjHand2GuiMsgAdditional additional_data_1,  MovObjHand2GuiMsgAdditional additional_data_2);
bool get_next_mov_obj_hand_2_gui_msg_buffer_item(MovObjHand2GuiMsg* msg_buffer, MovObjHand2GuiMsgItem *msg_item);	// take care of static read_idx value //only request buffer handler uses




#endif
