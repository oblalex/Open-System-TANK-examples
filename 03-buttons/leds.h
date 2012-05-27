#ifndef LEDS_H_
#define LEDS_H_

#include <avr/io.h>
#include "bit_ops.h"

#define LED_RED		0
#define LED_GREEN	1

/**
 * Set LEDs' pins to write-mode
 */
void initLEDs(){
	BIT_ON(DDRG, LED_RED);
	BIT_ON(DDRG, LED_GREEN);
}

void LEDon(char LED){
	BIT_ON(PORTG, LED);
}

void LEDoff(char LED){
	BIT_OFF(PORTG, LED);
}

void LEDset(char LED, char value){
	BIT_SET(PORTG, LED, value);
}

#endif /* LEDS_H_ */
