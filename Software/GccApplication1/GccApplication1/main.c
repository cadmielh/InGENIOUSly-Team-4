


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
	
	
	while (1)  // main loop										
	{
		//total=0;
		
		
		ADC_read(0);
		for(int i=0;i<40;i++)
		{	v[i]=ADC_read(0);
			media=media+v[i];
		}
		media=media/40;
		reglation_by_left(PWM,PWM);
		
		
		
			
			
		//if(flag==1)
			//rezultat = get_ADC_average(0);
		
		/*if(flag==0)
		{	motors_backward(170);
			flag=1;
		}
	*/
		
		//_delay_ms(1000);
		//motors_right(0,'f');
		//motors_left(0,'f');
		//PORTD|=(1<<PORTD5);
		
		/*for(int i=0;i<=200;i++)
		{
			OCR0A=i;
			OCR0B=i;
			_delay_ms(10);
		}*/
		
		
		
		
		

	} 
return 0;
}
