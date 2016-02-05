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
#include <robot-comlib/Socket/Client/TCPClient.h>

#include "Message.h"
#include "Semaphore.h"

//TODO : Add Clock module

class Module {
public:
	Module( uint8_t address, TCPClient& client );
	virtual ~Module();

	// Stop the module
	void close();

	void wakeup();

	void pushMsg(Message& msg);

	uint8_t getAddress() const;

	bool isWaitingMsg() const;

protected:

	virtual void run() = 0;

	bool wait(uint timeout = 0);

	bool requestBoard(Message out, Message& in);

private:
	uint8_t maddress;
	TCPClient& mclient;
	bool mrunning;
	std::thread mthread;

	bool mwaiting;
	std::queue<Message> mmsgs;
	Semaphore msem;

	void threadfct();
	void send(const Message& msg);
};

#endif /* MODULE_H_ */
