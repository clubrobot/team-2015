/*
 * LogClient.h
 *
 *  Created on: 23 févr. 2016
 *      Author: gab
 */

#ifndef LOG_LOGCLIENT_H_
#define LOG_LOGCLIENT_H_

#include <robot-comlib/Socket/Client/TCPClient.h>

class LogClient : public TCPClient, TCPClient::Events {
public:
	LogClient();
	virtual ~LogClient();
};

#endif /* LOG_LOGCLIENT_H_ */
