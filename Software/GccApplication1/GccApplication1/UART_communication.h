/*
 * UART_communication.h
 *
 * Created: 05-Apr-16 12:35:00 AM
 *  Author: user
 */ 
 
 #ifndef UART_COMMUNICATION_H_
 #define UART_COMMUNICATION_H_
 
 
 #define MYUBRR 130
 
 
 #include <avr/io.h>
 
 
 
 unsigned int my_ubrr = MYUBRR;
 
 void USART_Init();
 void USART_Transmit( unsigned char data );
 unsigned char USART_Receive( void );
 
 
 #endif