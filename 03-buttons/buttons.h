#ifndef BUTTONS_H_
#define BUTTONS_H_

#include <avr/io.h>

#define SB2 0
#define SB3 1
#define SB4 2

/**
 * Set buttons' pins to read-mode
 */
void initButtons(){
	DDRC &= ~(1 << SB2);
	DDRC &= ~(1 << SB3);
	DDRC &= ~(1 << SB4);
}

char isButtonPressed(char SB){
	return (~PINC) & (1 << SB);
}

#endif /* BUTTONS_H_ */
