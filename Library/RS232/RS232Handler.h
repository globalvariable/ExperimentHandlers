#ifndef RS232_HANDLER_H
#define RS232_HANDLER_H

#include <rtai_serial.h>
#include <stdbool.h>
#include <gtk/gtk.h>
#include "../../../BlueSpike/Library/Misc/Misc.h"



bool enable_rs232_com1_9600_baud(void);
void disable_rs232_com1(void);
bool read_from_rs232_com1(char *msg, int msg_size);
bool write_to_rs232_com1(char *msg, int msg_size);






#endif
