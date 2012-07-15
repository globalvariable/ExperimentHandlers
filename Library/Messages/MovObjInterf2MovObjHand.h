#ifndef MOV_OBJ_INTERF_2_MOV_OBJ_HAND_H
#define MOV_OBJ_INTERF_2_MOV_OBJ_HAND_H

//  MESSAGES FROM MOV OBJ INTERFACER TO MOV OBJ HANDLER

typedef struct __MovObjInterf2MovObjHandMsg MovObjInterf2MovObjHandMsg;
typedef struct __MovObjInterf2MovObjHandMsgItem MovObjInterf2MovObjHandMsgItem;
typedef unsigned int MovObjInterf2MovObjHandMsgType;
typedef double MovObjInterf2MovObjHandMsgAdditional;  


#define MOV_OBJ_INTERF_2_MOV_OBJ_HAND_MSG_STRING_LENGTH					100

#define MOV_OBJ_INTERF_2_MOV_OBJ_HAND_MSG_NULL							0
#define MOV_OBJ_INTERF_2_MOV_OBJ_HAND_MSG_I_AM_ALIVE						1
#define MOV_OBJ_INTERF_2_MOV_OBJ_HAND_MSG_DIRECTION_SPEED_LOCATION		2

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
#include "../MovObjData/MovObjDirectionTypes.h"
#include "../MovObjData/MovObjSpeedType.h"
#include "../MovObjData/MovObjLocationType.h"

struct __MovObjInterf2MovObjHandMsgItem
{
	TimeStamp 								msg_time;		
	MovObjInterf2MovObjHandMsgType			msg_type;
	MovObjCompNum							comp_num;
	MovObjDirectionType						direction;
	MovObjSpeedType							speed;
	MovObjLocationType						location;
};

struct __MovObjInterf2MovObjHandMsg		
{
	MovObjInterf2MovObjHandMsgItem		buff[MOV_OBJ_INTERF_2_MOV_OBJ_HAND_MSG_BUFF_SIZE];
	unsigned int						buff_write_idx;	// only one message sender can write into this buffer and edit this write index
	unsigned int						buff_read_idx;	// only one request handler can edit this read index
};

bool get_mov_obj_interf_2_mov_obj_hand_msg_type_string(MovObjInterf2MovObjHandMsgType msg_type, char *str);

// Messaging through allocated memory (in same program) 
MovObjInterf2MovObjHandMsg* allocate_mov_obj_interf_2_mov_obj_hand_msg_buffer(MovObjInterf2MovObjHandMsg* msg_buffer);
MovObjInterf2MovObjHandMsg* deallocate_mov_obj_interf_2_mov_obj_hand_msg_buffer(MovObjInterf2MovObjHandMsg* msg_buffer);

// Messaging through shared memory (separate programs) 
MovObjInterf2MovObjHandMsg* allocate_shm_server_mov_obj_interf_2_mov_obj_hand_msg_buffer(MovObjInterf2MovObjHandMsg* msg_buffer);
MovObjInterf2MovObjHandMsg* allocate_shm_client_mov_obj_interf_2_mov_obj_hand_msg_buffer(MovObjInterf2MovObjHandMsg* msg_buffer);
MovObjInterf2MovObjHandMsg* deallocate_shm_mov_obj_interf_2_mov_obj_hand_msg_buffer(MovObjInterf2MovObjHandMsg* msg_buffer);
bool write_to_mov_obj_interf_2_mov_obj_hand_msg_buffer(MovObjInterf2MovObjHandMsg* msg_buffer, TimeStamp msg_time, MovObjInterf2MovObjHandMsgType msg_type, MovObjCompNum comp_num, MovObjDirectionType direction, MovObjSpeedType speed, MovObjLocationType location);
bool get_next_mov_obj_interf_2_mov_obj_hand_msg_buffer_item(MovObjInterf2MovObjHandMsg* msg_buffer, MovObjInterf2MovObjHandMsgItem *msg_item);	// take care of static read_idx value //only request buffer handler uses

#endif
