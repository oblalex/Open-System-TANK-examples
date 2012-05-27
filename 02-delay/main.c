/**
 * Blink red and green LEDs consequentially
 * with period of 1 second using delay
 */

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "leds.h"

unsigned char led_r = 1;
unsigned char led_g = 0;

int main(void){
	DDRG  = 0xFF;
	while (1){
		PORTG = (led_r << LED_RED_POS) + (led_g << LED_GREEN_POS);

		led_r ^= 1;
		led_g ^= 1;

		_delay_ms(1000);
	}
	return 0;
}
