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

	virtual void onClientConnected(TCPSocket* client) const;
	virtual void onClientDisconnected(TCPSocket* client) const;
	virtual void onMessageReceived(TCPSocket* client, uint8_t buffer[], uint8_t len) const;

	virtual void onConnected() const;
	virtual void onDisconnected() const;
	virtual void onConnectionFailed() const;
	virtual void onMessageReceived(uint8_t buffer[], uint8_t len) const;
private:
	TCPServer mtcpserver;
	UARTServer muartserver;
	std::vector<TCPSocket*> mmapping[NB_SLOTS] ;//TODO change number of slots
};

#endif /* DEAMONSERVER_H_ */
