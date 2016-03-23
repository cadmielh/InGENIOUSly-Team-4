#define F_CPU 20000000ul	// 20 MHz oscillator.
#define BAUD 9600
#define MYUBRR 130


#include <avr/delay.h>
#include <avr/io.h> 




void USART_Init();
void USART_Transmit( unsigned char data );
unsigned char USART_Receive( void );
void PWM_init();
unsigned int my_ubrr = MYUBRR;
unsigned char speed;


int main (void)
{ 
	USART_Init();
	 PWM_init();
	 
	 
	
	 
	while (1)  // main loop										
	{
		
		speed = USART_Receive();
		if(speed != 0)
		 {
				OCR0A=speed;
				USART_Transmit(speed);
		 }
	} 
return 0;
}


void PWM_init()
{
	// initialize TCCR0 as per requirement, say as follows
	TCCR0A |= (1<<COM0A1)|(1<<WGM00);
	TCCR0B = (1<<CS01);
	
	//DDRD|=(1<<PORTD5);
	//PWM PIN
	DDRB|= (1<<PORTB3);
}



void USART_Init()
{
	/* Set baud rate */
	UBRR0H = (unsigned char)(my_ubrr>>8);
	UBRR0L = (unsigned char)my_ubrr;
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