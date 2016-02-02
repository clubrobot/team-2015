/*
 * Module.cpp
 *
 *  Created on: Nov 10, 2015
 *      Author: gabriel
 */

#include "Module.h"



Module::Module( uint8_t address, TCPClient& client ):
	maddress( address ),
	mclient( client ),
	mthread( Module::threadfct, this ),
	mrunning( true ) {
}

Module::~Module() {
	close();
}

void Module::close() {
	mrunning = false;
	mthread.join();
}

void Module::wakeup() {
	msem.notify();
}

void Module::pushMsg(Message& msg) {
	mmsgs.push( msg );
}

uint8_t Module::getAddress() const {
	return maddress;
}

bool Module::wait(uint timeout) {
	return msem.wait( timeout );
}

bool Module::requestBoard(Message out, Message& in) {
	send( out );
	if( wait( 100 ) ) // in microseconds
	{
		in = mmsgs.pop(); // TODO: copy constructor of class Message
		return true;
	}
	return false;
}

void Module::send(const Message& msg) {
	uint8_t* data = new uint8_t[msg.getRawDataLength()];
	msg.getRawData(data);
	mclient.write(data, msg.getRawDataLength());
	delete(data);
}

void Module::uploadSlotMapping(uint8_t slots[], uint8_t numSlots) {

	Message m = Message();
	m.setEmitter( 0 ); // don't care
	m.setReceiver( 0 ); // server
	m.append< uint8_t >( 0 ); // slot mapping message
	m.appendData( slots, numSlots );

	send( m );
}



