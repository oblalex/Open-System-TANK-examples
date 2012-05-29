#ifndef LFM_H_
#define LFM_H_

/*
 * T3 is used.
 * You need to call sei() in main module.
 */

#include <avr/io.h>
#include <avr/interrupt.h>

#include "bit_ops.h"

#define LFM 3
#define SAMPLES_PER_SECOND 5

volatile unsigned int LFMcounter;
volatile unsigned int lightFrequency;

void initLFMsamplingTimer();
void initLFMexternalInterrupt();

void initLFM(){
	BIT_OFF(DDRD, LFM);
	initLFMsamplingTimer();
	initLFMexternalInterrupt();
}

void initLFMsamplingTimer(){
	OCR3A   = 62500/SAMPLES_PER_SECOND;
	TCCR3B  = (1 << CS32) | (1 << WGM32);	// prescaler 256: 16MHz / 256 / 62500 = 1 Hz
	ETIMSK  = (1 << OCIE3A); 				// enable interrupt on compare
	TCNT3   = 0;
}

void initLFMexternalInterrupt(){
	EICRA  = (1 << ISC31) | (0 << ISC30);	// update on rising edge
	EIMSK  = (1 << INT3);					// external interrupt enable
}

ISR(INT3_vect){
	LFMcounter++;
}

ISR(TIMER3_COMPA_vect){
	lightFrequency = LFMcounter * SAMPLES_PER_SECOND;
	LFMcounter = 0;
	TCNT3 = 0;
}

#endif /* LFM_H_ */
