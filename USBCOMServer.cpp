/*
 * USBCOMServer.cpp
 *
 *  Created on: Nov 19, 2015
 *      Author: gabriel
 */
#include <fstream>
#include <cstdlib>
#include "USBCOMServer.h"

const string USBCOMServer::UUIDFOLDER = "/dev/disk/by-uuid/";

USBCOMServer::USBCOMServer() {
	//print in the file referenced by Server.ptrfile
	/*fstream outputFile ;
	outputFile.open(USBCOMServer::PTRFILE.c_str(),fstream::out|fstream::app);
	outputFile << ui+" "+num+" "+desc+"\n";
	cout << ui+" "+num+" "+desc <<endl;
	outputFile.close();

	//create the object
	muuid  = string (ui);
	numero = string (num);
	description = string (desc);*/
}

USBCOMServer::~USBCOMServer() {
}

void USBCOMServer::launch(const std::string& UUID) {
	muuid = UUID;
	UARTServer::launch(UUIDFOLDER+UUID);
}
