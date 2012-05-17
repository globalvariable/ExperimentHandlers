#ifndef EXP_ENVI_DUR_HAND_2_EXP_ENVI_HAND_H
#define EXP_ENVI_DUR_HAND_2_EXP_ENVI_HAND_H

//  MESSAGES FROM EXP ENVI DURATION HANDLER TO EXP ENVI HANDLER

typedef struct __ExpEnviDurHand2ExpEnviHandMsg ExpEnviDurHand2ExpEnviHandMsg;
typedef struct __ExpEnviDurHand2ExpEnviHandMsgItem ExpEnviDurHand2ExpEnviHandMsgItem;
typedef unsigned int ExpEnviDurHand2ExpEnviHandMsgType;
typedef unsigned int ExpEnviDurHand2ExpEnviHandMsgAdditional;


#define EXP_ENVI_DUR_HAND_2_EXP_ENVI_HAND_MSG_STRING_LENGTH					100

#define EXP_ENVI_DUR_HAND_2_EXP_ENVI_HAND_MSG_NULL							0
#define EXP_ENVI_DUR_HAND_2_EXP_ENVI_HAND_MSG_TIMEOUT_FOR_MIN				1
#define EXP_ENVI_DUR_HAND_2_EXP_ENVI_HAND_MSG_TIMEOUT_FOR_MAX				2



#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>
#include "MessageBuffersConfig.h"
#include "../../../BlueSpike/TimeStamp.h"
#include "../../../BlueSpike/Library/Misc/Misc.h"
#include "../ExpEnviData/ExpEnviComponentTypes.h"

struct __ExpEnviDurHand2ExpEnviHandMsgItem
{
	TimeStamp 								msg_time;		
	ExpEnviDurHand2ExpEnviHandMsgType		msg_type;
	ExpEnviInputCompNum						inp_comp_num;
	ExpEnviDurHand2ExpEnviHandMsgAdditional	additional_data;
};

struct __ExpEnviDurHand2ExpEnviHandMsg		
{
	ExpEnviDurHand2ExpEnviHandMsgItem		buff[EXP_ENVI_DUR_HAND_2_EXP_ENVI_HAND_MSG_BUFF_SIZE];
	unsigned int						buff_write_idx;	// only one message sender can write into this buffer and edit this write index
	unsigned int						buff_read_idx;	// only one request handler can edit this read index
};

bool get_exp_envi_dur_hand_2_exp_envi_hand_msg_type_string(ExpEnviDurHand2ExpEnviHandMsgType msg_type, char *str);

// Messaging through allocated memory (in same program) 
ExpEnviDurHand2ExpEnviHandMsg* allocate_exp_envi_dur_hand_2_exp_envi_hand_msg_buffer(ExpEnviDurHand2ExpEnviHandMsg* msg_buffer);
ExpEnviDurHand2ExpEnviHandMsg* deallocate_exp_envi_dur_hand_2_exp_envi_hand_msg_buffer(ExpEnviDurHand2ExpEnviHandMsg* msg_buffer);
bool write_to_exp_envi_dur_hand_2_exp_envi_hand_msg_buffer(ExpEnviDurHand2ExpEnviHandMsg* msg_buffer, TimeStamp msg_time, ExpEnviDurHand2ExpEnviHandMsgType msg_type, ExpEnviInputCompNum inp_comp_num, ExpEnviDurHand2ExpEnviHandMsgAdditional additional_data);
bool get_next_exp_envi_dur_hand_2_exp_envi_hand_msg_buffer_item(ExpEnviDurHand2ExpEnviHandMsg* msg_buffer, ExpEnviDurHand2ExpEnviHandMsgItem **msg_item);	// take care of static read_idx value //only request buffer handler uses

#endif
