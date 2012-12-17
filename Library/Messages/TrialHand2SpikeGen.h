#ifndef TRIAL_HAND_2_SPIKE_GEN_H
#define TRIAL_HAND_2_SPIKE_GEN_H

//  MESSAGES FROM TRIAL HANDLER TO SPIKE GENERATOR

typedef struct __TrialHand2SpikeGenMsg TrialHand2SpikeGenMsg;
typedef struct __TrialHand2SpikeGenMsgItem TrialHand2SpikeGenMsgItem;
typedef unsigned int TrialHand2SpikeGenMsgType;
typedef unsigned int TrialHand2SpikeGenMsgAdditional;


#define TRIAL_HAND_2_SPIKE_GEN_MSG_STRING_LENGTH						100

#define TRIAL_HAND_2_SPIKE_GEN_MSG_NULL									0
#define TRIAL_HAND_2_SPIKE_GEN_MSG_ARE_YOU_ALIVE						1
#define TRIAL_HAND_2_SPIKE_GEN_MSG_TRIAL_STATUS_CHANGED				2

#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>
#include <rtai_shm.h>
#include <rtai_nam2num.h>
#include "MessageBuffersConfig.h"
#include "../../../BlueSpike/System/ShmSemNum/ShmSemNum.h"
#include "../../../BlueSpike/System/TimeStamp/TimeStamp.h"
#include "../../../BlueSpike/Library/Misc/Misc.h"

struct __TrialHand2SpikeGenMsgItem
{
	TimeStamp 								msg_time;		
	TrialHand2SpikeGenMsgType				msg_type;
	TrialHand2SpikeGenMsgAdditional			additional_data_0;
	TrialHand2SpikeGenMsgAdditional			additional_data_1;
};

struct __TrialHand2SpikeGenMsg		// Requests to TrialControllers
{
	TrialHand2SpikeGenMsgItem		buff[TRIAL_HAND_2_SPIKE_GEN_MSG_BUFF_SIZE];
	unsigned int						buff_write_idx;	// only one message sender can write into this buffer and edit this write index
	unsigned int						buff_read_idx;	// only one request handler can edit this read index
};

bool get_trial_hand_2_spike_gen_msg_type_string(TrialHand2SpikeGenMsgType msg_type, char *str);

// Messaging through allocated memory (in same program) 
TrialHand2SpikeGenMsg* allocate_trial_hand_2_spike_gen_msg_buffer(TrialHand2SpikeGenMsg* msg_buffer);
TrialHand2SpikeGenMsg* deallocate_trial_hand_2_spike_gen_msg_buffer(TrialHand2SpikeGenMsg* msg_buffer);

// Messaging through shared memory (separate programs) 
TrialHand2SpikeGenMsg* allocate_shm_server_trial_hand_2_spike_gen_msg_buffer(TrialHand2SpikeGenMsg* msg_buffer);
TrialHand2SpikeGenMsg* allocate_shm_client_trial_hand_2_spike_gen_msg_buffer(TrialHand2SpikeGenMsg* msg_buffer);
TrialHand2SpikeGenMsg* deallocate_shm_trial_hand_2_spike_gen_msg_buffer(TrialHand2SpikeGenMsg* msg_buffer);
bool write_to_trial_hand_2_spike_gen_msg_buffer(TrialHand2SpikeGenMsg* msg_buffer, TimeStamp msg_time, TrialHand2SpikeGenMsgType msg_type, TrialHand2SpikeGenMsgAdditional additional_data_0, TrialHand2SpikeGenMsgAdditional additional_data_1);
bool get_next_trial_hand_2_spike_gen_msg_buffer_item(TrialHand2SpikeGenMsg* msg_buffer, TrialHand2SpikeGenMsgItem *msg_item);	// take care of static read_idx value //only request buffer handler uses

#endif
