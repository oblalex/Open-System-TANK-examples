/**
 * Blink red and green LEDs consequentially
 * with period of 1 second using delay
 */

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "leds.h"

char led_r = 1;
char led_g = 0;

int main(void){
	initLEDs();

	while (1){
		LEDset(LED_RED, led_r);
		LEDset(LED_GREEN, led_g);

		led_r ^= 1;
		led_g ^= 1;

		_delay_ms(1000);
	}
	return 0;
}
