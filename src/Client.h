/*
 * Client.h
 *
 *  Created on: 12 avr. 2015
 *      Author: gabriel
 */

#ifndef CLIENT_H_
#define CLIENT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/un.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define NAMESIZE 16
#define SOCKET int

typedef struct Client {
	SOCKET clientFD;
	struct sockaddr_in info;
	char name[NAMESIZE];
} Client;

Client client_create(SOCKET socket, struct sockaddr_in info, const char* name);

void client_print_info(Client *client);

#endif /* CLIENT_H_ */
