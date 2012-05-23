#ifndef TRIAL_HAND_2_NEURAL_NET_H
#define TRIAL_HAND_2_NEURAL_NET_H

//  MESSAGES FROM MOV OBJ HANDLER TO NEURAL NET

typedef struct __TrialHand2NeuralNetMsg TrialHand2NeuralNetMsg;
typedef struct __TrialHand2NeuralNetMsgItem TrialHand2NeuralNetMsgItem;
typedef unsigned int TrialHand2NeuralNetMsgType;
typedef unsigned int TrialHand2NeuralNetMsgAdditional;


#define TRIAL_HAND_2_NEURAL_NET_MSG_STRING_LENGTH						100

#define TRIAL_HAND_2_NEURAL_NET_MSG_NULL								0
#define TRIAL_HAND_2_NEURAL_NET_MSG_ARE_YOU_ALIVE						1



#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>
#include <rtai_shm.h>
#include <rtai_nam2num.h>
#include "MessageBuffersConfig.h"
#include "MessageBuffersSharedMem.h"
#include "../../../BlueSpike/TimeStamp.h"
#include "../../../BlueSpike/Library/Misc/Misc.h"

struct __TrialHand2NeuralNetMsgItem
{
	TimeStamp 								msg_time;		
	TrialHand2NeuralNetMsgType				msg_type;
	TrialHand2NeuralNetMsgAdditional			additional_data;
};

struct __TrialHand2NeuralNetMsg		// Requests to TrialControllers
{
	TrialHand2NeuralNetMsgItem		buff[TRIAL_HAND_2_NEURAL_NET_MSG_BUFF_SIZE];
	unsigned int						buff_write_idx;	// only one message sender can write into this buffer and edit this write index
	unsigned int						buff_read_idx;	// only one request handler can edit this read index
};

bool get_trial_hand_2_neural_net_msg_type_string(TrialHand2NeuralNetMsgType msg_type, char *str);

// Messaging through allocated memory (in same program) 
TrialHand2NeuralNetMsg* allocate_trial_hand_2_neural_net_msg_buffer(TrialHand2NeuralNetMsg* msg_buffer);
TrialHand2NeuralNetMsg* deallocate_trial_hand_2_neural_net_msg_buffer(TrialHand2NeuralNetMsg* msg_buffer);

// Messaging through shared memory (separate programs) 
TrialHand2NeuralNetMsg* allocate_shm_server_trial_hand_2_neural_net_msg_buffer(TrialHand2NeuralNetMsg* msg_buffer);
TrialHand2NeuralNetMsg* allocate_shm_client_trial_hand_2_neural_net_msg_buffer(TrialHand2NeuralNetMsg* msg_buffer);
TrialHand2NeuralNetMsg* deallocate_shm_trial_hand_2_neural_net_msg_buffer(TrialHand2NeuralNetMsg* msg_buffer);
bool write_to_trial_hand_2_neural_net_msg_buffer(TrialHand2NeuralNetMsg* msg_buffer, TimeStamp msg_time, TrialHand2NeuralNetMsgType msg_type, TrialHand2NeuralNetMsgAdditional additional_data);
bool get_next_trial_hand_2_neural_net_msg_buffer_item(TrialHand2NeuralNetMsg* msg_buffer, TrialHand2NeuralNetMsgItem **msg_item);	// take care of static read_idx value //only request buffer handler uses

#endif
