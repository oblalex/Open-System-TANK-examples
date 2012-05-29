#ifndef BUZZER_H_
#define BUZZER_H_

#include <avr/io.h>

#include "bit_ops.h"

#define BUZZER 7

void initBuzzer(){
	BIT_ON(DDRC, BUZZER);
}

void setBuzzerValue(char value){
	BIT_SET(PORTC, BUZZER, value);
}

#endif /* BUZZER_H_ */
