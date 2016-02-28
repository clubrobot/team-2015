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

	std::ostream& getInfoStream() {return minfo;}
	std::ostream& getErrStream() {return merr;}
	std::ostream& getWarningStream() {return mwarning;}
	std::ostream& getDebugStream() {return mdebug;}

protected:
private:
	std::ostream minfo;
	TCPstreambuf* mbufinfo;
	std::ostream mdebug;
	TCPstreambuf* mbufdebug;
	std::ostream mwarning;
	TCPstreambuf* mbufwarning;
	std::ostream merr;
	TCPstreambuf* mbuferr;
};

#endif /* LOG_LOGSERVER_H_ */
