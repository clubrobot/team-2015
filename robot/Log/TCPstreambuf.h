/*
 * TCPstreambuf.h
 *
 *  Created on: 23 févr. 2016
 *      Author: gab
 */

#ifndef LOG_TCPSTREAMBUF_H_
#define LOG_TCPSTREAMBUF_H_

#include <streambuf>
#include <vector>
#include "robot-comlib/Socket/Server/TCPServer.h"

class TCPstreambuf : public std::streambuf {
public:
	enum Channel {INFO='A', DEBUG='B', WARNING='C', ERROR='D'};

	TCPstreambuf(TCPServer& server, Channel channel);
	virtual ~TCPstreambuf();

protected:
	virtual int overflow(int c);
	virtual int sync();

	bool sendToClients();

	std::vector<char> mbuffer;
	TCPServer& mserver;
	Channel mchannel;
private:
	TCPstreambuf(const TCPstreambuf& streambuf);
	TCPstreambuf& operator=(const TCPstreambuf& streambuf);
};

#endif /* LOG_TCPSTREAMBUF_H_ */
