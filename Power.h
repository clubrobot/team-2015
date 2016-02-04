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

	bool getBattery(uint16_t &level);
	uint32_t estimateAutonomy();//return autonomy in seconds.

};

#endif /* POWER_H_ */
