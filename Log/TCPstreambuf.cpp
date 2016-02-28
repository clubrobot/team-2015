/*
 * TCPstreambuf.cpp
 *
 *  Created on: 23 févr. 2016
 *      Author: gab
 */

#include <iostream>
#include "TCPstreambuf.h"

TCPstreambuf::TCPstreambuf(TCPServer& server, Channel channel) :
	std::streambuf(),
	mbuffer(256),
	mserver(server),
	mchannel(channel)
{
	char* base = &mbuffer.front();
	*base = (char)channel;
	setp(base+1, base + 255);
}

TCPstreambuf::~TCPstreambuf() {
}

int TCPstreambuf::overflow(int c) {
	if(c != traits_type::eof()){
		*pptr() = c;
		pbump(1);
		if(sendToClients()) {
			return c;
		}
	}
	return traits_type::eof();
}

int TCPstreambuf::sync() {
	return (sendToClients() ? 0 : -1);
}

bool TCPstreambuf::sendToClients() {
	bool res;

	std::streamsize size = pptr() - pbase();
	char* contents = &mbuffer.front();

	res = mserver.sendAll((const void*)contents, size+1);

	pbump(-size);
	return res;
}
