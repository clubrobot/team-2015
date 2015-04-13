/*
 * Server.c
 *
 *  Created on: 12 avr. 2015
 *      Author: gabriel
 */
#include "Server.h"

void server_init(long port) {

	Server.nbclients = 0;
	struct sockaddr_in c = {0};
	Server.sin = c;

	/* Crée un point de sortie représenté par un file descriptor permettant au process de communiquer avec l'extérieur.
	 * Paramètres :
	 * 	int domain : Famille de protocole de communication. AF_INET correspond à l'IPv4.
	 * 	int type : Mode de séquencement utilisé. SOCK_STREAM correspond à une communication en flux de données.
	 *	int protocol : Spécifie le protocole utilisé. TODO : Trouver pourquoi 0.
	 * Retour :
	 * 	int : File descriptor du point de sortie.
	 */
	Server.serverFD = socket(AF_INET, SOCK_STREAM, 0);

	if(Server.serverFD == -1) {
		perror("socket() : Cannot create an endpoint");
		exit(EXIT_FAILURE);
	}

	Server.sin.sin_addr.s_addr = htonl(INADDR_ANY); //N'importe quelle adresse
	Server.sin.sin_port = htons(port); //Port de communication
	Server.sin.sin_family = AF_INET; //IPv4

	//TODO : Documenter par là
	if(bind(Server.serverFD, (struct sockaddr*)&Server.sin, sizeof(Server.sin)) == -1) {
		perror("bind() : Cannot bind");
		exit(EXIT_FAILURE);
	}

	if(listen(Server.serverFD, MAXCLIENTS) == -1) {
		perror("listen() : Cannot listen");
		exit(EXIT_FAILURE);
	}

	printf("Info : Server is listening on port %ld\n", port);
}

void server_close() {
	close(Server.serverFD);
}

void server_run() {
	int i;
	int fdmax = Server.serverFD; //File descriptor ayant le plus grand numéro.
	fd_set fdwatched; //Stocke les files descriptors (FDs) prêts à être lus.
	struct timeval timeout;
	timeout.tv_usec = 20000; //20ms
	timeout.tv_sec = 0;

	while(1) {
		//On charge les FDs à surveiller.
		FD_ZERO(&fdwatched);
		FD_SET(Server.serverFD, &fdwatched);
		for(i=0; i < Server.nbclients; i++) FD_SET(Server.clients[i].clientFD, &fdwatched);

		//TODO : Documenter par là
		if(select(fdmax + 1, &fdwatched, NULL, NULL, &timeout) == -1) {
			perror("select() : Cannot watch FDs");
			exit(EXIT_FAILURE);
		}

		//Si le serveur reçoit une requête, alors il s'agit d'une nouvelle connection client.
		if(FD_ISSET(Server.serverFD, &fdwatched)) {
			printf("New client connected.\n");
			struct sockaddr_in info = {0};
			char name[NAMESIZE];
			socklen_t infosize = sizeof(info);
			SOCKET clientFD = accept(Server.serverFD, (struct sockaddr*)&info, &infosize);
			if(clientFD == -1) {
				perror("accept() : Cannot accept new client.");
			}
			else {
				int n = recv(clientFD, name, NAMESIZE, 0);
				if(n == -1) {
					perror("Cannot get process name");
				}

				server_add_client(client_create(clientFD, info, name));
				server_print_clients();
				fdmax = fdmax < clientFD ? fdmax : clientFD;
			}
		}

		//On vérifie si les clients ont envoyé des infos
		for(i=0; i < Server.nbclients; i++) {
			SOCKET clientFD = Server.clients[i].clientFD;
			server_check_client(Server.clients[i]);

			if(FD_ISSET(clientFD, &fdwatched)) {

			}
		}
	}
}

void server_add_client(Client client) {
	if(Server.nbclients < MAXCLIENTS - 1) Server.clients[Server.nbclients++] = client;
	else perror("Can't add new client ! Max client limit reached.");
}

void server_rm_client(Client client) {
	int i;
	for(i=0; i < Server.nbclients; i++) {
		if(Server.clients[i].clientFD == client.clientFD) {
			close(client.clientFD);

			for(; i <Server.nbclients-1; i++) Server.clients[i] = Server.clients[i+1];
			Server.nbclients--;
			break;
		}
	}
}

void server_check_client(Client client) {
	char msg = 1, answer = 0, n = 0;

	send(client.clientFD, &msg, 1, 0);

	n = recv(client.clientFD, &answer, 1, 0);
	if(answer != 1 && n != 1) {
		server_rm_client(client);
		printf("Client %s disconnected\n", client.name);
		server_print_clients();
	}

}

void server_print_clients() {
	int i;
	for(i=0; i < Server.nbclients; i++) {
		printf("\t\tClient %d\n", i);
		client_print_info(&Server.clients[i]);
		if(i != Server.nbclients-1) printf("\n\n");
	}
	if(!Server.nbclients) printf("No client connected\n");
}
