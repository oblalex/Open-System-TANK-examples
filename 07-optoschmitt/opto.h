#ifndef OPTO_H_
#define OPTO_H_

#include <avr/io.h>

#include "bit_ops.h"

#define OPTO_L 3
#define OPTO_R 4

void initOpto(){
	BIT_OFF(DDRE, OPTO_L);
	BIT_OFF(DDRE, OPTO_R);
}

char isOptoInterrupted(char OPTO_SIDE){
	return (BIT_CHECK(PINE, OPTO_SIDE)) ? 1 : 0;
}

#endif /* OPTO_H_ */
