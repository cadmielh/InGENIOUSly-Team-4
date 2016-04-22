/*
 * sensors.c
 *
 * Created: 04-Apr-16 11:06:10 PM
 *  Author: user
 */ 

#include "sensors.h"


volatile uint8_t adc_high, adc_low;
uint16_t data_sensor;
uint16_t v[50],chan0[10],chan1[10],chan2[10],chan3[10];
uint32_t total;
uint8_t tmp = 0;
uint8_t contor=0;
uint8_t val;
uint32_t sum0=0,sum1=0,sum2=0,sum3=0,s[4];

float distance;



void ADC_init()
{
	DDRA &= ~(1<<PINA1);
	ADCSRA |= 1<<ADEN;		  //Turn on ADC
}



float ADC_read(uint8_t channel)
{
	float distance;
	float volts;
	uint16_t adc_value;            //Variable used to store the value read from the ADC
	
	channel=channel & 0b00000111;		//Select ADC Channel, channel must be 0-7
	ADMUX = 0;
	//ADMUX |= (1<<MUX0);        //Clear the older channel that was read
	ADMUX|= channel;		//Defines the new ADC channel to be read
	
	ADCSRA |=(1<<ADSC);	// enable ADC and start single conversion
	
	
	while(ADCSRA & (1<<ADSC));	// wait for conversion to complete
	adc_value=ADC;
	volts = adc_value+1;
	distance = 65 * pow(volts, -1.1);
	//distance = (2914. / (ADC + 5)) -1;
	return distance;
}


void ADC_update_values()
{		//taking first value from sensor which is inaccurate
		flag=0;
		
		ADC_read(0);
		ADC_read(1);
		ADC_read(2);
		ADC_read(3);
		
		chan0[contor]=ADC_read(0);
		chan1[contor]=ADC_read(1);
		chan2[contor]=ADC_read(2);
		chan3[contor]=ADC_read(3);
		
		sum0 += chan0[contor];
		chan0[contor]=0;
		sum1 += chan1[contor];
		chan1[contor]=0;
		sum2 += chan2[contor];
		chan2[contor]=0;
		sum3 += chan3[contor];
		chan3[contor]=0;
		
	contor++;
	if(contor==10)
			{
				flag=1;
				contor=0;
				
				s[0]=sum0;
				sum0=0;
				s[1]=sum1;
				sum1=0;
				s[2]=sum2;
				sum2=0;
				s[3]=sum3;
				sum3=0;
				
			}
}


float get_ADC_average(uint8_t channel)
{

		switch(channel)
		{
			case 0:  data_sensor = s[0] /10;
					s[0]=0;
					 distance = (2914. / (data_sensor + 4.98)) -1;	//in cm formula
					 break;
			case 1:  data_sensor = s[1] /10;
					s[1]=0;
					 distance = (2914. / (data_sensor + 4.98)) -1;	//in cm formula
					 break;
			case 2:  data_sensor = s[2] /10;
					s[2]=0;
					 distance = (2914. / (data_sensor + 4.98)) -1;	//in cm formula
					 break;
			case 3:  data_sensor = s[3] /10;
					s[3]=0;
				     distance = (2914. / (data_sensor + 4.98)) -1;	//in cm formula
					 break;		 
		}
		flag=0;
		return distance; //ADC average in cm
}


void encoders_init()
{
	/* set PD2, PD3 as input */
	DDRD &=~ (1 << PORTD2);
	DDRD &=~(1 << PORTD3);/* PD2 and PD3 as input */
	PORTD |= (1 << PORTD2)|(1<<PORTD3);   /* PD2 and PD3 pull-up enabled   */
	
	EIMSK|=(1<<INT0)|(1<<INT1);	//We use external interrupt INT0 and INT1
	EICRA|=(1<<ISC00)|(1<<ISC01)|(1<<ISC10)|(1<<ISC11);	//The rising edge of INT0 and INT1 generates asynchronously an interrupt request.
	
	grey_left=0;
	grey_right=0;
	rotations_right=0;
	rotations_left=0;
	
}



ISR(INT0_vect) //Right side interrupt
{
	
		grey_right++;
		if(grey_right>=10)
		{
			rotations_right++;
			grey_right=0;
		}
	
}


ISR(INT1_vect)  //Left side interrupt
{
	
	grey_left++;
	if(grey_left>=10)
	{
		rotations_left++;
		grey_left=0;
	}
	
}


