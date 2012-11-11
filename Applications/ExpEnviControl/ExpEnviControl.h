#ifndef EXP_ENVI_CONTROL_H
#define EXP_ENVI_CONTROL_H

#define EXP_ENVI_STATUS_MSG_LEN			1
#define EXP_ENVI_STATUS_MSG_START_IDX	1
#define EXP_ENVI_CMD_MSG_LEN				1
#define EXP_ENVI_CMD_MSG_START_IDX		1


union ExpEnviCmd			
{
	struct 
	{
		unsigned guide_led:1;  
		unsigned left_led:1;  
		unsigned right_led:1;  
		unsigned levers_avaiable:1;  
		unsigned valve:1;  
		unsigned buzzer:1;
		unsigned none0:1;
		unsigned none1:1;  // Keep this one clear(reserved) for 0xFF check for exp_envi command check. 'E'+0xFF+CMD 
	} ;
	unsigned char all_cmd;  /// one byte (unsigned char, see it via Watch in debug mode)
} exp_envi_cmd;


union ExpEnviStatus			
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
} exp_envi_status;

#include "Gui.h"
#include "ExpEnviControlRtTask.h"




#endif
