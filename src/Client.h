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

#include "Clock.h"

#define ADDRESS 0
#define REQUEST 1

//Resquests
#define RQ_ASK 1 // Ping le client pour savoir s'il est toujours connecté

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

	uint8_t buffer_in[BUFSIZE];
	uint8_t size_in;
	uint8_t buffer_out[BUFSIZE];

	Clock out_of_sync;
	int check_sync;

	int output_buf_ready;
} Client;

//Crée un client initialisé
Client client_create(SOCKET socket, struct sockaddr_in info, const char* name);

//Affiche les infos d'un client
void client_print_info(Client *client);

//Récupère le msg d'un client
int client_receive(Client* client);

//Prépare le buffer de sortie d'un client
void client_prepare_send(Client* client, unsigned int length, uint8_t address, ...);

//Envoie le contenu du buffer de sortie d'un client
int client_send(Client* client);

//Questionne un client pour détecter une déconnection
int client_ask(Client* client);

#endif /* CLIENT_H_ */
