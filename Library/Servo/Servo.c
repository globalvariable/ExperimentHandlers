#include "Servo.h"


void write_servo_pw_val(ServoData *servo_data, ServoPulse pulse)
{
	servo_data->pulse_command.pulse_width = (unsigned short int)65536 - (unsigned short int)((9216/10000.0)*10*pulse.pulse_width);
}

void get_servo_pw_val(ServoData *servo_data, unsigned char *low_byte, unsigned char *high_byte)
{
	*low_byte = servo_data->pulse_command.byte[0];
	*high_byte = servo_data->pulse_command.byte[1];
}

void write_servo_position_val(ServoData *servo_data, unsigned char low_byte, unsigned char high_byte)
{
	servo_data->position.byte[0] = low_byte;
	servo_data->position.byte[1] = high_byte;
}

void get_servo_position_val(ServoData *servo_data, unsigned short int *servo_position)
{
	*servo_position = servo_data->position.position;
}

void write_servo_pw_adc_ranges(ServoData *servo_data, ServoPulse zero_degree_pulse,ServoPulse ninety_degree_pulse, ServoPosition zero_degree_adc_val, ServoPosition ninety_degree_adc_val)
{
	servo_data->range.pulse_width_0_degree = zero_degree_pulse;
	servo_data->range.pulse_width_90_degree = ninety_degree_pulse;
	servo_data->range.position_0_degree = zero_degree_adc_val;
	servo_data->range.position_90_degree = ninety_degree_adc_val;
	servo_data->range.radian_per_pos_quanta = M_PI_2 / (servo_data->range.position_90_degree.position - servo_data->range.position_0_degree.position);
}

void write_servo_0_degree_adc_val(ServoData *servo_data, ServoPosition zero_degree_adc_val)
{
	if (zero_degree_adc_val.position > servo_data->range.position_90_degree.position)
		servo_data->range.position_90_degree.position = zero_degree_adc_val.position;
	servo_data->range.position_0_degree.position = zero_degree_adc_val.position;
	servo_data->range.radian_per_pos_quanta = M_PI_2 / (servo_data->range.position_90_degree.position - servo_data->range.position_0_degree.position);
}

void write_servo_90_degree_adc_val(ServoData *servo_data, ServoPosition ninety_degree_adc_val)
{
	if (ninety_degree_adc_val.position < servo_data->range.position_0_degree.position)
		servo_data->range.position_0_degree.position = ninety_degree_adc_val.position;
	servo_data->range.position_90_degree.position = ninety_degree_adc_val.position;
	servo_data->range.radian_per_pos_quanta = M_PI_2 / (servo_data->range.position_90_degree.position - servo_data->range.position_0_degree.position);
}
