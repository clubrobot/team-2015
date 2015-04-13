/*
 * Client.c
 *
 *  Created on: 12 avr. 2015
 *      Author: gabriel
 */
#include "Client.h"

Client client_create(SOCKET socket, struct sockaddr_in info, const char* name) {
	Client c = {socket, info, 0};
	strcpy(c.name, name);
	return c;
}

void client_print_info(Client *client) {
	printf("Client %s assigned to the file descriptor %d\n"
			"IP : %s\n", client->name, client->clientFD, inet_ntoa(client->info.sin_addr));
}
