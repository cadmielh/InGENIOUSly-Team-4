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
#include <avr/interrupt.h>
#include <math.h>


volatile uint8_t grey_right;
volatile uint8_t rotations_right;
volatile uint8_t grey_left;
volatile uint8_t rotations_left;

void ADC_init(void);            //Function to initialize/configure the ADC
uint16_t ADC_read(uint8_t channel);    //Function to read an arbitrary analogic channel/pin		
void encoders_init(void);




#endif