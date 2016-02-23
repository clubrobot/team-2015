/*
 * TCPstreambuf.h
 *
 *  Created on: 23 févr. 2016
 *      Author: gab
 */

#ifndef LOG_TCPSTREAMBUF_H_
#define LOG_TCPSTREAMBUF_H_

#include <streambuf>
#include "robot-comlib/Socket/Server/TCPServer.h"

class TCPstreambuf : public std::streambuf {
public:
	TCPstreambuf(TCPServer& server);
	virtual ~TCPstreambuf();

protected:
	virtual int sync();

	TCPServer& mserver;
};

#endif /* LOG_TCPSTREAMBUF_H_ */
