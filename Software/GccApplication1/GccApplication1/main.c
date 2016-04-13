

#define PORT_ON(port,pin) port |= (1<<pin)
#define PORT_OFF(port,pin) port &= ~(1<<pin)
#define F_CPU 20000000ul	// 20 MHz oscillator.

#include <util/delay.h>
#include <avr/interrupt.h>
#include "sensors.h" 
#include "UART_communication.h"
#include <math.h>




void PWM1_init();
void PWM2_init();
unsigned int receive_parameters();
void Motor_1(unsigned char direction_1, unsigned char speed_1, unsigned char time_1);
void Motor_2(unsigned char direction_2, unsigned char speed_2, unsigned char time_2);
int timer(uint8_t x);
void timer3_init();


unsigned char speed,direction,time;
int verify,sec;
unsigned char test = 0;
uint8_t j=0;
uint16_t data_sensor;
uint16_t v[50];
uint32_t total;

// global variable to count the number of overflows
volatile uint16_t ovfl,time_ms;


struct{
		unsigned int ms;
		unsigned int s;
		unsigned int m;
}sys_time;




int main (void)
{ 
	int tm=1;

	
	//USART_Init();
	ADC_init();
	PWM1_init();
	timer3_init();
	//PWM2_init();
	
	
	sec=0;
	verify=1;
	speed=160;
	/*USART_Init();
	 PWM_init();
	
	 timer3_init();
	int sec=0;
	verify=1;
	time=0;
	
	//PORT_ON(PORTD,PORTD6);
	 */
	while (1)  // main loop										
	{
		//total=0;
		
		
		
		/*data_sensor=0;
		for(int i=0;i<50;i++)
			{
				v[i]=ADC_read(0);
				//total = total + ADC_read(0);
			}
			
		//total=(uint32_t)total/10;
		data_sensor=v[25];
		
		USART_Transmit(data_sensor);
		USART_Transmit(' ');
		_delay_ms(1000);
		*/
		
		
		
		
		
		if(verify==1)
		{
			Motor_1('b',speed,5);
			//Motor_2('F',speed,5);
			sec=sys_time.s;
			verify=0;
		}
		
		if ((sys_time.s - sec)>=5 && tm)
		{
			for(uint8_t i=speed;i>0;i--)
			{
				OCR0A=i;
				
				_delay_ms(5);
			}
			tm=0;
		}
		
		
		
		
		
		
		/*if(data_sensor>=160 && data_sensor<170)
		{
			USART_Transmit('A');
			USART_Transmit(' ');
			_delay_ms(200);
		}
		if(data_sensor>170 && data_sensor<175)
		{
			USART_Transmit('B');
			USART_Transmit(' ');
			_delay_ms(200);
		}
		if(data_sensor>=175 && data_sensor<180)
		{
			USART_Transmit('C');
			USART_Transmit(' ');
			_delay_ms(200);
		}
		 if (data_sensor >=180 && data_sensor<200)
		{
			USART_Transmit('D');
			USART_Transmit(' ');
			_delay_ms(200);
		}
		 if (data_sensor >=200 && data_sensor<250)
		{
			USART_Transmit('E');
			USART_Transmit(' ');
			_delay_ms(200);
		}
		 if (data_sensor >=250 && data_sensor<350)
		{
			USART_Transmit('F');
			USART_Transmit(' ');
			_delay_ms(200);
		}
		 if (data_sensor >=350 && data_sensor<500)
		{
			USART_Transmit('G');
			USART_Transmit(' ');
			_delay_ms(200);
		}
		if(data_sensor>=500 || data_sensor<=164)
		{
			USART_Transmit('X');
			USART_Transmit(' ');
			_delay_ms(200);
		}*/
		
		
		
		

		
		/*if(receive_parameters())
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
		*/
		
	} 
return 0;
}



void PWM1_init()
{
	// initialize TCCR0 as per requirement, say as follows
	TCCR0A |= (1<<COM0A1)|(1<<WGM00);
	TCCR0B = (1<<CS01);
	
	//DDRD|=(1<<PORTD5);
	//PWM PIN
	DDRB|= (1<<PORTB3);
}


void PWM2_init()
{
	// initialize TCCR1 as per requirement, say as follows
	TCCR1A |= (1<<COM1A1)|(1<<WGM10);
	TCCR1B = (1<<CS10);
	
	//DDRD|=(1<<PORTD5);
	//PWM PIN
	DDRB|= (1<<PORTB4);
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
						else
						{
							speed=0x00;
							direction=0x00;
							time=0x00;
						}
				}
				/*else
				{
					speed=0x00;
					direction=0x00;
					time=0x00;
				}*/
		}
		else
		{
			speed=0x00;
			direction=0x00;
			time=0x00;
		}
	}
			

	return OK;
}


void Motor_1(unsigned char direction_1, unsigned char speed_1, unsigned char time_1)
{
	
	if(direction_1=='F' || direction_1=='f')
	{
		//go forward
		//PORT_ON(PORTD,PORTD5);
		//PORT_ON(PORTD,PORTD6);
		PORTD|=(1<<PORTD5)|(1<<PORTD6);
		_delay_ms(1);
		//PORT_ON(PORTD,PORTD5);
		PORTD|=(1<<PORTD5);
		//PORT_OFF(PORTD,PORTD6);
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
		//PORT_ON(PORTD,PORTD5);
		//PORT_ON(PORTD,PORTD6);
		PORTD|=(1<<PORTD5)|(1<<PORTD6);
		_delay_ms(1);
		//PORT_ON(PORTD,PORTD6);
		PORTD|=(1<<PORTD6);
		//PORT_OFF(PORTD,PORTD5);
		PORTD&=~(1<<PORTD5);
		for(uint8_t i=32;i<speed;i++)
		{
			OCR0A=i;
			_delay_ms(30);
		}
		
		
	}
	
}


void Motor_2(unsigned char direction_2, unsigned char speed_2, unsigned char time_2)
{
	
	if(direction_2=='F' || direction_2=='f')
	{
		//go forward
		//PORT_ON(PORTD,PORTD3);
		//PORT_ON(PORTD,PORTD4);
		PORTD|=(1<<PORTD3)|(1<<PORTD4);
		_delay_ms(1);
		//PORT_ON(PORTD,PORTD3);
		PORTD|=(1<<PORTD3);
		//PORT_OFF(PORTD,PORTD4);
		PORTD&=~(1<<PORTD4);
		for(uint8_t i=32;i<speed;i++)
		{
			OCR1A=i;
			_delay_ms(5);
		}
		//timer(time_1)
		
	}
	if(direction_2=='B' || direction_2=='b')
	{
		//go backward
		//PORT_ON(PORTD,PORTD3);
		//PORT_ON(PORTD,PORTD4);
		PORTD|=(1<<PORTD3)|(1<<PORTD4);
		_delay_ms(1);
		//PORT_ON(PORTD,PORTD4);
		PORTD|=(1<<PORTD4);
		//PORT_OFF(PORTD,PORTD3);
		PORTD&=~(1<<PORTD3);
		for(uint8_t i=32;i<speed;i++)
		{
			OCR1A=i;
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


