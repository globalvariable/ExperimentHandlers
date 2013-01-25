#ifndef GUI_2_EXP_ENVI_HAND_H
#define GUI_2_EXP_ENVI_HAND_H

//  MESSAGES FROM EXP ENVI HANDLER GUI TO EXP ENVI HANDLER

typedef struct __Gui2ExpEnviHandMsg Gui2ExpEnviHandMsg;
typedef struct __Gui2ExpEnviHandMsgItem Gui2ExpEnviHandMsgItem;
typedef unsigned int Gui2ExpEnviHandMsgType;
typedef unsigned int Gui2ExpEnviHandMsgAdditional;


#define GUI_2_EXP_ENVI_HAND_MSG_STRING_LENGTH		50

#define GUI_2_EXP_ENVI_HAND_MSG_NULL					0


#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>
#include "MessageBuffersConfig.h"
#include "../../../BlueSpike/System/TimeStamp/TimeStamp.h"
#include "../../../BlueSpike/Library/Misc/Misc.h"

struct __Gui2ExpEnviHandMsgItem
{
	TimeStamp 								msg_time;		
	Gui2ExpEnviHandMsgType					msg_type;
	Gui2ExpEnviHandMsgAdditional				additional_data;
};

struct __Gui2ExpEnviHandMsg		// Requests to TrialControllers
{
	Gui2ExpEnviHandMsgItem		buff[GUI_2_EXP_ENVI_HAND_MSG_BUFFER_SIZE];
	unsigned int					buff_write_idx;	// only one message sender can write into this buffer and edit this write index
	unsigned int					buff_read_idx;	// only one request handler can edit this read index
};

Gui2ExpEnviHandMsg* allocate_gui_2_exp_envi_hand_msg_buffer(Gui2ExpEnviHandMsg* msg_buffer);
Gui2ExpEnviHandMsg* deallocate_gui_2_exp_envi_hand_msg_buffer(Gui2ExpEnviHandMsg* msg_buffer);
bool get_gui_2_exp_envi_hand_msg_type_string(Gui2ExpEnviHandMsgType msg_type, char *str);
bool write_to_gui_2_exp_envi_hand_msg_buffer(Gui2ExpEnviHandMsg* msg_buffer, TimeStamp msg_time, Gui2ExpEnviHandMsgType msg_type, Gui2ExpEnviHandMsgAdditional additional_data);
bool get_next_gui_2_exp_envi_hand_msg_buffer_item(Gui2ExpEnviHandMsg* msg_buffer, Gui2ExpEnviHandMsgItem *msg_item);	// take care of static read_idx value //only request buffer handler uses
#endif
