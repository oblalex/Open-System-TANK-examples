#ifndef IFM_H_
#define IFM_H_

/*
 * T3 is used.
 * You need to call sei() in main module.
 */

#include <avr/io.h>
#include <avr/interrupt.h>

#include "bit_ops.h"

#define IFM 7
#define SAMPLES_PER_SECOND 5

volatile unsigned int IFMcounter;
volatile unsigned int inductiveFrequency;

void initIFMsamplingTimer();

void initIFM(){
	BIT_OFF(DDRE, IFM);
	initIFMsamplingTimer();
}

void initIFMsamplingTimer(){
	OCR3A   = 62500/SAMPLES_PER_SECOND;
	TCCR3B  = (1 << CS32) | (1 << WGM32);	 // prescaler 256: 16MHz / 256 / 62500 = 1 Hz
	ETIMSK  = (1 << TICIE3) | (1 << OCIE3A); // enable interrupt on compare & capture
	TCNT3   = 0;
}

ISR(TIMER3_CAPT_vect){
	IFMcounter++;
}

ISR(TIMER3_COMPA_vect){
	inductiveFrequency = IFMcounter * SAMPLES_PER_SECOND;
	IFMcounter = 0;
	TCNT3 = 0;
}

#endif /* IFM_H_ */
