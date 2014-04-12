#ifndef HANDLE_RS232_HAND_2_RS232_DUR_HAND_MSGS_H
#define HANDLE_RS232_HAND_2_RS232_DUR_HAND_MSGS_H



#include "../../../Library/RS232/RS232Data.h"
#include "../../../Library/Status/RS232DurStatus.h"
#include "../../../Library/Messages/RS232DurHand2RS232Hand.h"
#include "../../../Library/Messages/RS232Hand2RS232DurHand.h"

bool create_rs232_duration_handler_data(unsigned int arg_num_of_rs232_components);
bool handle_rs232_handler_to_rs232_dur_handler_msgs(RS232Data *rs_232_data, TimeStamp current_time, RS232DurHand2RS232HandMsg *msgs_rs232_dur_hand_2_rs232_hand, RS232Hand2RS232DurHandMsg *msgs_rs232_hand_2_rs232_dur_hand);
bool handle_rs232_duration_handler(TimeStamp current_time, RS232DurHand2RS232HandMsg *msgs_rs232_dur_hand_2_rs232_hand);









#endif 
