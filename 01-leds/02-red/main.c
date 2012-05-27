/**
 * Light on red LED
 */

#include <avr/io.h>

#include "leds.h"

int main(void){
	DDRG  = 0xFF; // set all register G pins to output
	PORTG = 1 << LED_RED_POS;
	return 0;
}
