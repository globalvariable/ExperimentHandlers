#ifndef TRIAL_HAND_2_EXP_ENVI_HAND_H
#define TRIAL_HAND_2_EXP_ENVI_HAND_H

//  MESSAGES FROM TRIAL HANDLER TO EXP ENVI HANDLER

typedef struct __TrialHand2ExpEnviHandMsg TrialHand2ExpEnviHandMsg;
typedef struct __TrialHand2ExpEnviHandMsgItem TrialHand2ExpEnviHandMsgItem;
typedef unsigned int TrialHand2ExpEnviHandMsgType;
typedef unsigned int TrialHand2ExpEnviHandMsgAdditional;


#define TRIAL_HAND_2_EXP_ENVI_HAND_MSG_STRING_LENGTH						100

#define TRIAL_HAND_2_EXP_ENVI_HAND_MSG_NULL									0
#define TRIAL_HAND_2_EXP_ENVI_HAND_MSG_ARE_YOU_ALIVE						1
#define TRIAL_HAND_2_EXP_ENVI_HAND_MSG_START_TRIAL							2		// send trial type as additional
#define TRIAL_HAND_2_EXP_ENVI_HAND_MSG_END_TRIAL							3
#define TRIAL_HAND_2_EXP_ENVI_HAND_MSG_RELEASE_REWARD					4	
#define TRIAL_HAND_2_EXP_ENVI_HAND_MSG_RELEASE_PUNISHMENT				5	
#define TRIAL_HAND_2_EXP_ENVI_HAND_MSG_START_RECORDING					6
#define TRIAL_HAND_2_EXP_ENVI_HAND_MSG_STOP_RECORDING					7
#define TRIAL_HAND_2_EXP_ENVI_HAND_MSG_CANCEL_RECORDING					8    		// sent to cancel current recording
#define TRIAL_HAND_2_EXP_ENVI_HAND_MSG_ENABLE_INP_COMPS_W_NO_STATUS_RESET	9    		
#define TRIAL_HAND_2_EXP_ENVI_HAND_MSG_ENABLE_INP_COMPS_W_STATUS_RESET	10    		
#define TRIAL_HAND_2_EXP_ENVI_HAND_MSG_DISABLE_INPUT_COMPONENTS			11    		
#define TRIAL_HAND_2_EXP_ENVI_HAND_MSG_GET_READY_TO_TRIAL_START			12    
#define TRIAL_HAND_2_EXP_ENVI_HAND_MSG_DISABLE_LEVERS						13
#define TRIAL_HAND_2_EXP_ENVI_HAND_MSG_ENABLE_LEVERS_W_STATUS_RESET	14
#define TRIAL_HAND_2_EXP_ENVI_HAND_MSG_DISABLE_NOSE_POKE_RETRACT		15
#define TRIAL_HAND_2_EXP_ENVI_HAND_MSG_ENABLE_NOSE_POKE_RETRACT		16

#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>
#include <rtai_shm.h>
#include <rtai_nam2num.h>
#include "MessageBuffersConfig.h"
#include "../../../BlueSpike/System/ShmSemNum/ShmSemNum.h"
#include "../../../BlueSpike/System/TimeStamp/TimeStamp.h"
#include "../../../BlueSpike/Library/Misc/Misc.h"

struct __TrialHand2ExpEnviHandMsgItem
{
	TimeStamp 								msg_time;		
	TrialHand2ExpEnviHandMsgType				msg_type;
	TrialHand2ExpEnviHandMsgAdditional			additional_data;
};

struct __TrialHand2ExpEnviHandMsg		// Requests to TrialControllers
{
	TrialHand2ExpEnviHandMsgItem		buff[TRIAL_HAND_2_EXP_ENVI_HAND_MSG_BUFF_SIZE];
	unsigned int						buff_write_idx;	// only one message sender can write into this buffer and edit this write index
	unsigned int						buff_read_idx;	// only one request handler can edit this read index
};

bool get_trial_hand_2_exp_envi_hand_msg_type_string(TrialHand2ExpEnviHandMsgType msg_type, char *str);

// Messaging through allocated memory (in same program) 
TrialHand2ExpEnviHandMsg* allocate_trial_hand_2_exp_envi_hand_msg_buffer(TrialHand2ExpEnviHandMsg* msg_buffer);
TrialHand2ExpEnviHandMsg* deallocate_trial_hand_2_exp_envi_hand_msg_buffer(TrialHand2ExpEnviHandMsg* msg_buffer);

// Messaging through shared memory (separate programs) 
TrialHand2ExpEnviHandMsg* allocate_shm_server_trial_hand_2_exp_envi_hand_msg_buffer(TrialHand2ExpEnviHandMsg* msg_buffer);
TrialHand2ExpEnviHandMsg* allocate_shm_client_trial_hand_2_exp_envi_hand_msg_buffer(TrialHand2ExpEnviHandMsg* msg_buffer);
TrialHand2ExpEnviHandMsg* deallocate_shm_trial_hand_2_exp_envi_hand_msg_buffer(TrialHand2ExpEnviHandMsg* msg_buffer);
bool write_to_trial_hand_2_exp_envi_hand_msg_buffer(TrialHand2ExpEnviHandMsg* msg_buffer, TimeStamp msg_time, TrialHand2ExpEnviHandMsgType msg_type, TrialHand2ExpEnviHandMsgAdditional additional_data);
bool get_next_trial_hand_2_exp_envi_hand_msg_buffer_item(TrialHand2ExpEnviHandMsg* msg_buffer, TrialHand2ExpEnviHandMsgItem *msg_item);	// take care of static read_idx value //only request buffer handler uses

#endif
