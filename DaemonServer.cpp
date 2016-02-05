/*
 * DeamonServer.cpp
 *
 *  Created on: Aug 28, 2015
 *      Author: gabriel
 */

#include "DaemonServer.h"

const string DaemonServer::UUIDFOLDER = "/dev/disk/by-uuid/";
const string DaemonServer::PTRFILE = "/etc/robot/usbmapping.cfg";

DaemonServer::DaemonServer() : FDListener() {
	mtcpserver.setFDListener(this);
	mtcpserver.setEvents(this);

	std::cout << "Launching TCP server..." << std::flush;

	mtcpserver.launch(3000, 10);

	std::cout << "done" << std::endl;

	for(int i=0; i<NB_SLOTS; i++) {
		mmappingusb[i].setFDListener(this);
		mmappingusb[i].setEvents(this);
	}

	std::cout << "Loading mapping configuration" << std::endl;

	initAllUSB();
}

DaemonServer::~DaemonServer() {
}

void DaemonServer::launch() {
	for(;;) {
		listen();
		mtcpserver.run();

		for(int i=0; i<NB_SLOTS; i++) {
			if(!mmappingusb[i].isClosed()) mmappingusb[i].run();
		}
	}
}

void DaemonServer::initAllUSB(){
	ifstream file;

	string line;

	string UIID;
	int address;

	try {
		file.open(PTRFILE.c_str(), ifstream::in);
	}
	catch(std::ifstream::failure &exception) {
		std::cerr << "Cannot open mapping config file at : " << PTRFILE << std::endl;
	}

	while(getline(file,line)){
		stringstream linestream (line);
		//consume the first word of the line, which is the uuid
		linestream >> UIID;
		linestream >> address;

		if(address < NB_SLOTS)
		{
			if(!mmappingusb[address].isConnected())
			{
				mmappingusb[address].launch(UIID);
			}
		}
	}

	file.close();
}

void DaemonServer::onClientConnected(TCPSocket* client) {
	std::cout << "New client connected" << std::endl;
}

void DaemonServer::onClientDisconnected(TCPSocket* client) {
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

void DaemonServer::onConnected(UARTServer* uart) {
	std::cout << "Device connected" << std::endl;
	addFD(uart);
}

void DaemonServer::onDisconnected(UARTServer* uart) {
	std::cout << "Device disconnected" << std::endl;
	remFD(uart);
}

//communication towards uart
void DaemonServer::onMessageReceived(TCPSocket* client, uint8_t buffer[], uint32_t len) {
	//Step 1 : Read buffer to get the address (to know if the message is a server message or not)
	Message newmsg = Message(buffer, len);
	int address = newmsg.getReceiver();

	if(address==0) {//Server message
		serverMessage(client, newmsg.getData(), newmsg.getDataLength());
	}
	else {//UART
		if(mmappingusb[address-1].isConnected()) {
			mmappingusb[address-1].write((uint8_t*)buffer,(uint)len);
		}
	}

}

/*communication towards clients
 * a slot can communicate with his clients with the use of this function
 */
void DaemonServer::onMessageReceived(UARTServer* uart, uint8_t buffer[], uint32_t len) {
	//Step 1 : Get the address to know which slot has sent the message
	Message newmsg = Message(buffer, len);
	int address = newmsg.getEmitter();

	//Step 2 : Redirection of the message to the concerned clients
	std::vector< TCPSocket* >::iterator it = mmappingtcp[address-1].begin();
	std::vector< TCPSocket* >::iterator end = mmappingtcp[address-1].end();
	while(it != end) {
		(*it)->write(buffer,(uint32_t)len);
		it++;
	}
}

void DaemonServer::serverMessage(TCPSocket* client, const uint8_t data[], uint32_t len) {
	switch(data[0]){//First byte contains the type of server message
	case 0 ://Message Slot Mapping
		onReceivingSlotMapping(client,data+1,len-1);//From data+1 we have the slots numeros that will allow the new client
		break;
	default:
		break;
	}
}

void DaemonServer::onReceivingSlotMapping(TCPSocket* client, const uint8_t slots[], uint32_t len){
	for(int i=0 ; i<len ; i++){//for each concerned slot
		mmappingtcp[slots[i]-1].push_back(client);//Add client to the mapping
	}
}

