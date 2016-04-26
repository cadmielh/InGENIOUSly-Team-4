


#include "sensors.h" 
#include "UART_communication.h"
#include "motors.h"
#include "timers.h"




float rezultat;
 char primit;
float v[40];
double media=0, medieb;

int main (void)
{ 
	
	uint8_t speed;
	speed=200;

	flag=0;
	
	USART_Init();
	ADC_init();
	PWM1_init();
	PWM2_init();
	timer3_init();
	encoders_init();
	sei(); //enable interrupts
	
	OCR0A=0;
	while (1)  // main loop										
	{
	
		
		
		ADC_read(0);
		for(int i=0;i<40;i++)
		{	v[i]=ADC_read(0);
			media=media+v[i];
		}
		media=media/40;
		if(media<3)
			OCR0B=0;
		if(media>=3 && media<=5)
			OCR0B=250;
		if(media>5 && media<=10)
			OCR0B=200;
		if(media>10 && media<=15)
			OCR0B=150;
		if(media > 15)
			OCR0B=100;
		
		

	} 
return 0;
}
