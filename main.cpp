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

int main(){
	std::set_terminate(myterminate);
	srv.launch();
	return 0;
}

