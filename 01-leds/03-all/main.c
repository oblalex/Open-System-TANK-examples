/**
 * Light on red & green LEDs
 */

#include <avr/io.h>

#include "leds.h"

int main(void){
	initLEDs();
	LEDon(LED_GREEN);
	LEDon(LED_RED);
	return 0;
}
