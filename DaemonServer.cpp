/*
 * DeamonServer.cpp
 *
 *  Created on: Aug 28, 2015
 *      Author: gabriel
 */

#include "DaemonServer.h"

const std::string DaemonServer::UUIDFOLDER = "/dev/disk/by-uuid/";
const std::string DaemonServer::PTRFILE = "/etc/robot/usbmapping.cfg";

DaemonServer::DaemonServer() : FDListener(), Log(), mrunning(true) {
	mtcpserver.setFDListener(this);
	mtcpserver.setEvents(this);
	Log.setFDListener(this);

	std::cout << "Launching TCP server" << std::endl;

	mtcpserver.launch(3000, 10);

	std::cout << "Launching log server" << std::endl;

	Log.launch(3003, 1);

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
	while(mrunning) {
		listen();
		mtcpserver.run();
		Log.run();

		for(int i=0; i<NB_SLOTS; i++) {
			if(!mmappingusb[i].isClosed()) mmappingusb[i].run();
		}
	}
}

void DaemonServer::initAllUSB(){
	/*ifstream file;

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

		if(address < NB_SLOTS+1)
		{
			if(!mmappingusb[address-1].isConnected())
			{
				mmappingusb[address-1].launch(UIID);
			}
		}
	}

	file.close();*/
	mmappingusb[0].launch("/dev/ttyUSB0");
	mmappingusb[1].launch(std::string("/dev/")+"ttyUSB1");
}

void DaemonServer::onClientConnected(TCPSocket* client) {
	Log.info << "A client connected" << std::endl;
}

void DaemonServer::onClientDisconnected(TCPSocket* client) {
	Log.info << "disconnected" << std::endl;
}

void DaemonServer::onConnected(UARTServer* uart) {
	Log.info << "Device connected" << std::endl;
	addFD(uart);
}

void DaemonServer::onDisconnected(UARTServer* uart) {
	Log.info << "Device disconnected" << std::endl;
	remFD(uart);
	uart->close();
}

void DaemonServer::onConnectionFailed(UARTServer* uart) {
	Log.info << "Connection to USB slot has failed" << std::endl;
	perror("");
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
			Log.debug << "writing to address : " << address << std::endl;
		}
	}

}

/*communication towards clients
 * a slot can communicate with his clients with the use of this function
 */
void DaemonServer::onMessageReceived(UARTServer* uart, uint8_t buffer[], uint32_t len) {
	std::vector< TCPSocket* > clients = mtcpserver.getClients();
	//Send the message to all the clients
	std::vector< TCPSocket* >::iterator it = clients.begin();
	std::vector< TCPSocket* >::iterator end = clients.end();
	Log.debug << "writing to clients : " << std::endl;
	while(it != end) {
		(*it)->write(buffer,(uint32_t)len);
		it++;
	}
}

void DaemonServer::serverMessage(TCPSocket* client, const uint8_t data[], uint32_t len) {
	// The first byte contains the instruction type of the server message
	switch(data[0]){
	case 0 ://Reload USB devices
		onReloadUSBDevices(client);//From data+1 we have the slots numeros that will allow the new client
		break;
	default:
		break;
	}
}

void DaemonServer::onReloadUSBDevices(TCPSocket* client){
	initAllUSB();
}

void DaemonServer::close() {
	mrunning = false;
}
