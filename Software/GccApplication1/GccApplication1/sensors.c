/*
 * sensors.c
 *
 * Created: 04-Apr-16 11:06:10 PM
 *  Author: user
 */ 

#include "sensors.h"

uint16_t adc_value;            //Variable used to store the value read from the ADC
volatile uint8_t adc_high, adc_low;
uint16_t data_sensor;
uint16_t v[50];
uint32_t total;


void ADC_init()
{
	ADCSRA |= ((1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0)); // prescaler of 128, 20M/128 = 156250 Hz
	ADCSRA |= 1<<ADEN;		  //Turn on ADC
}


uint16_t ADC_read(uint8_t channel)
{
	adc_low=0;
	adc_high=0;
	//channel=channel & 0b00000111;		//Select ADC Channel, channel must be 0-7

	
	//ADMUX &= 0xb00000000;        //Clear the older channel that was read
	//ADMUX|= channel;		//Defines the new ADC channel to be read
	
	ADCSRA |= (1<<ADSC);	// start single conversion
	
	while(ADCSRA & (1<<ADSC));	// wait for conversion to complete
	
	adc_value=ADC;
	
	return adc_value;
}

