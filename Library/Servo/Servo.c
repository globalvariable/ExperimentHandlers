#include "Servo.h"

void init_servo_data(ServoData *servo_data)
{
	pthread_mutex_init(&(servo_data->mutex), NULL);	
	pthread_mutex_lock(&(servo_data->mutex));
	servo_data->pulse_command.pulse_width = 0;
	servo_data->pulse_current = 0;
	servo_data->pulse_target= 0;
	servo_data->pulse_change = 0;
	servo_data->position.position = 0;
	pthread_mutex_unlock(&(servo_data->mutex));
}

void init_servo_pulse(ServoData *servo_data, ServoPulse pulse_width)
{
	pthread_mutex_lock(&(servo_data->mutex));	
	servo_data->pulse_current = pulse_width;
	servo_data->pulse_target = pulse_width;
	servo_data->pulse_command.pulse_width = (unsigned short int)65536 - (unsigned short int)((9216/10000.0)*10*servo_data->pulse_current);		
	pthread_mutex_unlock(&(servo_data->mutex));	
}

void submit_servo_target(ServoData *servo_data, ServoPulse target_pulse_width, double change_rate)
{
	pthread_mutex_lock(&(servo_data->mutex));
	servo_data->pulse_target = target_pulse_width;
	servo_data->pulse_change = (ServoPulseChange)((((double)servo_data->pulse_target) - ((double)servo_data->pulse_current))*change_rate);
	pthread_mutex_unlock(&(servo_data->mutex));
}

void submit_servo_direction_and_speed(ServoData *servo_data,  ServoPulseChange amount)
{
	pthread_mutex_lock(&(servo_data->mutex));
	servo_data->pulse_change = 0;
	servo_data->pulse_target = servo_data->pulse_target + amount;
	pthread_mutex_unlock(&(servo_data->mutex));
}

void evaluate_servo_pw_command(ServoData *servo_data)
{
	pthread_mutex_lock(&(servo_data->mutex));
	servo_data->pulse_current += servo_data->pulse_change;
	if (servo_data->pulse_change == 0)	// it is evaluating submit_servo_direction_and_speed
	{
		servo_data->pulse_current = servo_data->pulse_target;
		servo_data->pulse_command.pulse_width = (unsigned short int)65536 - (unsigned short int)((9216/10000.0)*10*servo_data->pulse_current);
	}
	else if (servo_data->pulse_change > 0)  // target pulse width given and it reaches that pulse width with servo_data->pulse_change with the servo pulsing frequency period.
	{
		if (servo_data->pulse_current > servo_data->pulse_target)
		{
			servo_data->pulse_current = servo_data->pulse_target;
		}
		servo_data->pulse_command.pulse_width = (unsigned short int)65536 - (unsigned short int)((9216/10000.0)*10*servo_data->pulse_current);
	}
	else if (servo_data->pulse_change < 0) 
	{
		if (servo_data->pulse_current < servo_data->pulse_target)
		{
			servo_data->pulse_current = servo_data->pulse_target;
		}
		servo_data->pulse_command.pulse_width = (unsigned short int)65536 - (unsigned short int)((9216/10000.0)*10*servo_data->pulse_current);		
	}
	pthread_mutex_unlock(&(servo_data->mutex));	
}

void get_servo_pw_val_bytes(ServoData *servo_data, unsigned char *low_byte, unsigned char *high_byte)
{
	pthread_mutex_lock(&(servo_data->mutex));
	*low_byte = servo_data->pulse_command.byte[0];
	*high_byte = servo_data->pulse_command.byte[1];
	pthread_mutex_unlock(&(servo_data->mutex));	
}

void write_servo_position_val(ServoData *servo_data, unsigned char low_byte, unsigned char high_byte)
{
	pthread_mutex_lock(&(servo_data->mutex));
	servo_data->position.byte[0] = low_byte;
	servo_data->position.byte[1] = high_byte;
	pthread_mutex_unlock(&(servo_data->mutex));	
}

void get_servo_position_val(ServoData *servo_data, ServoPosition *servo_position)
{
	pthread_mutex_lock(&(servo_data->mutex));
	*servo_position = servo_data->position.position;
	pthread_mutex_unlock(&(servo_data->mutex));	
}

void write_servo_pw_adc_ranges(ServoData *servo_data, ServoPulse zero_degree_pulse, ServoPulse ninety_degree_pulse, ServoPosition zero_degree_adc_val, ServoPosition ninety_degree_adc_val)
{
	pthread_mutex_lock(&(servo_data->mutex));
	servo_data->range.pulse_width_0_degree = zero_degree_pulse;
	servo_data->range.pulse_width_90_degree = ninety_degree_pulse;
	servo_data->range.position_0_degree = zero_degree_adc_val;
	servo_data->range.position_90_degree = ninety_degree_adc_val;
	servo_data->range.radian_per_pos_quanta = M_PI_2 / (servo_data->range.position_90_degree - servo_data->range.position_0_degree);
	pthread_mutex_unlock(&(servo_data->mutex));	
}

void write_servo_0_degree_adc_val(ServoData *servo_data, ServoPosition zero_degree_adc_val)
{
	if (zero_degree_adc_val > servo_data->range.position_90_degree)
		servo_data->range.position_90_degree = zero_degree_adc_val;
	servo_data->range.position_0_degree = zero_degree_adc_val;
	servo_data->range.radian_per_pos_quanta = M_PI_2 / (servo_data->range.position_90_degree - servo_data->range.position_0_degree);
}

void write_servo_90_degree_adc_val(ServoData *servo_data, ServoPosition ninety_degree_adc_val)
{
	if (ninety_degree_adc_val < servo_data->range.position_0_degree)
		servo_data->range.position_0_degree = ninety_degree_adc_val;
	servo_data->range.position_90_degree = ninety_degree_adc_val;
	servo_data->range.radian_per_pos_quanta = M_PI_2 / (servo_data->range.position_90_degree - servo_data->range.position_0_degree);
}
