#include "Servo.h"


void write_servo_pw_val(ServoData *servo_data, unsigned int servo_num, unsigned short int pulse_width)
{
	servo_data[servo_num].pulse_command.pulse_width = pulse_width;
}

void get_servo_pw_val(ServoData *servo_data, unsigned int servo_num, unsigned char *low_byte, unsigned char *high_byte)
{
	*low_byte = servo_data[servo_num].pulse_command.byte[0];
	*high_byte = servo_data[servo_num].pulse_command.byte[1];
}

void write_servo_position_val(ServoData *servo_data, unsigned int servo_num, unsigned char low_byte, unsigned char high_byte)
{
	servo_data[servo_num].position.byte[0] = low_byte;
	servo_data[servo_num].position.byte[1] = high_byte;
}
