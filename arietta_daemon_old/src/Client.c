/*
 * Client.c
 *
 *  Created on: 12 avr. 2015
 *      Author: gabriel
 */
#include "Client.h"

Client client_create(SOCKET socket, struct sockaddr_in info, const char* name) {
	Client c = {socket, info, 0};
	c.output_buf_ready = 0;
	c.check_sync = 1;
	c.size_in = 0;
	clock_reset(&(c.out_of_sync));
	strcpy(c.name, name);
	return c;
}

void client_print_info(Client *client) {
	printf("Client %s assigned to the file descriptor %d\n"
			"IP : %s\n", client->name, client->clientFD, inet_ntoa(client->info.sin_addr));
}

int client_receive(Client* client) {
	int n = recv(client->clientFD, client->buffer_in, BUFSIZE, 0);
	if(n == -1){
		perror("Cannot receive infos from client");
		n = 0;
	}
	return n;
}

void client_prepare_send(Client* client, unsigned int length, uint8_t address, ...) {
	int i;
	if(length>BUFSIZE) length = BUFSIZE;
	client->buffer_out[0] = address;
	va_list list;
	va_start(list, address);
	for(i=1; i < length; i++) {
		client->buffer_out[i] = (uint8_t)va_arg(list, int);
	}
	va_end(list);
	client->output_buf_ready = 1;
}

int client_send(Client* client) {
	if(client->output_buf_ready ) {
		if(send(client->clientFD, client->buffer_out, BUFSIZE, 0) == -1) {
			perror("Cannot send infos to client");
			return -1;
		}
		client->output_buf_ready = 0;
		return 1;
	}
	return 0;
}

int client_ask(Client* client) {
	client_prepare_send(client, 2, SERVER_SLOT, RQ_ASK);
	clock_reset(&(client->out_of_sync));
	client->check_sync = 0;
	return client_send(client);
}
