/*
 * Brain.h
 *
 *  Created on: 28 janv. 2016
 *      Author: gab
 */

#ifndef BRAIN_H_
#define BRAIN_H_

#include <arietta-comlib/Socket/Client/TCPClient.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "Module.h"

class Brain : public TCPClient, private TCPClient::Events {
public:
	Brain();
	virtual ~Brain();

	// Add new module to the brain
	void addModule(Module module);

	// Launch all the modules
	void launchModules();

private:
	std::vector<Module> mmodules;

	//Configuration file functions
	void loadTCPConfiguration();

	// TODO : implement these methods
	void onConnected(TCPClient* client);
	void onConnectionFailed(TCPClient* client);
	void onDisconnected(TCPClient* client);
	void onMessageReceived(TCPClient* client, uint8_t buffer[], uint32_t len);

	std::string maddress;
	int mport;

	static const std::string configfilepath;

};

#endif /* BRAIN_H_ */
