#ifndef TRIAL_HAND_2_TRIAL_DUR_HAND_H
#define TRIAL_HAND_2_TRIAL_DUR_HAND_H

//  MESSAGES FROM TRIAL HANDLER TO TRIAL DURATION HANDLER

#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>
#include "MessageBuffersConfig.h"
#include "../../../BlueSpike/TimeStamp.h"
#include "../../../BlueSpike/Library/Misc/Misc.h"


typedef struct __TrialHand2TrialDurHandMsg TrialHand2TrialDurHandMsg;
typedef struct __TrialHand2TrialDurHandMsgItem TrialHand2TrialDurHandMsgItem;
typedef unsigned int TrialHand2TrialDurHandMsgType;
typedef TimeStamp TrialHand2TrialDurHandMsgAdditional;


#define TRIAL_HAND_2_TRIAL_DUR_HAND_MSG_STRING_LENGTH					100

#define TRIAL_HAND_2_TRIAL_DUR_HAND_MSG_NULL							0
#define TRIAL_HAND_2_TRIAL_DUR_HAND_MSG_ENABLE_DURATION_HANDLING	1
#define TRIAL_HAND_2_TRIAL_DUR_HAND_MSG_DISABLE_DURATION_HANDLING	2  // When a phase of trial is complete, trial handler sends this to trial duration handler to cancel timer.
 




struct __TrialHand2TrialDurHandMsgItem
{
	TimeStamp 								msg_time;		
	TrialHand2TrialDurHandMsgType				msg_type;
	TrialHand2TrialDurHandMsgAdditional			additional_data;
};

struct __TrialHand2TrialDurHandMsg		// Requests to TrialControllers
{
	TrialHand2TrialDurHandMsgItem		buff[TRIAL_HAND_2_TRIAL_DUR_HAND_MSG_BUFF_SIZE];
	unsigned int						buff_write_idx;	// only one message sender can write into this buffer and edit this write index
	unsigned int						buff_read_idx;	// only one request handler can edit this read index
};

bool get_trial_hand_2_trial_dur_hand_msg_type_string(TrialHand2TrialDurHandMsgType msg_type, char *str);

// Messaging through allocated memory (in same program) 
TrialHand2TrialDurHandMsg* allocate_trial_hand_2_trial_dur_hand_msg_buffer(TrialHand2TrialDurHandMsg* msg_buffer);
TrialHand2TrialDurHandMsg* deallocate_trial_hand_2_trial_dur_hand_msg_buffer(TrialHand2TrialDurHandMsg* msg_buffer);
bool write_to_trial_hand_2_trial_dur_hand_msg_buffer(TrialHand2TrialDurHandMsg* msg_buffer, TimeStamp msg_time, TrialHand2TrialDurHandMsgType msg_type, TrialHand2TrialDurHandMsgAdditional additional_data);
bool get_next_trial_hand_2_trial_dur_hand_msg_buffer_item(TrialHand2TrialDurHandMsg* msg_buffer, TrialHand2TrialDurHandMsgItem *msg_item);	// take care of static read_idx value //only request buffer handler uses

#endif
