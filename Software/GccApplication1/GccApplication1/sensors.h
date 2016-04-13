/*
 * sensors.h
 *
 * Created: 05-Apr-16 12:27:52 AM
 *  Author: user
 */ 
#ifndef SENSORS_H_
#define SENSORS_H_


#include <avr/io.h>
#include <stdlib.h>


uint16_t adc_value;            //Variable used to store the value read from the ADC
volatile uint8_t adc_high, adc_low;

void ADC_init(void);            //Function to initialize/configure the ADC
uint16_t ADC_read(uint8_t channel);    //Function to read an arbitrary analogic channel/pin		

#endif