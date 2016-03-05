/*
 * LogServer.h
 *
 *  Created on: 23 févr. 2016
 *      Author: gab
 */

#ifndef LOG_LOGSERVER_H_
#define LOG_LOGSERVER_H_

#include <ostream>

#include <robot-comlib/Socket/Server/TCPServer.h>

#include "TCPstreambuf.h"

class LogServer: public TCPServer {
public:
	LogServer();
	virtual ~LogServer();

	std::ostream info, debug, warning, error;

protected:
private:
	TCPstreambuf* mbufinfo;
	TCPstreambuf* mbufdebug;
	TCPstreambuf* mbufwarning;
	TCPstreambuf* mbuferr;
};

#endif /* LOG_LOGSERVER_H_ */
