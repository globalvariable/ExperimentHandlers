#ifndef HANDLE_RS232_DUR_HAND_2_RS232_HAND_MSGS_H
#define HANDLE_RS232_DUR_HAND_2_RS232_HAND_MSGS_H


#include "HandleExpEnviHand2ExpEnviInterfMsgs.h"
#include "HandleExpEnviInterf2ExpEnviHandMsgs.h"
#include "HandleMovObjHand2MovObjInterfMsgs.h"
#include "HandleMovObjInterf2MovObjHandMsgs.h"
#include "../../../Library/RS232/RS232Data.h"
#include "../../../Library/RS232/RS232Handler.h"
#include "../../../Library/Messages/RS232Hand2RS232DurHand.h"
#include "../../../Library/Messages/RS232DurHand2RS232Hand.h"

bool handle_rs232_dur_hand_to_rs232_hand_msgs(RS232Data *rs_232_data, TimeStamp current_time, ExpEnviHand2ExpEnviInterfMsg *msgs_exp_envi_hand_2_exp_envi_interf, ExpEnviInterf2ExpEnviHandMsg *msgs_exp_envi_interf_2_exp_envi_hand, MovObjHand2MovObjInterfMsg *msgs_mov_obj_hand_2_mov_obj_interf, MovObjInterf2MovObjHandMsg *msgs_mov_obj_interf_2_mov_obj_hand, RS232DurHand2RS232HandMsg *msgs_rs232_dur_hand_2_rs232_hand, RS232Hand2RS232DurHandMsg *msgs_rs232_hand_2_rs232_dur_hand);



#endif
