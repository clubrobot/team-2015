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
	for (int i = 0; i < NB_SLOTS ; i++){//Loop on the slots
		std::vector< TCPSocket* >::iterator it = mmapping[i].begin();
		std::vector< TCPSocket* >::iterator end = mmapping[i].end();
		while(it != end) {
			if(*it != client){//Client not found
				it++;
			}
			else{//Client found : we erase him from the mapping
				it = mmapping[i].erase(it);
			}
		}
	}
	std::cout << "A client has disconnected" << std::endl;
}

void DeamonServer::onConnected() {
}

void DeamonServer::onDisconnected() {
}

void DeamonServer::onConnectionFailed() {
}

//communication towards uart
void DeamonServer::onMessageReceived(TCPSocket* client, uint8_t buffer[], uint8_t len) {
	std::cout << "New message ! Length : " << (int)len << std::endl;

	int address;
	uint8_t data;
	uint8_t lenght;

	msgb_tcp.appendRawData(buffer,len);

	while(msgb_tcp.newMessagesCompleted()){
		Message newmsg = msgb_tcp.retrieveMessage();
		address = newmsg.getDestination();
		data = newmsg.getData();
		lenght = newmsg.getDataSize();


		//Etape 1 : Read buffer to get the address (to know if the message is a server message or not)
		if(address==0) {//Server message
			serverMessage(client,&data,lenght);
		}
		else {//UART
			muartserver.write(&data,(uint)lenght);
		}
	}
}

/*communication towards clients
 * a slot can communicate with his clients with the use of this function
 */
void DeamonServer::onMessageReceived(uint8_t buffer[], uint8_t len) {
	//Step 1 : Get the address to know which slot has sent the message
	int address;
	uint8_t data;
	uint8_t lenght;
	msgb_uart.appendRawData(buffer,len);

	while(msgb_uart.newMessagesCompleted()){
		Message newmsg = msgb_uart.retrieveMessage();
		address = newmsg.getEmitter();
		data = newmsg.getData();
		lenght = newmsg.getRawDataSize();

		//Step 2 : Redirection of the message to the clients concerned
		std::vector< TCPSocket* >::iterator it = mmapping[address].begin();
		std::vector< TCPSocket* >::iterator end = mmapping[address].end();
		while(it != end) {
			(*it)->write(&data,(uint32_t)lenght);
			it++;
		}
	}
	delete(buffer);
}

void DeamonServer::serverMessage(TCPSocket* client, uint8_t data[], uint8_t len) {
	switch(data[0]){//First byte contains the type of server message
	case 0 ://Message Slot Mapping
		onReceivingSlotMapping(client,data+1,len-1);//From data+1 we have the slots numeros that will allow the new client
		break;
	default:
		break;
	}
}

void DeamonServer::onReceivingSlotMapping(TCPSocket* client, uint8_t slots[], uint8_t len){
	for(int i=0 ; i<len ; i++){//for each concerned slot
		mmapping[slots[i]].push_back(client);//Add client to the mapping
	}
}

