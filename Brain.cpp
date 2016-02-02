/*
 * Brain.cpp
 *
 *  Created on: 28 janv. 2016
 *      Author: gab
 */

#include "Brain.h"

const std::string Brain::configfilepath = "/etc/robot/TCP.cfg";

Brain::Brain() : TCPClient(), maddress("127.0.0.1"), mport(3000) {
	setEvents(this);

	loadTCPConfiguration();

	std::cout << "TCP configuration is :\n\tIP : " << maddress << "\n\tPort : " << mport << std::endl;

	launch(maddress, mport);
}

Brain::~Brain() {
}

void Brain::loadTCPConfiguration() {
	std::ifstream file;
	std::string port;

	try {
		file.open(configfilepath.c_str());
	}
	catch(std::ifstream::failure &exception) {
		std::cout << "Cannot open TCP config file at : " << configfilepath << std::endl;
	}

	file >> maddress >> port;

	mport = std::stoi(port);

	file.close();
}

void Brain::onConnected(TCPClient* client) {
	std::cout << "Module connected" << std::endl;
}

void Brain::onConnectionFailed(TCPClient* client) {
	std::cout << "Connection to server failed" << std::endl;
}

void Brain::onDisconnected(TCPClient* client) {
	std::cout << "Module disconnected" << std::endl;
}

void Brain::onMessageReceived(TCPClient* client, uint8_t buffer[], uint32_t len) {
	Message msg(buffer, len);

	// Aiguillage/Abonnement

	//Use pushMsg vers bon module

	//Module.wakeup();
}
