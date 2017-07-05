#include <avr/io.h>
#include <string.h>
#include <stdint.h>
#include "TC74_driver.h"
#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#include <avr/delay.h>

void TWI_init(void)
{
	// Set Prescaler to 4
	TWSR = 0x01;

	// Set SCL frequency = 16000000 / (16 + 2 * 48 * 4) = 40Khz
	//So set the correct register to 0x30
	TWBR = 0x30;

	//Enable TWI
	TWCR |= 1 << TWEN;

}

void TWI_start(void)
{
	//Send start signal
	TWCR = (1 << TWINT)| (1 << TWSTA) | (1 << TWEN);

	// Wait for TWINT Flag set. This indicates that
	//the START condition has been transmitted.
	while (!(TWCR & (1 << TWINT)));
}

void TWI_stop(void)
{
	//Send stop signal
	TWCR = (1 << TWINT)| (1 << TWEN) | (1 << TWSTO);
}

uint8_t TWI_read_ack(void)
{
	//Read byte with ACK
	//Wait for TWINT Flag set. This indicates that
	//the DATA has been transmitted, and ACK/
	//NACK has been received.	
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
	while (!(TWCR & (1 << TWINT)));
	return TWDR;
}


uint8_t TWI_read_nack(void)
{
	//Read byte with NACK
	//Wait for TWINT Flag set. This indicates that
	//the DATA has been transmitted, and ACK/
	//NACK has been received.
	TWCR = (1<<TWINT)|(1<<TWEN);	
	while (!(TWCR & (1 << TWINT)));
	uint8_t read_val = TWDR;
	return TWDR;
}

void TWI_write(uint8_t u8data)
{
	//Load DATA into TWDR Register. Clear TWINT
	//bit in TWCR to start transmission of data.
	//Wait for TWINT Flag set. This indicates that
	//the DATA has been transmitted, and ACK/
	//NACK has been received.	
	TWDR = u8data;
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));
}


//function for communicating with the TC74A0
uint8_t read_temp (uint8_t address)
{
	TWI_start();
	TWI_write(address << 1 | 0);
	TWI_write(REG_ADDRESS);
	TWI_start();
	TWI_write(address << 1 | 1);
	uint8_t temperature = TWI_read_nack();
	TWI_stop();	
	return temperature;
}


