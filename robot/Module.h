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
#include "EventsHandler.h"

//TODO : Add Clock module

class Module {
public:
	Module( uint8_t address, TCPClient& client );
	virtual ~Module();

protected:

	// Launch the thread
	void launch();

	// Stop the thread
	void close();

	// Unlock the thread
	void wakeup();

	void plugEventsHandler( EventsHandler &handler );

	void dispatchEvent( EventName name, EventParams params ) const;

	// Get the associated slot address
	uint8_t getAddress() const;

	// Return true if the module is waiting for a message
	bool isWaitingMsg() const;

	// Unimplement thread routine
	virtual void run() = 0;

	// Push a message in the message queue
	void pushData(uint8_t buffer[], uint32_t len);

	// Get the thread to sleep until wakeup() is called or
	// until the specified timeout in microseconds
	// Returns true if it is unlocked by the function wakeup()
	// or false if it is unlock by the timeout
	// NOTE : if timeout equals 0, the thread will wait forever
	bool wait(uint timeout = 0);

	// Send a request to a slot
	bool requestSlot(Message out, Message& in);

	// Send a message through the TCP connection
	void send(uint8_t buffer[], uint32_t len);

	size_t getBufferSize();

	void getBufferData(uint8_t buffer[], uint32_t len);

	void setBufferAllocSize(size_t size);

	// Received data enters in the data buffer
	inline void startReceiving() {mwaiting = true;}

	// Received date doesn't enter in the data buffer
	inline void stopReceiving() {mwaiting = false;}

protected:

	EventsHandler* mhandler;

private:
	uint8_t maddress;
	TCPClient& mclient;
	bool mrunning;
	std::thread *mthread;
	std::mutex mmutex;

	std::vector<uint8_t> mmsgs;
	uint32_t mread, mwrite, msize;

	Semaphore msem;
	bool mwaiting;

	// Function launched by the thread
	// It calls the function run within a loop an
	// manage thread kill
	void threadfct();

	friend class Brain;
};

#endif /* MODULE_H_ */
