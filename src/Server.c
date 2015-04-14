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
	fd_set fdwatched; //Stocke les files descriptors (FDs) à survveiller.
	struct timeval timeout; //Timeout instantanée
	timeout.tv_usec = 0;
	timeout.tv_sec = 0;

	while(1) {
			//On charge les FDs (Files Descriptors) à surveiller.
		//On remet à zéro
		FD_ZERO(&fdwatched);
		//On veut surveiller le serveur
		FD_SET(Server.serverFD, &fdwatched);
		//On veut surveiller tous les clients
		for(i=0; i < Server.nbclients; i++) FD_SET(Server.clients[i].clientFD, &fdwatched);

		/* int select (int nfds, fd_set *read-fds, fd_set *write-fds, fd_set *except-fds, struct timeval *timeout)
		 *
		 * Gros conseil pour mieux comprendre : "man select" dans la console linux.
		 * Select permet de détecter quand des FDs sont prêts à être lus.
		 * Intérêt : On évite d'utilisé une fct bloquante comme send et recv alors qu'il n'y en a pas besoin.
		 *
		 * Il faut lui envoyer en premier paramètre (nfds) le FD avec le plus grand numéro plus un.
		 * Pas d'explication à ça, le manuel n'en dit pas plus.
		 * read-fds : FDs qu'on veut surveiller.
		 * write-fds : J'en sais rien.
		 * except-fds : J'en sais rien.
		 * timeout : Structure contenant le temps que va attendre select avant de trouver un FD prêt.
		 * Si on met NULL, il attendra indéfiniment un FD. Il faut donc lui envoyé une structure initialisiée
		 * à 0 seconde et 0 useconde.
		 */
		if(select(fdmax + 1, &fdwatched, NULL, NULL, &timeout) == -1) {
			perror("select() : Cannot watch FDs");
			exit(EXIT_FAILURE);
		}

		//Si le serveur reçoit une requête, alors il s'agit d'une nouvelle connection client.
		if(FD_ISSET(Server.serverFD, &fdwatched)) {
			printf("New client connected.\n");

			//Préparation des éléments à récupérer
			struct sockaddr_in info = {0};
			char name[NAMESIZE];
			socklen_t infosize = sizeof(info);

			//On accepte la connection entrante
			SOCKET clientFD = accept(Server.serverFD, (struct sockaddr*)&info, &infosize);
			if(clientFD == -1) {
				perror("accept() : Cannot accept new client.");
			}
			else {
				//Récupération du nom du process client
				int n = recv(clientFD, name, NAMESIZE, 0);
				if(n == -1) {
					perror("Cannot get process name");
				}
				name[NAMESIZE-1]=0;

				//Ajout du client à la liste des clients
				server_add_client(client_create(clientFD, info, name));
				server_print_clients();

				//Mise à jour du plus grand FD
				fdmax = fdmax > clientFD ? fdmax : clientFD;
			}
		}

		//On vérifie si les clients ont envoyé des infos
		for(i=0; i < Server.nbclients; i++) {
			SOCKET clientFD = Server.clients[i].clientFD;

			if(FD_ISSET(clientFD, &fdwatched)) {
				//Données réçues
				Server.clients[i].size_in = client_receive(&(Server.clients[i]));
			}
			else {
				//Pas de donnée réçue
				Server.clients[i].size_in = 0;
			}
			//Vérification de la connection des clients
			server_check_client(&(Server.clients[i]), timeout, fdmax);
		}
	}
}

void server_add_client(Client client) {
	if(Server.nbclients < MAXCLIENTS - 1) Server.clients[Server.nbclients++] = client;
	else perror("Can't add new client ! Clients limit reached.");
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
	printf("Client %s disconnected\n", client.name);
	server_print_clients();
}

void server_check_client(Client* client, struct timeval timeout, int max) {
	//On envoie une requête au client
	if(client->check_sync){
		if(client_ask(client) == -1) {
			server_rm_client(*client);
			return;
		}
	}

	if(client->size_in) {
		//Si le message est bon
		if(client->buffer_in[ADDRESS] == SERVER_SLOT && client->buffer_in[REQUEST] == RQ_ASK) {
			clock_reset(&(client->out_of_sync));
			client->check_sync = 1;
		}
	}

	double time;
	//Timeout de 200 ms dépassé : Client déconnecté
	if((time = clock_getTime(&(client->out_of_sync))) > 0.2) {
		server_rm_client(*client);
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
