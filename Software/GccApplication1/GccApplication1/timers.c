/*
 * timers.c
 *
 * Created: 13-Apr-16 10:56:16 AM
 *  Author: user
 */ 


#include "timers.h"


 // global variable to count the number of overflows
 volatile uint16_t ovfl,time_ms;
 uint8_t chan;
 float sum[3];
 float a[3][36];
 





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
	
	
	
	TIMSK3 |= (1<<OCIE3A) | (1<<TOIE3);
}


float ADC_read(uint8_t channel)
{
	float distance;
	channel=channel & 0b00000111;		//Select ADC Channel, channel must be 0-7
	ADMUX = 0;
	//ADMUX |= (1<<MUX0);        //Clear the older channel that was read
	ADMUX|= channel;		//Defines the new ADC channel to be read
	ADCSRA |=(1<<ADSC);	// enable ADC and start single conversion
	
	
	while(ADCSRA & (1<<ADSC));	// wait for conversion to complete
	//volts=ADC*0.0048828125;
	//distance = 65 * pow(volts, -1.10);
	distance = (2914. / (ADC + 4.98)) -1;
	return distance;
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
	
	
	for(chan=0;chan<=3)
		for(int i=0;i<=35;i++)
			{	a[chan][i]=ADC_read(chan);
				if(i>=2)
					sum[chan]=sum[chan]+a[chan][i];
				a[chan][i]=0;
			}
	sum[chan]=sum[chan]/34;
	
}