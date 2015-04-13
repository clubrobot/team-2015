/*
 * Server.h
 *
 *  Created on: 12 avr. 2015
 *      Author: gabriel
 */

#ifndef SERVER_H_
#define SERVER_H_

#include "Client.h"
#include "Clock.h"

#define MAXCLIENTS 10

typedef struct Server_s {
	SOCKET serverFD;	//File descriptor du serveur
	struct sockaddr_in sin;	//Config du serveur

	Client clients[MAXCLIENTS];
	int nbclients;
} Server_s;

Server_s Server; //Structure globale (un seul serveur pour le process).

void server_init(long port);

void server_close();

void server_run();

void server_add_client(Client client);

void server_rm_client(Client client);

void server_check_client(Client client);

void server_print_clients();

#endif /* SERVER_H_ */
