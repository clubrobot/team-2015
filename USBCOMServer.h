/*
 * USBCOMServer.h
 *
 *  Created on: Nov 19, 2015
 *      Author: gabriel
 */

#ifndef USBCOMSERVER_H_
#define USBCOMSERVER_H_

#include <string>
#include <iostream>
#include <robot-comlib/Serial/UARTServer.h>

class USBCOMServer: public UARTServer {
private:
	std::string muuid;

public:
	USBCOMServer();
	virtual ~USBCOMServer();

	void launch(const std::string& UUID);
};

#endif /* USBCOMSERVER_H_ */
