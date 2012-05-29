/**
 * Displays light freaquency to LCD.
 */
#define F_CPU 16000000UL

#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

#include "LCD.h"
#include "LFM.h"

void init();
void run();

#define MAIN_LOOP_DELAY_MS 40

int main(void){
	FILE lcd_str = FDEV_SETUP_STREAM(lcd_putc_stream, NULL, _FDEV_SETUP_WRITE);
	stdout = &lcd_str;

	init();
	run();
	return 0;
}

void init(){
	initLCD();
	initLFM();
	sei();
}

void run(){
	while(1){
		lcd_clrscr();
		lcd_gotoxy(0,0);
		fprintf(stdout, "%d Hz", lightFrequency);
		_delay_ms(MAIN_LOOP_DELAY_MS);
	}
}