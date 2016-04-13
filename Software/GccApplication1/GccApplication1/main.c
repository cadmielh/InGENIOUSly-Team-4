

#define F_CPU 20000000ul	// 20 MHz oscillator.

#include "sensors.h" 
#include "UART_communication.h"
#include "motors.h"
#include "timers.h"




int main (void)
{ 
	int check=1,sec=0,tm=1;
	uint8_t speed;
	
	USART_Init();
	ADC_init();
	PWM1_init();
	PWM2_init();
	timer3_init();
	
	
	speed=160;
	
	
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
		
		
		if(check==1)
		{
			Motor_1('b',speed,5);
			//Motor_2('F',speed,5);
			sec=sys_time.s;
			check=0;
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

		
		
	} 
return 0;
}
