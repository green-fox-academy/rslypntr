#include <avr/io.h>
#include <stdint.h>
#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#include <util/delay.h>
#include "PWM.h"

//this does not work
/*
int main(void)
{	
	uint8_t duty;
	fast_PWM_init();
	while(1) {
		for (duty = 0; duty < 100; duty++) {
			set_duty_cycle(duty);
			_delay_ms(10);
		}
		for(duty = 100; duty > 0; duty--) {
			set_duty_cycle(duty);
			_delay_ms(10);
		}
	}	
}
*/


int main(void)
{
	uint8_t duty;
	fast_PWM_init();
	while(1) {
		
		for(duty = 0; duty < 255; duty++) {
			OCR0A = duty;
			_delay_ms(1);
		}
		for(duty = 255; duty > 0; duty--) {
			OCR0A = duty;
			_delay_ms(5);
		}
	}
}