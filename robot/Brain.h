/*
 * Brain.h
 *
 *  Created on: 28 janv. 2016
 *      Author: gab
 */

#ifndef BRAIN_H_
#define BRAIN_H_

#include <robot-comlib/Socket/Client/TCPClient.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "Module.h"
#include "Clock.h"

class Brain : public TCPClient, private TCPClient::Events {
public:
	Brain();
	virtual ~Brain();

	// Add a new module to the brain
	void addModule(Module* module);

	void launchModules();

private:
	std::vector<Module*> mmodules;

	//Load TCP configuration : connection port and address
	void loadTCPConfiguration();

	// TCP events
	void onConnected(TCPClient* client);
	void onConnectionFailed(TCPClient* client);
	void onDisconnected(TCPClient* client);
	void onMessageReceived(TCPClient* client, uint8_t buffer[], uint32_t len);

	void computeBitrate(uint32_t count);

	std::string maddress;
	int mport;

	bool mlaunchwaiting;

	// For bitrate
	uint32_t mcount;
	Clock mclock;

	static const std::string configfilepath;

};

#endif /* BRAIN_H_ */
