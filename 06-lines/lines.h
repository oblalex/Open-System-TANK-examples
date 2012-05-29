#ifndef LINES_H_
#define LINES_H_

#include <avr/io.h>

#include "bit_ops.h"

#define LINE_FRONT_L 1
#define LINE_FRONT_R 0
#define LINE_REAR_L	 2
#define LINE_REAR_R  3

void initLines(){
	BIT_OFF(DDRF, LINE_FRONT_L);
	BIT_OFF(DDRF, LINE_FRONT_R);
	BIT_OFF(DDRF, LINE_REAR_L);
	BIT_OFF(DDRF, LINE_REAR_R);
}

char isLineBarrierDetected(char LINE_SIDE){
	return (BIT_CHECK(PINF, LINE_SIDE)) ? 1 : 0;
}

#endif /* LINES_H_ */
