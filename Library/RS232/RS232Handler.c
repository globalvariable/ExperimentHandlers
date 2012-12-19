#include "RS232Handler.h"

#define NUMBITS		8
#define STOPBITS		1

bool init_rs232_com1(unsigned int baud_rate)   // rs 232 is enabled by mov obj handler
{
	int sp_open_return;
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

bool init_exp_envi_rx_buffer_semaphore(SEM **exp_envi_rx_buff_sem)
{
	if (*exp_envi_rx_buff_sem != NULL)
        	return print_message(ERROR_MSG ,"ExpEnviHandlers", "RS232Handler", "init_exp_envi_rx_buffer_semaphore", "exp_envi_rx_buff_sem != NULL.");
	*exp_envi_rx_buff_sem = rt_get_adr(SEM_NUM_EXP_ENVI_RX_BUFFER);
	if (*exp_envi_rx_buff_sem == NULL)  // semaphore had not been created before.
	{
		*exp_envi_rx_buff_sem = rt_typed_sem_init(SEM_NUM_EXP_ENVI_RX_BUFFER, 1, BIN_SEM | FIFO_Q );
		print_message(INFO_MSG ,"ExpEnviHandlers", "RS232Handler", "init_exp_envi_rx_buffer_semaphore", "Initialized exp_envi_rx_buff semaphore.");  
	}
	else // a semaphore created before, delete and init it again.
	{
		rt_sem_delete(*exp_envi_rx_buff_sem);
		*exp_envi_rx_buff_sem = rt_typed_sem_init(SEM_NUM_EXP_ENVI_RX_BUFFER, 1, BIN_SEM | FIFO_Q );
		print_message(INFO_MSG ,"ExpEnviHandlers", "RS232Handler", "init_exp_envi_rx_buffer_semaphore", "Re-initialized exp_envi_rx_buff semaphore.");  
	}
	return TRUE;
}

bool bind_to_exp_envi_rx_buffer_semaphore(SEM **exp_envi_rx_buff_sem) // init_exp_envi_rx_buffer_semaphore is used by mov obj handler process Other processes(programs) using COM1 via semaphore are binded to the (static value)semaphore created by mov obj handler. 
{
	*exp_envi_rx_buff_sem = rt_get_adr(SEM_NUM_EXP_ENVI_RX_BUFFER);
	if (*exp_envi_rx_buff_sem  == NULL)
         	return print_message(ERROR_MSG ,"ExpEnviHandlers", "RS232Handler", "bind_to_exp_envi_rx_buffer_semaphore", "No exp_envi_rx_buff semaphore created. Create it with mov obj handler.");
	print_message(INFO_MSG ,"ExpEnviHandlers", "RS232Handler", "bind_to_exp_envi_rx_buffer_semaphore", "Binded to exp_envi_rx_buffer_semaphore.");  
	return TRUE;
}

bool init_exp_envi_tx_buffer_semaphore(SEM **exp_envi_tx_buff_sem)
{
	if (*exp_envi_tx_buff_sem != NULL)
        	return print_message(ERROR_MSG ,"ExpEnviHandlers", "RS232Handler", "init_exp_envi_tx_buffer_semaphore", "exp_envi_tx_buff_sem != NULL.");
	*exp_envi_tx_buff_sem = rt_get_adr(SEM_NUM_EXP_ENVI_TX_BUFFER);
	if (*exp_envi_tx_buff_sem == NULL)  // semaphore had not been created before.
	{
		*exp_envi_tx_buff_sem = rt_typed_sem_init(SEM_NUM_EXP_ENVI_TX_BUFFER, 1, BIN_SEM | FIFO_Q );
		print_message(INFO_MSG ,"ExpEnviHandlers", "RS232Handler", "init_exp_envi_tx_buffer_semaphore", "Initialized exp_envi_tx_buff semaphore.");  
	}
	else // a semaphore created before, delete and init it again.
	{
		rt_sem_delete(*exp_envi_tx_buff_sem);
		*exp_envi_tx_buff_sem = rt_typed_sem_init(SEM_NUM_EXP_ENVI_TX_BUFFER, 1, BIN_SEM | FIFO_Q );
		print_message(INFO_MSG ,"ExpEnviHandlers", "RS232Handler", "init_exp_envi_tx_buffer_semaphore", "Re-initialized exp_envi_tx_buff semaphore.");  
	}
	return TRUE;
}

bool bind_to_exp_envi_tx_buffer_semaphore(SEM **exp_envi_tx_buff_sem) // init_exp_envi_tx_buffer_semaphore is used by mov obj handler process Other processes(programs) using COM1 via semaphore are binded to the (static value)semaphore created by mov obj handler. 
{
	*exp_envi_tx_buff_sem = rt_get_adr(SEM_NUM_EXP_ENVI_TX_BUFFER);
	if (*exp_envi_tx_buff_sem  == NULL)
         	return print_message(ERROR_MSG ,"ExpEnviHandlers", "RS232Handler", "bind_to_exp_envi_tx_buffer_semaphore", "No exp_envi_tx_buff semaphore created. Create it with mov obj handler.");
	print_message(INFO_MSG ,"ExpEnviHandlers", "RS232Handler", "bind_to_exp_envi_tx_buffer_semaphore", "Binded to exp_envi_tx_buffer_semaphore.");  
	return TRUE;
}

bool init_exp_envi_rx_buffer_shm(unsigned char **exp_envi_rx_buff, unsigned int buff_size) // This proc is used by mov obj handler program to enable RS232 and clear shared memory buffer. 
{
	if (*exp_envi_rx_buff != NULL)
         	return print_message(ERROR_MSG ,"ExpEnviHandlers", "RS232Handler", "init_exp_envi_rx_buffer_shm", "exp_envi_rx_buff was allocated before.");
	*exp_envi_rx_buff = rt_get_adr(SHM_NUM_EXP_ENVI_RX_BUFFER);
	if (*exp_envi_rx_buff == NULL)
	{
		*exp_envi_rx_buff = rtai_malloc(SHM_NUM_EXP_ENVI_RX_BUFFER, buff_size*sizeof(unsigned char));
		memset(*exp_envi_rx_buff, 0, buff_size*sizeof(unsigned char));
		print_message(INFO_MSG ,"ExpEnviHandlers", "RS232Handler", "init_exp_envi_rx_buffer_shm", "Initialized exp_envi_rx_buff shm object.");  
	}
	else
	{
		rtai_free(SHM_NUM_EXP_ENVI_RX_BUFFER, *exp_envi_rx_buff);
		*exp_envi_rx_buff = rtai_malloc(SHM_NUM_EXP_ENVI_RX_BUFFER, buff_size*sizeof(unsigned char));
		memset(*exp_envi_rx_buff, 0, buff_size*sizeof(unsigned char));
		print_message(INFO_MSG ,"ExpEnviHandlers", "RS232Handler", "init_exp_envi_rx_buffer_shm", "Re-initialized exp_envi_rx_buff shm object..");  		
	}
	return TRUE;
} 

bool bind_to_exp_envi_rx_buffer_shm(unsigned char **exp_envi_rx_buff) // init_exp_envi_mov_obj_rs232_com1_shm is used by mov obj handler program. Other processes(i.e exp envi handler) using COM1 via semaphore are binded to the (static value) shm buffer created by mov obj handler. 
{
	if (*exp_envi_rx_buff != NULL)
         	return print_message(ERROR_MSG ,"ExpEnviHandlers", "RS232Handler", "bind_to_exp_envi_rx_buffer_shm", "This program binded to shared memory previously.");
	*exp_envi_rx_buff = rt_get_adr(SHM_NUM_EXP_ENVI_RX_BUFFER);
	if (*exp_envi_rx_buff == NULL)
         	return print_message(ERROR_MSG ,"ExpEnviHandlers", "RS232Handler", "bind_to_exp_envi_rx_buffer_shm", "No exp_envi_rx_buff shared memory created. Initialize it with Mov Obj Handler.");
	*exp_envi_rx_buff = rtai_malloc(SHM_NUM_EXP_ENVI_RX_BUFFER, 0);
	if (*exp_envi_rx_buff == NULL)
         	return print_message(ERROR_MSG ,"ExpEnviHandlers", "RS232Handler", "bind_to_exp_envi_rx_buffer_shm", "Couldn't bind to exp_envi_rx_buffer_shm shared memory.");
	print_message(INFO_MSG ,"ExpEnviHandlers", "RS232Handler", "bind_to_exp_envi_rx_buffer_shm", "Binded to exp_envi_rx_buffer_shm shared memory.");  
	return TRUE;
}

bool init_exp_envi_tx_buffer_shm(unsigned char **exp_envi_tx_buff, unsigned int buff_size) // This proc is used by mov obj handler program to enable RS232 and clear shared memory buffer. 
{
	if (*exp_envi_tx_buff != NULL)
         	return print_message(ERROR_MSG ,"ExpEnviHandlers", "RS232Handler", "init_exp_envi_tx_buffer_shm", "exp_envi_tx_buff was allocated before.");
	*exp_envi_tx_buff = rt_get_adr(SHM_NUM_EXP_ENVI_TX_BUFFER);
	if (*exp_envi_tx_buff == NULL)
	{
		*exp_envi_tx_buff = rtai_malloc(SHM_NUM_EXP_ENVI_TX_BUFFER, buff_size*sizeof(unsigned char));
		memset(*exp_envi_tx_buff, 0, buff_size*sizeof(unsigned char));
		print_message(INFO_MSG ,"ExpEnviHandlers", "RS232Handler", "init_exp_envi_tx_buffer_shm", "Initialized exp_envi_tx_buff shm object.");  
	}
	else
	{
		rtai_free(SHM_NUM_EXP_ENVI_TX_BUFFER, exp_envi_tx_buff);
		*exp_envi_tx_buff = rtai_malloc(SHM_NUM_EXP_ENVI_TX_BUFFER, buff_size*sizeof(unsigned char));
		memset(*exp_envi_tx_buff, 0, buff_size*sizeof(unsigned char));
		print_message(INFO_MSG ,"ExpEnviHandlers", "RS232Handler", "init_exp_envi_tx_buffer_shm", "Re-initialized exp_envi_tx_buff shm object..");  		
	}
	return TRUE;
} 

bool bind_to_exp_envi_tx_buffer_shm(unsigned char **exp_envi_tx_buff) // init_exp_envi_mov_obj_rs232_com1_shm is used by mov obj handler program. Other processes(i.e exp envi handler) using COM1 via semaphore are binded to the (static value) shm buffer created by mov obj handler. 
{
	if (*exp_envi_tx_buff != NULL)
         	return print_message(ERROR_MSG ,"ExpEnviHandlers", "RS232Handler", "bind_to_exp_envi_tx_buffer_shm", "This program binded to shared memory previously.");
	*exp_envi_tx_buff = rt_get_adr(SHM_NUM_EXP_ENVI_TX_BUFFER);
	if (*exp_envi_tx_buff == NULL)
         	return print_message(ERROR_MSG ,"ExpEnviHandlers", "RS232Handler", "bind_to_exp_envi_tx_buffer_shm", "No exp_envi_tx_buff shared memory created. Initialize it with Mov Obj Handler.");
	*exp_envi_tx_buff = rtai_malloc(SHM_NUM_EXP_ENVI_TX_BUFFER, 0);
	if (*exp_envi_tx_buff == NULL)
         	return print_message(ERROR_MSG ,"ExpEnviHandlers", "RS232Handler", "bind_to_exp_envi_tx_buffer_shm", "Couldn't bind to exp_envi_tx_buffer_shm shared memory.");
	print_message(INFO_MSG ,"ExpEnviHandlers", "RS232Handler", "bind_to_exp_envi_tx_buffer_shm", "Binded to exp_envi_tx_buffer_shm shared memory.");  
	return TRUE;
}


bool write_to_exp_envi_rx_buff_shm(unsigned char *msg, unsigned char *exp_envi_rx_buff_shm, unsigned int buff_size, SEM *exp_envi_rx_buff_sem) // mov obj handler writes here after handling rs232 rx buffer.
{
	unsigned int i;
        rt_sem_wait(exp_envi_rx_buff_sem);
	for (i = 0; i < buff_size; i++)
	{
		exp_envi_rx_buff_shm[i] = msg[i];
	}
        rt_sem_signal(exp_envi_rx_buff_sem);
	return TRUE;
}

bool read_exp_envi_rx_buff_shm(unsigned char *msg, unsigned char *exp_envi_rx_buff_shm, unsigned int buff_size, SEM *exp_envi_rx_buff_sem) // exp envi handler reads here.
{
	unsigned int i;
        rt_sem_wait(exp_envi_rx_buff_sem);
	for (i = 0; i < buff_size; i++)
	{
		msg[i] = exp_envi_rx_buff_shm[i];
	}
        rt_sem_signal(exp_envi_rx_buff_sem);
	return TRUE;
}

bool write_to_exp_envi_tx_buff_shm(unsigned char *msg, unsigned char *exp_envi_tx_buff_shm, unsigned int buff_size, SEM *exp_envi_tx_buff_sem) // exp_envi handler writes here to send command via mov obj handler.
{
	unsigned int i;
        rt_sem_wait(exp_envi_tx_buff_sem);
	for (i = 0; i < buff_size; i++)
	{
		exp_envi_tx_buff_shm[i] = msg[i];
	}
        rt_sem_signal(exp_envi_tx_buff_sem);
	return TRUE;
}

bool read_exp_envi_tx_buff_shm(unsigned char *msg, unsigned char *exp_envi_tx_buff_shm, unsigned int buff_size, SEM *exp_envi_tx_buff_sem) // mov obj handler reads here to tx via rs232.
{
	unsigned int i;
        rt_sem_wait(exp_envi_tx_buff_sem);
	for (i = 0; i < buff_size; i++)
	{
		msg[i] = exp_envi_tx_buff_shm[i];
	}
        rt_sem_signal(exp_envi_tx_buff_sem);
	return TRUE;
}

bool read_from_rs232_com1(unsigned char *msg, unsigned int msg_size)  // mov obj handler uses to read all rx buffer of rs232
{
	int rx_num_of_chars_remaining;
	rx_num_of_chars_remaining = rt_spread(COM1, (char*) msg, (int)msg_size);
	if (rx_num_of_chars_remaining != 0)
		return print_message(ERROR_MSG ,"ExpEnviHandlers", "RS232Handler", "write_to_rs232_com1", "rx_num_of_chars_remaining != 0.");
	return TRUE;	
}


bool write_to_rs232_com1(unsigned char *msg, unsigned int msg_size)
{
	if (rt_spwrite(COM1, (char*) msg, (int)msg_size))
		return print_message(ERROR_MSG ,"ExpEnviHandlers", "RS232Handler", "write_to_rs232_com1", "rt_spwrite().");
	return TRUE;
}

void disable_rs232_com1(void)
{
	rt_spclose(COM1); 
	print_message(INFO_MSG ,"ExpEnviHandlers", "RS232Handler", "disable_rs232_com1", "RS-232 COM1 - Disabled.");       		
}

void clear_rx_buffer(unsigned char *rx_buffer, unsigned int buff_size) 
{
	unsigned int i;
	for (i = 0; i < buff_size; i++)
		rx_buffer[i] = 0;
}
