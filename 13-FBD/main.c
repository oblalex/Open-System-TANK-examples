/**
 * Front barrier detector.
 * Lights red LED is barrier was found.
 */
#define F_CPU 16000000UL

#include <util/delay.h>

#include "leds.h"
#include "FBD.h"

volatile unsigned char led;

void init();
void run();

int main(void){
	init();
	run();
	return 0;
}

void init(){
	initLEDs();
	initFBD();
}

void run(){
	while(1){
		if (isFrontBarrierDetected()){
			LEDset(LED_RED, 1);
		} else {
			LEDset(LED_RED, 0);
		}
		_delay_ms(10);
	}
}
