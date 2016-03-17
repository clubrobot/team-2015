/*
 * Asservissement.cpp
 *
 *  Created on: 4 févr. 2016
 *      Author: ethel
 */

#include "Asservissement.h"
#include "Clock.h"

Asservissement::Asservissement( uint8_t address, TCPClient &client )
:	Module( address, client )
,	mleftWheel( 0x0000 ), mrightWheel( 0x0000 )
,	mleftPWM( 0x00 ), mrightPWM( 0x00 )
,	minstructions( 0x0000 ) {}

Asservissement::~Asservissement() {}

void Asservissement::getWheels( int32_t &leftw, int32_t &rightw )
{
	leftw = mleftWheel;
	rightw = mrightWheel;
}

void Asservissement::setWheels( int32_t leftw, int32_t rightw )
{
	mleftWheel = leftw;
	mrightWheel = rightw;
	setInstruction( SET_WHEELS, true );
}

void Asservissement::resetWheels()
{
	setWheels( 0x0000, 0x0000 );
}

void Asservissement::setPulseWidth( uint16_t leftpw, uint16_t rightpw )
{
	mleftPWM = leftpw;
	mrightPWM = rightpw;
	setInstruction( SET_PWM, true );
}

void Asservissement::run()
{
	Clock clk;
	clk.tic();

	// do something here...

	handleInstructions();
	wait( 1000 - clk.tac() );
}

void Asservissement::handleInstructions()
{
	if( getInstruction( SET_WHEELS ) )
		__setWheels(); // request the board to set the wheels value to mleftWheel and mrightWheel
	else
		__getWheels(); // this is requested every time except during a setting request so that mleftWheel and mrightWheel are always up to date
	if( getInstruction( SET_PWM ) )
		__setPWM();
	minstructions = 0x0000; // reset the instructions register because everything has been handled
}

bool Asservissement::__getWheels()
{
//	Message out, in;
//	out.setEmitter( 0 );
//	out.setReceiver( getAddress() );
//	out.append< uint8_t >( GET_WHEELS );
//	if( requestSlot( out, in ) )
//	{
//		mleftWheel = in.retrieve< uint32_t >();
//		mrightWheel = in.retrieve< uint32_t >();
//		return true;
//	}
//	return false;
}

bool Asservissement::__setWheels()
{
//	Message out, in;
//	out.setEmitter( 0 );
//	out.setReceiver( getAddress() );
//	out.append< uint8_t >( SET_WHEELS );
//	out.append< uint32_t >( mleftWheel );
//	out.append< uint32_t >( mrightWheel );
//	return requestSlot( out, in );
}

bool Asservissement::__setPWM()
{
//	Message out, in;
//	out.setEmitter( 0 );
//	out.setReceiver( getAddress() );
//	out.append< uint8_t >( SET_PWM );
//	out.append< uint32_t >( mleftPWM );
//	out.append< uint32_t >( mrightPWM );
//	return requestSlot( out, in );
}

bool Asservissement::getInstruction( Instruction inst )
{
	uint32_t flag = 1 << int( inst ); // use the opcode as the bit index (could go to 32 different operations)
	return bool( minstructions & flag );
}

void Asservissement::setInstruction( Instruction inst, bool b )
{
	uint32_t flag = 1 << int( inst );
	if( b )
		minstructions |= flag;
	else
		minstructions &= ~flag;
}
