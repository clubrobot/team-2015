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
									mrunning( true) ,
									mthread( &Module::threadfct, this ),
									mwaiting( false ) {
}

Module::~Module() {
	close();
}

void Module::close() {
	if(mrunning) {
		wakeup();
		mrunning = false;
		mthread.join();
	}
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
	mwaiting = true;
	if( wait( 100 ) ) // in microseconds
	{
		in = mmsgs.front();
		mmsgs.pop();
		mwaiting = false;
		return true;
	}
	mwaiting = false;
	return false;
}

bool Module::isWaitingMsg() const {
	return mwaiting;
}

void Module::send(const Message& msg) {
	uint8_t* data = new uint8_t[msg.getRawDataLength()];
	msg.getRawData(data);
	mclient.write(data, msg.getRawDataLength());
	delete(data);
}

void Module::threadfct() {
	while( mrunning )
	{
		run();
	}
}
