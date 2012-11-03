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
#include "../../../BlueSpike/SemaNames.h"
#include "../../../BlueSpike/ShmNames.h"


bool init_rs232_com1(unsigned int baud_rate, bool with_semaphore);
bool bind_to_rs232_com1_semaphore(void);
bool init_exp_envi_mov_obj_rs232_com1_shm(void) ;
bool bind_to_exp_envi_mov_obj_rs232_com1_shm(void);
bool write_to_rs232_com1_with_semaphore(char *msg, int msg_size);
int read_from_rs232_com1_exp_envi_with_semaphore(char *user_exp_envi_buffer);
int read_from_rs232_com1_mov_obj_with_semaphore(char *user_mov_obj_buffer);
bool enable_rs232_com2(unsigned int baud_rate, bool with_semaphore);
void disable_rs232_com1(void);
void disable_rs232_com2(void);
bool read_from_rs232_com1(char *msg, int msg_size);
bool read_from_rs232_com2(char *msg, int msg_size);
bool write_to_rs232_com1(char *msg, int msg_size);
bool write_to_rs232_com2(char *msg, int msg_size);





#endif
