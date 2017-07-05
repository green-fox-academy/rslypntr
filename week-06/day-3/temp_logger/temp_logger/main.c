#include "TC74_driver.h"
#include "UART_driver.h"

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <avr/interrupt.h>

#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#include <avr/delay.h>


void system_init()
{
	TWI_init();
	UART_init();
	//set LED a output for code testing
	DDRB|= 1 << DDRB5;	
}
void print_menu()
{
	char buffer[255];
	FILE *fp;
	PINB |= 1 <<PINB5;
	_delay_ms(500);
	PINB |= 1 << PINB5;
	/*fp = fopen("startup_info.txt", "r");
	fgets(buffer, 255, fp);
	while(!feof(fp)) {
		printf("%s", buffer);
		fgets(buffer, 255, fp);
	}
	fclose(fp);*/
}

int main(void)
{
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
		PINB |= 1 << PINB5;
		_delay_ms(500);
		
		print_menu();
		
	}
}
