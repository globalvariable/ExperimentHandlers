#ifndef NEURAL_NET_2_TRIAL_HAND_H
#define NEURAL_NET_2_TRIAL_HAND_H

//  MESSAGES FROM NEURAL NET TO TRIAL HANDLER

typedef struct __NeuralNet2TrialHandMsg NeuralNet2TrialHandMsg;
typedef struct __NeuralNet2TrialHandMsgItem NeuralNet2TrialHandMsgItem;
typedef unsigned int NeuralNet2TrialHandMsgType;
typedef unsigned int NeuralNet2TrialHandMsgAdditional;

#define NEURAL_NET_2_TRIAL_HAND_MSG_STRING_LENGTH					100

#define NEURAL_NET_2_TRIAL_HAND_MSG_NULL							0
#define NEURAL_NET_2_TRIAL_HAND_MSG_I_AM_ALIVE						1



#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>
#include <rtai_shm.h>
#include <rtai_nam2num.h>
#include "MessageBuffersConfig.h"
#include "MessageBuffersSharedMem.h"
#include "../../../BlueSpike/TimeStamp.h"
#include "../../../BlueSpike/Library/Misc/Misc.h"

struct __NeuralNet2TrialHandMsgItem
{
	TimeStamp 								msg_time;		
	NeuralNet2TrialHandMsgType				msg_type;
	NeuralNet2TrialHandMsgAdditional			additional_data;
};

struct __NeuralNet2TrialHandMsg		// Requests to TrialControllers
{
	NeuralNet2TrialHandMsgItem		buff[NEURAL_NET_2_TRIAL_HAND_MSG_BUFF_SIZE];
	unsigned int						buff_write_idx;	// only one message sender can write into this buffer and edit this write index
	unsigned int						buff_read_idx;	// only one request handler can edit this read index
};

bool get_neural_net_2_trial_hand_msg_type_string(NeuralNet2TrialHandMsgType msg_type, char *str);

// Messaging through allocated memory (in same program) 
NeuralNet2TrialHandMsg* allocate_neural_net_2_trial_hand_msg_buffer(NeuralNet2TrialHandMsg* msg_buffer);
NeuralNet2TrialHandMsg* deallocate_neural_net_2_trial_hand_msg_buffer(NeuralNet2TrialHandMsg* msg_buffer);

// Messaging through shared memory (separate programs) 
NeuralNet2TrialHandMsg* allocate_shm_server_neural_net_2_trial_hand_msg_buffer(NeuralNet2TrialHandMsg* msg_buffer);
NeuralNet2TrialHandMsg* allocate_shm_client_neural_net_2_trial_hand_msg_buffer(NeuralNet2TrialHandMsg* msg_buffer);
NeuralNet2TrialHandMsg* deallocate_shm_neural_net_2_trial_hand_msg_buffer(NeuralNet2TrialHandMsg* msg_buffer);
bool write_to_neural_net_2_trial_hand_msg_buffer(NeuralNet2TrialHandMsg* msg_buffer, TimeStamp msg_time, NeuralNet2TrialHandMsgType msg_type,  NeuralNet2TrialHandMsgAdditional additional_data);
bool get_next_neural_net_2_trial_hand_msg_buffer_item(NeuralNet2TrialHandMsg* msg_buffer, NeuralNet2TrialHandMsgItem **msg_item);	// take care of static read_idx value //only request buffer handler uses

#endif
