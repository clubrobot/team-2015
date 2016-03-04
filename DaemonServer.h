/*
 * DeamonServer.h
 *
 *  Created on: Aug 28, 2015
 *      Author: gabriel
 */

#ifndef DAEMONSERVER_H_
#define DAEMONSERVER_H_

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include "USBCOMServer.h"
#include <robot-comlib/Serial/UARTServer.h>
#include <robot-comlib/Socket/Server/TCPServer.h>
#include <robot-robot/Message.h>
#include <robot-robot/Log/LogServer.h>


#define NB_SLOTS 10

class DaemonServer : public FDListener, TCPServer::Events, UARTServer::Events {
public:
	DaemonServer();
	virtual ~DaemonServer();

	void launch();
	void close();

	// TCP Events
	virtual void onClientConnected(TCPSocket* client);
	virtual void onClientDisconnected(TCPSocket* client);
	virtual void onMessageReceived(TCPSocket* client, uint8_t buffer[], uint32_t len);

	// Serial events
	virtual void onConnected(UARTServer* uart);
	virtual void onDisconnected(UARTServer* uart);
	virtual void onConnectionFailed(UARTServer* uart);
	virtual void onMessageReceived(UARTServer* uart, uint8_t buffer[], uint32_t len);
private:
	void initAllUSB();

	void serverMessage(TCPSocket* client, const uint8_t data[], uint32_t len);

	//Internal events (Server messages)
	void onReloadUSBDevices(TCPSocket* client);

	TCPServer mtcpserver;
	LogServer Log;
	bool mrunning;

	USBCOMServer mmappingusb[NB_SLOTS];

	static const string UUIDFOLDER;
	static const  string PTRFILE;
};

#endif /* DAEMONSERVER_H_ */
