/*
 * DeamonServer.h
 *
 *  Created on: Aug 28, 2015
 *      Author: gabriel
 */

#ifndef DEAMONSERVER_H_
#define DEAMONSERVER_H_

#include <iostream>

#include <arietta-comlib/Socket/Server/TCPServer.h>

class DeamonServer : public FDListener, TCPServer::Events {
public:
	DeamonServer();
	virtual ~DeamonServer();

	void launch();

	virtual void onClientConnected(TCPSocket* client) const;
	virtual void onClientDisconnected(TCPSocket* client) const;
	virtual void onMessageReceived(TCPSocket* client, uint8_t buffer[], uint8_t len) const;
private:
	void serverMessage(TCPSocket* client, uint8_t data[], uint8_t len);

	//Internal events (Server messages)
	void onReceivingSlotMapping(TCPSocket* client, uint8_t slots[], uint8_t len);

	TCPServer mtcpserver;
};

#endif /* DEAMONSERVER_H_ */
