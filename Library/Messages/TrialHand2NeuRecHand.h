#ifndef TRIAL_HAND_2_NEU_REC_HAND_H
#define TRIAL_HAND_2_NEU_REC_HAND_H

//  MESSAGES FROM TRIAL HANDLER TO NEURAL RECORDING HANDLER

typedef struct __TrialHand2NeuRecHandMsg TrialHand2NeuRecHandMsg;
typedef struct __TrialHand2NeuRecHandMsgItem TrialHand2NeuRecHandMsgItem;
typedef unsigned int TrialHand2NeuRecHandMsgType;
typedef unsigned int TrialHand2NeuRecHandMsgAdditional;


#define TRIAL_HAND_2_NEU_REC_HAND_MSG_STRING_LENGTH						100

#define TRIAL_HAND_2_NEU_REC_HAND_MSG_NULL									0
#define TRIAL_HAND_2_NEU_REC_HAND_MSG_ARE_YOU_ALIVE						1
#define TRIAL_HAND_2_NEU_REC_HAND_MSG_START_RECORDING					2
#define TRIAL_HAND_2_NEU_REC_HAND_MSG_STOP_RECORDING					3
#define TRIAL_HAND_2_NEU_REC_HAND_MSG_CANCEL_RECORDING					4    		// sent to cancel current recording
	

#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>
#include <rtai_shm.h>
#include <rtai_nam2num.h>
#include "MessageBuffersConfig.h"
#include "../../../BlueSpike/System/ShmSemNum/ShmSemNum.h"
#include "../../../BlueSpike/System/TimeStamp/TimeStamp.h"
#include "../../../BlueSpike/Library/Misc/Misc.h"

struct __TrialHand2NeuRecHandMsgItem
{
	TimeStamp 								msg_time;		
	TrialHand2NeuRecHandMsgType				msg_type;
	TrialHand2NeuRecHandMsgAdditional			additional_data;
};

struct __TrialHand2NeuRecHandMsg		// Requests to TrialControllers
{
	TrialHand2NeuRecHandMsgItem		buff[TRIAL_HAND_2_NEU_REC_HAND_MSG_BUFF_SIZE];
	unsigned int						buff_write_idx;	// only one message sender can write into this buffer and edit this write index
	unsigned int						buff_read_idx;	// only one request handler can edit this read index
};

bool get_trial_hand_2_neu_rec_hand_msg_type_string(TrialHand2NeuRecHandMsgType msg_type, char *str);

// Messaging through allocated memory (in same program) 
TrialHand2NeuRecHandMsg* allocate_trial_hand_2_neu_rec_hand_msg_buffer(TrialHand2NeuRecHandMsg* msg_buffer);
TrialHand2NeuRecHandMsg* deallocate_trial_hand_2_neu_rec_hand_msg_buffer(TrialHand2NeuRecHandMsg* msg_buffer);

// Messaging through shared memory (separate programs) 
TrialHand2NeuRecHandMsg* allocate_shm_server_trial_hand_2_neu_rec_hand_msg_buffer(TrialHand2NeuRecHandMsg* msg_buffer);
TrialHand2NeuRecHandMsg* allocate_shm_client_trial_hand_2_neu_rec_hand_msg_buffer(TrialHand2NeuRecHandMsg* msg_buffer);
TrialHand2NeuRecHandMsg* deallocate_shm_trial_hand_2_neu_rec_hand_msg_buffer(TrialHand2NeuRecHandMsg* msg_buffer);
bool write_to_trial_hand_2_neu_rec_hand_msg_buffer(TrialHand2NeuRecHandMsg* msg_buffer, TimeStamp msg_time, TrialHand2NeuRecHandMsgType msg_type, TrialHand2NeuRecHandMsgAdditional additional_data);
bool get_next_trial_hand_2_neu_rec_hand_msg_buffer_item(TrialHand2NeuRecHandMsg* msg_buffer, TrialHand2NeuRecHandMsgItem *msg_item);	// take care of static read_idx value //only request buffer handler uses

#endif


