/*
 * Asservissement.h
 *
 *  Created on: 4 févr. 2016
 *      Author: ethel
 */

#include "Module.h"
#include "Message.h"


#ifndef ASSERVISSEMENT_H_
#define ASSERVISSEMENT_H_

class Asservissement : public Module {
public:
	Asservissement( uint8_t address, TCPClient& client );
	virtual ~Asservissement();

	// store the value of both wheels in the given references
	void getWheels( int32_t &leftw, int32_t &rightw );

	// set the value of both wheels to the given ones
	void setWheels( int32_t leftw, int32_t rightw );

	// set the value of both wheels to zero
	void resetWheels();

protected:

	// the main loop
	// @see Module::threadfct
	void run();

	// set the pulse width modulation (PWM) of both motors
	void setPulseWidth( uint16_t leftpw, uint16_t rightpw );

	// do the specified board requests
	// @see minstructions
	void handleInstructions();

	// request both wheels value from the board
	// this is a board request and must only be called in the Module's thread (i.e. in Asservissement::run )
	// @see Module::requestBoard
	bool __getWheels();

	// request the board to set both wheels value
	bool __setWheels();

	// request the board to set the pulse width modulation (PWM) of both motors
	bool __setPWM();

private:

	// the opcodes of the board instructions
	enum Instruction{ CONFIRM, GET_WHEELS, SET_WHEELS, SET_PWM };

	// does the module
	bool getInstruction( Instruction inst );
	void setInstruction( Instruction inst, bool b );

	int32_t mleftWheel;
	int32_t mrightWheel;
	uint16_t mleftPWM;
	uint16_t mrightPWM;

	// This is a 32 bits register that stores which instructions have been requested during the
	// last cycle (through getWheels() or setPulseWidth()).
	// For example when making a GET_WHEELS request (within getWheels()), its corresponding bit
	// ( the 2nd one ) is set to 1.
	// Then its value is read by run() which will do the corresponding board request (through
	// __getWheels() in our example)
	uint32_t minstructions;
};

#endif /* ASSERVISSEMENT_H_ */
