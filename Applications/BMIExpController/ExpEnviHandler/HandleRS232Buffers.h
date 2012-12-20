#ifndef HANDLE_RS232_BUFFERS_H
#define HANDLE_RS232_BUFFERS_H



#include <gtk/gtk.h>
#include <stdbool.h>
#include <rtai_shm.h>
#include "ConfigExpEnviComponentNums.h"
#include "../../Library/RS232/RS232Handler.h"
#include "../../Library/ExpEnviData/ExpEnviData.h"
#include "../../Library/ExpEnviData/ExpEnviEvaluate.h"
#include "../../Library/Messages/ExpEnviHand2ExpEnviDurHand.h"
#include "../../../../BlueSpike/System/TimeStamp/TimeStamp.h"

typedef union 			
{
	struct 
	{
		unsigned guide_led:1;  
		unsigned left_led:1;  
		unsigned right_led:1;  
		unsigned levers_available:1;  
		unsigned valve:1;  
		unsigned buzzer:1;
		unsigned none0:1;
		unsigned none1:1;  // Keep this one clear(reserved) for 0xFF check for exp_envi command check. 'E'+0xFF+CMD 
	} ;
	unsigned char all_cmd;  /// one byte (unsigned char, see it via Watch in debug mode)
} ExpEnviRS232Cmd;


typedef union  			
{
	struct 
	{
		unsigned ir_beam:1;  
		unsigned left_lever:1;  
		unsigned right_lever:1;  
		unsigned none0:1;
		unsigned none1:1;
		unsigned none2:1;
		unsigned none3:1;
		unsigned none4:1;
	} ;
	unsigned char all_status;  /// one byte (unsigned char, see it via Watch in debug mode)
} ExpEnviRS232Status;

bool init_rs232_buffers(SEM **exp_envi_rx_buff_sem, SEM **exp_envi_tx_buff_sem, unsigned char **exp_envi_rx_buff_shm, unsigned char **exp_envi_tx_buff_shm);
bool handle_exp_envi_tx_shm(ExpEnviRS232Cmd *exp_envi_cmd);
bool handle_exp_envi_rx_shm(ExpEnviRS232Status *exp_envi_rs232_status, ExpEnviData *exp_envi_data, TimeStamp current_time, ExpEnviHand2ExpEnviDurHandMsg *msgs_exp_envi_hand_2_exp_envi_dur_hand);






#endif
