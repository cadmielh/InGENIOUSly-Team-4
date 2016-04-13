/*
 * motors.h
 *
 * Created: 13-Apr-16 10:41:35 AM
 *  Author: user
 */ 

#ifndef MOTORS_H_
#define MOTORS_H_

#define F_CPU 20000000ul	// 20 MHz oscillator.

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>





void PWM1_init();
void PWM2_init();
void Motor_1(unsigned char direction_1, unsigned char speed_1, unsigned char time_1);
void Motor_2(unsigned char direction_2, unsigned char speed_2, unsigned char time_2);
unsigned int receive_parameters();
void timer3_init();



#endif