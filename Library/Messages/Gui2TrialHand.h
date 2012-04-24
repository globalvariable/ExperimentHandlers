#ifndef GUI_2_TRIAL_HAND_H
#define GUI_2_TRIAL_HAND_H

//  MESSAGES FROM TRIAL HANDLER GUI TO TRIAL HANDLER

typedef struct __Gui2TrialHandMsg Gui2TrialHandMsg;
typedef struct __Gui2TrialHandMsgItem Gui2TrialHandMsgItem;
typedef unsigned int Gui2TrialHandMsgType;
typedef unsigned int Gui2TrialHandMsgAdditional;


#define GUI_2_TRIAL_HAND_MSG_STRING_LENTGH		20

#define GUI_2_TRIAL_HAND_MSG_NULL							0
#define GUI_2_TRIAL_HAND_MSG_ENABLE_TRIAL_HANDLING		1
#define GUI_2_TRIAL_HAND_MSG_DISABLE_TRIAL_HANDLING		2


#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>
#include "../../Config.h"
#include "../../../BlueSpike/TimeStamp.h"

struct __Gui2TrialHandMsgItem
{
	TimeStamp 								msg_time;		
	Gui2TrialHandMsgType						msg_type;
	Gui2TrialHandMsgAdditional					additional_data;
};

struct __Gui2TrialHandMsg		// Requests to TrialControllers
{
	Gui2TrialHandMsgItem		buff[GUI_2_TRIAL_HAND_MSG_BUFFER_SIZE];
	unsigned int				buff_write_idx;	// only one message sender can write into this buffer and edit this write index
	unsigned int				buff_read_idx;	// only one request handler can edit this read index
};


bool get_gui_2_trial_hand_msg_type_string(Gui2TrialHandMsgType msg_type, char *str);
bool write_to_gui_2_trial_hand_msg_buffer(Gui2TrialHandMsg* msg_buffer, TimeStamp msg_time, Gui2TrialHandMsgType msg_type, Gui2TrialHandMsgAdditional additional_data);
bool get_gui_2_trial_hand_msg_buffer_item(Gui2TrialHandMsg* msg_buffer, Gui2TrialHandMsgItem **msg_item);	// take care of static read_idx value //only request buffer handler uses
#endif
