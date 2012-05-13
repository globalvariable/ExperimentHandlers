#ifndef EXP_ENVI_HAND_2_TRIAL_HAND_H
#define EXP_ENVI_HAND_2_TRIAL_HAND_H

//  MESSAGES FROM EXP ENVI HANDLER TO TRIAL HANDLER

typedef struct __ExpEnviHand2TrialHandMsg ExpEnviHand2TrialHandMsg;
typedef struct __ExpEnviHand2TrialHandMsgItem ExpEnviHand2TrialHandMsgItem;
typedef unsigned int ExpEnviHand2TrialHandMsgType;
typedef unsigned int ExpEnviHand2TrialHandMsgAdditional;


#define EXP_ENVI_HAND_2_TRIAL_HAND_MSG_STRING_LENGTH					100

#define EXP_ENVI_HAND_2_TRIAL_HAND_MSG_NULL								0
#define EXP_ENVI_HAND_2_TRIAL_HAND_MSG_I_AM_ALIVE						1
#define EXP_ENVI_HAND_2_TRIAL_HAND_MSG_START_TRIAL_REQUEST			2



#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>
#include <rtai_shm.h>
#include <rtai_nam2num.h>
#include "MessageBuffersConfig.h"
#include "MessageBuffersSharedMem.h"
#include "../../../BlueSpike/TimeStamp.h"
#include "../../../BlueSpike/Library/Misc/Misc.h"

struct __ExpEnviHand2TrialHandMsgItem
{
	TimeStamp 								msg_time;		
	ExpEnviHand2TrialHandMsgType				msg_type;
	ExpEnviHand2TrialHandMsgAdditional			additional_data;
};

struct __ExpEnviHand2TrialHandMsg		// Requests to TrialControllers
{
	ExpEnviHand2TrialHandMsgItem		buff[EXP_ENVI_HAND_2_TRIAL_HAND_MSG_BUFF_SIZE];
	unsigned int						buff_write_idx;	// only one message sender can write into this buffer and edit this write index
	unsigned int						buff_read_idx;	// only one request handler can edit this read index
};

bool get_exp_envi_hand_2_trial_hand_msg_type_string(ExpEnviHand2TrialHandMsgType msg_type, char *str);

// Messaging through allocated memory (in same program) 
ExpEnviHand2TrialHandMsg* allocate_exp_envi_hand_2_trial_hand_msg_buffer(ExpEnviHand2TrialHandMsg* msg_buffer);
ExpEnviHand2TrialHandMsg* deallocate_exp_envi_hand_2_trial_hand_msg_buffer(ExpEnviHand2TrialHandMsg* msg_buffer);

// Messaging through shared memory (separate programs) 
ExpEnviHand2TrialHandMsg* allocate_shm_server_exp_envi_hand_2_trial_hand_msg_buffer(ExpEnviHand2TrialHandMsg* msg_buffer);
ExpEnviHand2TrialHandMsg* allocate_shm_client_exp_envi_hand_2_trial_hand_msg_buffer(ExpEnviHand2TrialHandMsg* msg_buffer);
ExpEnviHand2TrialHandMsg* deallocate_shm_exp_envi_hand_2_trial_hand_msg_buffer(ExpEnviHand2TrialHandMsg* msg_buffer);
bool write_to_exp_envi_hand_2_trial_hand_msg_buffer(ExpEnviHand2TrialHandMsg* msg_buffer, TimeStamp msg_time, ExpEnviHand2TrialHandMsgType msg_type, ExpEnviHand2TrialHandMsgAdditional additional_data);
bool get_next_exp_envi_hand_2_trial_hand_msg_buffer_item(ExpEnviHand2TrialHandMsg* msg_buffer, ExpEnviHand2TrialHandMsgItem **msg_item);	// take care of static read_idx value //only request buffer handler uses



#endif
