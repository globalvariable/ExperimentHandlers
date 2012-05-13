#ifndef EXP_ENVI_INTERF_2_EXP_ENVI_HAND_H
#define EXP_ENVI_INTERF_2_EXP_ENVI_HAND_H

//  MESSAGES FROM EXP ENVI INTERFACER TO EXP ENVI HANDLER

typedef struct __ExpEnviInterf2ExpEnviHandMsg ExpEnviInterf2ExpEnviHandMsg;
typedef struct __ExpEnviInterf2ExpEnviHandMsgItem ExpEnviInterf2ExpEnviHandMsgItem;
typedef unsigned int ExpEnviInterf2ExpEnviHandMsgType;
typedef unsigned int ExpEnviInterf2ExpEnviHandMsgAdditional;


#define EXP_ENVI_INTERF_2_EXP_ENVI_HAND_MSG_STRING_LENGTH					100

#define EXP_ENVI_INTERF_2_EXP_ENVI_HAND_MSG_NULL							0
#define EXP_ENVI_INTERF_2_EXP_ENVI_HAND_MSG_I_AM_ALIVE						1


#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>
#include <rtai_shm.h>
#include <rtai_nam2num.h>
#include "MessageBuffersConfig.h"
#include "MessageBuffersSharedMem.h"
#include "../../../BlueSpike/TimeStamp.h"
#include "../../../BlueSpike/Library/Misc/Misc.h"


struct __ExpEnviInterf2ExpEnviHandMsgItem
{
	TimeStamp 								msg_time;		
	ExpEnviInterf2ExpEnviHandMsgType			msg_type;
	ExpEnviInterf2ExpEnviHandMsgAdditional		additional_data;
};

struct __ExpEnviInterf2ExpEnviHandMsg		
{
	ExpEnviInterf2ExpEnviHandMsgItem		buff[EXP_ENVI_INTERF_2_EXP_ENVI_HAND_MSG_BUFF_SIZE];
	unsigned int						buff_write_idx;	// only one message sender can write into this buffer and edit this write index
	unsigned int						buff_read_idx;	// only one request handler can edit this read index
};

bool get_exp_envi_interf_2_exp_envi_hand_msg_type_string(ExpEnviInterf2ExpEnviHandMsgType msg_type, char *str);

// Messaging through allocated memory (in same program) 
ExpEnviInterf2ExpEnviHandMsg* allocate_exp_envi_interf_2_exp_envi_hand_msg_buffer(ExpEnviInterf2ExpEnviHandMsg* msg_buffer);
ExpEnviInterf2ExpEnviHandMsg* deallocate_exp_envi_interf_2_exp_envi_hand_msg_buffer(ExpEnviInterf2ExpEnviHandMsg* msg_buffer);

// Messaging through shared memory (separate programs) 
ExpEnviInterf2ExpEnviHandMsg* allocate_shm_server_exp_envi_interf_2_exp_envi_hand_msg_buffer(ExpEnviInterf2ExpEnviHandMsg* msg_buffer);
ExpEnviInterf2ExpEnviHandMsg* allocate_shm_client_exp_envi_interf_2_exp_envi_hand_msg_buffer(ExpEnviInterf2ExpEnviHandMsg* msg_buffer);
ExpEnviInterf2ExpEnviHandMsg* deallocate_shm_exp_envi_interf_2_exp_envi_hand_msg_buffer(ExpEnviInterf2ExpEnviHandMsg* msg_buffer);
bool write_to_exp_envi_interf_2_exp_envi_hand_msg_buffer(ExpEnviInterf2ExpEnviHandMsg* msg_buffer, TimeStamp msg_time, ExpEnviInterf2ExpEnviHandMsgType msg_type, ExpEnviInterf2ExpEnviHandMsgAdditional additional_data);
bool get_next_exp_envi_interf_2_exp_envi_hand_msg_buffer_item(ExpEnviInterf2ExpEnviHandMsg* msg_buffer, ExpEnviInterf2ExpEnviHandMsgItem **msg_item);	// take care of static read_idx value //only request buffer handler uses

#endif
