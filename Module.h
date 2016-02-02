/*
 * Module.h
 *
 *  Created on: Nov 10, 2015
 *      Author: gabriel
 */

#ifndef MODULE_H_
#define MODULE_H_

#include <thread>
#include <queue>
#include <arietta-comlib/Socket/Client/TCPClient.h>

#include "Message.h"

//TODO : Add Clock module
//TODO : Config file for TCP connection (IP address + port)
//TODO : Add event that give a received Message

class Module {
public:
	Module();
	virtual ~Module();

	// Stop the module
	void close();

	void wakeup();

	void pushMsg(Message& msg);

	uint8_t getAddress();

	void setClient(TCPClient& client);

protected:

	virtual void run() = 0;

	void wait(uint timeout = 0);

	bool requestBoard(Message out, Message& in);
	//TODO : Server messages
	void uploadSlotMapping(uint8_t slots[], uint8_t numSlots);

private:
	uint8_t maddress;
	TCPClient& mclient;
	std::thread* mthread;
	bool mrunning;
	std::queue<Message> mmsgs;

	void threadfct();
	void send(const Message& msg);
};

#endif /* MODULE_H_ */
