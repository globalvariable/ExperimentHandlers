#ifndef MOV_OBJ_HAND_2_MOV_OBJ_INTERF_H
#define MOV_OBJ_HAND_2_MOV_OBJ_INTERF_H

//  MESSAGES FROM EXP ENVI HANDLER TO TRIAL HANDLER

typedef struct __MovObjHand2MovObjInterfMsg MovObjHand2MovObjInterfMsg;
typedef struct __MovObjHand2MovObjInterfMsgItem MovObjHand2MovObjInterfMsgItem;
typedef unsigned int MovObjHand2MovObjInterfMsgType;
typedef unsigned int MovObjHand2MovObjInterfMsgAdditional;


#define MOV_OBJ_HAND_2_MOV_OBJ_INTERF_MSG_STRING_LENGTH					100

#define MOV_OBJ_HAND_2_MOV_OBJ_INTERF_MSG_NULL							0
#define MOV_OBJ_HAND_2_MOV_OBJ_INTERF_MSG_ARE_YOU_ALIVE					1
#define MOV_OBJ_HAND_2_MOV_OBJ_INTERF_SET_DIRECTION_SPEED_LOCATION		2



#include <stdbool.h>
#include <gtk/gtk.h>
#include <string.h>
#include <rtai_shm.h>
#include <rtai_nam2num.h>
#include "MessageBuffersConfig.h"
#include "MessageBuffersSharedMem.h"
#include "../../../BlueSpike/TimeStamp.h"
#include "../../../BlueSpike/Library/Misc/Misc.h"
#include "../MovObjData/MovObjComponentTypes.h"

struct __MovObjHand2MovObjInterfMsgItem
{
	TimeStamp 								msg_time;		
	MovObjHand2MovObjInterfMsgType			msg_type;
	MovObjCompNum							comp_num;
	MovObjDirectionType						direction;
	MovObjSpeedType							speed;
	MovObjLocationType						location;
};

struct __MovObjHand2MovObjInterfMsg		// Requests to TrialControllers
{
	MovObjHand2MovObjInterfMsgItem	buff[MOV_OBJ_HAND_2_MOV_OBJ_INTERF_MSG_BUFF_SIZE];
	unsigned int						buff_write_idx;	// only one message sender can write into this buffer and edit this write index
	unsigned int						buff_read_idx;	// only one request handler can edit this read index
};

bool get_mov_obj_hand_2_mov_obj_interf_msg_type_string(MovObjHand2MovObjInterfMsgType msg_type, char *str);

// Messaging through allocated memory (in same program) 
MovObjHand2MovObjInterfMsg* allocate_mov_obj_hand_2_mov_obj_interf_msg_buffer(MovObjHand2MovObjInterfMsg* msg_buffer);
MovObjHand2MovObjInterfMsg* deallocate_mov_obj_hand_2_mov_obj_interf_msg_buffer(MovObjHand2MovObjInterfMsg* msg_buffer);

// Messaging through shared memory (separate programs) 
MovObjHand2MovObjInterfMsg* allocate_shm_server_mov_obj_hand_2_mov_obj_interf_msg_buffer(MovObjHand2MovObjInterfMsg* msg_buffer);
MovObjHand2MovObjInterfMsg* allocate_shm_client_mov_obj_hand_2_mov_obj_interf_msg_buffer(MovObjHand2MovObjInterfMsg* msg_buffer);
MovObjHand2MovObjInterfMsg* deallocate_shm_mov_obj_hand_2_mov_obj_interf_msg_buffer(MovObjHand2MovObjInterfMsg* msg_buffer);
bool write_to_mov_obj_hand_2_mov_obj_interf_msg_buffer(MovObjHand2MovObjInterfMsg* msg_buffer, TimeStamp msg_time, MovObjHand2MovObjInterfMsgType msg_type, MovObjCompNum comp_num, MovObjDirectionType direction, MovObjSpeedType speed, MovObjLocationType location);
bool get_next_mov_obj_hand_2_mov_obj_interf_msg_buffer_item(MovObjHand2MovObjInterfMsg* msg_buffer, MovObjHand2MovObjInterfMsgItem **msg_item);	// take care of static read_idx value //only request buffer handler uses



#endif
