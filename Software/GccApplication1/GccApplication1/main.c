

#define F_CPU 20000000ul	// 20 MHz oscillator.

#include "sensors.h" 
#include "UART_communication.h"
#include "motors.h"
#include "timers.h"




int main (void)
{ 
	
	uint8_t speed;
	
	USART_Init();
	ADC_init();
	PWM1_init();
	PWM2_init();
	timer3_init();
	
	
	speed=130;
	
	
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
		
		
			Motor_1('b',speed,8);
			
		
		

		
		
	} 
return 0;
}
