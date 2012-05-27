/**
 * Displays "This is\nTank!" message to LCD.
 * Press SB3 to turn backlight off.
 * Press SB4 to turn backlight on.
 */
#define F_CPU 16000000UL

#include <util/delay.h>
#include <stdio.h>

#include "buttons.h"
#include "LCD.h"

void run();

int main(void){
	initButtons();
	initLCD();

	FILE lcd_str = FDEV_SETUP_STREAM(lcd_putc_stream, NULL, _FDEV_SETUP_WRITE);
	stdout = &lcd_str;

	run();

	return 0;
}

void run(){
	lcd_backlight_on();
	fprintf(stdout, "This is\nTank!");

	while (1){
		if (isButtonPressed(SB4)){
			lcd_backlight_on();
		} else
		if (isButtonPressed(SB3)){
			lcd_backlight_off();
		}
		_delay_ms(50);
	}
}
