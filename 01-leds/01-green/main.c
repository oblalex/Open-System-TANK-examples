/**
 * Light on green LED
 */

#include <avr/io.h>

#include "leds.h"

int main(void){
	initLEDs();
	LEDon(LED_GREEN);
	return 0;
}
