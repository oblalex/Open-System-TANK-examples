/**
 * Controls boom position using Servo0.
 * Servo0 is controlled by T1 in PWM mode.
 * Press SB3 to rotate boom to the right by 5% of overall range.
 * Press SB4 to rotate boom to the left  by 5% of overall range.
 * Current position (in percent of overall range) is displayed on LCD.
 */
#define F_CPU 16000000UL

#include <util/delay.h>
#include <stdio.h>

#include "LCD.h"
#include "buttons.h"
#include "boom.h"

void init();

void run();
void checkButtons();
void onSB4pressed();
void onSB3pressed();
void updateBoomPosition();

#define MAIN_LOOP_DELAY_MS 40
#define ANTI_CONTACT_BOUNCE_DELAY_MS 400
#define ANTI_CONTACT_BOUNCE_PERIODS (ANTI_CONTACT_BOUNCE_DELAY_MS/MAIN_LOOP_DELAY_MS)

#define BOOM_STEP 5

unsigned char boom_position = 50;

int main(void){
	FILE lcd_str = FDEV_SETUP_STREAM(lcd_putc_stream, NULL, _FDEV_SETUP_WRITE);
	stdout = &lcd_str;

	init();
	run();
	return 0;
}

void init(){
	initLCD();
	initButtons();
	initBoom();

	updateBoomPosition();
	updateBoomPosition();
	updateBoomPosition();
}

void run(){
	while(1){
		checkButtons();
		lcd_gotoxy(0,0);
		fprintf(stdout, "%3d%%", boom_position);
		_delay_ms(MAIN_LOOP_DELAY_MS);
	}
}

void checkButtons(){
	static char SB4_periods = 0;
	static char SB3_periods = 0;

	if(isButtonPressed(SB4)){
		if (SB4_periods < ANTI_CONTACT_BOUNCE_PERIODS){
			SB4_periods++;
		} else {
			onSB4pressed();
			SB4_periods = 0;
		}
		return;
	}
	SB4_periods = 0;

	if(isButtonPressed(SB3)){
		if (SB3_periods < ANTI_CONTACT_BOUNCE_PERIODS){
			SB3_periods++;
		} else {
			onSB3pressed();
			SB3_periods = 0;
		}
		return;
	}
	SB3_periods = 0;
}

void onSB4pressed(){
	if (boom_position>0){
		boom_position -= BOOM_STEP;
		if (boom_position<0){
			boom_position=0;
		}
		updateBoomPosition();
	}
}

void onSB3pressed(){
	if (boom_position<100){
		boom_position += BOOM_STEP;
		if (boom_position>100){
			boom_position=100;
		}
		updateBoomPosition();
	}
}

void updateBoomPosition(){
	boomSet(boom_position);
	_delay_ms(50);
	boomStop();
}
