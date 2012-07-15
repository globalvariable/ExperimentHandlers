#ifndef MOV_OBJ_HAND_2_NEURAL_NET_H
#define MOV_OBJ_HAND_2_NEURAL_NET_H

//  MESSAGES FROM MOV OBJ HANDLER TO NEURAL NET

typedef struct __MovObjHand2NeuralNetMsg MovObjHand2NeuralNetMsg;
typedef struct __MovObjHand2NeuralNetMsgItem MovObjHand2NeuralNetMsgItem;
typedef unsigned int MovObjHand2NeuralNetMsgType;
typedef unsigned int MovObjHand2NeuralNetMsgAdditional;


#define MOV_OBJ_HAND_2_NEURAL_NET_MSG_STRING_LENGTH						100

#define MOV_OBJ_HAND_2_NEURAL_NET_MSG_NULL								0
#define MOV_OBJ_HAND_2_NEURAL_NET_MSG_ARE_YOU_ALIVE						1



#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>
#include <rtai_shm.h>
#include <rtai_nam2num.h>
#include "MessageBuffersConfig.h"
#include "MessageBuffersSharedMem.h"
#include "../../../BlueSpike/TimeStamp.h"
#include "../../../BlueSpike/Library/Misc/Misc.h"

struct __MovObjHand2NeuralNetMsgItem
{
	TimeStamp 								msg_time;		
	MovObjHand2NeuralNetMsgType				msg_type;
	MovObjHand2NeuralNetMsgAdditional			additional_data;
};

struct __MovObjHand2NeuralNetMsg		// Requests to TrialControllers
{
	MovObjHand2NeuralNetMsgItem		buff[MOV_OBJ_HAND_2_NEURAL_NET_MSG_BUFF_SIZE];
	unsigned int						buff_write_idx;	// only one message sender can write into this buffer and edit this write index
	unsigned int						buff_read_idx;	// only one request handler can edit this read index
};

bool get_mov_obj_hand_2_neural_net_msg_type_string(MovObjHand2NeuralNetMsgType msg_type, char *str);

// Messaging through allocated memory (in same program) 
MovObjHand2NeuralNetMsg* allocate_mov_obj_hand_2_neural_net_msg_buffer(MovObjHand2NeuralNetMsg* msg_buffer);
MovObjHand2NeuralNetMsg* deallocate_mov_obj_hand_2_neural_net_msg_buffer(MovObjHand2NeuralNetMsg* msg_buffer);

// Messaging through shared memory (separate programs) 
MovObjHand2NeuralNetMsg* allocate_shm_server_mov_obj_hand_2_neural_net_msg_buffer(MovObjHand2NeuralNetMsg* msg_buffer);
MovObjHand2NeuralNetMsg* allocate_shm_client_mov_obj_hand_2_neural_net_msg_buffer(MovObjHand2NeuralNetMsg* msg_buffer);
MovObjHand2NeuralNetMsg* deallocate_shm_mov_obj_hand_2_neural_net_msg_buffer(MovObjHand2NeuralNetMsg* msg_buffer);
bool write_to_mov_obj_hand_2_neural_net_msg_buffer(MovObjHand2NeuralNetMsg* msg_buffer, TimeStamp msg_time, MovObjHand2NeuralNetMsgType msg_type, MovObjHand2NeuralNetMsgAdditional additional_data);
bool get_next_mov_obj_hand_2_neural_net_msg_buffer_item(MovObjHand2NeuralNetMsg* msg_buffer, MovObjHand2NeuralNetMsgItem *msg_item);	// take care of static read_idx value //only request buffer handler uses

#endif
