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

	for(int i=0; i<NB_SLOTS; i++) {
		mmappingusb[i] = USBCOMServer();
		mmappingusb[i].setFDListener(this);
		mmappingusb[i].setEvents(this);
	}
	for(int i=0; i<NB_SLOTS; i++) {
		mmappingtcp[i] = std::vector< TCPSocket* >();
	}
}

DeamonServer::~DeamonServer() {
}

void DeamonServer::launch() {
	for(;;) {
		listen();
		mtcpserver.run();

		for(int i=0; i<NB_SLOTS; i++) {
			if(!mmappingusb[i].isClosed()) mmappingusb[i].run();
		}
	}
}

void DeamonServer::onClientConnected(TCPSocket* client) {
	std::cout << "New client connected" << std::endl;
}

void DeamonServer::onClientDisconnected(TCPSocket* client) {
	for (int i = 0; i < NB_SLOTS ; i++){//Loop on the slots
		std::vector< TCPSocket* >::iterator it = mmappingtcp[i].begin();
		std::vector< TCPSocket* >::iterator end = mmappingtcp[i].end();
		while(it != end) {
			if(*it != client){//Client not found
				it++;
			}
			else{//Client found : we erase him from the mapping
				it = mmappingtcp[i].erase(it);
			}
		}
	}
	std::cout << "A client has disconnected" << std::endl;
}

void DeamonServer::onConnected(UARTServer* uart) {
	addFD(uart);
}

void DeamonServer::onDisconnected(UARTServer* uart) {
	remFD(uart);
}

void DeamonServer::onConnectionFailed(UARTServer* uart) {
}

//communication towards uart
void DeamonServer::onMessageReceived(TCPSocket* client, uint8_t buffer[], uint8_t len) {
	//std::cout << "New message ! Length : " << (int)len << std::endl;

	Message newmsg = Message(buffer, len);
	int address = newmsg.getReceiver();


	//Etape 1 : Read buffer to get the address (to know if the message is a server message or not)
	if(address==0) {//Server message
		serverMessage(client, newmsg.getData(), newmsg.getDataLength());
	}
	else {//UART
		mmappingusb[address-1].write((uint8_t*)buffer,(uint)len);
	}

}

/*communication towards clients
 * a slot can communicate with his clients with the use of this function
 */
void DeamonServer::onMessageReceived(UARTServer* uart, uint8_t buffer[], uint8_t len) {
	//Step 1 : Get the address to know which slot has sent the message
	Message newmsg = Message(buffer, len);
	int address = newmsg.getEmitter();

	//Step 2 : Redirection of the message to the clients concerned
	std::vector< TCPSocket* >::iterator it = mmappingtcp[address].begin();
	std::vector< TCPSocket* >::iterator end = mmappingtcp[address].end();
	while(it != end) {
		(*it)->write(buffer,(uint32_t)len);
		it++;
	}
}

void DeamonServer::serverMessage(TCPSocket* client, const uint8_t data[], uint8_t len) {
	switch(data[0]){//First byte contains the type of server message
	case 0 ://Message Slot Mapping
		onReceivingSlotMapping(client,data+1,len-1);//From data+1 we have the slots numeros that will allow the new client
		break;
	default:
		break;
	}
}

void DeamonServer::onReceivingSlotMapping(TCPSocket* client, const uint8_t slots[], uint8_t len){
	for(int i=0 ; i<len ; i++){//for each concerned slot
		mmappingtcp[slots[i]].push_back(client);//Add client to the mapping
	}
}

