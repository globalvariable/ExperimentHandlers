#ifndef MOV_OBJ_HAND_2_TRIAL_HAND_H
#define MOV_OBJ_HAND_2_TRIAL_HAND_H

//  MESSAGES FROM EXP ENVI HANDLER TO TRIAL HANDLER

typedef struct __MovObjHand2TrialHandMsg MovObjHand2TrialHandMsg;
typedef struct __MovObjHand2TrialHandMsgItem MovObjHand2TrialHandMsgItem;
typedef unsigned int MovObjHand2TrialHandMsgType;
typedef double MovObjHand2TrialHandMsgAdditional;


#define MOV_OBJ_HAND_2_TRIAL_HAND_MSG_STRING_LENGTH					100

#define MOV_OBJ_HAND_2_TRIAL_HAND_MSG_NULL								0
#define MOV_OBJ_HAND_2_TRIAL_HAND_MSG_I_AM_ALIVE						1
#define MOV_OBJ_HAND_2_TRIAL_HAND_MSG_REWARD_REQUEST				2		// sends it out when the robot reached the threshold point.
#define MOV_OBJ_HAND_2_TRIAL_HAND_MSG_PUNISHMENT_REQUEST			3		// sends it out when the robot reached the threshold point.
#define MOV_OBJ_HAND_2_TRIAL_HAND_MSG_END_TRIAL_REQUEST				4		// sends it out when the timeout after reaching to target appears
#define MOV_OBJ_HAND_2_TRIAL_HAND_MSG_MOV_OBJ_CONTROL_ENABLED		5		// sends it out when the timeout after staying at start point appears.
#define MOV_OBJ_HAND_2_TRIAL_HAND_MSG_MOV_OBJ_INITIAL_DIST_2_TARGET	6		// sends it out when the timeout after staying at start point appears.
#define MOV_OBJ_HAND_2_TRIAL_HAND_MSG_REACHED_2_TARGET				7		// sends it out by the time mov obj reaches the target
#define MOV_OBJ_HAND_2_TRIAL_HAND_MSG_OUT_OF_ROBOT_SPACE			8
#define MOV_OBJ_HAND_2_TRIAL_HAND_MSG_REACHED_2_LEVER_PRESS		9		// sends it out by the time mov obj reaches the target
#define MOV_OBJ_HAND_2_TRIAL_HAND_MSG_REACHED_2_REWARD_THRES		10
#define MOV_OBJ_HAND_2_TRIAL_HAND_MSG_REACHED_2_THRESHOLD			11
#define MOV_OBJ_HAND_2_TRIAL_HAND_MSG_REACHED_2_THRESHOLD_2		12

#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>
#include <rtai_shm.h>
#include <rtai_nam2num.h>
#include "MessageBuffersConfig.h"
#include "../../../BlueSpike/System/ShmSemNum/ShmSemNum.h"
#include "../../../BlueSpike/System/TimeStamp/TimeStamp.h"
#include "../../../BlueSpike/Library/Misc/Misc.h"

struct __MovObjHand2TrialHandMsgItem
{
	TimeStamp 								msg_time;		
	MovObjHand2TrialHandMsgType				msg_type;
	MovObjHand2TrialHandMsgAdditional			additional_data;
};

struct __MovObjHand2TrialHandMsg		// Requests to TrialControllers
{
	MovObjHand2TrialHandMsgItem		buff[MOV_OBJ_HAND_2_TRIAL_HAND_MSG_BUFF_SIZE];
	unsigned int						buff_write_idx;	// only one message sender can write into this buffer and edit this write index
	unsigned int						buff_read_idx;	// only one request handler can edit this read index
};

bool get_mov_obj_hand_2_trial_hand_msg_type_string(MovObjHand2TrialHandMsgType msg_type, char *str);

// Messaging through allocated memory (in same program) 
MovObjHand2TrialHandMsg* allocate_mov_obj_hand_2_trial_hand_msg_buffer(MovObjHand2TrialHandMsg* msg_buffer);
MovObjHand2TrialHandMsg* deallocate_mov_obj_hand_2_trial_hand_msg_buffer(MovObjHand2TrialHandMsg* msg_buffer);

// Messaging through shared memory (separate programs) 
MovObjHand2TrialHandMsg* allocate_shm_server_mov_obj_hand_2_trial_hand_msg_buffer(MovObjHand2TrialHandMsg* msg_buffer);
MovObjHand2TrialHandMsg* allocate_shm_client_mov_obj_hand_2_trial_hand_msg_buffer(MovObjHand2TrialHandMsg* msg_buffer);
MovObjHand2TrialHandMsg* deallocate_shm_mov_obj_hand_2_trial_hand_msg_buffer(MovObjHand2TrialHandMsg* msg_buffer);
bool write_to_mov_obj_hand_2_trial_hand_msg_buffer(MovObjHand2TrialHandMsg* msg_buffer, TimeStamp msg_time, MovObjHand2TrialHandMsgType msg_type, MovObjHand2TrialHandMsgAdditional additional_data);
bool get_next_mov_obj_hand_2_trial_hand_msg_buffer_item(MovObjHand2TrialHandMsg* msg_buffer, MovObjHand2TrialHandMsgItem *msg_item);	// take care of static read_idx value //only request buffer handler uses

#endif
