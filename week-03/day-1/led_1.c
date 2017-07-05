/*
 * led_1.c
 *
 * Created: 2017.05.15. 11:40:57
 * Author : Orsi
 */ 

#include <avr/io.h>

#define F_CPU	16000000	
#include <util/delay.h>


int main(void)
{
    DDRB |= 1 << DDRB5;
	DDRB |= 1 << DDRB4;
	DDRB |= 1 << DDRB3;
	DDRB |= 1 << DDRB2;
	
	
    while (1) 
    {
		PORTB |= 1 << PORTB5;
		/*_delay_ms(50);
		PORTB &= ~(1 << PORTB5);
		*/_delay_ms(50);
		
		PORTB |= 1 << PORTB4;
		/*_delay_ms(50);
		PORTB &= ~(1 << PORTB4);
		*/_delay_ms(50);
		
		PORTB |= 1 << PORTB3;
		/*_delay_ms(50);
		PORTB &= ~(1 << PORTB3);
		*/_delay_ms(50);
		
		PORTB |= 1 << PORTB2;
		/*_delay_ms(50);
		PORTB &= ~(1 << PORTB2);
		*/_delay_ms(50);
		
		PORTB |= 1 << PORTB3;
		/*_delay_ms(50);
		PORTB &= ~(1 << PORTB3);
		*/_delay_ms(50);
		
		PORTB |= 1 << PORTB4;
		/*_delay_ms(50);
		PORTB &= ~(1 << PORTB4);
		*/_delay_ms(50);
		
		
	
    }
}

