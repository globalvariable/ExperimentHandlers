#ifndef NEURAL_NET_2_POST_TRIAL_HAND_H
#define NEURAL_NET_2_POST_TRIAL_HAND_H

//  MESSAGES FROM NEURAL NET TO POST TRIAL HANDLER

typedef struct __NeuralNet2PostTrialHandMsg NeuralNet2PostTrialHandMsg;
typedef struct __NeuralNet2PostTrialHandMsgItem NeuralNet2PostTrialHandMsgItem;
typedef unsigned int NeuralNet2PostTrialHandMsgType;
typedef double NeuralNet2PostTrialHandMsgAdditional;

#define NEURAL_NET_2_POST_TRIAL_HAND_MSG_STRING_LENGTH					100

#define NEURAL_NET_2_POST_TRIAL_HAND_MSG_NULL							0
#define NEURAL_NET_2_POST_TRIAL_HAND_MSG_I_AM_ALIVE						1
#define NEURAL_NET_2_POST_TRIAL_HAND_MSG_TRIAL_END						2


#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>
#include <rtai_shm.h>
#include <rtai_nam2num.h>
#include "MessageBuffersConfig.h"
#include "../../../BlueSpike/System/TimeStamp/TimeStamp.h"
#include "../../../BlueSpike/Library/Misc/Misc.h"

struct __NeuralNet2PostTrialHandMsgItem
{
	TimeStamp 								msg_time;		
	NeuralNet2PostTrialHandMsgType				msg_type;
	NeuralNet2PostTrialHandMsgAdditional			additional_data;		// such as reward magnitude
};

struct __NeuralNet2PostTrialHandMsg		// Requests to TrialControllers
{
	NeuralNet2PostTrialHandMsgItem		buff[NEURAL_NET_2_POST_TRIAL_HAND_MSG_BUFF_SIZE];
	unsigned int						buff_write_idx;	// only one message sender can write into this buffer and edit this write index
	unsigned int						buff_read_idx;	// only one request handler can edit this read index
};

bool get_neural_net_2_post_trial_hand_msg_type_string(NeuralNet2PostTrialHandMsgType msg_type, char *str);

// Messaging through allocated memory (in same program) 
NeuralNet2PostTrialHandMsg* allocate_neural_net_2_post_trial_hand_msg_buffer(NeuralNet2PostTrialHandMsg* msg_buffer);
NeuralNet2PostTrialHandMsg* deallocate_neural_net_2_post_trial_hand_msg_buffer(NeuralNet2PostTrialHandMsg* msg_buffer);
bool write_to_neural_net_2_post_trial_hand_msg_buffer(NeuralNet2PostTrialHandMsg* msg_buffer, TimeStamp msg_time, NeuralNet2PostTrialHandMsgType msg_type,  NeuralNet2PostTrialHandMsgAdditional additional_data);
bool get_next_neural_net_2_post_trial_hand_msg_buffer_item(NeuralNet2PostTrialHandMsg* msg_buffer, NeuralNet2PostTrialHandMsgItem *msg_item);	// take care of static read_idx value //only request buffer handler uses

#endif
