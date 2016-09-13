/*
 * LogClient.h
 *
 *  Created on: 23 févr. 2016
 *      Author: gab
 */

#ifndef LOG_LOGCLIENT_H_
#define LOG_LOGCLIENT_H_

#include <iostream>

#include <robot-comlib/Socket/Client/TCPClient.h>

#include "Color.h"

class LogClient : public TCPClient, TCPClient::Events {
public:
	LogClient();
	virtual ~LogClient();

	void onConnected(TCPClient* client);
	void onConnectionFailed(TCPClient* client);
	void onDisconnected(TCPClient* client);
	void onMessageReceived(TCPClient* client, uint8_t buffer[], uint32_t len);

private:
	static const Color::Code color[4];
};

#endif /* LOG_LOGCLIENT_H_ */
