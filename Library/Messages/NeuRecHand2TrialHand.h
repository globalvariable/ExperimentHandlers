#ifndef NEU_REC_HAND_2_TRIAL_HAND_H
#define NEU_REC_HAND_2_TRIAL_HAND_H

//  MESSAGES FROM NEURAL RECORDING HANDLER TO TRIAL HANDLER

typedef struct __NeuRecHand2TrialHandMsg NeuRecHand2TrialHandMsg;
typedef struct __NeuRecHand2TrialHandMsgItem NeuRecHand2TrialHandMsgItem;
typedef unsigned int NeuRecHand2TrialHandMsgType;
typedef unsigned int NeuRecHand2TrialHandMsgAdditional;


#define NEU_REC_HAND_2_TRIAL_HAND_MSG_STRING_LENGTH					100

#define NEU_REC_HAND_2_TRIAL_HAND_MSG_NULL								0
#define NEU_REC_HAND_2_TRIAL_HAND_MSG_I_AM_ALIVE						1



#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>
#include <rtai_shm.h>
#include <rtai_nam2num.h>
#include "MessageBuffersConfig.h"
#include "../../../BlueSpike/System/ShmSemNum/ShmSemNum.h"
#include "../../../BlueSpike/System/TimeStamp/TimeStamp.h"
#include "../../../BlueSpike/Library/Misc/Misc.h"

struct __NeuRecHand2TrialHandMsgItem
{
	TimeStamp 								msg_time;		
	NeuRecHand2TrialHandMsgType				msg_type;
	NeuRecHand2TrialHandMsgAdditional			additional_data;
};

struct __NeuRecHand2TrialHandMsg		// Requests to TrialControllers
{
	NeuRecHand2TrialHandMsgItem		buff[NEU_REC_HAND_2_TRIAL_HAND_MSG_BUFF_SIZE];
	unsigned int						buff_write_idx;	// only one message sender can write into this buffer and edit this write index
	unsigned int						buff_read_idx;	// only one request handler can edit this read index
};

bool get_neu_rec_hand_2_trial_hand_msg_type_string(NeuRecHand2TrialHandMsgType msg_type, char *str);

// Messaging through allocated memory (in same program) 
NeuRecHand2TrialHandMsg* allocate_neu_rec_hand_2_trial_hand_msg_buffer(NeuRecHand2TrialHandMsg* msg_buffer);
NeuRecHand2TrialHandMsg* deallocate_neu_rec_hand_2_trial_hand_msg_buffer(NeuRecHand2TrialHandMsg* msg_buffer);

// Messaging through shared memory (separate programs) 
NeuRecHand2TrialHandMsg* allocate_shm_server_neu_rec_hand_2_trial_hand_msg_buffer(NeuRecHand2TrialHandMsg* msg_buffer);
NeuRecHand2TrialHandMsg* allocate_shm_client_neu_rec_hand_2_trial_hand_msg_buffer(NeuRecHand2TrialHandMsg* msg_buffer);
NeuRecHand2TrialHandMsg* deallocate_shm_neu_rec_hand_2_trial_hand_msg_buffer(NeuRecHand2TrialHandMsg* msg_buffer);
bool write_to_neu_rec_hand_2_trial_hand_msg_buffer(NeuRecHand2TrialHandMsg* msg_buffer, TimeStamp msg_time, NeuRecHand2TrialHandMsgType msg_type, NeuRecHand2TrialHandMsgAdditional additional_data);
bool get_next_neu_rec_hand_2_trial_hand_msg_buffer_item(NeuRecHand2TrialHandMsg* msg_buffer, NeuRecHand2TrialHandMsgItem *msg_item);	// take care of static read_idx value //only request buffer handler uses



#endif
