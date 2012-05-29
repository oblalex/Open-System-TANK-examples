#ifndef LCD_H_
#define LCD_H_

#include <avr/io.h>

#include "bit_ops.h"
#include "LCD/hd44780.h"
#include "LCD/hd44780_hw.h"

#define LCD_BACKLIGHT 2

void init_stdout();
void init_backlight();

void initLCD(){
	lcd_init(LCD_DISP_ON);
	lcd_clrscr();
	init_backlight();
}

void init_backlight(){
	BIT_ON(DDRG, LCD_BACKLIGHT);
}

void lcd_backlight_on(){
	BIT_ON(PORTG, LCD_BACKLIGHT);
}

void lcd_backlight_off(){
	BIT_OFF(PORTG, LCD_BACKLIGHT);
}

void lcd_backlight_set(char value){
	BIT_SET(PORTG, LCD_BACKLIGHT, value);
}

#endif /* LCD_H_ */
