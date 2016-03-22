


 
#include <avr/io.h> 
//#include <avr/interrupt.h>

#define F_CPU 20000000ul	// 20 MHz oscillator.
#define BaudRate 9600
#define MYUBRR (uint8_t)(F_CPU / 20 / BaudRate )
#define BaudRate 9600


 



void delayLong()
{
	unsigned int delayvar;
	delayvar = 0; 
	while (delayvar <=  65500U)		
	{ 
		asm("nop");  
		delayvar++;
	} 
}


uint8_t serialCheckRxComplete(void)
{
	
	return( UCSR0A & _BV(RXC0)) ;		// nonzero if serial data is available to read.
}

uint8_t serialCheckTxReady(void)
{
	return( UCSR0A & _BV(UDRE0) ) ;		// nonzero if transmit register is ready to receive new data.
}

uint8_t serialRead(void)
{
	while (serialCheckRxComplete() == 0)		// While data is NOT available to read
	{;;} 
	
	return UDR0;
}

void serialWrite(uint8_t DataOut)
{
	while (serialCheckTxReady() == 0)		// while NOT ready to transmit 
	{;;} 
	UDR0 = DataOut;
}



void establishContact() {
	while (serialCheckRxComplete() == 0) { 
		//serialWrite('A');
	//	serialWrite(65U);
		delayLong();
		delayLong();
		delayLong();
		delayLong();
		delayLong();
		delayLong();
		delayLong();
	}
}

  

int main (void)
{ 
	
//Interrupts are not needed in this program. You can optionally disable interrupts.	
//asm("cli");		// DISABLE global interrupts.

		
	DDRD = _BV(1);
	DDRB = _BV(0) | _BV(1) | _BV(3) | _BV(5);
	 
	//Serial Initialization
	
 	/*Set baud rate */ 
	UBRR0H = (uint8_t)(MYUBRR>>8); 
	UBRR0L = (uint8_t) MYUBRR; 
	/* Enable receiver and transmitter   */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0); 
	/* Frame format: 8data, No parity, 1stop bit */ 
	UCSR0C = (3<<UCSZ00);  
	
	 
	int firstSensor = 0;    // first analog sensor
	int secondSensor = 0;   // second analog sensor
	int thirdSensor = 0;    // digital sensor
	volatile uint8_t inByte = 0;         // incoming serial byte
	
	
	PORTB |= _BV(1); // Turn on LED @ PB1
	

//establishContact();  // send a byte to establish contact until Processing responds 

		PORTB &= 253U; // Turn off LED
	

for (;;)  // main loop										
{

	
	if (serialCheckRxComplete()) {
		PORTB |= _BV(1); // Turn on LED @ PB1
		
		inByte = serialRead();
		//inByte &= 0x7fu;
		
		UDR0 = 0x00u;
		
		// Simulated data!
		firstSensor++;
		
		secondSensor = firstSensor * firstSensor;
		
		thirdSensor = firstSensor + secondSensor;
		
		//serialWrite(firstSensor & 255U);
		//serialWrite(secondSensor & 255U);
		//serialWrite(thirdSensor & 255U);

		PORTB &= 253U; // Turn off LED
              
	}
	
	
	 	
	

}	//End main loop.
	return 0;
}

