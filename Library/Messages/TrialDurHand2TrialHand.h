#ifndef TRIAL_DUR_HAND_2_TRIAL_HAND_H
#define TRIAL_DUR_HAND_2_TRIAL_HAND_H

//  MESSAGES FROM TRIAL DURATION HANDLER TO TRIAL HANDLER

typedef struct __TrialDurHand2TrialHandMsg TrialDurHand2TrialHandMsg;
typedef struct __TrialDurHand2TrialHandMsgItem TrialDurHand2TrialHandMsgItem;
typedef unsigned int TrialDurHand2TrialHandMsgType;
typedef unsigned int TrialDurHand2TrialHandMsgAdditional;


#define TRIAL_DUR_HAND_2_TRIAL_HAND_MSG_STRING_LENGTH					100

#define TRIAL_DUR_HAND_2_TRIAL_HAND_MSG_NULL							0
#define TRIAL_DUR_HAND_2_TRIAL_HAND_MSG_TIMEOUT						1
#define TRIAL_DUR_HAND_2_TRIAL_HAND_MSG_EMERGENCY_EXIT				2




#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>
#include "MessageBuffersConfig.h"
#include "../../../BlueSpike/System/TimeStamp/TimeStamp.h"
#include "../../../BlueSpike/Library/Misc/Misc.h"

struct __TrialDurHand2TrialHandMsgItem
{
	TimeStamp 								msg_time;		
	TrialDurHand2TrialHandMsgType				msg_type;
	TrialDurHand2TrialHandMsgAdditional			additional_data;
};

struct __TrialDurHand2TrialHandMsg		// Requests to TrialControllers
{
	TrialDurHand2TrialHandMsgItem		buff[TRIAL_DUR_HAND_2_TRIAL_HAND_MSG_BUFF_SIZE];
	unsigned int						buff_write_idx;	// only one message sender can write into this buffer and edit this write index
	unsigned int						buff_read_idx;	// only one request handler can edit this read index
};

bool get_trial_dur_hand_2_trial_hand_msg_type_string(TrialDurHand2TrialHandMsgType msg_type, char *str);

// Messaging through allocated memory (in same program) 
TrialDurHand2TrialHandMsg* allocate_trial_dur_hand_2_trial_hand_msg_buffer(TrialDurHand2TrialHandMsg* msg_buffer);
TrialDurHand2TrialHandMsg* deallocate_trial_dur_hand_2_trial_hand_msg_buffer(TrialDurHand2TrialHandMsg* msg_buffer);
bool write_to_trial_dur_hand_2_trial_hand_msg_buffer(TrialDurHand2TrialHandMsg* msg_buffer, TimeStamp msg_time, TrialDurHand2TrialHandMsgType msg_type, TrialDurHand2TrialHandMsgAdditional additional_data);
bool get_next_trial_dur_hand_2_trial_hand_msg_buffer_item(TrialDurHand2TrialHandMsg* msg_buffer, TrialDurHand2TrialHandMsgItem *msg_item);	// take care of static read_idx value //only request buffer handler uses

#endif
