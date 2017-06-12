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
	//Enable TC0
	//PRR &= ~(1 << PRTIM0);	
	

	// Clear OC0A on Compare Match, set OC0A at BOTTOM (non-inverting mode)
	TCCR0A |= 1 << COM0A1; //done
	//TCCR0A &= ~(1 << COM0A0);
	
	// Timer/counter mode of operation == Fast PWM
	//TOP == 0xFF, Update of OCR0x at BOTTOM, TOV flag set on TOP
	TCCR0A |= 1 << WGM01; 
	TCCR0A |= 1 << WGM00; 
	//TCCR0A &= 1 << WGM02;
	
	TCCR0B |= 1 << CS02;
	TCCR0B |= 1 << CS00;
	
	//set PD6 as output 
	DDRD |= 1 << DDRD6;	
}

void set_duty_cycle(uint8_t duty)
{
	OCR0A = (duty * 255) / 100;
	printf("%d\n", OCR0A);
	
}
