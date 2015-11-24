/*
 * USBCOMServer.h
 *
 *  Created on: Nov 19, 2015
 *      Author: gabriel
 */

#ifndef USBCOMSERVER_H_
#define USBCOMSERVER_H_

#include <string>
#include <arietta-comlib/Serial/UARTServer.h>
using namespace std;

class USBCOMServer: public UARTServer {
private:
	string uuid;
	string numero;
	string description;

public:
	//file to print the config
	static const  string PTRFILE;
	//folder containing all the uuid
	static const string UUIDFOLDER;

	USBCOMServer(string ui, string num, string desc);
	virtual ~USBCOMServer();
	string getTTY();
	void launch(const std::string& UUID);
};

#endif /* USBCOMSERVER_H_ */
