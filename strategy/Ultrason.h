/*
 * Ultrason.h
 *
 *  Created on: 6 mai 2016
 *      Author: ethel
 */

#ifndef ULTRASON_H_
#define ULTRASON_H_

#include <robot-robot/Module.h>


class Ultrason : public Module{

public:
	Ultrason(uint8_t address, TCPClient& client);
	virtual ~Ultrason();

	virtual void run();

	void initUltrason();
	void disableUltrason();
	void enableUltrason();

	enum Order {INIT, STOP, DISABLE, ENABLE};
	Order morder;

	static const uint8_t order_stop, order_disable ,order_enable;

};

#endif /* ULTRASON_H_ */
