/**
 * Shows how much optopair's interruptions have happened.
 *
 * Right optopair's counter is shown on the 1st line of LCD.
 * Left  optopair's counter is shown on the 2nd line of LCD.
 *
 * Status-request is done 625 times per second. This value
 * is optional.
 */
#define F_CPU 16000000UL

#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

#include "LCD.h"
#include "opto.h"

volatile unsigned int opto_counter_L = 0;
volatile unsigned int opto_counter_R = 0;

void init();
void initTimer0();

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
	initOpto();
	initTimer0();
	sei(); //set global interrupt enable
}

void initTimer0(){
	OCR0   = 0x64;						// run up to 100 ticks	:
	TCCR0  = (1 << CS01) | (1 << CS02);	// prescaler 256 		: 16MHz / 256 / 100 = 625 Hz
	TIMSK  = (1 << TOIE0); 				// enable interrupt
}

ISR(TIMER0_OVF_vect){
	static char prev_Opto_R = 0;
	static char prev_Opto_L = 0;
	static char curr_Opto_R = 0;
	static char curr_Opto_L = 0;

	curr_Opto_R = isOptoInterrupted(OPTO_R);
	curr_Opto_L = isOptoInterrupted(OPTO_L);

	if ((curr_Opto_R == 0) && (prev_Opto_R == 1)){
		opto_counter_R++;
	}

	if ((curr_Opto_L == 0) && (prev_Opto_L == 1)){
		opto_counter_L++;
	}

	prev_Opto_R = curr_Opto_R;
	prev_Opto_L = curr_Opto_L;
}

void run(){
	while(1){
		lcd_gotoxy(0,0);
		fprintf(stdout, "%d", opto_counter_R);
		lcd_gotoxy(0,1);
		fprintf(stdout, "%d", opto_counter_L);
		_delay_ms(40);
	}
}
