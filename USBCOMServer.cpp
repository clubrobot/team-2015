/*
 * USBCOMServer.cpp
 *
 *  Created on: Nov 19, 2015
 *      Author: gabriel
 */
#include <fstream>
#include <unistd.h>
#include "USBCOMServer.h"

USBCOMServer::USBCOMServer(string ui, string num, string desc) {
	//print in the file referenced by Server.ptrfile
	fstream outputFile ;
	outputFile.open(USBCOMServer::PTRFILE.c_str(),fstream::out|fstream::app);
	outputFile << ui+" "+num+" "+desc+"\n";
	cout << ui+" "+num+" "+desc <<endl;
	outputFile.close();

	//create the object
	uuid  = string (ui);
	numero = string (num);
	description = string (desc);
}

USBCOMServer::~USBCOMServer() {
}

void USBCOMServer::launch(const std::string& UUID) {
	//UARTServer.launch(UUID);
}

string USBCOMServer::getTTY()
{
	char buf[16];
	string path = string (USBCOMServer::UUIDFOLDER+uuid);
	ssize_t len = readlink(path.c_str(),buf,sizeof(buf)-1);
	buf[len] = '\0';
	return string(buf);
}
