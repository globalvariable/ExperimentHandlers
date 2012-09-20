#include "RS232Handler.h"

#define NUMBITS		8
#define STOPBITS		1
#define BAUD_9600	9600
#define BAUD_115200	115200

bool enable_rs232_com1_115200_baud(void)
{
	int sp_open_return;
	rt_spclose(COM1);  // it might be left open since the previous program.
	sp_open_return = rt_spopen(COM1, BAUD_115200, NUMBITS, STOPBITS, RT_SP_PARITY_NONE, RT_SP_NO_HAND_SHAKE, RT_SP_FIFO_DISABLE);
   	if(sp_open_return) 
	{
		print_message(ERROR_MSG ,"ExpEnviHandlers", "RS232Handler", "enable_rs232_com1_115200_baud", "sp_open_return.");
      		switch(sp_open_return) 
		{
         		case -ENODEV:
        	 		return print_message(ERROR_MSG ,"ExpEnviHandlers", "RS232Handler", "enable_rs232_com1_115200_baud", "No Device.");
         		case -EINVAL:
          	 		return print_message(ERROR_MSG ,"ExpEnviHandlers", "RS232Handler", "enable_rs232_com1_115200_baud", "Invalid Value.");       		
         		case -EADDRINUSE:
          	 		return print_message(ERROR_MSG ,"ExpEnviHandlers", "RS232Handler", "enable_rs232_com1_115200_baud", "Address in Use.");       		
         		default:
          	 		return print_message(ERROR_MSG ,"ExpEnviHandlers", "RS232Handler", "enable_rs232_com1_115200_baud", "Unknown Error.");       		
      		}
	}
	rt_spclear_rx(COM1);
	rt_spclear_tx(COM1);
	print_message(INFO_MSG ,"ExpEnviHandlers", "RS232Handler", "enable_rs232_com1_115200_baud", "RS-232 COM1 - Enabled.");  
	return TRUE;
}

bool enable_rs232_com2_115200_baud(void)
{
	int sp_open_return;
	rt_spclose(COM2);  // it might be left open since the previous program.
	sp_open_return = rt_spopen(COM2, BAUD_115200, NUMBITS, STOPBITS, RT_SP_PARITY_NONE, RT_SP_NO_HAND_SHAKE, RT_SP_FIFO_DISABLE);
   	if(sp_open_return) 
	{
		print_message(ERROR_MSG ,"ExpEnviHandlers", "RS232Handler", "enable_rs232_com2_115200_baud", "sp_open_return.");
      		switch(sp_open_return) 
		{
         		case -ENODEV:
        	 		return print_message(ERROR_MSG ,"ExpEnviHandlers", "RS232Handler", "enable_rs232_com2_115200_baud", "No Device.");
         		case -EINVAL:
          	 		return print_message(ERROR_MSG ,"ExpEnviHandlers", "RS232Handler", "enable_rs232_com2_115200_baud", "Invalid Value.");       		
         		case -EADDRINUSE:
          	 		return print_message(ERROR_MSG ,"ExpEnviHandlers", "RS232Handler", "enable_rs232_com2_115200_baud", "Address in Use.");       		
         		default:
          	 		return print_message(ERROR_MSG ,"ExpEnviHandlers", "RS232Handler", "enable_rs232_com2_115200_baud", "Unknown Error.");       		
      		}
	}
	rt_spclear_rx(COM2);
	rt_spclear_tx(COM2);
 	print_message(INFO_MSG ,"ExpEnviHandlers", "RS232Handler", "enable_rs232_com2_115200_baud", "RS-232 COM2 - Enabled.");      		
	return TRUE;
}

void disable_rs232_com1(void)
{
	rt_spclose(COM1); 
	print_message(INFO_MSG ,"ExpEnviHandlers", "RS232Handler", "disable_rs232_com1", "RS-232 COM1 - Disabled.");       		
}

void disable_rs232_com2(void)
{
	rt_spclose(COM2); 
	print_message(INFO_MSG ,"ExpEnviHandlers", "RS232Handler", "disable_rs232_com2", "RS-232 COM2 - Disabled.");       		
}


bool read_from_rs232_com1(char *msg, int msg_size)
{
	if (rt_spread(COM1, msg, msg_size) )
		return print_message(ERROR_MSG ,"ExpEnviHandlers", "RS232Handler", "read_from_rs232_com1", "rt_spread().");
	return TRUE;
}

bool read_from_rs232_com2(char *msg, int msg_size)
{
	if (rt_spread(COM2, msg, msg_size) )
		return print_message(ERROR_MSG ,"ExpEnviHandlers", "RS232Handler", "read_from_rs232_com2", "rt_spread().");
	return TRUE;
}

bool write_to_rs232_com1(char *msg, int msg_size)
{
	if (rt_spwrite(COM1, msg, msg_size))
		return print_message(ERROR_MSG ,"ExpEnviHandlers", "RS232Handler", "write_to_rs232_com1", "rt_spwrite().");
	return TRUE;
}

bool write_to_rs232_com2(char *msg, int msg_size)
{
	if (rt_spwrite(COM2, msg, msg_size))
		return print_message(ERROR_MSG ,"ExpEnviHandlers", "RS232Handler", "write_to_rs232_com2", "rt_spwrite().");
	return TRUE;
}
