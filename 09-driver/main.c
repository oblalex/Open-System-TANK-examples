/**
 * Controls 3 state per each track driver.
 * State 0 - driver is stopped.
 * State 1 - driver is rotating forwards.
 * State 2 - driver is rotating backwards.
 *
 * Current states for each driver are displayed on LCD.
 *
 * Press SB3 to change right driver's state.
 * Press SB4 to change left driver's state.
 */
#define F_CPU 16000000UL

#include <util/delay.h>
#include <stdio.h>

#include "LCD.h"
#include "buttons.h"
#include "driver.h"

void init();

void run();
void checkButtons();
void onSB4pressed();
void onSB3pressed();

#define ASCII_ZERO 48
#define STATES 3

#define MAIN_LOOP_DELAY_MS 40
#define ANTI_CONTACT_BOUNCE_DELAY_MS 320
#define ANTI_CONTACT_BOUNCE_PERIODS (ANTI_CONTACT_BOUNCE_DELAY_MS/MAIN_LOOP_DELAY_MS)

unsigned char state_L = 0;
unsigned char state_R = 0;

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
	initDriver();
}

void run(){
	while(1){
		checkButtons();
		lcd_gotoxy(0,0);
		fprintf(stdout, "%c %c", state_L+ASCII_ZERO, state_R+ASCII_ZERO);
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
	if (state_L<(STATES-1)){
		state_L++;
	} else state_L = 0;
	switch (state_L) {
		case 0:
			driver_stop_left();
			break;
		case 1:
			driver_go_forward_left();
			break;
		case 2:
			driver_go_backward_left();
			break;
		default:
			break;
	}
}

void onSB3pressed(){
	if (state_R<(STATES-1)){
		state_R++;
	} else state_R = 0;
	switch (state_R) {
		case 0:
			driver_stop_right();
			break;
		case 1:
			driver_go_forward_right();
			break;
		case 2:
			driver_go_backward_right();
			break;
		default:
			break;
	}
}
