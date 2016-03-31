/*
 * DeamonServer.cpp
 *
 *  Created on: Aug 28, 2015
 *      Author: gabriel
 */

#include "DaemonServer.h"

const std::string DaemonServer::UUIDFOLDER = "/dev/disk/by-uuid/";
const std::string DaemonServer::PTRFILE = "/etc/robot/usbmapping.cfg";

DaemonServer::DaemonServer() : FDListener(), mtcpserver(), Log(), mrunning(true) {
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
	blocksig();
	while(mrunning) {
		listen();
		if(errno == EINTR) {
			break;
		}
		mtcpserver.run();
		Log.run();

		for(int i=0; i<NB_SLOTS; i++) {
			if(!mmappingusb[i].isClosed()) mmappingusb[i].run();
		}
	}
}

void DaemonServer::initAllUSB(){
	std::ifstream file;

	std::string line;

	std::string UIID;
	int address;

	try {
		file.open(PTRFILE.c_str(), std::ifstream::in);
	}
	catch(std::ifstream::failure &exception) {
		std::cerr << "Cannot open mapping config file at : " << PTRFILE << std::endl;
	}

	while(getline(file,line)){
		std::stringstream linestream(line);
		//consume the first word of the line, which is the uuid
		linestream >> UIID;
		linestream >> address;

		if(address < NB_SLOTS+1)
		{
			if(!mmappingusb[address-1].isConnected())
			{
				std::cout << "Starting device on slot " << address << " : " << std::flush;
				mmappingusb[address-1].launchbyUUID(UIID);

				Log.info << "Slot " << address << " : Starting" << std::endl;
			}
			else {
				Log.info << "Slot " << address << " : Connected" << std::endl;
			}
		}
	}

	file.close();
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
	Log.error << "Connection to USB slot has failed" << std::endl;
	perror("");
}

//communication towards uart
void DaemonServer::onMessageReceived(TCPSocket* client, uint8_t buffer[], uint32_t len) {
	#define translate(n) buffer+=n; len-=n;
	//Separate messages from buffer

	while(len > 0) {
		uint32_t sublen = buffer[0];
		onUniqueTCPMessage(client, buffer+1, sublen+1);
		translate(sublen+2);
	}
}

void DaemonServer::onUniqueTCPMessage(TCPSocket* client, uint8_t buffer[], uint32_t len) {
	int address = buffer[0];

	if(address==0) {//Server message
		serverMessage(client, buffer+1, len);
	}
	else {//UART
		if(mmappingusb[address-1].isConnected()) {
			mmappingusb[address-1].write((uint8_t*)(buffer+1),(uint)(len-1));
			Log.warning << "writing to address : " << address << " len : " << len << std::endl;
		}
	}
}

/*communication towards clients
 * a slot can communicate with his clients with the use of this function
 */
void DaemonServer::onMessageReceived(UARTServer* uart, uint8_t buffer[], uint32_t len) {
	uint8_t* data = new uint8_t[len + 1];
	data[0] = getUARTIndex((USBCOMServer*)uart) + 1;
	memcpy(data+1, buffer, len);

	std::vector< TCPSocket* > clients = mtcpserver.getClients();
	//Send the message to all the clients
	std::vector< TCPSocket* >::iterator it = clients.begin();
	std::vector< TCPSocket* >::iterator end = clients.end();
	Log.debug << "writing to clients : " << (int)data[0]
    << " len : " << len << " ptr : " << std::endl;
	while(it != end) {
		(*it)->write(data,(uint32_t)len+1);
		it++;
	}
	delete(data);
}

void DaemonServer::serverMessage(TCPSocket* client, const uint8_t data[], uint32_t len) {
	// The first byte contains the instruction type of the server message
	switch(data[0]){
	case 0 ://Reload USB devices
		onReloadUSBDevices(client);//From data+1 we have the slots numeros that will allow the new client
		break;
	case 1 ://Call commande on robot app
		onRemoteCmd(client, data+1);
		break;
	default:
		break;
	}
}

void DaemonServer::onReloadUSBDevices(TCPSocket* client){
	initAllUSB();
}

void DaemonServer::onRemoteCmd(TCPSocket* client, const uint8_t command[]) {

	auto run = [client, command]() {
		FILE *fp;
		char c;

		/* Open the command for reading. */
		fp = popen((std::string("robot ")+ (char*)command).c_str(), "r");
		if (fp == NULL) {
			//Log.error << "Failed to run command" << std::endl;
		}
		/* Read the output a line at a time - output it. */
		while((c = fgetc(fp)) != EOF) {
			client->write(&c, 1);
		}

		/* close */
		pclose(fp);
	};
	std::thread exec(run);
	//mcmdthreads.push_back(new std::thread(run));
}

void DaemonServer::close() {
	mrunning = false;
}

uint8_t DaemonServer::getUARTIndex(USBCOMServer* ptr) {
	return (ptr - mmappingusb);
}
