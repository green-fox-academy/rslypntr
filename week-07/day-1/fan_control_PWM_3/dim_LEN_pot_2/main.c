/*
 * dim_LEN_pot_2.c
 *
 * Created: 2017.06.12. 13:15:18
 * Author : Orsi
 */ 

#include <avr/io.h>
#include <stdint.h>
#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#include <util/delay.h>
#include "PWM.h"
#include "ADC_driver.h"


int main(void)
{
	uint8_t duty;
    fast_PWM_init();
	ADC_init();
	
    while (1) 
    {
		duty = ADC_read() >> 2;
		OCR0A = duty;	
			
    }
}

