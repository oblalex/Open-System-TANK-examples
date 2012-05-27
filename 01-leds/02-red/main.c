/**
 * Light on red LED
 */

#include <avr/io.h>

#include "leds.h"

int main(void){
	initLEDs();
	LEDon(LED_RED);
	return 0;
}
