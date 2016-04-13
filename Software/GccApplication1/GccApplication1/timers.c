/*
 * timers.c
 *
 * Created: 13-Apr-16 10:56:16 AM
 *  Author: user
 */ 


#include "timers.h"


 // global variable to count the number of overflows
 volatile uint16_t ovfl,time_ms;





void timer3_init()
{
	// clear on compare match
	TCCR3A |= (1<<COM3A1);
	TCCR3B |= (1<<WGM32);
	// set up timer with no prescaler count to 500
	TCCR3B |= (1 << CS30);
	
	//set up compare value
	OCR3AH = 0x01;
	OCR3AL = 0xF4;
	
	// initialize counter
	TCNT3H = 0;
	TCNT3L = 0;
	
	sei();
	
	TIMSK3 |= (1<<OCIE3A) | (1<<TOIE3);
}

ISR(TIMER3_COMPA_vect)
{
	
	// initialize counter
	TCNT3H = 0;
	TCNT3L = 0;
	// keep a track of number of overflows
	ovfl++;
	if(ovfl>=40)
	{	s_time.ms++;
		if (s_time.ms>=1000)
		{
			s_time.s++;
			s_time.ms=0;
			if(s_time.s>=60)
			{
				s_time.m++;
				s_time.s=0;
				
				if(s_time.m>=60)
				s_time.m=0;
			}
			
		}
		ovfl=0;
	}
	
}

