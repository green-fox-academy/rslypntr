#include "TC74_driver.h"
#include "UART_driver.h"

#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>

#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#include <avr/delay.h>

#define LED_DDR			DDRB
#define LED_DDR_POS		DDRB5
#define LED_PIN			PINB
#define LED_PIN_POS		PINB5
#define LED_PORT		PORTB
#define LED_PORT_POS	PORTB5



void system_init()
{
	//TODO
	// Call the TWI driver init function
	TWI_init();

	//TODO
	//Init the uart
	UART_init();
	
	//set LED as output for code test
	DDRB|= 1 << DDRB5;
}

int main(void)
{

	// Don't forget to call the init function :)
	system_init();

	// Setting up STDIO input and output buffer
	// You don't have to understand this!
	//----- START OF STDIO IO BUFFER SETUP
	FILE UART_output = FDEV_SETUP_STREAM(UART_send_character, NULL, _FDEV_SETUP_WRITE);
	stdout = &UART_output;
	FILE UART_input = FDEV_SETUP_STREAM(NULL, UART_get_character, _FDEV_SETUP_READ);
	stdin = &UART_input;
	//----- END OF STDIO IO BUFFER SETUP

	// Try printf
	printf("Startup...\r\n");
	
	sei();

	// Infinite loop

	
	while (1) {
		_delay_ms(1000);		
		//uint8_t temp = read_temp(TC_ADDRESS);
		printf("\naverage of last 16 measured temperatures: %d", avg_temp(TC_ADDRESS));	
					

		//TODO
		//Advanced: Don't use delay, use timer.

		//TODO
		//Blink the led to make sure the code is running
		PINB |= 1 << PINB5;
		break;
	}
}
