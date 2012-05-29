/**
 * Plays 7 notes via buzzer and T1.
 * Current note's frequency is displayed on LCD.
 *
 * Press SB3 to increase frequency.
 * Press SB4 to decrease frequency.
 */
#define F_CPU 16000000UL

#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

#include "LCD.h"
#include "buttons.h"
#include "buzzer.h"

void init();
void initTimer1();

void run();
void checkButtons();
void onSB4pressed();
void onSB3pressed();
void updateFrequency();

#define MAIN_LOOP_DELAY_MS 40
#define ANTI_CONTACT_BOUNCE_DELAY_MS 400
#define ANTI_CONTACT_BOUNCE_PERIODS (ANTI_CONTACT_BOUNCE_DELAY_MS/MAIN_LOOP_DELAY_MS)
#define NOTES 7

int frequencies[NOTES][2] = {
		{522, 0x77BB}, // Do
		{586, 0x6AA8}, // Re
		{658, 0x5EFC}, // Mi
		{697, 0x59AC}, // Fa
		{782, 0x4FEC}, // Sol
		{878, 0x472F}, // La
		{985, 0x3F74}  // Si
	};

unsigned char selectedFreq = 0;

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
	initBuzzer();
	initTimer1();
	sei(); //set global interrupt enable
}

void initTimer1(){
	updateFrequency();
	TCCR1B = (1<<WGM12) | (1 << CS10);	// prescaler 1
	TIMSK  = (1 << OCIE1A);				// enable interrupt
}

ISR(TIMER1_COMPA_vect){
	static char buz_value = 0;
	buz_value ^= 1;
	setBuzzerValue(buz_value);
}

void run(){
	while(1){
		checkButtons();
		lcd_gotoxy(0,0);
		fprintf(stdout, "%d Hz", frequencies[selectedFreq][0]);
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
	if (selectedFreq>0){
		selectedFreq--;
		updateFrequency();
	}
}

void onSB3pressed(){
	if (selectedFreq<(NOTES-1)){
		selectedFreq++;
		updateFrequency();
	}
}

void updateFrequency(){
	OCR1A  = frequencies[selectedFreq][1];
	TCNT1  = 0;
}
