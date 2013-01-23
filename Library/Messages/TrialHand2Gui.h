#ifndef TRIAL_HAND_2_GUI_H
#define TRIAL_HAND_2_GUI_H

//  MESSAGES FROM TRIAL HANDLER TO TRIAL HANDLER GUI

typedef struct __TrialHand2GuiMsg TrialHand2GuiMsg;
typedef struct __TrialHand2GuiMsgItem TrialHand2GuiMsgItem;
typedef unsigned int TrialHand2GuiMsgType;
typedef unsigned int TrialHand2GuiMsgAdditional;


#define TRIAL_HAND_2_GUI_MSG_STRING_LENGTH		60

#define TRIAL_HAND_2_GUI_MSG_NULL									0
#define TRIAL_HAND_2_GUI_MSG_BROADCAST_START_RECORDING_MSG_ACK			1   // acknowledge
#define TRIAL_HAND_2_GUI_MSG_BROADCAST_STOP_RECORDING_MSG_ACK			2   // acknowledge
#define TRIAL_HAND_2_GUI_MSG_BROADCAST_DELETE_RECORDING_MSG_ACK		3   // acknowledge
#define TRIAL_HAND_2_GUI_MSG_TRIAL_STATUS_CHANGE				4

#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>
#include "MessageBuffersConfig.h"
#include "../../../BlueSpike/System/TimeStamp/TimeStamp.h"
#include "../../../BlueSpike/Library/Misc/Misc.h"

struct __TrialHand2GuiMsgItem
{
	TimeStamp 								msg_time;		
	TrialHand2GuiMsgType						msg_type;
	TrialHand2GuiMsgAdditional					additional_data;
};

struct __TrialHand2GuiMsg		// Requests to TrialControllers
{
	TrialHand2GuiMsgItem		buff[TRIAL_HAND_2_GUI_MSG_BUFFER_SIZE];
	unsigned int				buff_write_idx;	// only one message sender can write into this buffer and edit this write index
	unsigned int				buff_read_idx;	// only one request handler can edit this read index
};

TrialHand2GuiMsg* allocate_trial_hand_2_gui_msg_buffer(TrialHand2GuiMsg* msg_buffer);
TrialHand2GuiMsg* deallocate_trial_hand_2_gui_msg_buffer(TrialHand2GuiMsg* msg_buffer);
bool get_trial_hand_2_gui_msg_type_string(TrialHand2GuiMsgType msg_type, char *str);
bool write_to_trial_hand_2_gui_msg_buffer(TrialHand2GuiMsg* msg_buffer, TimeStamp msg_time, TrialHand2GuiMsgType msg_type, TrialHand2GuiMsgAdditional additional_data);
bool get_next_trial_hand_2_gui_msg_buffer_item(TrialHand2GuiMsg* msg_buffer, TrialHand2GuiMsgItem *msg_item);	// take care of static read_idx value //only request buffer handler uses
#endif
