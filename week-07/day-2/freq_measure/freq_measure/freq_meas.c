#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include "freq_meas.h"

#define COUNTER_MAX 0xFFFF //as per p187

// TODO:
// Write the interrupt handlers
volatile uint8_t ovf_cntr = 0;
volatile uint16_t timestamp_first = 0;
volatile uint16_t timestamp_last = 0;


ISR(TIMER1_CAPT_vect)
{	
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
	
	//If enabled (TIMSK1.ICIE=1), the Input Capture Flag (ICF) generates an Input Capture interrupt
	TIMSK1 |= 1 << ICIE1; // interrupts have been enabled globally in system_init()
	
	// TODO: overflow interrupt
	TIMSK1 |= 1 << TOIE1;
	
	//The ICR1 Register can only be written when using a Waveform Generation mode that utilizes the ICR1
	//Register for defining the counter’s TOP value. In these cases the Waveform Generation mode bits
	//(WGM1[3:0]) must be set before the TOP value can be written to the ICR1 Register.
	
	//the mode of operation, i.e., the behavior of the Timer/Counter and the Output Compare pins, is defined
	//by the combination of the Waveform Generation mode (WGM1[3:0]) and Compare Output mode
	//(TCCR1A.COM1x[1:0]) bits.

	
	//the Timer/Counter can be clocked directly by the system clock (by setting the CSn[2:0]=0x1)
	//setting middle value: clk / 64
	TCCR1B |= 1 << CS11;
	TCCR1B |= 1 << CS10;
	

		
	//Normal mode set by default	
	
	//edge select - does not matter this time, generally it can matter
	//TCCR1B |= 1 << ICES1;
	
	// In Normal and CTC modes, the TOV flag is set when the timer overflows.
	
}

// TODO:
// Write this function. It returns the measured frequency in Hz
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
	float period = (float)steps * ((float)1 / 16000000) * 64;  //1/16 MHz // prescaler!!!
	float freq = 1 / period; 
	
	//set overflow counter to 0
	ovf_cntr = 0;
	return freq;
}


//QUESTIONS

//1. what if period == 0?
//	this can only occur before the first measurement, but then there is no frequency to calculate yet.
// (period can only be 0 if steps == 0 which only occurs before the fisrt overflow and before the first measurement

//2. what if  interrupt occurs while computing get_freq()?

//3. my initial solution for ISR(TIMER1_CAPT_vect) was wrong! - see frequency calculation after 1 interrupt