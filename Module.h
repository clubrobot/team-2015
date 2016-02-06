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

	// Stop the thread
	void close();

	// Unlock the thread
	void wakeup();

	// Push a message in the message queue
	void pushMsg(Message& msg);

	// Get the associated slot address
	uint8_t getAddress() const;

	// Return true if the module is waiting for a message
	bool isWaitingMsg() const;

protected:

	// Unimplement thread routine
	virtual void run() = 0;

	// Get the thread to sleep until wakeup() is called or
	// until the specified timeout in microseconds
	// Returns true if it is unlocked by the function wakeup()
	// or false if it is unlock by the timeout
	// NOTE : if timeout equals 0, the thread will wait forever
	bool wait(uint timeout = 0);

	// Send a request to a slot
	bool requestSlot(Message out, Message& in);

private:
	uint8_t maddress;
	TCPClient& mclient;
	bool mrunning;
	std::thread mthread;

	bool mwaiting;
	std::queue<Message> mmsgs;
	Semaphore msem;

	// Function launched by the thread
	// It calls the function run within a loop an
	// manage thread kill
	void threadfct();

	// Send a message through the TCP connection
	void send(const Message& msg);
};

#endif /* MODULE_H_ */
