#ifndef EXP_ENVI_HAND_2_EXP_ENVI_INTERF_H
#define EXP_ENVI_HAND_2_EXP_ENVI_INTERF_H

//  MESSAGES FROM EXP ENVI HANDLER TO TRIAL HANDLER

typedef struct __ExpEnviHand2ExpEnviInterfMsg ExpEnviHand2ExpEnviInterfMsg;
typedef struct __ExpEnviHand2ExpEnviInterfMsgItem ExpEnviHand2ExpEnviInterfMsgItem;
typedef unsigned int ExpEnviHand2ExpEnviInterfMsgType;
typedef unsigned int ExpEnviHand2ExpEnviInterfMsgAdditional;


#define EXP_ENVI_HAND_2_EXP_ENVI_INTERF_MSG_STRING_LENGTH					100

#define EXP_ENVI_HAND_2_EXP_ENVI_INTERF_MSG_NULL							0





#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>
#include <rtai_shm.h>
#include <rtai_nam2num.h>
#include "MessageBuffersConfig.h"
#include "MessageBuffersSharedMem.h"
#include "../../../BlueSpike/TimeStamp.h"
#include "../../../BlueSpike/Library/Misc/Misc.h"


struct __ExpEnviHand2ExpEnviInterfMsgItem
{
	TimeStamp 								msg_time;		
	ExpEnviHand2ExpEnviInterfMsgType			msg_type;
	ExpEnviHand2ExpEnviInterfMsgAdditional		additional_data;
};

struct __ExpEnviHand2ExpEnviInterfMsg		// Requests to TrialControllers
{
	ExpEnviHand2ExpEnviInterfMsgItem	buff[EXP_ENVI_HAND_2_EXP_ENVI_INTERF_MSG_BUFF_SIZE];
	unsigned int						buff_write_idx;	// only one message sender can write into this buffer and edit this write index
	unsigned int						buff_read_idx;	// only one request handler can edit this read index
};

bool get_exp_envi_hand_2_exp_envi_interf_msg_type_string(ExpEnviHand2ExpEnviInterfMsgType msg_type, char *str);

// Messaging through allocated memory (in same program) 
ExpEnviHand2ExpEnviInterfMsg* allocate_exp_envi_hand_2_exp_envi_interf_msg_buffer(ExpEnviHand2ExpEnviInterfMsg* msg_buffer);
ExpEnviHand2ExpEnviInterfMsg* deallocate_exp_envi_hand_2_exp_envi_interf_msg_buffer(ExpEnviHand2ExpEnviInterfMsg* msg_buffer);

// Messaging through shared memory (separate programs) 
ExpEnviHand2ExpEnviInterfMsg* allocate_shm_server_exp_envi_hand_2_exp_envi_interf_msg_buffer(ExpEnviHand2ExpEnviInterfMsg* msg_buffer);
ExpEnviHand2ExpEnviInterfMsg* allocate_shm_client_exp_envi_hand_2_exp_envi_interf_msg_buffer(ExpEnviHand2ExpEnviInterfMsg* msg_buffer);
ExpEnviHand2ExpEnviInterfMsg* deallocate_shm_exp_envi_hand_2_exp_envi_interf_msg_buffer(ExpEnviHand2ExpEnviInterfMsg* msg_buffer);
bool write_to_exp_envi_hand_2_exp_envi_interf_msg_buffer(ExpEnviHand2ExpEnviInterfMsg* msg_buffer, TimeStamp msg_time, ExpEnviHand2ExpEnviInterfMsgType msg_type, ExpEnviHand2ExpEnviInterfMsgAdditional additional_data);
bool get_next_exp_envi_hand_2_exp_envi_interf_msg_buffer_item(ExpEnviHand2ExpEnviInterfMsg* msg_buffer, ExpEnviHand2ExpEnviInterfMsgItem **msg_item);	// take care of static read_idx value //only request buffer handler uses



#endif
