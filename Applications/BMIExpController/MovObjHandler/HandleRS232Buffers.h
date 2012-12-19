#ifndef HANDLE_RS232_BUFFERS_H
#define HANDLE_RS232_BUFFERS_H

#include <gtk/gtk.h>
#include <stdbool.h>
#include <rtai_shm.h>
#include <rtai_nam2num.h>
#include "../../Library/RS232/RS232Handler.h"
#include "../../Library/Robot/ThreeDofRobot.h"

bool init_rs232_buffers(ThreeDofRobot *robot_arm, SEM **exp_envi_rx_buff_sem, SEM **exp_envi_tx_buff_sem, unsigned char **exp_envi_rx_buff_shm, unsigned char **exp_envi_tx_buff_shm);
bool handle_exp_envi_tx_shm_and_send_rs232_adc_command(void);
bool handle_exp_envi_tx_shm_and_send_rs232_pulse_width_command(void);
bool handle_rs232_rx_buffer_and_write_to_exp_envi_rx_shm(void);









#endif
