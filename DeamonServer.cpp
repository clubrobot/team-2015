/*
 * DeamonServer.cpp
 *
 *  Created on: Aug 28, 2015
 *      Author: gabriel
 */

#include "DeamonServer.h"

DeamonServer::DeamonServer() : FDListener() {
	mtcpserver.setFDListener(this);
	mtcpserver.setEvents(this);
	mtcpserver.launch(3000, 10);
	muartserver.setFDListener(this);
	muartserver.setEvents(this);
	muartserver.launch("ttyS0");
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

void DeamonServer::onClientConnected(TCPSocket* client) const {
	std::cout << "New client connected" << std::endl;
}

void DeamonServer::onClientDisconnected(TCPSocket* client) const {
	std::cout << "A client has disconnected" << std::endl;
}

void DeamonServer::onMessageReceived(TCPSocket* client, uint8_t buffer[], uint8_t len) const {
	std::cout << "New message ! Length : " << (int)len << std::endl;
	//Etape 1 : lecture trame -> recupère l'adresse
	int address = 0;
	//Etape 2 : Décision
	if(address==0) {//Message server
	}
	else {//UART
		muartserver.write(buffer,(uint32_t)len);
	}
}

void DeamonServer::onConnected() const {
}

void DeamonServer::onDisconnected() const {
}

void DeamonServer::onConnectionFailed() const {
}

void DeamonServer::onMessageReceived(uint8_t buffer[], uint8_t len) const {
	//Etape 1 : Analyse de la trame pour récupérer l'adresse
	//int address = 1;
	//Etape 2 : Redirection du message vers le client
	//TODO
	for (std::vector< TCPSocket* >::iterator it = mmapping.begin() ; it != mmapping.end(); ++it) {
		(*it)->write(buffer,(uint32_t)len);
	}
	delete(buffer);

}

void DeamonServer::serverMessage(TCPSocket* client, uint8_t data[], uint8_t len) {
}
