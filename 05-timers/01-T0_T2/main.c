/**
 * This example shows usage of 2 8-bit timers: T0 and T2.
 * T0 increases counter_0 value with frequency of  1Hz.
 * T2 increases counter_2 value with frequency of 10Hz.
 * Read ATmega64A datasheet.
 * Look here for help: http://www.et06.dk/atmega_timers
 *
 * !! There is an additive frequency deviation between
 * !! changes of counters. It can be noticed after
 * !! 30-40 seconds of runtime
 */
#define F_CPU 16000000UL

#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

#include "LCD.h"

volatile unsigned int counter_0;
volatile unsigned int counter_2;

void init();
void initTimers();
void initTimer0();
void initTimer2();

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
	initTimer0();
	initTimer2();
}

void initTimer0(){
	OCR0   = 0xFA;						// run up to 250 ticks	:
	TCCR0  = (1 << CS01) | (1 << CS02);	// prescaler 256 		: 16MHz / 256 / 250 = 250 Hz
	TIMSK  = (1 << TOIE0); 				// enable interrupt
}

ISR(TIMER0_OVF_vect){
unsigned static char ct0_0 = 0;
	if (ct0_0 == 250 ){
		counter_0++;
		ct0_0 = 0;
	} else ct0_0++;
}

void initTimer2(){
	OCR2   = 0x64;						// run up to 100 ticks	:
	TCCR2  = (1 << CS21) | (1 << CS20);	// prescaler 64 		: 16MHz / 64 / 100 = 2500 Hz
	TIMSK |= (1 << TOIE2);				// enable interrupt
}

ISR(TIMER2_OVF_vect){
unsigned static char ct2_0 = 0;
	if (ct2_0 == 100){
		counter_2++;
		ct2_0 = 0;
	} else ct2_0++;
}

void run(){
	while(1){
		lcd_gotoxy(0,0);
		fprintf(stdout, "%8d", counter_0);
		lcd_gotoxy(0,1);
		fprintf(stdout, "%8d", counter_2);
		_delay_ms(1);
	}
}
