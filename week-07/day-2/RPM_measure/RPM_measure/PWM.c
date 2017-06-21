#include <avr/io.h>
//#include <avr/interrupt.h>
#include <stdint.h>



#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#include <util/delay.h>

// initialize the TC0 timer in Fast PWM mode
void fast_PWM_init()
{
	// Clear OC2A on Compare Match
	TCCR2A |= 1 << COM2A1;
	
	 //Set FAST PWM mode, with comparison of OCRA
	TCCR2A |= 1 << WGM21; 
	TCCR2A |= 1 << WGM20; 

	//set clock speed (to maximum?)
	TCCR2B |= 1 << CS22;
	TCCR2B |= 1 << CS20;
		
	//set PB3 as output
	DDRB |= 1 << DDRB3;
	
	// Set OCR2A register to generate 50% duty cycle
	OCR2A = 10; // 255 is max duty cycle
}

void set_duty_cycle(uint8_t duty)
{
	OCR2A = ((float)duty * 255) / 100;
	printf("%d\n", OCR2A);
	
}
