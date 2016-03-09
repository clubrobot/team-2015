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

int main(){
	std::set_terminate(myterminate);

	struct sigaction act;

	memset (&act, 0, sizeof(act));
	act.sa_handler = hdl;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;

	/* This server should shut down on SIGTERM. */
	if (sigaction(SIGTERM, &act, 0) < 0 || sigaction(SIGINT, &act, 0)) {
		perror ("sigaction");
		return 1;
	}

	srv.launch();
	return 0;
}

