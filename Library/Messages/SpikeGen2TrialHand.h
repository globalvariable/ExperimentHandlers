#ifndef SPIKE_GEN_2_TRIAL_HAND_H
#define SPIKE_GEN_2_TRIAL_HAND_H

//  MESSAGES FROM SPIKE GENERATOR TO TRIAL HANDLER

typedef struct __SpikeGen2TrialHandMsg SpikeGen2TrialHandMsg;
typedef struct __SpikeGen2TrialHandMsgItem SpikeGen2TrialHandMsgItem;
typedef unsigned int SpikeGen2TrialHandMsgType;
typedef unsigned int SpikeGen2TrialHandMsgAdditional;

#define SPIKE_GEN_2_TRIAL_HAND_MSG_STRING_LENGTH					100

#define SPIKE_GEN_2_TRIAL_HAND_MSG_NULL							0
#define SPIKE_GEN_2_TRIAL_HAND_MSG_I_AM_ALIVE						1



#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>
#include <rtai_shm.h>
#include <rtai_nam2num.h>
#include "MessageBuffersConfig.h"
#include "MessageBuffersSharedMem.h"
#include "../../../BlueSpike/TimeStamp.h"
#include "../../../BlueSpike/Library/Misc/Misc.h"

struct __SpikeGen2TrialHandMsgItem
{
	TimeStamp 								msg_time;		
	SpikeGen2TrialHandMsgType				msg_type;
	SpikeGen2TrialHandMsgAdditional			additional_data;
};

struct __SpikeGen2TrialHandMsg		// Requests to TrialControllers
{
	SpikeGen2TrialHandMsgItem		buff[SPIKE_GEN_2_TRIAL_HAND_MSG_BUFF_SIZE];
	unsigned int						buff_write_idx;	// only one message sender can write into this buffer and edit this write index
	unsigned int						buff_read_idx;	// only one request handler can edit this read index
};

bool get_spike_gen_2_trial_hand_msg_type_string(SpikeGen2TrialHandMsgType msg_type, char *str);

// Messaging through allocated memory (in same program) 
SpikeGen2TrialHandMsg* allocate_spike_gen_2_trial_hand_msg_buffer(SpikeGen2TrialHandMsg* msg_buffer);
SpikeGen2TrialHandMsg* deallocate_spike_gen_2_trial_hand_msg_buffer(SpikeGen2TrialHandMsg* msg_buffer);

// Messaging through shared memory (separate programs) 
SpikeGen2TrialHandMsg* allocate_shm_server_spike_gen_2_trial_hand_msg_buffer(SpikeGen2TrialHandMsg* msg_buffer);
SpikeGen2TrialHandMsg* allocate_shm_client_spike_gen_2_trial_hand_msg_buffer(SpikeGen2TrialHandMsg* msg_buffer);
SpikeGen2TrialHandMsg* deallocate_shm_spike_gen_2_trial_hand_msg_buffer(SpikeGen2TrialHandMsg* msg_buffer);
bool write_to_spike_gen_2_trial_hand_msg_buffer(SpikeGen2TrialHandMsg* msg_buffer, TimeStamp msg_time, SpikeGen2TrialHandMsgType msg_type,  SpikeGen2TrialHandMsgAdditional additional_data);
bool get_next_spike_gen_2_trial_hand_msg_buffer_item(SpikeGen2TrialHandMsg* msg_buffer, SpikeGen2TrialHandMsgItem **msg_item);	// take care of static read_idx value //only request buffer handler uses

#endif
