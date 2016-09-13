/*
 * Motor.cpp
 *
 *  Created on: 6 mai 2016
 *      Author: ethel
 */

#include "Motor.h"

const uint8_t Motor::order_stop = 's';
const uint8_t Motor::order_forward = 'f';
const uint8_t Motor::order_left = 'l';
const uint8_t Motor::order_right = 'r';
const uint8_t Motor::order_backwards = 'b';

Motor::Motor(uint8_t address, TCPClient& client): Module(address, client) {
	// TODO Auto-generated constructor stub

}

Motor::~Motor() {
	// TODO Auto-generated destructor stub
}


void Motor::run()
{
	wait();

	if(morder == STOP) {
		send((uint8_t*)&order_stop, 1);
	}

	if(morder == FORWARD ) {
		send((uint8_t*)&order_forward, 1);
	}

	if(morder == LEFT){
		send((uint8_t*)&order_left, 1);
	}

	if(morder == RIGHT){
		send((uint8_t*)&order_right, 1);
	}

	if(morder == BACKWARDS){
		send((uint8_t*)&order_backwards, 1);
	}
}

void Motor::stop(){
	morder = STOP;
	wakeup();
}

void Motor::forward(){
	morder = FORWARD;
	wakeup();

}

void Motor::left(){
	morder = LEFT;
	wakeup();
}

void Motor::right(){
	morder = RIGHT;
	wakeup();
}

void Motor::backwards(){
	morder = BACKWARDS;
	wakeup();
}
