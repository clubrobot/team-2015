/*
 * TCPstreambuf.cpp
 *
 *  Created on: 23 févr. 2016
 *      Author: gab
 */

#include "TCPstreambuf.h"

TCPstreambuf::TCPstreambuf(TCPServer& server) : std::streambuf(), mserver(server) {
}

TCPstreambuf::~TCPstreambuf() {
}

int TCPstreambuf::sync() {
	int res = 0;
	std::vector<TCPSocket*> clients = mserver.getClients();

	if(clients.size() > 0) {
		std::streamsize size = in_avail();
		char* contents = new char[size];
		sgetn (contents,size);
		for(std::vector<TCPSocket*>::iterator it = clients.begin(); it != clients.end(); ++it) {
			try {
				(*it)->write((const void*)contents, size);
			}
			catch(IOException& e) {
				res = -1;
			}
		}
	}
	return res;
}
