#ifndef BOOM_H_
#define BOOM_H_

/**
 * !! T1 in inverted 8-bit PWM mode is used to control boom
 */

#include <avr/io.h>
#include "bit_ops.h"

#define BOOM 5

#define BOOM_STOP 255
#define BOOM_MAX 210
#define BOOM_MIN 90
#define BOOM_RANGE (BOOM_MAX-BOOM_MIN)

void initBoom(){
	BIT_ON(DDRB, BOOM);
	OCR1A  = BOOM_STOP;
	TCCR1A = (1 << COM1A1) | (1 << COM1A0) | (1 << WGM10);	// inverted PWM
	TCCR1B = (1 << WGM12)  | (1 << CS12) | (0 << CS11);		// 8-bit PWM; prescaler 64
}

void boomSet(char value){
	OCR1A = BOOM_MIN + ((BOOM_RANGE*value)/100);
}

void boomStop(){
	OCR1A = BOOM_STOP;
}

#endif /* BOOM_H_ */
