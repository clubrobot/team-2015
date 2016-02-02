/*
 * Module.cpp
 *
 *  Created on: Nov 10, 2015
 *      Author: gabriel
 */

#include "Module.h"



Module::Module() {

}

Module::~Module() {
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



