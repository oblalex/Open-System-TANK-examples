#ifndef DRIVER_H_
#define DRIVER_H_

#include <avr/io.h>
#include "bit_ops.h"

#define DRIVER_FORWARD_L  7
#define DRIVER_BACKWARD_L 6
#define DRIVER_FORWARD_R  3
#define DRIVER_BACKWARD_R 2

void driver_stop_side(char pin_forward, char pin_backward);
void driver_go_forward(char pin_forward, char pin_backward);
void driver_go_backward(char pin_forward, char pin_backward);

void initDriver(){
	BIT_ON(DDRA, DRIVER_FORWARD_L);
	BIT_ON(DDRA, DRIVER_BACKWARD_L);
	BIT_ON(DDRA, DRIVER_FORWARD_R);
	BIT_ON(DDRA, DRIVER_BACKWARD_R);
}

void driver_stop_left(){
	driver_stop_side(DRIVER_FORWARD_L, DRIVER_BACKWARD_L);
}

void driver_stop_right(){
	driver_stop_side(DRIVER_FORWARD_R, DRIVER_BACKWARD_R);
}

void driver_stop_side(char pin_forward, char pin_backward){
	BIT_OFF(PORTA, pin_forward);
	BIT_OFF(PORTA, pin_backward);
}

void driver_go_forward_left(){
	driver_go_forward(DRIVER_FORWARD_L, DRIVER_BACKWARD_L);
}

void driver_go_forward_right(){
	driver_go_forward(DRIVER_FORWARD_R, DRIVER_BACKWARD_R);
}

void driver_go_forward(char pin_forward, char pin_backward){
	BIT_ON(PORTA, pin_forward);
	BIT_OFF(PORTA, pin_backward);
}

void driver_go_backward_left(){
	driver_go_backward(DRIVER_FORWARD_L, DRIVER_BACKWARD_L);
}

void driver_go_backward_right(){
	driver_go_backward(DRIVER_FORWARD_R, DRIVER_BACKWARD_R);
}

void driver_go_backward(char pin_forward, char pin_backward){
	BIT_OFF(PORTA, pin_forward);
	BIT_ON(PORTA, pin_backward);
}

#endif /* DRIVER_H_ */
