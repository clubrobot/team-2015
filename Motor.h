/*
 * Motor.h
 *
 *  Created on: 6 mai 2016
 *      Author: ethel
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include <robot-robot/Module.h>


class Motor : public Module{
public:
	Motor(uint8_t address, TCPClient& client);
	virtual ~Motor();

	virtual void run();


	void stop();
	void forward();
	void left();
	void right();
	void backwards();

	enum Order {STOP, FORWARD, LEFT, RIGHT, BACKWARDS};
	Order morder;

	static const uint8_t order_stop, order_forward ,order_left, order_right, order_backwards;


};

#endif /* MOTOR_H_ */
