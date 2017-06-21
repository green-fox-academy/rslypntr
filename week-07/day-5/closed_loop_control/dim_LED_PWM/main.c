#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include "TC0_PWM_driver.h"
#include "ADC_driver.h"
#include "UART_driver.h"
#include "freq_meas.h"
#include "AC_driver.h"

#define F_CPU	16000000
#include <util/delay.h>

#define LED_DDR			DDRB
#define LED_DDR_POS		DDRB5
#define LED_PIN			PINB
#define LED_PIN_POS		PINB5
#define LED_PORT		PORTB
#define LED_PORT_POS	PORTB5



float ref_duty; //reference input
float err; //error
float rpm;
float duty; //ctrler_out
float adc_data;
float ref_rpm;  // = 1500; //fixed reference RPM
float p = 0.05;
float i = 0.01;
float duty_min = 0.0;
float duty_max = 100.0;
char buffer_1[65];
char buffer_2[65];



void system_init()
{
	LED_DDR |= 1 << LED_DDR_POS;
	AC_driver_init();
	freq_meas_init();
	TC2_fast_pwm_init();
	ADC_init();
	UART_init();
	sei();
}



int main(void)
{
	system_init();
	
	// Setting up STDIO input and output buffer
	// You don't have to understand this!
	//----- START OF STDIO IO BUFFER SETUP
	FILE UART_output = FDEV_SETUP_STREAM(UART_send_character, NULL, _FDEV_SETUP_WRITE);
	stdout = &UART_output;
	FILE UART_input = FDEV_SETUP_STREAM(NULL, UART_get_character, _FDEV_SETUP_READ);
	stdin = &UART_input;
	//----- END OF STDIO IO BUFFER SETUP
	
	float duty_start = 0;
	TC2_set_duty(duty_start);
	float rpm_test = get_rpm();
	printf("duty cycle: %f\tRPM: %f\n", duty_start, rpm_test);
	float integral = 0;
	
	
	//read reference from UART
	printf("Please enter reference RPM:\n");
	gets(buffer_1);	
	printf("Please enter size of acceptance interval:\n");
	gets(buffer_2);
	//define acceptance interval
	ref_rpm = (float) atoi(buffer_1);
	float interval = (float) atoi(buffer_2) / 2;
	float rpm_low = ref_rpm - interval;
	float rpm_high = ref_rpm + interval;
	
	duty_start = 0;
	TC2_set_duty(duty_start);
	rpm_test = get_rpm();
	
	while (rpm_test < rpm_low || rpm_test > rpm_high) {
	//while (1) {
		/*
		
		//get data from potentiometer - open loop control		
		float adc_data = (ADC_read() >> 2) / 2.55;
		//TC2_set_duty(adc_data / ADC_DATA_MAX * 100);		
		TC2_set_duty(adc_data); 
		float freq_test = get_freq();
		float rpm_test = get_rpm();
		printf("duty set: %f\tfreq: %f\tRPM: %f\n", adc_data, freq_test, rpm_test);
		_delay_ms(500); 
		*/
		
		/*	
		//P control
		err = ref_rpm - rpm_test;
		duty = p * err;		
		if (duty < duty_min)	
			duty = duty_min;
		else if (duty > duty_max)	
			duty = duty_max;			
		TC2_set_duty(duty);		
		rpm_test = get_rpm();
		printf("duty cycle: %f\tRPM: %f\n", duty, rpm_test);
		printf("\n");	
		_delay_ms(10);
		*/
		
		
		//PI control
		err = ref_rpm - rpm_test;		
		integral = integral + err;		
		duty = p * err + i * integral;

		if (duty < duty_min) {
			duty = duty_min;
			integral = integral - err;
		}
		else if (duty > duty_max) {
			duty = duty_max;
			integral = integral - err;
		}
		TC2_set_duty(duty);	
		rpm_test = get_rpm();
		printf("duty cycle: %f\tRPM: %f\n", duty, rpm_test);
		_delay_ms(10);
		
		 
		/*
		if (!UART_is_buffer_empty()) {
			char command[64];
			gets(command);
			uint8_t duty = atoi(command);
			TC2_set_duty(duty);
		}
		*/
		/*
		//RPM measure test
		LED_PORT |= 1 << LED_PORT_POS;
		_delay_ms(500);
		LED_PORT &= ~(1 << LED_PORT_POS);
		_delay_ms(500);
		printf("%f Hz\n", get_freq());
		printf("%f RPM\n", get_rpm());
		*/	
	}
	printf("Provided reference reached, final value: %f\n", rpm_test);
	while(1) {
		TC2_set_duty(duty);	
	}
	
}
