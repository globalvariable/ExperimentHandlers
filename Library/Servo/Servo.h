#ifndef SERVO_H
#define SERVO_H

#include <math.h>
#include <stdbool.h>

#define SERVO_CONTROLLER_CRYSTAL_FREQ	9216  // MHz

typedef union 
{
	unsigned char		byte[2];
	unsigned short int	pulse_width;
} ServoPulse;	// X PointOneMicrosec

typedef union 
{
	unsigned char		byte[2];
	unsigned short int	position;  // servo potentiometer output's adc quanta
} ServoPosition;	// X PointOneMicrosec

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
	ServoPulse			pulse_command;		// saves pulse width relative to neutral_pulse (positive or negative)
	ServoPosition			position;
	ServoRange			range;
	ServoAngle			current_angle;
} ServoData;

void write_servo_pw_val(ServoData *servo_data, ServoPulse pulse);
void get_servo_pw_val(ServoData *servo_data, unsigned char *low_byte, unsigned char *high_byte);
void write_servo_position_val(ServoData *servo_data, unsigned char low_byte, unsigned char high_byte);
void get_servo_position_val(ServoData *servo_data, unsigned short int *servo_position);
void write_servo_pw_adc_ranges(ServoData *servo_data, ServoPulse zero_degree_pulse,ServoPulse ninety_degree_pulse, ServoPosition zero_degree_adc_val, ServoPosition ninety_degree_adc_val);
void write_servo_0_degree_adc_val(ServoData *servo_data, ServoPosition zero_degree_adc_val);
void write_servo_90_degree_adc_val(ServoData *servo_data, ServoPosition ninety_degree_adc_val);

#endif
