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
#include <arietta-comlib/Serial/UARTServer.h>
#include <arietta-comlib/Socket/Server/TCPServer.h>
#include <arietta-robot/Message.h>


#define NB_SLOTS 10

class DaemonServer : public FDListener, TCPServer::Events, UARTServer::Events {
public:
	DaemonServer();
	virtual ~DaemonServer();

	void launch();

	virtual void onClientConnected(TCPSocket* client);
	virtual void onClientDisconnected(TCPSocket* client);
	virtual void onMessageReceived(TCPSocket* client, uint8_t buffer[], uint32_t len);

	virtual void onConnected(UARTServer* uart);
	virtual void onDisconnected(UARTServer* uart);
	virtual void onConnectionFailed(UARTServer* uart);
	virtual void onMessageReceived(UARTServer* uart, uint8_t buffer[], uint32_t len);
private:
	void initAllUSB();

	void serverMessage(TCPSocket* client, const uint8_t data[], uint32_t len);

	//Internal events (Server messages)
	void onReceivingSlotMapping(TCPSocket* client, const uint8_t slots[], uint32_t len);

	TCPServer mtcpserver;

	USBCOMServer mmappingusb[NB_SLOTS];
	std::vector<TCPSocket*> mmappingtcp[NB_SLOTS] ;//TODO change number of slots

	static const string UUIDFOLDER;
	static const  string PTRFILE;
};

#endif /* DAEMONSERVER_H_ */
