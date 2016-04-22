


#include "sensors.h" 
#include "UART_communication.h"
#include "motors.h"
#include "timers.h"




float rezultat;
 char primit;
float v[40];

int main (void)
{ 
	
	uint8_t speed;
	speed=200;

	
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
		

		//rezultat=get_ADC_average(0);
		rezultat = get_ADC_average(0);
	
	
				
		
		
		
		
		/*if(rotations_left>=3)
		{
		Motor_2('b',speed,5);
		_delay_ms(1000);
		}*/
		
			//Motor_1('b',speed,5);
			//Motor_2('b',speed,5);
		

	} 
return 0;
}
