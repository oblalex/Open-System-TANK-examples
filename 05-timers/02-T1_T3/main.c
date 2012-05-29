/**
 * This example shows usage of 2 16-bit timers: T1 and T3.
 * T1 increases counter_1 value with frequency of  1Hz.
 * T3 increases counter_3 value with frequency of 10Hz.
 * Read ATmega64A datasheet.
 * Look here for help: http://www.et06.dk/atmega_timers
 *
 * !! There is _NO_ deviation like in T0_T2 example
 *
 */
#define F_CPU 16000000UL

#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

#include "LCD.h"

volatile unsigned int counter_1;
volatile unsigned int counter_3;

void init();
void initTimers();
void initTimer1();
void initTimer3();

void run();

int main(void){
	FILE lcd_str = FDEV_SETUP_STREAM(lcd_putc_stream, NULL, _FDEV_SETUP_WRITE);
	stdout = &lcd_str;

	init();
	run();
	return 0;
}

void init(){
	initLCD();
	initTimers();
	sei(); //set global interrupt enable
}

void initTimers(){
	initTimer1();
	initTimer3();
}

void initTimer1(){
	OCR1A = 0xF424; 					// run up to 62500 ticks	:
	TCCR1B = (1<<WGM12) | (1 << CS12);	// prescaler 256			: 16MHz / 256 / 62500 = 1 Hz
	TIMSK  = (1 << OCIE1A);				// enable interrupt
	TCNT1=0;
}

ISR(TIMER1_COMPA_vect){
	counter_1++;
}

void initTimer3(){
	OCR3A  = 0x61A8;									// run up to 25000 ticks :
	TCCR3B = (1<<WGM12) | (1 << CS31) | (1 << CS30);	// prescaler 64			 : 16MHz / 64 / 25000 = 10 Hz
	ETIMSK = (1 << OCIE3A);								// enable interrupt
	TCNT3=0;
}

ISR(TIMER3_COMPA_vect){
	counter_3++;
}

void run(){
	while(1){
		lcd_gotoxy(0,0);
		fprintf(stdout, "%8d", counter_1);
		lcd_gotoxy(0,1);
		fprintf(stdout, "%8d", counter_3);
		_delay_ms(10);
	}
}
