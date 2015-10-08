/*
 * DeamonServer.h
 *
 *  Created on: Aug 28, 2015
 *      Author: gabriel
 */

#ifndef DEAMONSERVER_H_
#define DEAMONSERVER_H_

#include <iostream>
#include <vector>
#include <arietta-comlib/Serial/UARTServer.h>
#include <arietta-comlib/Socket/Server/TCPServer.h>
#define NB_SLOTS 10

class DeamonServer : public FDListener, TCPServer::Events, UARTServer::Events {
public:
	DeamonServer();
	virtual ~DeamonServer();

	void launch();

	virtual void onClientConnected(TCPSocket* client);
	virtual void onClientDisconnected(TCPSocket* client);
	virtual void onMessageReceived(TCPSocket* client, uint8_t buffer[], uint8_t len);

	virtual void onConnected();
	virtual void onDisconnected();
	virtual void onConnectionFailed();
	virtual void onMessageReceived(uint8_t buffer[], uint8_t len);
private:
	void serverMessage(TCPSocket* client, uint8_t data[], uint8_t len);

	//Internal events (Server messages)
	void onReceivingSlotMapping(TCPSocket* client, uint8_t slots[], uint8_t len);

	TCPServer mtcpserver;
	UARTServer muartserver;
	std::vector<TCPSocket*> mmapping[NB_SLOTS] ;//TODO change number of slots
};

#endif /* DEAMONSERVER_H_ */
