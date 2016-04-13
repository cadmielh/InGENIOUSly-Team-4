/*
 * timers.h
 *
 * Created: 13-Apr-16 10:56:27 AM
 *  Author: user
 */ 


 #ifndef TIMERS_H_
 #define TIMERS_H_
 
 #define F_CPU 20000000ul	// 20 MHz oscillator.
 
 
 #include <avr/io.h>
 #include <util/delay.h>
 #include <avr/interrupt.h>
 
  struct{
	  unsigned int ms;
	  unsigned int s;
	  unsigned int m;
  }sys_time;

 
 void timer3_init();
 
 
 
 #endif