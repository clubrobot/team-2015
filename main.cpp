/*
 * main.cpp
 *
 *  Created on: 29 sept. 2015
 *      Author: antoine
 */

#include "DaemonServer.h"

DaemonServer srv;

void myterminate() {
	std::cout << "Terminate" << std::endl;
	srv.close();
	abort();
}

/* Signal handler. */
void hdl(int sig)
{
	std::cout << "Server closed" << std::endl;
	srv.close();
}

void myterminate2(){
	signal(SIGTERM, hdl);
	signal(SIGINT, hdl);
}


int main(){
	std::set_terminate(myterminate);
	std::set_terminate(myterminate2);//terminate Ctrl+C and kill sig
	srv.launch();
	return 0;
}

