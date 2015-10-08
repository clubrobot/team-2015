/*
 * DeamonServer.cpp
 *
 *  Created on: Aug 28, 2015
 *      Author: gabriel
 */

#include "DeamonServer.h"

DeamonServer::DeamonServer() : FDListener() {
	mtcpserver = TCPServer();
	mtcpserver.setFDListener(this);
	mtcpserver.setEvents(this);
	mtcpserver.launch(3000, 10);
	muartserver = UARTServer();
	muartserver.setFDListener(this);
	muartserver.setEvents(this);
	muartserver.launch("ttyS0");
	for(int i=0; i<NB_SLOTS; i++) {
		mmapping[i] = std::vector< TCPSocket* >();
	}
}

DeamonServer::~DeamonServer() {
}

void DeamonServer::launch() {
	for(;;) {
		listen();
		mtcpserver.run();
		muartserver.run();
	}
}

void DeamonServer::onClientConnected(TCPSocket* client) {
	std::cout << "New client connected" << std::endl;
}

void DeamonServer::onClientDisconnected(TCPSocket* client) {
	std::cout << "A client has disconnected" << std::endl;
}

void DeamonServer::onMessageReceived(TCPSocket* client, uint8_t buffer[], uint8_t len) {
	std::cout << "New message ! Length : " << (int)len << std::endl;

	const void* bufferptr = buffer;
	//Etape 1 : lecture trame -> recupère l'adresse
	int address = 0;
	//Etape 2 : Décision
	if(address==0) {//Message server
	}
	else {//UART
		muartserver.write(bufferptr,(uint)len);
	}
}

void DeamonServer::onConnected() {
}

void DeamonServer::onDisconnected() {
}

void DeamonServer::onConnectionFailed() {
}

void DeamonServer::onMessageReceived(uint8_t buffer[], uint8_t len) {
	//Etape 1 : Analyse de la trame pour récupérer l'adresse
	int address = 1;
	//Etape 2 : Redirection du message vers le client
	//TODO
	std::vector< TCPSocket* >::const_iterator it = mmapping[address].begin();
	std::vector< TCPSocket* >::const_iterator end = mmapping[address].end();
	while(it != end) {
		(*it)->write(buffer,(uint32_t)len);
		it++;
	}

	delete(buffer);

}

void DeamonServer::serverMessage(TCPSocket* client, uint8_t data[], uint8_t len) {
}
