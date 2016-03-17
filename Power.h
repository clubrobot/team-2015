/*
 * Power.h
 *
 *  Created on: 4 févr. 2016
 *      Author: ethel
 */
#include "Module.h"
#include "Message.h"


#ifndef POWER_H_
#define POWER_H_

class Power : public Module{
public:

	Power(uint8_t address, TCPClient& client);
	virtual ~Power();

	// Get an estimation of the robot autonomy (in seconds)
	int getAutonomy();

	// Set the robot autonomy... Joke people !! =B
	bool setAutonomy( int autonomy ) { return false; }

protected:

	virtual void run();

	bool getBatteryVoltage();

private:

	enum Instruction{ CONFIRM, GET_BATTERY };

	uint16_t mbattery;
};

#endif /* POWER_H_ */
