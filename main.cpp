/*
 * main.cpp
 *
 *  Created on: 29 sept. 2015
 *      Author: antoine
 */

#include "DaemonServer.h"

DaemonServer srv;

/* Signal handler. */
void hdl(int sig)
{
	std::cout << "Server closed" << std::endl;
	srv.close();
}


int main(){
	std::cout << "Launching daemon" << std::endl;

	signal(SIGINT, hdl);
	signal(SIGTERM, hdl);

	srv.launch();
	return 0;
}

