#ifndef SERVO_H
#define SERVO_H

#include <math.h>
#include <stdbool.h>
#include <pthread.h>
#include <stdio.h>
#include <gtk/gtk.h>

#define SERVO_CONTROLLER_CRYSTAL_FREQ	9216  // MHz

typedef union 
{
	unsigned char		byte[2];
	unsigned short int	pulse_width;
} ServoPulseCmd;	// X PointOneMicrosec

typedef unsigned short int ServoPulse;
typedef short int ServoPulseChange;   /// roration direction is provided signed int

typedef short int ServoPosition;   

typedef union 
{
	unsigned char		byte[2];
	ServoPosition			position;  // servo potentiometer output's adc quanta
} ServoPositionUnion;	// X PointOneMicrosec

typedef double ServoAngle;

typedef struct 
{ 
	ServoPulse			pulse_width_0_degree;	
	ServoPulse			pulse_width_90_degree;	
	ServoPosition			position_0_degree;
	ServoPosition			position_90_degree;
	double				radian_per_pos_quanta;
} ServoRange;

typedef struct 
{ 
	pthread_mutex_t 		mutex; 
	ServoPulseCmd		pulse_command;	// pulse width to transmit (65536 - Timer value for MCU)
	ServoPulse			pulse_current;	// pulse width to transmit
	ServoPulse			pulse_target;		// pulse width for the target position.
	ServoPulseChange	pulse_change;	// inc/decrement pulse width to control speed to reach target.
	ServoPositionUnion	position;
	ServoRange			range;
	ServoAngle			current_angle;
} ServoData;

void init_servo_data(ServoData *servo_data);
void init_servo_pulse(ServoData *servo_data, ServoPulse pulse_width);
void submit_servo_target(ServoData *servo_data, ServoPulse target_pulse_width, double change_rate);
void submit_servo_direction_and_speed(ServoData *servo_data,  ServoPulseChange amount);
void evaluate_servo_pw_command(ServoData *servo_data);
void get_servo_pw_val_bytes(ServoData *servo_data, unsigned char *low_byte, unsigned char *high_byte);
void get_servo_position_val(ServoData *servo_data, ServoPosition *servo_position);
void write_servo_position_val(ServoData *servo_data, unsigned char low_byte, unsigned char high_byte);
void write_servo_pw_adc_ranges(ServoData *servo_data, ServoPulse zero_degree_pulse,ServoPulse ninety_degree_pulse, ServoPosition zero_degree_adc_val, ServoPosition ninety_degree_adc_val);
void write_servo_0_degree_adc_val(ServoData *servo_data, ServoPosition zero_degree_adc_val);
void write_servo_90_degree_adc_val(ServoData *servo_data, ServoPosition ninety_degree_adc_val);

#endif
