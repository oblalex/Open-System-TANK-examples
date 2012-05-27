/**
 * Light LEDs with buttons
 * SB4 sets green LED
 * SB3 sets red LED
 * SB2 clears both LEDs
 */

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "leds.h"
#include "buttons.h"

void turnOffLEDs();
void checkLEDsSettingButtons();

int main(void){
	initLEDs();
	initButtons();

	while (1){
		if (isButtonPressed(SB2)){
			turnOffLEDs();
		} else {
			checkLEDsSettingButtons();
		}
		_delay_ms(50);
	}
	return 0;
}

void turnOffLEDs(){
	LEDoff(LED_GREEN);
	LEDoff(LED_RED);
}

void checkLEDsSettingButtons(){
	if (isButtonPressed(SB4)){
		LEDon(LED_GREEN);
	}
	if (isButtonPressed(SB3)){
		LEDon(LED_RED);
	}
}
