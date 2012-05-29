#ifndef FBD_H_
#define FBD_H_

#include <util/delay.h>
#include <avr/io.h>

#include "bit_ops.h"

#define BAMP_DIR 2
#define BAMP_EN  2
#define F_TSOP 	 5
#define F0 		 7

void initFBD(){
	BIT_ON(DDRE, BAMP_DIR);
	BIT_OFF(DDRE, F_TSOP);

	BIT_ON(DDRB, F0);
	BIT_ON(DDRD, BAMP_EN);

	BIT_ON(PORTE, BAMP_DIR);
}

char isFrontBarrierDetected(){
	BIT_ON(PORTD, BAMP_EN);

	for(int i = 0; i <= 370; i++) {  // 384 times 27 us = 9.990 ms for a IR burst
		BIT_ON(PORTB, F0);
		_delay_us(13);
		BIT_OFF(PORTB, F0);
		_delay_us(13);
	}
	BIT_OFF(PORTD, BAMP_EN);

	return (BIT_CHECK(PINE, F_TSOP)) ? 1 : 0;
}

#endif /* FBD_H_ */
