/*
 * motors.c
 *
 * Created: 13-Apr-16 10:40:53 AM
 *  Author: user
 */ 

#include "motors.h"
#include "sensors.h"
#include "UART_communication.h"
#include "timers.h"


unsigned char speed;
unsigned char direction;
unsigned char time;
int verify;
int start_once1=1;
int start_once2=1;
unsigned int sec1;
unsigned int sec2;
uint8_t tm1=1;
uint8_t tm2=1;
uint8_t moving_forward,moving_backward;



void PWM1_init()
{
	// initialize TCCR0 as per requirement, say as follows
	TCCR0A |= (1<<COM0A1)|(1<<WGM00);
	TCCR0B = (1<<CS02); //prescaler of 254
	
	//PWM PIN
	DDRB|= (1<<PORTB3);
}


void PWM2_init()
{
	// initialize TCCR1 as per requirement, say as follows
	TCCR0A |= (1<<COM0B1)|(1<<WGM02);
	TCCR0B = (1<<CS02); //prescaler of 254
	
	//PWM PIN
	DDRB|= (1<<PORTB4);
}




unsigned int receive_parameters()
{
	unsigned int OK=0;    // semaphore to verify that parameters were received properly
	
	if (verify)
	{
		direction=0x00;		
		direction = USART_Receive();
		if(direction=='F' || direction=='B' || direction=='f' || direction=='b')   //if first parameter is B(backward) or F(forward), ready to receive the speed
		{
			speed=0x00;
			speed=USART_Receive();
			if(speed>0 && speed<=0xFF)     //if speed parameter is in speed limits
				{
					time = 0x00;
					time=USART_Receive();
					if(time!=0x00)        
						{
							OK=1;  //all parameters were received properly and are free to use
						}
						else
						{
							speed=0x00;
							direction=0x00;
							time=0x00;
						}
				}
		}
		else
		{
			speed=0x00;
			direction=0x00;
			time=0x00;
		}
	}
			

	return OK;
}


void Motor_1(unsigned char direction_1, unsigned char speed_1)
{
	
		if(direction_1=='F' || direction_1=='f')
		{
				//go forward
				PORTD|=(1<<PORTD5)|(1<<PORTD6);
				_delay_ms(1);
				PORTD|=(1<<PORTD5);
				PORTD&=~(1<<PORTD6);
				OCR0A=speed_1;
				//timer(time_1)
		
		}
		if(direction_1=='B' || direction_1=='b')
		{
				//go backward
				PORTD|=(1<<PORTD5)|(1<<PORTD6);
				_delay_ms(1);
				PORTD|=(1<<PORTD6);
				PORTD&=~(1<<PORTD5);
					OCR0A=speed_1;
	}
	
}

void Motor_2(unsigned char direction_2, unsigned char speed_2)
{
	
	if(direction_2=='F' || direction_2=='f')
	{
		//go forward
		PORTD|=(1<<PORTD3)|(1<<PORTD4);
		_delay_ms(1);
		PORTD|=(1<<PORTD3);
		PORTD&=~(1<<PORTD4);
		OCR0B=speed_2;
		//timer(time_1)
		
	}
	if(direction_2=='B' || direction_2=='b')
	{
		//go backward
		PORTD|=(1<<PORTD3)|(1<<PORTD4);
		_delay_ms(1);
		PORTD|=(1<<PORTD4);
		PORTD&=~(1<<PORTD3);
		OCR0B=speed_2;
		
	}
	
}


void motors_right(uint8_t speed_right, char direction_right)
{
	if(direction_right == 'f')	//forward 
	{
		PORTD&=~(1<<PORTD5);
		OCR0A=speed_right;
	}
	if(direction_right == 'b')
	{
		PORTD|=(1<<PORTD5);
		OCR0A=speed_right;
	}
}


void motors_left(uint8_t speed_left,char direction_left)
{
	if(direction_left == 'f')	//forward
	{
		PORTD&=~(1<<PORTD6);
		OCR0B=speed_left;
	}
	if(direction_left == 'b')
	{
		PORTD|=(1<<PORTD6);
		OCR0B=speed_left;
	}
}


void reglation_by_left(uint8_t pwm_left, uint8_t pwm_right)
{
	float data_sensor,error;
	data_sensor=ADC_read(0);		//left sensor's channel
									//in loc de ADC_read, valoarea filtrata
	error=11.9 - data_sensor;
	
	if(error<=0.1 && error>=-0.2)
		{
			OCR0B=pwm_left;
			OCR0A=pwm_right;
		}
	if(error> 0.1 && error<=1)
		{
			OCR0B=pwm_left+5;
			OCR0B=pwm_right;
		}
	if (error>1 && error <=2)
	{	
		OCR0B=pwm_left+10;
		OCR0A=pwm_right;
	}
	if(error>2 && error <=3)
	{
		OCR0B=pwm_left+20;
		OCR0A=pwm_right;
	}
	if(error > 3)
	{
		OCR0B=pwm_left+40;
		OCR0A=pwm_right;
	}
	if(error < -0.2 &&  error >= -1)
	{
		OCR0A=pwm_right+5;
		OCR0B=pwm_left;
	}
	if(error <-1 && error >=-2)
	{
		OCR0A=pwm_right+10;
		OCR0B=pwm_left;
	}
	if(error <-2 && error>=-3)
	{
		OCR0A=pwm_right+20;
		OCR0B=pwm_left;
	}
	if(error < -3)
	{
		OCR0A=pwm_right+40;
		OCR0B=pwm_left;
	}
		

}

void stop_motors()
{
	OCR0A=0;
	OCR0B=0;
	moving_forward=0;
}

/*

if ((s_time.s - sec1)>=time_1 && tm1)
{
	for(uint8_t i=speed_1;i>0;i--)
	{
		OCR0A=i;
		_delay_ms(5);
	}
	tm1=0;
}*/