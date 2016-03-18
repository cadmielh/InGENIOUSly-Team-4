/*
 * App.cpp
 *
 * Created: 18-Mar-16 2:54:52 PM
 * Author : user
 */ 

#include <avr/io.h>
#include <avr/delay.h>
#include <stdlib.h>




void USART_Init(  )
{
	/* Set baud rate */
	long int baud=20000000/(16*(UBRR0 + 1));
	UBRR0H = (unsigned char)(baud>>8);
	UBRR0L = (unsigned char)baud;
	
	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}


void USART_Transmit( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) )
	;
	/* Put data into buffer, sends the data */
	UDR0 = data;
}


unsigned char USART_Receive( void )
{
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) )
	;
	/* Get and return received data from buffer */
	return UDR0;
}





	
		void pwm()
		{
			    // initialize TCCR0 as per requirement, say as follows
			    TCCR0B |= (1<<WGM00)|(1<<COM0B1)|(1<<WGM01)|(1<<CS00);
				//PWM PIN
			    DDRB|= (1<<PB3);
		}
		
	int main(void)
		{
				DDRB|= (1<<PB3);
				USART_Init( );
				USART_Receive();
				int valoare=UDR0;
		while(1)
		{
					
		
		
		
		if(valoare == 48+1)
			{
				PORTB|=(1<<PB3);
				_delay_ms(10000);
				PORTB&=~(1<<PB3);
				_delay_ms(500);
			}
			else if (valoare == 48+2)
			{
				PORTB|=(1<<PB3);
				_delay_ms(500);
				PORTB&=~(1<<PB3);
				_delay_ms(500);
			}
			else
			{
				PORTB|=(1<<PB3);
				_delay_ms(500);
				PORTB&=~(1<<PB3);
				_delay_ms(10000);
			}
	
	}
	}

