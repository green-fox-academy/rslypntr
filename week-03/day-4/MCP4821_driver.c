#include <avr/io.h>
#include <string.h>
#include <stdint.h>
#include "MCP4821_driver.h"

void MCP4821_Init() {
	// TODO:
	// Initialize the SPI related pins. Use the definitions from MCP4821_driver.h! 
	DDRB |= 1 << DDRB2;
	DDRB |= 1 << DDRB3;
	DDRB |= 1 << DDRB5;	
	

	// TODO:
	// Pull SS pin to high!
	PORTB |= 1 << PORTB2;


	// TODO:
	// Set the SPI mode (CPOL and CPHA). Use the definitions from MCP4821_driver.h!
	SPCR &=  ~(1 << CPOL);
	SPCR &=  ~(1 << CPHA);
	

	// TODO:
	// Set master mode
	SPCR |= 1 << MSTR;

	// TODO:
	// Set the clock frequency. Use the definitions from MCP4821_driver.h
	SPSR &= ~(1 << SPI2X);
	SPCR |= 1 << SPR0;
	SPCR |= 1 << SPR1;
	

	// TODO:
	// Enable SPI peripheral
	SPCR |= 1 << SPE;
	
	
}

void MCP4821_SendRawData(uint16_t data) {
	// TODO:
	// Pull SS low
	PORTB &= ~(1 << PORTB2); 

	// TODO:
	// Put the top 8bits of the data to the SPI shift register
	SPDR = data >> 8;

	// TODO:
	// Wait for the end of the transmission
	while ( !( SPSR & (1<<SPIF)));

	// You have to read the SPDR register to clear the SPIF flag after the end of transmission
	volatile uint8_t dummy_variable = SPDR;

	// TODO:
	// Put the bottom 8bits of the data to the SPI shift register
	SPDR = data;

	// TODO:
	// Wait for the end of the transmission
	while ( !( SPSR & (1<<SPIF))); //do while SPIF flag is 0

	// You have to read the SPDR register to clear the SPIF flag after the end of transmission
	dummy_variable = SPDR;

	// TODO:
	// Pull SS high
	PORTB |= 1 << PORTB2; 
}

void MCP4821_SendData(MCP4821_Data_t* data) {
	// Convert the data variable to a 16bit number with memcpy()
	// Then use the MCP4821_SendRawData() function to send the data
	uint16_t buffer;
	memcpy(&buffer, data, sizeof(MCP4821_Data_t));
	MCP4821_SendRawData(buffer);
}
