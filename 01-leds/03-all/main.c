/**
 * Light on red & green LEDs
 */

#include <avr/io.h>

#include "leds.h"

int main(void){
	DDRG  = 0xFF; // set all register G pins to output
	PORTG = (1 << LED_RED_POS) | (1 << LED_GREEN_POS);
	return 0;
}
