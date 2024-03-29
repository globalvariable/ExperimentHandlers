#ifndef EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_H
#define EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_H

//  MESSAGES FROM EXP ENVI HANDLER TO EXP ENVI DURATION HANDLER

#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>
#include "MessageBuffersConfig.h"
#include "../../../BlueSpike/System/TimeStamp/TimeStamp.h"
#include "../../../BlueSpike/Library/Misc/Misc.h"
#include "../ExpEnviData/ExpEnviComponentTypes.h"

typedef struct __ExpEnviHand2ExpEnviDurHandMsg ExpEnviHand2ExpEnviDurHandMsg;
typedef struct __ExpEnviHand2ExpEnviDurHandMsgItem ExpEnviHand2ExpEnviDurHandMsgItem;
typedef unsigned int ExpEnviHand2ExpEnviDurHandMsgType;
typedef TimeStamp ExpEnviHand2ExpEnviDurHandMsgAdditional;


#define EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_STRING_LENGTH					100

#define EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_NULL								0
#define EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_START_INPUT_MIN_TIMER				1
#define EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_START_INPUT_MAX_TIMER			2
#define EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_CANCEL_INPUT_MIN_TIMER			3
#define EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_CANCEL_INPUT_MAX_TIMER			4
#define EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_START_OUTPUT_TIMER				5     // "send current time" to cancel out the timer which is set before 
#define EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_CANCEL_OUTPUT_TIMER				6


struct __ExpEnviHand2ExpEnviDurHandMsgItem
{
	TimeStamp 								msg_time;		
	ExpEnviHand2ExpEnviDurHandMsgType		msg_type;
	ExpEnviInputCompNum						comp_num;
	ExpEnviHand2ExpEnviDurHandMsgAdditional	additional_data;		// min time
};

struct __ExpEnviHand2ExpEnviDurHandMsg		
{
	ExpEnviHand2ExpEnviDurHandMsgItem		buff[EXP_ENVI_HAND_2_EXP_ENVI_DUR_HAND_MSG_BUFF_SIZE];
	unsigned int						buff_write_idx;	// only one message sender can write into this buffer and edit this write index
	unsigned int						buff_read_idx;	// only one request handler can edit this read index
};

bool get_exp_envi_hand_2_exp_envi_dur_hand_msg_type_string(ExpEnviHand2ExpEnviDurHandMsgType msg_type, char *str);

// Messaging through allocated memory (in same program) 
ExpEnviHand2ExpEnviDurHandMsg* allocate_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer(ExpEnviHand2ExpEnviDurHandMsg* msg_buffer);
ExpEnviHand2ExpEnviDurHandMsg* deallocate_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer(ExpEnviHand2ExpEnviDurHandMsg* msg_buffer);
bool write_to_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer(ExpEnviHand2ExpEnviDurHandMsg* msg_buffer, TimeStamp msg_time, ExpEnviHand2ExpEnviDurHandMsgType msg_type, ExpEnviCompNum comp_num, ExpEnviHand2ExpEnviDurHandMsgAdditional additional_data);
bool get_next_exp_envi_hand_2_exp_envi_dur_hand_msg_buffer_item(ExpEnviHand2ExpEnviDurHandMsg* msg_buffer, ExpEnviHand2ExpEnviDurHandMsgItem *msg_item);	// take care of static read_idx value //only request buffer handler uses

#endif
