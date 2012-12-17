#ifndef NEURAL_NET_2_MOV_OBJ_HAND_H
#define NEURAL_NET_2_MOV_OBJ_HAND_H

#define NUM_OF_NEURAL_NET_2_MOV_OBJ_HAND_MSG_BUFFERS IZ_PS_NETWORK_SIM_NUM_OF_DEDICATED_CPUS*MAX_NUM_OF_CPU_THREADS_PER_CPU

//  MESSAGES FROM NEURAL NET TO MOV OBJ HANDLER

typedef struct __NeuralNet2MovObjHandMsg NeuralNet2MovObjHandMsg;
typedef struct __NeuralNet2MovObjHandMsgItem NeuralNet2MovObjHandMsgItem;
typedef unsigned int NeuralNet2MovObjHandMsgType;
#include "../../../BlueSpike/System/RtTasksData/RtTasksData.h"
#include "../../../BlueSpike/System/ShmSemNum/ShmSemNum.h"
typedef NeuralNet2MovObjHandMsg *NeuralNet2MovObjHandMsgPtr;
typedef NeuralNet2MovObjHandMsgPtr NeuralNet2MovObjHandMsgMultiThread[NUM_OF_NEURAL_NET_2_MOV_OBJ_HAND_MSG_BUFFERS];



#define NEURAL_NET_2_MOV_OBJ_HAND_MSG_STRING_LENGTH					100

#define NEURAL_NET_2_MOV_OBJ_HAND_MSG_NULL							0
#define NEURAL_NET_2_MOV_OBJ_HAND_MSG_I_AM_ALIVE						1
#define NEURAL_NET_2_MOV_OBJ_HAND_MSG_SPIKE_OUTPUT					2

#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>
#include <rtai_shm.h>
#include <rtai_nam2num.h>
#include "MessageBuffersConfig.h"
#include "../../../BlueSpike/System/TimeStamp/TimeStamp.h"
#include "../../../BlueSpike/Library/Misc/Misc.h"
#include "../MovObjData/MovObjComponentTypes.h"
#include "../MovObjData/MovObjDirectionTypes.h"
#include "../MovObjData/MovObjSpeedType.h"
#include "../MovObjData/MovObjLocationType.h"

struct __NeuralNet2MovObjHandMsgItem
{
	TimeStamp 					msg_time;		
	NeuralNet2MovObjHandMsgType	msg_type;
	unsigned int					layer_num;
	unsigned int					nrn_grp_num;
	unsigned int					neuron_num;
	TimeStamp 					spike_time;		
};

struct __NeuralNet2MovObjHandMsg		// Requests to TrialControllers
{
	NeuralNet2MovObjHandMsgItem	buff[NEURAL_NET_2_MOV_OBJ_HAND_MSG_BUFF_SIZE];
	unsigned int					buff_write_idx;	// only one message sender can write into this buffer and edit this write index
	unsigned int					buff_read_idx;	// only one request handler can edit this read index
};

bool get_neural_net_2_mov_obj_hand_msg_type_string(NeuralNet2MovObjHandMsgType msg_type, char *str);

// Messaging through allocated memory (in same program) 
NeuralNet2MovObjHandMsg* allocate_neural_net_2_mov_obj_hand_msg_buffer(NeuralNet2MovObjHandMsg* msg_buffer);
NeuralNet2MovObjHandMsg* deallocate_neural_net_2_mov_obj_hand_msg_buffer(NeuralNet2MovObjHandMsg* msg_buffer);

// Messaging through shared memory (separate programs) 
NeuralNet2MovObjHandMsg* allocate_shm_server_neural_net_2_mov_obj_hand_msg_buffer(NeuralNet2MovObjHandMsg* msg_buffer);
NeuralNet2MovObjHandMsg* allocate_shm_client_neural_net_2_mov_obj_hand_msg_buffer(NeuralNet2MovObjHandMsg* msg_buffer);
NeuralNet2MovObjHandMsg* deallocate_shm_neural_net_2_mov_obj_hand_msg_buffer(NeuralNet2MovObjHandMsg* msg_buffer);
bool write_to_neural_net_2_mov_obj_hand_msg_buffer(NeuralNet2MovObjHandMsg* msg_buffer, TimeStamp msg_time, NeuralNet2MovObjHandMsgType msg_type, unsigned int layer_num, unsigned int nrn_grp_num, unsigned int neuron_num, TimeStamp spike_time);
bool get_next_neural_net_2_mov_obj_hand_msg_buffer_item(NeuralNet2MovObjHandMsg* msg_buffer, NeuralNet2MovObjHandMsgItem *msg_item);	// take care of static read_idx value //only request buffer handler uses

NeuralNet2MovObjHandMsgMultiThread* allocate_shm_server_neural_net_2_mov_obj_hand_multi_thread_msg_buffer(NeuralNet2MovObjHandMsgMultiThread* msg_buffers);
NeuralNet2MovObjHandMsg* allocate_shm_client_neural_net_2_mov_obj_hand_multi_thread_msg_buffer_item(NeuralNet2MovObjHandMsgMultiThread* msg_buffers, unsigned int msg_buffer_num);
NeuralNet2MovObjHandMsgMultiThread* deallocate_shm_neural_net_2_mov_obj_hand_multi_thread_msg_buffer(NeuralNet2MovObjHandMsgMultiThread* msg_buffers);


#endif
