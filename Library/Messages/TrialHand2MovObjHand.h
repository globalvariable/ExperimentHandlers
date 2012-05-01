#ifndef TRIAL_HAND_2_MOV_OBJ_HAND_H
#define TRIAL_HAND_2_MOV_OBJ_HAND_H

//  MESSAGES FROM TRIAL HANDLER TO MOV OBJ HANDLER

typedef struct __TrialHand2MovObjHandMsg TrialHand2MovObjHandMsg;
typedef struct __TrialHand2MovObjHandMsgItem TrialHand2MovObjHandMsgItem;
typedef unsigned int TrialHand2MovObjHandMsgType;
typedef unsigned int TrialHand2MovObjHandMsgAdditional;


#define TRIAL_HAND_2_MOV_OBJ_HAND_MSG_STRING_LENGTH					100

#define TRIAL_HAND_2_MOV_OBJ_HAND_MSG_NULL							0



#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>
#include "MessageBuffersConfig.h"
#include "../../../BlueSpike/TimeStamp.h"
#include "../../../BlueSpike/Library/Misc/Misc.h"

struct __TrialHand2MovObjHandMsgItem
{
	TimeStamp 								msg_time;		
	TrialHand2MovObjHandMsgType				msg_type;
	TrialHand2MovObjHandMsgAdditional			additional_data;
};

struct __TrialHand2MovObjHandMsg		// Requests to TrialControllers
{
	TrialHand2MovObjHandMsgItem		buff[TRIAL_HAND_2_MOV_OBJ_HAND_MSG_BUFF_SIZE];
	unsigned int						buff_write_idx;	// only one message sender can write into this buffer and edit this write index
	unsigned int						buff_read_idx;	// only one request handler can edit this read index
};

bool get_trial_hand_2_mov_obj_hand_msg_type_string(TrialHand2MovObjHandMsgType msg_type, char *str);

// Messaging through allocated memory (in same program) 
TrialHand2MovObjHandMsg* allocate_trial_hand_2_mov_obj__hand_msg_buffer(TrialHand2MovObjHandMsg* msg_buffer);
TrialHand2MovObjHandMsg* deallocate_trial_hand_2_mov_obj__hand_msg_buffer(TrialHand2MovObjHandMsg* msg_buffer);

// Messaging through shared memory (separate programs) 
TrialHand2MovObjHandMsg* allocate_shm_server_trial_hand_2_mov_obj__hand_msg_buffer(TrialHand2MovObjHandMsg* msg_buffer);
TrialHand2MovObjHandMsg* allocate_shm_client_trial_hand_2_mov_obj__hand_msg_buffer(TrialHand2MovObjHandMsg* msg_buffer);
TrialHand2MovObjHandMsg* deallocate_shm_trial_hand_2_mov_obj__hand_msg_buffer(TrialHand2MovObjHandMsg* msg_buffer);
bool write_to_trial_hand_2_mov_obj__hand_msg_buffer(TrialHand2MovObjHandMsg* msg_buffer, TimeStamp msg_time, TrialHand2MovObjHandMsgType msg_type, TrialHand2MovObjHandMsgAdditional additional_data);
bool get_next_trial_hand_2_mov_obj__hand_msg_buffer_item(TrialHand2MovObjHandMsg* msg_buffer, TrialHand2MovObjHandMsgItem **msg_item);	// take care of static read_idx value //only request buffer handler uses

#endif
