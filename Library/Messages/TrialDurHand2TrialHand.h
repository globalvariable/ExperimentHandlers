#ifndef TRIAL_DUR_HAND_2_TRIAL_HAND_H
#define TRIAL_DUR_HAND_2_TRIAL_HAND_H

//  MESSAGES FROM TRIAL DURATION HANDLER TO TRIAL HANDLER

typedef struct __TrialDurHand2TrialHandMsg TrialDurHand2TrialHandMsg;
typedef struct __TrialDurHand2TrialHandMsgItem TrialDurHand2TrialHandMsgItem;
typedef unsigned int TrialDurHand2TrialHandMsgType;
typedef unsigned int TrialDurHand2TrialHandMsgAdditional;


#define TRIAL_DUR_HAND_2_TRIAL_HAND_MSG_STRING_LENTGH		20

#define TRIAL_DUR_HAND_2_TRIAL_HAND_MSG_NULL							0
#define TRIAL_DUR_HAND_2_TRIAL_HAND_MSG_ENABLE_TRIAL_HANDLING		1
#define TRIAL_DUR_HAND_2_TRIAL_HAND_MSG_DISABLE_TRIAL_HANDLING		2


#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>
#include "MessageBuffersConfig.h"
#include "../../../BlueSpike/TimeStamp.h"

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

/*
bool get_trial_dur_hand_2_trial_hand_msg_type_string(Gui2TrialHandMsgType msg_type, char *str);

// Messaging through shared memory
TrialDurHand2TrialHandMsg* allocate_shm_server_trial_dur_hand_2_trial_hand_msg_buffer(TrialDurHand2TrialHandMsg* msg_buff);
TrialDurHand2TrialHandMsg* allocate_shm_client_trial_dur_hand_2_trial_hand_msg_buffer(TrialDurHand2TrialHandMsg* msg_buff);
TrialDurHand2TrialHandMsg* deallocate_shm_trial_dur_hand_2_trial_hand_msg_buffer(TrialDurHand2TrialHandMsg* msg_buff);
bool shm_write_to_trial_dur_hand_2_trial_hand_msg_buffer(Gui2TrialHandMsg* msg_buffer, TimeStamp msg_time, Gui2TrialHandMsgType msg_type, Gui2TrialHandMsgAdditional additional_data);
bool shm_get_next_trial_dur_hand_2_trial_hand_msg_buffer_item(Gui2TrialHandMsg* msg_buffer, Gui2TrialHandMsgItem **msg_item);	// take care of static read_idx value //only request buffer handler uses
*/
// Messaging through socket

#endif
