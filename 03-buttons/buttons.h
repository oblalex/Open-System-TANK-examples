#ifndef BUTTONS_H_
#define BUTTONS_H_

#include <avr/io.h>
#include "bit_ops.h"

#define SB2 0
#define SB3 1
#define SB4 2

/**
 * Set buttons' pins to read-mode
 */
void initButtons(){
	BIT_OFF(DDRC, SB2);
	BIT_OFF(DDRC, SB3);
	BIT_OFF(DDRC, SB4);
}

char isButtonPressed(char SB){
	return BIT_CHECK((~PINC), SB);
}

#endif /* BUTTONS_H_ */
