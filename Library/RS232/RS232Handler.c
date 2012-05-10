#include "RS232Handler.h"

#define NUMBITS		8
#define STOPBITS		1
#define BAUD_9600	9600

bool enable_rs232_com1_9600_baud(void)
{
	int sp_open_return;
	rt_spclose(COM1);  // it might be left open since the previous program.
	sp_open_return = rt_spopen(COM1, BAUD_9600, NUMBITS, STOPBITS, RT_SP_PARITY_NONE, RT_SP_NO_HAND_SHAKE, RT_SP_FIFO_DISABLE);
   	if(sp_open_return) 
	{
		print_message(ERROR_MSG ,"ExpEnviHandlers", "RS232Handler", "enable_rs232_com1_9600_baud", "sp_open_return.");
      		switch(sp_open_return) 
		{
         		case -ENODEV:
        	 		return print_message(ERROR_MSG ,"ExpEnviHandlers", "RS232Handler", "enable_rs232_com1_9600_baud", "No Device.");
         		case -EINVAL:
          	 		return print_message(ERROR_MSG ,"ExpEnviHandlers", "RS232Handler", "enable_rs232_com1_9600_baud", "Invalid Value.");       		
         		case -EADDRINUSE:
          	 		return print_message(ERROR_MSG ,"ExpEnviHandlers", "RS232Handler", "enable_rs232_com1_9600_baud", "Address in Use.");       		
         		default:
          	 		return print_message(ERROR_MSG ,"ExpEnviHandlers", "RS232Handler", "enable_rs232_com1_9600_baud", "Unknown Error.");       		
      		}
	}
	rt_spclear_rx(COM1);
	rt_spclear_tx(COM1);
	print_message(INFO_MSG ,"ExpEnviHandlers", "RS232Handler", "enable_rs232_com1_9600_baud", "RS-232 COM1 - Enabled.");       		
	return TRUE;
}

void disable_rs232_com1(void)
{
	rt_spclose(COM1); 
	print_message(INFO_MSG ,"ExpEnviHandlers", "RS232Handler", "disable_rs232_com1", "RS-232 COM1 - Disabled.");       		
}

bool read_from_rs232_com1(char *msg, int msg_size)
{
	if (rt_spread(COM1, msg, msg_size) )
		return print_message(ERROR_MSG ,"ExpEnviHandlers", "RS232Handler", "read_from_rs232_com1", "rt_spread().");
	return TRUE;
}

bool write_to_rs232_com1(char *msg, int msg_size)
{
	if (rt_spwrite(COM1, msg, msg_size))
		return print_message(ERROR_MSG ,"ExpEnviHandlers", "RS232Handler", "write_to_rs232_com1", "rt_spwrite().");
	return TRUE;
}
