#ifndef RS232_HANDLER_H
#define RS232_HANDLER_H
 
#include <rtai_serial.h>
#include <rtai_sem.h>  
#include <rtai_registry.h>  
#include <rtai_shm.h>
#include <rtai_nam2num.h>
#include <stdbool.h>
#include <gtk/gtk.h>
#include "../../../BlueSpike/Library/Misc/Misc.h"
#include "../../../BlueSpike/System/ShmSemNum/ShmSemNum.h"
#include "../../../BlueSpike/System/TimeStamp/TimeStamp.h"

#define EXP_ENVI_TX_BUFFER_SIZE 10
#define EXP_ENVI_RX_BUFFER_SIZE 10

typedef struct
{
	TimeStamp		last_write_time;		
	unsigned char	exp_envi_tx_buff[EXP_ENVI_RX_BUFFER_SIZE];
} ExpEnviTxShm;

typedef struct
{
	unsigned char	exp_envi_rx_buff[EXP_ENVI_TX_BUFFER_SIZE];
} ExpEnviRxShm;

bool init_rs232_com1(unsigned int baud_rate);
bool init_exp_envi_rx_buffer_semaphore(SEM **exp_envi_rx_buff_sem);
bool bind_to_exp_envi_rx_buffer_semaphore(SEM **exp_envi_rx_buff_sem);
bool init_exp_envi_tx_buffer_semaphore(SEM **exp_envi_tx_buff_sem);
bool bind_to_exp_envi_tx_buffer_semaphore(SEM **exp_envi_tx_buff_sem) ;
bool init_exp_envi_rx_buffer_shm(ExpEnviRxShm **exp_envi_rx_buff_shm, unsigned int buff_size_to_use);
bool bind_to_exp_envi_rx_buffer_shm(ExpEnviRxShm **exp_envi_rx_buff_shm);
bool init_exp_envi_tx_buffer_shm(ExpEnviTxShm **exp_envi_tx_buff_shm, unsigned int buff_size_to_use, TimeStamp current_time);
bool bind_to_exp_envi_tx_buffer_shm(ExpEnviTxShm **exp_envi_tx_buff_shm);
bool write_to_exp_envi_rx_buff_shm(unsigned char *msg, ExpEnviRxShm *exp_envi_rx_buff_shm, unsigned int buff_size, SEM *exp_envi_rx_buff_sem);
bool read_exp_envi_rx_buff_shm(ExpEnviRxShm *msg, ExpEnviRxShm *exp_envi_rx_buff_shm, unsigned int buff_size, SEM *exp_envi_rx_buff_sem);
bool write_to_exp_envi_tx_buff_shm(ExpEnviTxShm *msg, ExpEnviTxShm *exp_envi_tx_buff_shm, unsigned int buff_size, SEM *exp_envi_tx_buff_sem);
bool read_exp_envi_tx_buff_shm(ExpEnviTxShm *msg, ExpEnviTxShm *exp_envi_tx_buff_shm, unsigned int buff_size, SEM *exp_envi_tx_buff_sem);
bool read_from_rs232_com1(unsigned char *msg, unsigned int msg_size);
bool write_to_rs232_com1(unsigned char *msg, unsigned int msg_size);
void disable_rs232_com1(void);
void clear_rx_buffer(unsigned char *rx_buffer, unsigned int buff_size) ;




#endif
