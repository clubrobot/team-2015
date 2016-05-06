/*
 * Brain.cpp
 *
 *  Created on: 28 janv. 2016
 *      Author: gab
 */

#include "Brain.h"

const std::string Brain::configfilepath = "/etc/robot/TCP.cfg";

Brain::Brain() : TCPClient(), maddress("127.0.0.1"), mport(3000), mlaunchwaiting(false), mcount(0) {
	setEvents(this);

	loadTCPConfiguration();

	std::cout << "TCP configuration is :\n\tIP : " << maddress << "\n\tPort : " << mport << std::endl;

	launch(maddress, mport);

	mclock.tic();
}

Brain::~Brain() {
}

void Brain::loadTCPConfiguration() {
	std::ifstream file;
	std::string port;

	try {
		file.open(configfilepath.c_str());
		file >> maddress >> port;

		mport = std::stoi(port);
	}
	catch(std::ifstream::failure &exception) {
		std::cout << "Cannot open TCP config file at : " << configfilepath << std::endl;
	}
	catch(std::invalid_argument &exception) {
		std::cout << "Config file at : " << configfilepath << "is invalid\n"
				"Switching to default config" << std::endl;
	}


	file.close();
}

void Brain::onConnected(TCPClient* client) {
	std::cout << "Module connected" << std::endl;


	// Launch the modules when connected
	if(mlaunchwaiting) launchModules();
}

void Brain::onConnectionFailed(TCPClient* client) {
	std::cout << "Connection to server failed" << std::endl;

        usleep(10000);
        launch(maddress, mport);
}

void Brain::onDisconnected(TCPClient* client) {
	std::cout << "Module disconnected" << std::endl;
	exit(0);
}

void Brain::onMessageReceived(TCPClient* client, uint8_t buffer[], uint32_t len) {
	computeBitrate(len);

	uint8_t eid;

	// Get the slot address
	eid = buffer[0];

	// Find a concerned module
	for(std::vector<Module *>::iterator it = mmodules.begin(); it !=mmodules.end(); ++it){

		// if the module is waiting for a message
		// and it matches the slot emitter address
		if((*it)->isWaitingMsg() && eid == (*it)->getAddress())
		{
			// Push the message into the module queue
			(*it)->pushData(buffer, len);

			// Wakeup the module
			(*it)->wakeup();
			break;
		}
	}
}

void Brain::addModule(Module* module){
	mmodules.push_back(module);
}

void Brain::launchModules() {
	// Launch the modules if connected
	if(isConnected()) {
		for(std::vector<Module *>::iterator it = mmodules.begin(); it !=mmodules.end(); ++it) {
			(*it)->launch();
		}
	}
	// Else launch them when connected
	else {
		mlaunchwaiting = true;
	}
}

void Brain::computeBitrate(uint32_t count) {
	mcount += count;

	if(mcount > 620000) {
		if((double)mcount/mclock.tac() > 1.0e+05)
			std::cout << "Warning : high bitrate !" << std::endl;
		mcount = 0;
		mclock.tic();
	}
}
