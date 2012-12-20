#ifndef TRIAL_HAND_2_MOV_OBJ_HAND_H
#define TRIAL_HAND_2_MOV_OBJ_HAND_H

//  MESSAGES FROM TRIAL HANDLER TO MOV OBJ HANDLER

#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>
#include <rtai_shm.h>
#include <rtai_nam2num.h>
#include "MessageBuffersConfig.h"
#include "../../../BlueSpike/System/ShmSemNum/ShmSemNum.h"
#include "../../../BlueSpike/System/TimeStamp/TimeStamp.h"
#include "../../../BlueSpike/Library/Misc/Misc.h"
#include "../Robot/ThreeDofRobot.h"

typedef struct __TrialHand2MovObjHandMsg TrialHand2MovObjHandMsg;
typedef struct __TrialHand2MovObjHandMsgItem TrialHand2MovObjHandMsgItem;
typedef unsigned int TrialHand2MovObjHandMsgType;

typedef union 
{
	ThreeDofRobotServoPulse	move_to_target_position_pulse;
	bool	dummy;
}
TrialHand2MovObjHandMsgAdditional;

#define TRIAL_HAND_2_MOV_OBJ_HAND_MSG_STRING_LENGTH					100

#define TRIAL_HAND_2_MOV_OBJ_HAND_MSG_NULL							0
#define TRIAL_HAND_2_MOV_OBJ_HAND_MSG_ARE_YOU_ALIVE				1
#define TRIAL_HAND_2_MOV_OBJ_HAND_MSG_START_TRIAL					2		// send trial type as additional
#define TRIAL_HAND_2_MOV_OBJ_HAND_MSG_TRIAL_TIMEOUT				3		
#define TRIAL_HAND_2_MOV_OBJ_HAND_MSG_END_TRIAL					4

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
TrialHand2MovObjHandMsg* allocate_trial_hand_2_mov_obj_hand_msg_buffer(TrialHand2MovObjHandMsg* msg_buffer);
TrialHand2MovObjHandMsg* deallocate_trial_hand_2_mov_obj_hand_msg_buffer(TrialHand2MovObjHandMsg* msg_buffer);

// Messaging through shared memory (separate programs) 
TrialHand2MovObjHandMsg* allocate_shm_server_trial_hand_2_mov_obj_hand_msg_buffer(TrialHand2MovObjHandMsg* msg_buffer);
TrialHand2MovObjHandMsg* allocate_shm_client_trial_hand_2_mov_obj_hand_msg_buffer(TrialHand2MovObjHandMsg* msg_buffer);
TrialHand2MovObjHandMsg* deallocate_shm_trial_hand_2_mov_obj_hand_msg_buffer(TrialHand2MovObjHandMsg* msg_buffer);
bool write_to_trial_hand_2_mov_obj_hand_msg_buffer(TrialHand2MovObjHandMsg* msg_buffer, TimeStamp msg_time, TrialHand2MovObjHandMsgType msg_type, TrialHand2MovObjHandMsgAdditional additional_data);
bool get_next_trial_hand_2_mov_obj_hand_msg_buffer_item(TrialHand2MovObjHandMsg* msg_buffer, TrialHand2MovObjHandMsgItem *msg_item);	// take care of static read_idx value //only request buffer handler uses

#endif
