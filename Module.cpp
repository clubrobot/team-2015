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
									mthread( nullptr ),
									mwaiting( false ) {
}

Module::~Module() {
	close();
}

void Module::launch() {
	mthread = new std::thread(&Module::threadfct, this);
}

void Module::close() {
	if(mrunning) {
		mrunning = false;

		// Unlock the thread
		wakeup();

		// Wait that the thread function returns
		mthread->join();

		delete(mthread);
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

bool Module::requestSlot(Message out, Message& in) {
	// Send the message
	send( out );

	// Module is now waiting for an answer
	mwaiting = true;
	if( wait( 100 ) ) // if the module is woke up by the brain
	{
		in = mmsgs.front();
		mmsgs.pop();
		mwaiting = false;
		return true;
	}
	// Timeout expired : no answer from the slot
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
		this->run();
	}
}
