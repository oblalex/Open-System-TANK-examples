/**
 * Shows under-lines barriers detecting.
 *
 * Status of front line is shown on the 1st line of LCD.
 * Status of rear line is shown on the 2nd line of LCD.
 *
 * Status-request is done 625 times per second. This value
 * is optional.
 */
#define F_CPU 16000000UL

#define ASCII_ZERO 48

#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

#include "LCD.h"
#include "lines.h"

volatile unsigned char line_FL, line_FR, line_RL, line_RR;

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
	initLines();
	initTimer0();
	sei(); //set global interrupt enable
}

void initTimer0(){
	OCR0   = 0x64;						// run up to 100 ticks	:
	TCCR0  = (1 << CS01) | (1 << CS02);	// prescaler 256 		: 16MHz / 256 / 100 = 625 Hz
	TIMSK  = (1 << TOIE0); 				// enable interrupt
}

ISR(TIMER0_OVF_vect){
	line_FL = isLineBarrierDetected(LINE_FRONT_L);
	line_FR = isLineBarrierDetected(LINE_FRONT_R);
	line_RL = isLineBarrierDetected(LINE_REAR_L);
	line_RR = isLineBarrierDetected(LINE_REAR_R);
}

void run(){
	while(1){
		lcd_gotoxy(0,0);
		fprintf(stdout, "%c %c", line_FL+ASCII_ZERO, line_FR+ASCII_ZERO);
		lcd_gotoxy(0,1);
		fprintf(stdout, "%c %c", line_RL+ASCII_ZERO, line_RR+ASCII_ZERO);
		_delay_ms(40);
	}
}
