#ifndef SERVO_H
#define SERVO_H

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

typedef struct 
{ 
	ServoPulse			pulse_command;		// saves pulse width relative to neutral_pulse (positive or negative)
	ServoPosition			position;
	unsigned short int	position_0_degree; // servo potentiometer output's adc quanta
	unsigned short int	position_90_degree; // servo potentiometer output's adc quanta
	double				radian_per_pos_quanta;
	double				angle_radian;
} ServoData;

void write_servo_pw_val(ServoData *servo_data, unsigned int servo_num, unsigned short int pulse_width);
void get_servo_pw_val(ServoData *servo_data, unsigned int servo_num, unsigned char *low_byte, unsigned char *high_byte);
void write_servo_position_val(ServoData *servo_data, unsigned int servo_num, unsigned char low_byte, unsigned char high_byte);

#endif
