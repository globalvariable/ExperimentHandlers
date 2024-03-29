#ifndef MOV_OBJ_HAND_2_NEURAL_NET_H
#define MOV_OBJ_HAND_2_NEURAL_NET_H

typedef struct __MovObjHand2NeuralNetMsg MovObjHand2NeuralNetMsg;
typedef struct __MovObjHand2NeuralNetMsgItem MovObjHand2NeuralNetMsgItem;
typedef unsigned int MovObjHand2NeuralNetMsgType;
typedef struct __MovObjHand2NeuralNetMsgAddBinaryReward MovObjHand2NeuralNetMsgAddBinaryReward;

#include "../Robot/ThreeDofRobot.h"

struct __MovObjHand2NeuralNetMsgAddBinaryReward
{
	int 			reward;
	unsigned int	target_idx;
};

typedef union 
{
	double three_dof_robot_joint_angles[THREE_DOF_ROBOT_NUM_OF_SERVOS];
	double three_dof_robot_min_joint_angles[THREE_DOF_ROBOT_NUM_OF_SERVOS];
	double three_dof_robot_max_joint_angles[THREE_DOF_ROBOT_NUM_OF_SERVOS];
	double momentary_reward;
	bool dummy;
	MovObjHand2NeuralNetMsgAddBinaryReward	binary_reward_add;
} MovObjHand2NeuralNetMsgAdditional;

#include "../../../BlueSpike/System/RtTasksData/RtTasksData.h"
#include "../../../BlueSpike/System/ShmSemNum/ShmSemNum.h"


#define MOV_OBJ_HAND_2_NEURAL_NET_MSG_STRING_LENGTH						100

#define MOV_OBJ_HAND_2_NEURAL_NET_MSG_NULL								0
#define MOV_OBJ_HAND_2_NEURAL_NET_MSG_ARE_YOU_ALIVE						1
#define MOV_OBJ_HAND_2_NEURAL_NET_MSG_3_DOF_JOINT_ANGLE					2
#define MOV_OBJ_HAND_2_NEURAL_NET_MSG_JOINT_ANGLE_MIN					3
#define MOV_OBJ_HAND_2_NEURAL_NET_MSG_JOINT_ANGLE_MAX					4
#define MOV_OBJ_HAND_2_NEURAL_NET_MSG_REINFORCEMENT						5
#define MOV_OBJ_HAND_2_NEURAL_NET_MSG_END_TRIAL_W_REWARD				6
#define MOV_OBJ_HAND_2_NEURAL_NET_MSG_END_TRIAL_W_PUNISH				7
#define MOV_OBJ_HAND_2_NEURAL_NET_MSG_START_TRIAL							8

#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>
#include <rtai_shm.h>
#include <rtai_nam2num.h>
#include "MessageBuffersConfig.h"
#include "../../../BlueSpike/System/TimeStamp/TimeStamp.h"
#include "../../../BlueSpike/Library/Misc/Misc.h"

struct __MovObjHand2NeuralNetMsgItem
{
	TimeStamp 								msg_time;
	MovObjHand2NeuralNetMsgType				msg_type;
	TimeStamp 								scheduled_time;  // for handling by the message buffer handler.
	MovObjHand2NeuralNetMsgAdditional			additional_data;
};

struct __MovObjHand2NeuralNetMsg		// Requests to TrialControllers
{
	MovObjHand2NeuralNetMsgItem		buff[MOV_OBJ_HAND_2_NEURAL_NET_MSG_BUFF_SIZE];
	unsigned int						buff_write_idx;	// only one message sender can write into this buffer and edit this write index
	unsigned int						buff_read_idx;	// only one request handler can edit this read index
	TimeStamp						event_scheduling_delay;
};

bool get_mov_obj_hand_2_neural_net_msg_type_string(MovObjHand2NeuralNetMsgType msg_type, char *str);

// Messaging through allocated memory (in same program) 
MovObjHand2NeuralNetMsg* allocate_mov_obj_hand_2_neural_net_msg_buffer(MovObjHand2NeuralNetMsg* msg_buffer);
MovObjHand2NeuralNetMsg* deallocate_mov_obj_hand_2_neural_net_msg_buffer(MovObjHand2NeuralNetMsg* msg_buffer);

// Messaging through shared memory (separate programs) 
MovObjHand2NeuralNetMsg* allocate_shm_server_mov_obj_hand_2_neural_net_msg_buffer(MovObjHand2NeuralNetMsg* msg_buffer);
MovObjHand2NeuralNetMsg* allocate_shm_client_mov_obj_hand_2_neural_net_msg_buffer(MovObjHand2NeuralNetMsg* msg_buffer, TimeStamp event_scheduling_delay, TimeStamp HARD_MIN_MOV_OBJ_HAND_2_NEURAL_NET_EVENT_SCHEDULING_DELAY) ;
MovObjHand2NeuralNetMsg* deallocate_shm_mov_obj_hand_2_neural_net_msg_buffer(MovObjHand2NeuralNetMsg* msg_buffer);
bool write_to_mov_obj_hand_2_neural_net_msg_buffer(MovObjHand2NeuralNetMsg* msg_buffer, TimeStamp msg_time, MovObjHand2NeuralNetMsgType msg_type, MovObjHand2NeuralNetMsgAdditional additional_data);
bool get_next_mov_obj_hand_2_neural_net_msg_buffer_item(MovObjHand2NeuralNetMsg* msg_buffer, MovObjHand2NeuralNetMsgItem *msg_item);	// take care of static read_idx value //only request buffer handler uses

MovObjHand2NeuralNetMsg** allocate_shm_server_mov_obj_hand_2_neural_net_multi_thread_msg_buffer(MovObjHand2NeuralNetMsg** msg_buffers, unsigned int num_of_threads);
MovObjHand2NeuralNetMsg* allocate_shm_client_mov_obj_hand_2_neural_net_multi_thread_msg_buffer_item(MovObjHand2NeuralNetMsg** msg_buffers, unsigned int msg_buffer_num, TimeStamp event_scheduling_delay, TimeStamp HARD_MIN_MOV_OBJ_HAND_2_NEURAL_NET_EVENT_SCHEDULING_DELAY);
MovObjHand2NeuralNetMsg** deallocate_shm_mov_obj_hand_2_neural_net_multi_thread_msg_buffer(MovObjHand2NeuralNetMsg** msg_buffers,  unsigned int num_of_threads);

#endif
