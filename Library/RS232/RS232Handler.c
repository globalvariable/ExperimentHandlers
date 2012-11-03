#include "RS232Handler.h"

#define NUMBITS		8
#define STOPBITS		1

#define MAX_EXP_ENVI_RX_BUFF_SIZE		2         //  'E'(start msg) + 0xFF + EXP_ENVI_STATUS 
#define MAX_MOV_OBJ_RX_BUFF_SIZE		8	  //	'P'(start msg) + 0x00 + 0x00 + SERVO_0_POSITION_L_BYTE + SERVO_0_POSITION_H_BYTE + SERVO_1_POSITION_L_BYTE + SERVO_1_ POSITION_H_BYTE + SERVO_2_POSITION_L_BYTE + SERVO_2_ POSITION_H_BYTE 
#define MAX_RX_BUFF_SIZE				100

static SEM *rs232_com1_semaphore = NULL;

static char rx_buffer[MAX_RX_BUFF_SIZE];


static struct ExpEnviMovObjRxBuffer
{
	unsigned char exp_envi_rx_buff[MAX_EXP_ENVI_RX_BUFF_SIZE];
	unsigned char mov_obj_rx_buff[MAX_MOV_OBJ_RX_BUFF_SIZE];
	unsigned int exp_envi_buff_write_idx;
	unsigned int mov_obj_buff_write_idx;
	bool rxing_exp_envi_msg;
	bool rxing_mov_obj_msg;
	bool rxed_exp_envi_msg;
	bool rxed_mov_obj_msg;
} *exp_envi_mov_obj_rx_buffer;


bool init_rs232_com1(unsigned int baud_rate, bool with_semaphore)  // This proc is used by Reset RS232 to enable RS232 and clear its buffers. 
{
	int sp_open_return;
	if (with_semaphore)
	{
		if (rs232_com1_semaphore != NULL)
        	 	return print_message(ERROR_MSG ,"ExpEnviHandlers", "RS232Handler", "enable_rs232_com1", "rs232_com1_semaphore != NULL.");
		rs232_com1_semaphore = rt_get_adr(NAME_RS232_COM1_SEMAPHORE);
		if (rs232_com1_semaphore == NULL)  // semaphore had not been created before.
		{
			rs232_com1_semaphore = rt_typed_sem_init(NAME_RS232_COM1_SEMAPHORE, 1, BIN_SEM | FIFO_Q );
			print_message(INFO_MSG ,"ExpEnviHandlers", "RS232Handler", "enable_rs232_com1", "Initialized RS-232 COM1 semaphore.");  
		}
		else
		{
			rt_sem_delete(rs232_com1_semaphore);
			rs232_com1_semaphore = rt_get_adr(NAME_RS232_COM1_SEMAPHORE);
			rs232_com1_semaphore = rt_typed_sem_init(NAME_RS232_COM1_SEMAPHORE, 1, BIN_SEM | FIFO_Q );
			print_message(INFO_MSG ,"ExpEnviHandlers", "RS232Handler", "enable_rs232_com1", "Re-initialized RS-232 COM1 semaphore.");  
		}
	}
	rt_spclose(COM1);  // it might be left open since the previous program.
	sp_open_return = rt_spopen(COM1, baud_rate, NUMBITS, STOPBITS, RT_SP_PARITY_NONE, RT_SP_NO_HAND_SHAKE, RT_SP_FIFO_DISABLE);
	if (sp_open_return)
	{
      		switch(sp_open_return)
		{
	 		case -ENODEV:
		 		return print_message(ERROR_MSG ,"ExpEnviHandlers", "RS232Handler", "enable_rs232_com1", "No Device.");
	 		case -EINVAL:
	  	 		return print_message(ERROR_MSG ,"ExpEnviHandlers", "RS232Handler", "enable_rs232_com1", "Invalid Value.");       		
	 		case -EADDRINUSE:
	  	 		return print_message(ERROR_MSG ,"ExpEnviHandlers", "RS232Handler", "enable_rs232_com1", "Address in Use.");     
	 		default:
	  	 		return print_message(ERROR_MSG ,"ExpEnviHandlers", "RS232Handler", "enable_rs232_com1", "Unknown Error.");       		
		}
	}
	rt_spclear_rx(COM1);
	rt_spclear_tx(COM1);
	print_message(INFO_MSG ,"ExpEnviHandlers", "RS232Handler", "enable_rs232_com1", "RS-232 COM1 - Enabled.");  
	return TRUE;
}

bool bind_to_rs232_com1_semaphore(void) // init_rs232_com1 is used by RS232 initializer process.. Other processes(programs) using COM1 via semaphore are binded to the (static value)semaphore created by RS232 COM1 initializer. 
{
	rs232_com1_semaphore = rt_get_adr(NAME_RS232_COM1_SEMAPHORE);
	if (rs232_com1_semaphore == NULL)
         	return print_message(ERROR_MSG ,"ExpEnviHandlers", "RS232Handler", "bind_to_rs232_com1_semaphore", "No RS232 COM1 semaphore created. Create it with RS232 COM1 initializer.");
	print_message(INFO_MSG ,"ExpEnviHandlers", "RS232Handler", "bind_to_rs232_com1_semaphore", "Binded to RS-232 COM1 Semaphore.");  
	return TRUE;
}

bool init_exp_envi_mov_obj_rs232_com1_shm(void) // This proc is used by RS232 iniitiazer program to enable RS232 and clear shared memory buffer. 
{
	if (exp_envi_mov_obj_rx_buffer != NULL)
         	return print_message(ERROR_MSG ,"ExpEnviHandlers", "RS232Handler", "init_exp_envi_mov_obj_rs232_com1", "exp_envi_mov_obj_rx_buffer was allocated before.");
	exp_envi_mov_obj_rx_buffer = rt_get_adr(NAME_EXP_ENVI_MOV_OBJ_RS232_RX_BUFFER);
	if (exp_envi_mov_obj_rx_buffer == NULL)
	{
		exp_envi_mov_obj_rx_buffer = rtai_malloc(NAME_EXP_ENVI_MOV_OBJ_RS232_RX_BUFFER, sizeof(struct ExpEnviMovObjRxBuffer));
		memset(exp_envi_mov_obj_rx_buffer, 0, sizeof(struct ExpEnviMovObjRxBuffer));
		print_message(INFO_MSG ,"ExpEnviHandlers", "RS232Handler", "enable_rs232_com1", "Initialized RS232 exp_envi_mov_obj_rx_buffer object.");  
	}
	else
	{
		rtai_free(NAME_EXP_ENVI_MOV_OBJ_RS232_RX_BUFFER, exp_envi_mov_obj_rx_buffer);
		exp_envi_mov_obj_rx_buffer = rtai_malloc(NAME_EXP_ENVI_MOV_OBJ_RS232_RX_BUFFER, sizeof(struct ExpEnviMovObjRxBuffer));
		memset(exp_envi_mov_obj_rx_buffer, 0, sizeof(struct ExpEnviMovObjRxBuffer));
		print_message(INFO_MSG ,"ExpEnviHandlers", "RS232Handler", "enable_rs232_com1", "Re-initialized RS232 exp_envi_mov_obj_rx_buffer object.");  		
	}
	return TRUE;
} 

bool bind_to_exp_envi_mov_obj_rs232_com1_shm(void) // init_exp_envi_mov_obj_rs232_com1_shm is used by RS232 initializer process.. Other processes(programs) using COM1 via semaphore are binded to the (static value) shm buffer created by RS232 COM1 initializer. 
{
	if (exp_envi_mov_obj_rx_buffer != NULL)
         	return print_message(ERROR_MSG ,"ExpEnviHandlers", "RS232Handler", "bind_to_exp_envi_mov_obj_rs232_com1_shm", "This program binded to shared memory previously.");
	exp_envi_mov_obj_rx_buffer = rt_get_adr(NAME_EXP_ENVI_MOV_OBJ_RS232_RX_BUFFER);
	if (exp_envi_mov_obj_rx_buffer == NULL)
         	return print_message(ERROR_MSG ,"ExpEnviHandlers", "RS232Handler", "bind_to_exp_envi_mov_obj_rs232_com1_shm", "No Exp_Envi_Mov_Obj RS232 COM1 shared memory created. Initialize it with RS232 COM1 initializer.");
	exp_envi_mov_obj_rx_buffer = rtai_malloc(NAME_EXP_ENVI_MOV_OBJ_RS232_RX_BUFFER, 0);
	if (exp_envi_mov_obj_rx_buffer == NULL)
         	return print_message(ERROR_MSG ,"ExpEnviHandlers", "RS232Handler", "bind_to_exp_envi_mov_obj_rs232_com1_shm", "Couldn't bind to Exp_Envi_Mov_Obj RS232 COM1 shared memory.");
	print_message(INFO_MSG ,"ExpEnviHandlers", "RS232Handler", "bind_to_exp_envi_mov_obj_rs232_com1_shm", "Binded to Exp_Envi_Mov_Obj RS-232 COM1 shared memory.");  
	return TRUE;
}

bool write_to_rs232_com1_with_semaphore(char *msg, int msg_size)
{
        rt_sem_wait(rs232_com1_semaphore);
	if (rt_spwrite(COM1, msg, msg_size))
		return print_message(ERROR_MSG ,"ExpEnviHandlers", "RS232Handler", "write_to_rs232_com1", "rt_spwrite().");
        rt_sem_signal(rs232_com1_semaphore);
	return TRUE;
}

int read_from_rs232_com1_exp_envi_with_semaphore(char *user_exp_envi_buffer)
{
	unsigned int num_of_chars_in_com1_buff, i;
        rt_sem_wait(rs232_com1_semaphore);
	num_of_chars_in_com1_buff = rt_spget_rxavbs(COM1);
	if (num_of_chars_in_com1_buff > 0)
	{
		if (num_of_chars_in_com1_buff > MAX_RX_BUFF_SIZE)
		{
       			rt_sem_signal(rs232_com1_semaphore);
			print_message(ERROR_MSG ,"ExpEnviHandlers", "RS232Handler", "read_from_rs232_com1_exp_envi_with_semaphore", "num_of_chars_in_com1_buff > MAX_RX_BUFF_SIZE.");
			return -1;
		}	
		rt_spread(COM1, rx_buffer, num_of_chars_in_com1_buff);
		for(i = 0; i < num_of_chars_in_com1_buff; i++)
		{
			if (exp_envi_mov_obj_rx_buffer->rxing_exp_envi_msg)
			{
				exp_envi_mov_obj_rx_buffer->exp_envi_rx_buff[exp_envi_mov_obj_rx_buffer->exp_envi_buff_write_idx] = rx_buffer[i];
				exp_envi_mov_obj_rx_buffer->exp_envi_buff_write_idx++;
				if (exp_envi_mov_obj_rx_buffer->exp_envi_buff_write_idx == MAX_EXP_ENVI_RX_BUFF_SIZE)
				{
					exp_envi_mov_obj_rx_buffer->exp_envi_buff_write_idx = 0;
					if (exp_envi_mov_obj_rx_buffer->rxed_exp_envi_msg) // the user could not read buffer on time. new exp_envi_message has been received before reading.
					{
       						rt_sem_signal(rs232_com1_semaphore);
						print_message(ERROR_MSG ,"ExpEnviHandlers", "RS232Handler", "read_from_rs232_com1_exp_envi_with_semaphore", "exp_envi_mov_obj_rx_buffer->rxed_exp_envi_msg.");
						return -2;
					}
					if (exp_envi_mov_obj_rx_buffer->exp_envi_rx_buff[0] != 0xFF)  // Message check failed !!
					{
       						rt_sem_signal(rs232_com1_semaphore);
						print_message(ERROR_MSG ,"ExpEnviHandlers", "RS232Handler", "read_from_rs232_com1_exp_envi_with_semaphore", "exp_envi_mov_obj_rx_buffer->exp_envi_rx_buff[0] != 0xFF.");
						return -3;
					}
					exp_envi_mov_obj_rx_buffer->rxed_exp_envi_msg = TRUE;
					exp_envi_mov_obj_rx_buffer->rxing_exp_envi_msg = FALSE;
				}
			}
			else if (exp_envi_mov_obj_rx_buffer->rxing_mov_obj_msg)
			{
				exp_envi_mov_obj_rx_buffer->mov_obj_rx_buff[exp_envi_mov_obj_rx_buffer->mov_obj_buff_write_idx] = rx_buffer[i];
				exp_envi_mov_obj_rx_buffer->mov_obj_buff_write_idx++;
				if (exp_envi_mov_obj_rx_buffer->mov_obj_buff_write_idx == MAX_MOV_OBJ_RX_BUFF_SIZE)
				{
					exp_envi_mov_obj_rx_buffer->mov_obj_buff_write_idx = 0;
					if (exp_envi_mov_obj_rx_buffer->rxed_mov_obj_msg) // the user could not read buffer on time. new mov_obj_message has been received before reading.
					{
       						rt_sem_signal(rs232_com1_semaphore);
						print_message(ERROR_MSG ,"ExpEnviHandlers", "RS232Handler", "read_from_rs232_com1_exp_envi_with_semaphore", "exp_envi_mov_obj_rx_buffer->rxed_mov_obj_msg.");
						return -4;
					}
					if ((exp_envi_mov_obj_rx_buffer->mov_obj_rx_buff[0] != 0x00)  || (exp_envi_mov_obj_rx_buffer->mov_obj_rx_buff[1] != 0x00))// Message check failed !!
					{
       						rt_sem_signal(rs232_com1_semaphore);
						print_message(ERROR_MSG ,"ExpEnviHandlers", "RS232Handler", "read_from_rs232_com1_exp_envi_with_semaphore", "exp_envi_mov_obj_rx_buffer->exp_envi_rx_buff[0] != 0xFF.");
						return -5;
					}
					exp_envi_mov_obj_rx_buffer->rxed_mov_obj_msg = TRUE;
					exp_envi_mov_obj_rx_buffer->rxing_mov_obj_msg = FALSE;
				}
			}
			else
			{
				switch (rx_buffer[i])
				{
					case 'E':
						exp_envi_mov_obj_rx_buffer->rxing_exp_envi_msg = TRUE;
						break;
					case 'P':
						exp_envi_mov_obj_rx_buffer->rxing_mov_obj_msg = TRUE;
						break;
					default:
       						rt_sem_signal(rs232_com1_semaphore);
						print_message(ERROR_MSG ,"ExpEnviHandlers", "RS232Handler", "read_from_rs232_com1_exp_envi_with_semaphore", "Invalid start message.");
						return -6;							
				}

			}
		}
	}
	if (exp_envi_mov_obj_rx_buffer->rxed_exp_envi_msg)   // copy the user's buffer.
	{
		for (i = 1; i < MAX_EXP_ENVI_RX_BUFF_SIZE; i++)
		{
			user_exp_envi_buffer[i-1] = exp_envi_mov_obj_rx_buffer->exp_envi_rx_buff[i];
		}
		exp_envi_mov_obj_rx_buffer->rxed_exp_envi_msg = FALSE;
	}
	else
	{
 	       rt_sem_signal(rs232_com1_semaphore);	
		return -7;	
	}
        rt_sem_signal(rs232_com1_semaphore);
	return 0;
}

int read_from_rs232_com1_mov_obj_with_semaphore(char *user_mov_obj_buffer)
{
	unsigned int num_of_chars_in_com1_buff, i;
        rt_sem_wait(rs232_com1_semaphore);
	num_of_chars_in_com1_buff = rt_spget_rxavbs(COM1);
	if (num_of_chars_in_com1_buff > 0)
	{
		if (num_of_chars_in_com1_buff > MAX_RX_BUFF_SIZE)
		{
       			rt_sem_signal(rs232_com1_semaphore);
			print_message(ERROR_MSG ,"ExpEnviHandlers", "RS232Handler", "read_from_rs232_com1_mov_obj_with_semaphore", "num_of_chars_in_com1_buff > MAX_RX_BUFF_SIZE.");
			return -1;
		}	
		rt_spread(COM1, rx_buffer, num_of_chars_in_com1_buff); 
		for (i = 0; i < num_of_chars_in_com1_buff; i++)
		{
			if (exp_envi_mov_obj_rx_buffer->rxing_exp_envi_msg)
			{
				exp_envi_mov_obj_rx_buffer->exp_envi_rx_buff[exp_envi_mov_obj_rx_buffer->exp_envi_buff_write_idx] = rx_buffer[i];
				exp_envi_mov_obj_rx_buffer->exp_envi_buff_write_idx++;
				if (exp_envi_mov_obj_rx_buffer->exp_envi_buff_write_idx == MAX_EXP_ENVI_RX_BUFF_SIZE)
				{
					exp_envi_mov_obj_rx_buffer->exp_envi_buff_write_idx = 0;
					if (exp_envi_mov_obj_rx_buffer->rxed_exp_envi_msg) // the user could not read buffer on time. new exp_envi_message has been received before reading.
					{
       						rt_sem_signal(rs232_com1_semaphore);
						print_message(ERROR_MSG ,"ExpEnviHandlers", "RS232Handler", "read_from_rs232_com1_mov_obj_with_semaphore", "exp_envi_mov_obj_rx_buffer->rxed_exp_envi_msg.");
						return -2;
					}
					if (exp_envi_mov_obj_rx_buffer->exp_envi_rx_buff[0] != 0xFF)  // Message check failed !!
					{
       						rt_sem_signal(rs232_com1_semaphore);
						print_message(ERROR_MSG ,"ExpEnviHandlers", "RS232Handler", "read_from_rs232_com1_mov_obj_with_semaphore", "exp_envi_mov_obj_rx_buffer->exp_envi_rx_buff[0] != 0xFF.");
						return -3;
					}
					exp_envi_mov_obj_rx_buffer->rxed_exp_envi_msg = TRUE;
					exp_envi_mov_obj_rx_buffer->rxing_exp_envi_msg = FALSE;
				}
			}
			else if (exp_envi_mov_obj_rx_buffer->rxing_mov_obj_msg)
			{
				exp_envi_mov_obj_rx_buffer->mov_obj_rx_buff[exp_envi_mov_obj_rx_buffer->mov_obj_buff_write_idx] = rx_buffer[i];
				exp_envi_mov_obj_rx_buffer->mov_obj_buff_write_idx++;
				if (exp_envi_mov_obj_rx_buffer->mov_obj_buff_write_idx == MAX_MOV_OBJ_RX_BUFF_SIZE)
				{
					exp_envi_mov_obj_rx_buffer->mov_obj_buff_write_idx = 0;
					if (exp_envi_mov_obj_rx_buffer->rxed_mov_obj_msg) // the user could not read buffer on time. new mov_obj_message has been received before reading.
					{
       						rt_sem_signal(rs232_com1_semaphore);
						print_message(ERROR_MSG ,"ExpEnviHandlers", "RS232Handler", "read_from_rs232_com1_mov_obj_with_semaphore", "exp_envi_mov_obj_rx_buffer->rxed_mov_obj_msg.");
						return -4;
					}
					if ((exp_envi_mov_obj_rx_buffer->mov_obj_rx_buff[0] != 0x00)  || (exp_envi_mov_obj_rx_buffer->mov_obj_rx_buff[1] != 0x00))// Message check failed !!
					{
       						rt_sem_signal(rs232_com1_semaphore);
						print_message(ERROR_MSG ,"ExpEnviHandlers", "RS232Handler", "read_from_rs232_com1_mov_obj_with_semaphore", "exp_envi_mov_obj_rx_buffer->exp_envi_rx_buff[0] != 0xFF.");
						return -5;
					}
					exp_envi_mov_obj_rx_buffer->rxed_mov_obj_msg = TRUE;
					exp_envi_mov_obj_rx_buffer->rxing_mov_obj_msg = FALSE;
				}
			}
			else
			{
				switch (rx_buffer[i])
				{
					case 'E':
						exp_envi_mov_obj_rx_buffer->rxing_exp_envi_msg = TRUE;
						break;
					case 'P':
						exp_envi_mov_obj_rx_buffer->rxing_mov_obj_msg = TRUE;
						break;
					default:
       						rt_sem_signal(rs232_com1_semaphore);
						print_message(ERROR_MSG ,"ExpEnviHandlers", "RS232Handler", "read_from_rs232_com1_mov_obj_with_semaphore", "Invalid start message.");
						return -6;							
				}
			}
		}
	}
	if (exp_envi_mov_obj_rx_buffer->rxed_mov_obj_msg)   // copy the user's buffer.
	{
		for (i = 2; i < MAX_MOV_OBJ_RX_BUFF_SIZE; i++)
		{
			user_mov_obj_buffer[i-2] = exp_envi_mov_obj_rx_buffer->mov_obj_rx_buff[i];
		}
		exp_envi_mov_obj_rx_buffer->rxed_mov_obj_msg = FALSE;
	}
	else
	{
 	       rt_sem_signal(rs232_com1_semaphore);	
		return -7;	
	}
        rt_sem_signal(rs232_com1_semaphore);
	return 0;
}

bool enable_rs232_com2(unsigned int baud_rate, bool with_semaphore)
{
	int sp_open_return;
	rt_spclose(COM2);  // it might be left open since the previous program.
	sp_open_return = rt_spopen(COM2, baud_rate, NUMBITS, STOPBITS, RT_SP_PARITY_NONE, RT_SP_NO_HAND_SHAKE, RT_SP_FIFO_DISABLE);
   	if(sp_open_return)
	{
		print_message(ERROR_MSG ,"ExpEnviHandlers", "RS232Handler", "enable_rs232_com2", "sp_open_return.");
      		switch(sp_open_return) 
		{
         		case -ENODEV:
        	 		return print_message(ERROR_MSG ,"ExpEnviHandlers", "RS232Handler", "enable_rs232_com2", "No Device.");
         		case -EINVAL:
          	 		return print_message(ERROR_MSG ,"ExpEnviHandlers", "RS232Handler", "enable_rs232_com2", "Invalid Value.");       		
         		case -EADDRINUSE:
          	 		return print_message(ERROR_MSG ,"ExpEnviHandlers", "RS232Handler", "enable_rs232_com2", "Address in Use.");       		
         		default:
          	 		return print_message(ERROR_MSG ,"ExpEnviHandlers", "RS232Handler", "enable_rs232_com2", "Unknown Error.");       		
      		}
	}
	rt_spclear_rx(COM2);
	rt_spclear_tx(COM2);
 	print_message(INFO_MSG ,"ExpEnviHandlers", "RS232Handler", "enable_rs232_com2", "RS-232 COM2 - Enabled.");      		
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
