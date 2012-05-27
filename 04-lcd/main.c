/**
 * Displays "This is\nTank!" message to LCD.
 */
#define F_CPU 16000000UL

#include <avr/io.h>
#include <stdio.h>

#include "LCD/hd44780.h"
#include "LCD/hd44780_hw.h"

int main(void){

	lcd_init(LCD_DISP_ON);
	lcd_clrscr();

	FILE lcd_str = FDEV_SETUP_STREAM(lcd_putc_stream, NULL, _FDEV_SETUP_WRITE);
	stderr = &lcd_str;

	fprintf(stderr, "This is\nTank!");

	return 0;
}
