#ifndef EXP_ENVI_HAND_2_GUI_H
#define EXP_ENVI_HAND_2_GUI_H

//  MESSAGES FROM TRIAL HANDLER TO TRIAL HANDLER GUI

typedef struct __ExpEnviHand2GuiMsg ExpEnviHand2GuiMsg;
typedef struct __ExpEnviHand2GuiMsgItem ExpEnviHand2GuiMsgItem;
typedef unsigned int ExpEnviHand2GuiMsgType;
typedef unsigned int ExpEnviHand2GuiMsgAdditional;


#define EXP_ENVI_HAND_2_GUI_MSG_STRING_LENGTH		60

#define EXP_ENVI_HAND_2_GUI_MSG_NULL									0
#define EXP_ENVI_HAND_2_GUI_MSG_START_RECORDING					1   
#define EXP_ENVI_HAND_2_GUI_MSG_STOP_RECORDING					2   
#define EXP_ENVI_HAND_2_GUI_MSG_CANCEL_RECORDING					3   


#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>
#include "MessageBuffersConfig.h"
#include "../../../BlueSpike/System/TimeStamp/TimeStamp.h"
#include "../../../BlueSpike/Library/Misc/Misc.h"

struct __ExpEnviHand2GuiMsgItem
{
	TimeStamp 								msg_time;		
	ExpEnviHand2GuiMsgType						msg_type;
	ExpEnviHand2GuiMsgAdditional					additional_data;
};

struct __ExpEnviHand2GuiMsg		// Requests to TrialControllers
{
	ExpEnviHand2GuiMsgItem		buff[EXP_ENVI_HAND_2_GUI_MSG_BUFF_SIZE];
	unsigned int				buff_write_idx;	// only one message sender can write into this buffer and edit this write index
	unsigned int				buff_read_idx;	// only one request handler can edit this read index
};

ExpEnviHand2GuiMsg* allocate_exp_envi_hand_2_gui_msg_buffer(ExpEnviHand2GuiMsg* msg_buffer);
ExpEnviHand2GuiMsg* deallocate_exp_envi_hand_2_gui_msg_buffer(ExpEnviHand2GuiMsg* msg_buffer);
bool get_exp_envi_hand_2_gui_msg_type_string(ExpEnviHand2GuiMsgType msg_type, char *str);
bool write_to_exp_envi_hand_2_gui_msg_buffer(ExpEnviHand2GuiMsg* msg_buffer, TimeStamp msg_time, ExpEnviHand2GuiMsgType msg_type, ExpEnviHand2GuiMsgAdditional additional_data);
bool get_next_exp_envi_hand_2_gui_msg_buffer_item(ExpEnviHand2GuiMsg* msg_buffer, ExpEnviHand2GuiMsgItem *msg_item);	// take care of static read_idx value //only request buffer handler uses
#endif
