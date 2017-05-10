/*
 * Timer_2.c
 *
 * Created: 2017.05.10. 15:55:06
 * Author : Orsi
 */ 

#include <avr/io.h>
#include <stdint.h>

void init()
{
	// Set the prescaler to 1024 division. See at the TC0 control register in the datasheet!
	// With this you also set the clock source to CLK_io and you will also turn on the timer!
	TCCR0B |= 1 << CS02;
	TCCR0B |= 1 << CS00;
	//TCCR0B = 0b00000101;

	// Set the PB5 LED pin to output
	DDRB = 1 << DDRB5;
	//DDRB |= 1 << DDRB5;
}

int main(void)
{
	// Create a variable which will be a counter variable, initialize it with 0.
	uint8_t counter = 0;
	// This will be the maximal value of our counter
	const uint8_t cntr_max = 30;

	// Don't forget to call the init function!
	init();

	while (1)
	{
		// Check the TOV0 overflow flag. If an overflow happened do the following:
		//	- clear the overflow flag
		//  - check the counter variable
		//		- if it is smaller than the maximal value, than increment it!
		//		- else set it to 0, and toggle the LED
		
		if((TIFR0&0b1) == 0b1 ){
			TIFR0 |= 1 << TOV0;
			if(counter < cntr_max){
				counter++;
			}
			else{
				counter=0;
				PINB |= 1 << PINB5;
			}
		}
		

	}
}
