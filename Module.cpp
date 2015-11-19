/*
 * Module.cpp
 *
 *  Created on: Nov 10, 2015
 *      Author: gabriel
 */

#include "Module.h"

const std::string Module::configfilepath = "/etc/robot/TCP.cfg";

Module::Module() : TCPClient(), maddress("127.0.0.1"), mport(3000) {
	setEvents(this);

	loadTCPConfiguration();

	std::cout << "TCP configuration is :\n\tIP : " << maddress << "\n\tPort : " << mport << std::endl;

	launch(maddress, mport);
}

Module::~Module() {
}

void Module::send(const Message& msg) {
	uint8_t* data = new uint8_t[msg.getRawDataLength()];
	msg.getRawData(data);
	write(data, msg.getRawDataLength());
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

void Module::loadTCPConfiguration() {
	std::ifstream file;

	try {
		file.open(configfilepath.c_str());
	}
	catch(std::ifstream::failure &exception) {
		std::cout << "Cannot open TCP config file at : " << configfilepath << std::endl;
	}

	file >> maddress >> mport;

	file.close();
}

void Module::onConnected(TCPClient* client) {
	std::cout << "Module connected" << std::endl;
}

void Module::onConnectionFailed(TCPClient* client) {
	std::cout << "Connection to server failed" << std::endl;
}

void Module::onDisconnected(TCPClient* client) {
	std::cout << "Module disconnected" << std::endl;
}

void Module::onMessageReceived(TCPClient* client, uint8_t buffer[], uint8_t len) {
	Message msg(buffer, len);
	onMessageReceived(msg);
}
