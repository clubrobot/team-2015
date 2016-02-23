/*
 * Power.cpp
 *
 *  Created on: 4 févr. 2016
 *      Author: ethel
 */

#include "Power.h"

Power::Power( uint8_t address, TCPClient& client )
:	Module( address,client )
,	mbattery( 0x0000 ) {}

Power::~Power() {}

void Power::run()
{
	Clock clk;
	clk.tic();

	// do something here...

	getBatteryVoltage();
	wait( 1000 - clk.tac() );
}

bool Power::getBatteryVoltage()
{
	Message out, in;
	out.setEmitter( 0 );
	out.setReceiver( getAddress() );
	out.append< uint8_t >( GET_BATTERY );
	if( requestSlot( out, in ) )
	{
		mbattery = in.retrieve< uint16_t >();
		return true;
	}
	return false;
}
