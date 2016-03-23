#define F_CPU 20000000ul	// 20 MHz oscillator.
#define BAUD 9600
#define MYUBRR 130


#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h> 




void USART_Init();
void USART_Transmit( unsigned char data );
unsigned char USART_Receive( void );
void PWM_init();
unsigned int receive_parameters();
void Motor_1(unsigned char direction_1, unsigned char speed_1, unsigned char time_1);
int timer(uint8_t x);
void timer3_init();
unsigned int my_ubrr = MYUBRR;
unsigned char speed,direction,time;
int verify;
unsigned char test = 0;

// global variable to count the number of overflows
volatile uint16_t ovfl,time_ms;


struct{
		unsigned int ms;
		unsigned int s;
		unsigned int m;
}sys_time;



int main (void)
{ 
	USART_Init();
	 PWM_init();
	 timer3_init();
	int sec =0;
	verify=1;
	time=0;
	
	PORTD|=(1<<PORTD6)	;
	 
	while (1)  // main loop										
	{
		
		if(receive_parameters())
		{
			
			Motor_1(direction,speed,time);
			sec=sys_time.s;
			verify=0;
		}
		
			
		if ((sys_time.s - sec)>=time)
		{
			for(uint8_t i=speed;i>0;i--)
			{
				OCR0A=i;
				_delay_ms(5);
			}
			verify=1;
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
	while ( !(UCSR0A & (1<<RXC0)))
	{;}
	/* Get and return received data from buffer */
	return UDR0;
}



unsigned int receive_parameters()
{
	unsigned int OK=0;    // semaphore to verify that parameters were received properly
	
	if (verify)
	{
		direction=0x00;		
		direction = USART_Receive();
		if(direction=='F' || direction=='B' || direction=='f' || direction=='b')   //if first parameter is B(backward) or F(forward), ready to receive the speed
		{
			speed=0x00;
			speed=USART_Receive();
			if(speed>0 && speed<=0xFF)     //if speed parameter is in speed limits
				{
					time = 0x00;
					time=USART_Receive();
					if(time!=0x00)        
						{
							OK=1;  //all parameters were received properly and are free to use
						}
				}
		}
	}
			

	return OK;
}


void Motor_1(unsigned char direction_1, unsigned char speed_1, unsigned char time_1)
{
	
	if(direction_1=='F' || direction_1=='f')
	{
		//go forward
		PORTD|=(1<<PORTD5)|(1<<PORTD6);
		_delay_ms(1);
		PORTD|=(1<<PORTD5);
		PORTD&=~(1<<PORTD6);
		for(uint8_t i=32;i<speed;i++)
		{
			OCR0A=i;
			_delay_ms(5);
		}
		//timer(time_1)
		
	}
	if(direction_1=='B' || direction_1=='b')
	{
		//go backward
		PORTD|=(1<<PORTD5)|(1<<PORTD6);
		_delay_ms(1);
		PORTD|=(1<<PORTD6);
		PORTD&=~(1<<PORTD5);
		for(uint8_t i=32;i<speed;i++)
		{
			OCR0A=i;
			_delay_ms(5);
		}
		
		
	}
	
}


void timer3_init()
{
	// clear on compare match
	TCCR3A |= (1<<COM3A1);
	TCCR3B |= (1<<WGM32);
	// set up timer with no prescaler count to 500
	TCCR3B |= (1 << CS30);
	
	//set up compare value
	OCR3AH = 0x01;
	OCR3AL = 0xF4;
	
	// initialize counter
	TCNT3H = 0;
	TCNT3L = 0;
	
	sei();
	
	TIMSK3 |= (1<<OCIE3A) | (1<<TOIE3);
}

ISR(TIMER3_COMPA_vect)
{
	
	
	// initialize counter
	TCNT3H = 0;
	TCNT3L = 0;
	// keep a track of number of overflows
	ovfl++;
	if(ovfl>=40)
	{	sys_time.ms++;	
		if (sys_time.ms>=1000)
		{
			sys_time.s++;
			sys_time.ms=0;
			if(sys_time.s>=60)
			{
				sys_time.m++;
				sys_time.s=0;
				
				if(sys_time.m>=60)
					sys_time.m=0;
			}
			
		}
		ovfl=0;
	}
	
}


