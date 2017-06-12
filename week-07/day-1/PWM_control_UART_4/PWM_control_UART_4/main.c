/*
 * dim_LEN_pot_2.c
 *
 * Created: 2017.06.12. 13:15:18
 * Author : Orsi
 */ 

#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include <avr/interrupt.h>
#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#include <util/delay.h>
#include "PWM.h"
#include "ADC_driver.h"
#include "UART_driver.h"

	


int main(void)
{
	uint8_t duty;
	char buffer[255];
    fast_PWM_init();
	ADC_init();
	UART_init();
	sei();
	
	// Setting up STDIO input and output buffer
	// You don't have to understand this!
	//----- START OF STDIO IO BUFFER SETUP
	FILE UART_output = FDEV_SETUP_STREAM(UART_send_character, NULL, _FDEV_SETUP_WRITE);
	stdout = &UART_output;
	FILE UART_input = FDEV_SETUP_STREAM(NULL, UART_get_character, _FDEV_SETUP_READ);
	stdin = &UART_input;
	//----- END OF STDIO IO BUFFER SETUP
	printf("Start\n");
	
	
	

	
    while (1) 
    {
		//duty = ADC_read() >> 2;
		gets(buffer);
		duty = atoi(buffer);			
		set_duty_cycle(duty);	
			
    }
}

