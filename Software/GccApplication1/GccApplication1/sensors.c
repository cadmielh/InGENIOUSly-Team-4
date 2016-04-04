/*
 * sensors.c
 *
 * Created: 04-Apr-16 11:06:10 PM
 *  Author: user
 */ 

void ADC_init()
{
	ADMUX |= (1<<REFS0);       //Voltage reference from AVCC (5v)
	ADCSRA = (1<<ADEN);		  //Turn on ADC 
	ADCSRA |= ((1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0)); // prescaler of 128, 20M/128 = 156250 Hz   
}


uint16_t ADC_read(uint8_t channel)
{
	
	channel=channel & 0b00000111;		//Select ADC Channel, channel must be 0-7
	
	ADMUX &= 0xF0;        //Clear the older channel that was read
	ADMUX|=channel;		//Defines the new ADC channel to be read
	
	ADCSRA |= (1<<ADSC);	// start single conversion
	
	while(ADCSRA & (1<<ADSC));		// wait for conversion to complete
	
	return ADC;
}
