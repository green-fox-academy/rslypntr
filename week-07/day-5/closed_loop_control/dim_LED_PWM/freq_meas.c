#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <math.h>
#include "freq_meas.h"

#define COUNTER_MAX 0xFFFF 

volatile uint8_t ovf_cntr = 0;
volatile uint8_t ovf_value;
volatile uint16_t timestamp_first = 0;
volatile uint16_t timestamp_last = 0;


ISR(TIMER1_CAPT_vect)
{
	ovf_value = ovf_cntr;
	ovf_cntr = 0;
	timestamp_first = timestamp_last;
	timestamp_last = ICR1;
}


ISR(TIMER1_OVF_vect)
{
	ovf_cntr++;
}

void freq_meas_init()
{
	/**************
	 * TC1 CONFIG *
	 **************/
	// TODO:
	// Configure the TC1 timer properly :)

	// TC1 Input capture interrupt enable
	TIMSK1 |= 1 << ICIE1;
	// TC1 overflow interrupt enable
	TIMSK1 |= 1 << TOIE1;
	// TC1 clock select, this will also start the timer!
	TCCR1B = CS_DEFAULT;
}

float get_freq()
{
	//disable interrupts, save timestamps locally and enable interrupts again			
	cli();
	uint16_t timest_first_local = timestamp_first;
	uint16_t timest_last_local = timestamp_last;
	uint16_t ovf_cntr_local = ovf_cntr;
	sei();
	
	//use value returned by interrupt handler, calculate frequency from formula
	uint32_t steps = ((uint32_t)ovf_cntr_local * COUNTER_MAX) + timest_last_local - timest_first_local;
	float period = (float)steps * ((float)1 / 16000000) * 64;  
	float freq = 1 / period;
	if (isnan(freq) || isinf(freq))
		return -1;
	else
		return freq;
}
