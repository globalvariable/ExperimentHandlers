#ifndef SERVO_CONTROL_H
#define SERVO_CONTROL_H

#define MAX_NUM_OF_SERVOS 8
#define NUM_OF_SERVOS	4

#define BASE_SERVO			0
#define SHOULDER_SERVO	1
#define ELBOW_SERVO		2

#define BASE_SERVO_INIT_PULSE			15000
#define SHOULDER_SERVO_INIT_PULSE	15000
#define ELBOW_SERVO_INIT_PULSE		15000

#define LOW_BYTE 0
#define HIGH_BYTE 1

#define MAX_NUM_OF_SERVOS 8
#define NUM_OF_SERVOS 4

#define RX_BUFF_SIZE 20
#define TX_BUFF_SIZE 20

typedef union 
{
	unsigned char		byte[2];
	unsigned short int	pulse_width;
} ServoPulse;	// X PointOneMicrosec

typedef union 
{
	unsigned char		byte[2];
	unsigned short int	position;
} ServoPosition;	// X PointOneMicrosec

typedef struct 
{ 
	ServoPulse		pulse_command;		// saves pulse width relative to neutral_pulse (positive or negative)
	ServoPosition		position;
} ServoData;

ServoData servos[NUM_OF_SERVOS];

char rx_buffer[RX_BUFF_SIZE];
char tx_buffer[TX_BUFF_SIZE];
unsigned char tx_pw_command_len;
unsigned char tx_adc_command_len;
unsigned char rx_position_len;

#include "Gui.h"
#include "ServoControlRtTask.h"




#endif
