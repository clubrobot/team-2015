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
#include <stdarg.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define ADDRESS 0
#define REQUEST 1

//Resquests
#define RQ_ANSWER 1

#define SERVER_SLOT 0
#define MBOARD_SLOT1 1
#define MBOARD_SLOT2 2
#define MBOARD_SLOT3 3
#define MBOARD_SLOT4 4
#define MBOARD_SLOT5 5
#define MBOARD_SLOT6 6
#define MBOARD_SLOT7 7
#define MBOARD_SLOT8 8
#define MBOARD_SLOT9 9
#define MBOARD_SLOT10 10

#define BUFSIZE 64
#define NAMESIZE 16
#define SOCKET int

typedef struct Client {
	SOCKET clientFD;
	struct sockaddr_in info;
	char name[NAMESIZE];

	char buffer_in[BUFSIZE];
	char buffer_out[BUFSIZE];

	int output_buf_ready;
} Client;

Client client_create(SOCKET socket, struct sockaddr_in info, const char* name);

void client_print_info(Client *client);

int client_receive(Client* client);

void client_handle_server_msg(Client* client, unsigned int length);

void client_prepare_send(Client* client, unsigned int length, char address, char request, ...);

void client_send(Client* client);

void client_answer(Client* client);

#endif /* CLIENT_H_ */
