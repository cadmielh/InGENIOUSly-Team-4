/*
 * sensors.c
 *
 * Created: 04-Apr-16 11:06:10 PM
 *  Author: user
 */ 

#include "sensors.h"




void ADC_init()
{
	//ADMUX |= 1<<ADLAR;
	ADCSRA |= ((1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0)); // prescaler of 128, 20M/128 = 156250 Hz
	//ADMUX |= 1<<REFS0;       //Voltage reference from AVCC (5v)
	ADCSRA |= 1<<ADEN;		  //Turn on ADC
	//ADCSRA |= 1<<ADSC;	//to start the first conversion
	
	
	/*ADCSRA |= ((1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0)); // prescaler of 128, 20M/128 = 156250 Hz
	ADMUX |= 1<<ADLAR;
	ADMUX |= (1<<REFS0);       //Voltage reference from AVCC (5v)
	ADCSRA |= 1<<ADIE;	//interrupt enable
	ADCSRA |= 1<<ADEN;		  //Turn on ADC
	sei();
	ADCSRA |= 1<<ADSC;	//to start the first conversion
	*/
	
	
	/*ADMUX |= (1<<REFS0);       //Voltage reference from AVCC (5v)
	 
	ADCSRA |= (1<<ADATE);                //Signal source, in this case is the free-running
	ADCSRB &= ~((1<<ADTS2)|(1<<ADTS1)|(1<<ADTS0));    //ADC in free-running mode
	*/
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

/*ISR(ADC_vect)
{
	char adcResult[4];
	itoa(ADCH, adcResult,10);
	USART_Transmit(adcResult);
	USART_Transmit("      ");
	ADCSRA |= 1<<ADSC;
}*/
