/*
 * USBCOMServer.cpp
 *
 *  Created on: Nov 19, 2015
 *      Author: gabriel
 */
#include "USBCOMServer.h"

#include <cstdio>
#include <fstream>
#include <cstdlib>

USBCOMServer::USBCOMServer() {
}

USBCOMServer::~USBCOMServer() {
}

void USBCOMServer::launch(const std::string& UUID) {
	muuid = UUID;

	FILE *fp;
	char tty[16];

	/* Open the command for reading. */
	fp = popen(("/etc/robot/get_TTYbyUSBid.sh "+UUID).c_str(), "r");
	if (fp == NULL) {
		printf("Failed to run command\n" );
	}

	/* Read the output a line at a time - output it. */
	fgets(tty, sizeof(tty)-1, fp);

	tty[strlen(tty)-1] = 0;

	/* close */
	pclose(fp);

	UARTServer::launch(std::string("/dev/")+tty);
}
