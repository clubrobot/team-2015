/*
 * Module.h
 *
 *  Created on: Nov 10, 2015
 *      Author: gabriel
 */

#ifndef MODULE_H_
#define MODULE_H_

#include <Socket/Client/TCPClient.h>
#include "Message.h"

//TODO : Add Clock module
//TODO : Config file for TCP connection (IP address + port)
//TODO : Add event that give a received Message

class Module : public TCPClient, private TCPClient::Events {
public:
	Module();
	virtual ~Module();

protected:

	void send(const Message& msg);

	//TODO : Add new events
	virtual void onMessageReceived(Message& msg) = 0;

	//TODO : Server messages
	void uploadSlotMapping(uint8_t slots[]);

	//TODO (fun) : Get all slots descriptions.

private:
	// TODO : implement these methods
	void onConnected();
	void onConnectionFailed();
	void onDisconnected();
	void onMessageReceived(uint8_t buffer[], uint8_t len);
};

#endif /* MODULE_H_ */