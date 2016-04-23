/*
 * motors.h
 *
 * Created: 13-Apr-16 10:41:35 AM
 *  Author: user
 */ 

#ifndef MOTORS_H_
#define MOTORS_H_

#define F_CPU 12000000ul	// 12 MHz oscillator.
#define PWM 60 
 
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>





void PWM1_init();
void PWM2_init();
void motors_left(uint8_t speed_left,char direction_left);
void motors_right(uint8_t speed_right, char direction_right);
void reglation_by_left(uint8_t pwm_left, uint8_t pwm_right);
unsigned int receive_parameters();
void timer3_init();
void stop_motors();



#endif