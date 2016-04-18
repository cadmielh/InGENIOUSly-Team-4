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


void PWM1_init()
{
	// initialize TCCR0 as per requirement, say as follows
	TCCR0A |= (1<<COM0A1)|(1<<WGM00);
	TCCR0B = (1<<CS01);
	
	//PWM PIN
	DDRB|= (1<<PORTB3);
}


void PWM2_init()
{
	// initialize TCCR1 as per requirement, say as follows
	TCCR0A |= (1<<COM0B1)|(1<<WGM02);
	TCCR0B = (1<<CS01);
	
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


void Motor_1(unsigned char direction_1, unsigned char speed_1,unsigned char time_1)
{
	
	sec1=0;
	
	if(start_once1==1)
	{
		if(direction_1=='F' || direction_1=='f')
		{
			//go forward
			PORTD|=(1<<PORTD6)|(1<<PORTD7);
			_delay_ms(1);
			PORTD|=(1<<PORTD6);
			PORTD&=~(1<<PORTD7);
			start_once1=0;
			sec1=s_time.s;
			for(uint8_t i=32;i<speed_1;i++)
			{
				OCR0A=i;
				_delay_ms(5);
			}
		
		}
		if(direction_1=='B' || direction_1=='b')
		{
			//go backward
			PORTD|=(1<<PORTD6)|(1<<PORTD7);
			_delay_ms(1);
			PORTD|=(1<<PORTD7);
			PORTD&=~(1<<PORTD6);
			start_once1=0;
			sec1=s_time.s;
			for(uint8_t i=32;i<speed_1;i++)
			{
				OCR0A=i;
				_delay_ms(5);
			}
		}
	}
	
	
		if ((s_time.s - sec1)>=time_1 && tm1)
		{
			for(uint8_t i=speed_1;i>0;i--)
			{
				OCR0A=i;	
				_delay_ms(5);
			}
			tm1=0;
		}	
	
}


void Motor_2(unsigned char direction_2, unsigned char speed_2,unsigned char time_2)
{
	sec2=0;
	if(start_once2==1)
	{
		
		if(direction_2=='F' || direction_2=='f')
		{
			//go forward
			PORTD|=(1<<PORTD4)|(1<<PORTD5);
			_delay_ms(1);
			PORTD|=(1<<PORTD4);
			PORTD&=~(1<<PORTD5);
			start_once2=0;
			sec2=s_time.s;
			for(uint8_t i=32;i<speed_2;i++)
			{
				OCR0B=i;
				_delay_ms(5);
			}
			//timer(time_1)
			
		}
		if(direction_2=='B' || direction_2=='b')
		{
			//go backward
			PORTD|=(1<<PORTD4)|(1<<PORTD5);
			_delay_ms(1);
			PORTD|=(1<<PORTD5);
			PORTD&=~(1<<PORTD4);
			start_once2=0;
			sec2=s_time.s;
			for(uint8_t i=32;i<speed_2;i++)
			{
				OCR0B=i;
				_delay_ms(5);
			}
		}
		
	}
	
	
	if ((s_time.s - sec2)>=time_2 && tm2)
	{
		for(uint8_t i=speed_2;i>0;i--)
		{
			OCR0B=i;
			_delay_ms(5);
		}
		tm2=0;
	}
	
	
	
}
