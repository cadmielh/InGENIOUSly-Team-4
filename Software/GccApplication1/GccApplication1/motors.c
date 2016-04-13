/*
 * motors.c
 *
 * Created: 13-Apr-16 10:40:53 AM
 *  Author: user
 */ 

#include "motors.h"
#include "sensors.h"
#include "UART_communication.h"


unsigned char speed, direction, time;
int verify,sec;


void PWM1_init()
{
	// initialize TCCR0 as per requirement, say as follows
	TCCR0A |= (1<<COM0A1)|(1<<WGM00);
	TCCR0B = (1<<CS01);
	
	//DDRD|=(1<<PORTD5);
	//PWM PIN
	DDRB|= (1<<PORTB3);
}


void PWM2_init()
{
	// initialize TCCR1 as per requirement, say as follows
	TCCR1A |= (1<<COM1A1)|(1<<WGM10);
	TCCR1B = (1<<CS10);
	
	//DDRD|=(1<<PORTD5);
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


void Motor_1(unsigned char direction_1, unsigned char speed_1, unsigned char time_1)
{
	
	if(direction_1=='F' || direction_1=='f')
	{
		//go forward
		PORTD|=(1<<PORTD5)|(1<<PORTD6);
		_delay_ms(1);
		PORTD|=(1<<PORTD5);
		PORTD&=~(1<<PORTD6);
		for(uint8_t i=32;i<speed;i++)
		{
			OCR0A=i;
			_delay_ms(5);
		}
		
		
	}
	if(direction_1=='B' || direction_1=='b')
	{
		//go backward
		PORTD|=(1<<PORTD5)|(1<<PORTD6);
		_delay_ms(1);
		PORTD|=(1<<PORTD6);
		PORTD&=~(1<<PORTD5);
		for(uint8_t i=32;i<speed;i++)
		{
			OCR0A=i;
			_delay_ms(30);
		}
		
		
	}
	
}


void Motor_2(unsigned char direction_2, unsigned char speed_2, unsigned char time_2)
{
	
	if(direction_2=='F' || direction_2=='f')
	{
		//go forward
		PORTD|=(1<<PORTD3)|(1<<PORTD4);
		_delay_ms(1);
		PORTD|=(1<<PORTD3);
		PORTD&=~(1<<PORTD4);
		for(uint8_t i=32;i<speed;i++)
		{
			OCR1A=i;
			_delay_ms(5);
		}
		//timer(time_1)
		
	}
	if(direction_2=='B' || direction_2=='b')
	{
		//go backward
		PORTD|=(1<<PORTD3)|(1<<PORTD4);
		_delay_ms(1);
		PORTD|=(1<<PORTD4);
		PORTD&=~(1<<PORTD3);
		for(uint8_t i=32;i<speed;i++)
		{
			OCR1A=i;
			_delay_ms(5);
		}
		
		
	}
	
}