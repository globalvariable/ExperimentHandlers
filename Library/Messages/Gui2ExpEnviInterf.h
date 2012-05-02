#ifndef GUI_2_EXP_ENVI_INTERF_H
#define GUI_2_EXP_ENVI_INTERF_H

//  MESSAGES FROM EXP ENVI INTERFACER GUI TO EXP ENVI INTERFACER

typedef struct __Gui2ExpEnviInterfMsg Gui2ExpEnviInterfMsg;
typedef struct __Gui2ExpEnviInterfMsgItem Gui2ExpEnviInterfMsgItem;
typedef unsigned int Gui2ExpEnviInterfMsgType;
typedef unsigned int Gui2ExpEnviInterfMsgAdditional;


#define GUI_2_EXP_ENVI_INTERF_MSG_STRING_LENGTH		50

#define GUI_2_EXP_ENVI_INTERF_MSG_NULL							0


#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>
#include "MessageBuffersConfig.h"
#include "../../../BlueSpike/TimeStamp.h"
#include "../../../BlueSpike/Library/Misc/Misc.h"

struct __Gui2ExpEnviInterfMsgItem
{
	TimeStamp 								msg_time;		
	Gui2ExpEnviInterfMsgType					msg_type;
	Gui2ExpEnviInterfMsgAdditional				additional_data;
};

struct __Gui2ExpEnviInterfMsg		// Requests to TrialControllers
{
	Gui2ExpEnviInterfMsgItem		buff[GUI_2_EXP_ENVI_INTERF_MSG_BUFFER_SIZE];
	unsigned int					buff_write_idx;	// only one message sender can write into this buffer and edit this write index
	unsigned int					buff_read_idx;	// only one message Interfler can edit this read index
};

Gui2ExpEnviInterfMsg* allocate_gui_2_exp_envi_interf_msg_buffer(Gui2ExpEnviInterfMsg* msg_buffer);
Gui2ExpEnviInterfMsg* deallocate_gui_2_exp_envi_interf_msg_buffer(Gui2ExpEnviInterfMsg* msg_buffer);
bool get_gui_2_exp_envi_interf_msg_type_string(Gui2ExpEnviInterfMsgType msg_type, char *str);
bool write_to_gui_2_exp_envi_interf_msg_buffer(Gui2ExpEnviInterfMsg* msg_buffer, TimeStamp msg_time, Gui2ExpEnviInterfMsgType msg_type, Gui2ExpEnviInterfMsgAdditional additional_data);
bool get_next_gui_2_exp_envi_interf_msg_buffer_item(Gui2ExpEnviInterfMsg* msg_buffer, Gui2ExpEnviInterfMsgItem **msg_item);	// take care of static read_idx value //only request buffer handler uses
#endif
