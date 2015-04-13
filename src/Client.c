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

int client_receive(Client* client) {
	int n = recv(client->clientFD, client->buffer_in, BUFSIZE, 0);
	if(n==-1) perror("Cannot receive infos from client");
	return n;
}

void client_handle_server_msg(Client* client, unsigned int length) {
	if(client->buffer_in[ADDRESS] == SERVER_SLOT) {
		switch(client->buffer_in[REQUEST]) {
		case RQ_ANSWER :
			client_answer(client);
			break;
		default :
			break;
		}
	}
}

void client_prepare_send(Client* client, unsigned int length, char address, char request, ...) {
	int i;
	if(length>BUFSIZE) length = BUFSIZE;
	client->buffer_out[0] = address;
	client->buffer_out[1] = request;
	va_list list;
	va_start(list, request);
	for(i=2; i < length; i++) {
		client->buffer_out[i] = (char)va_arg(list, int);
	}
	va_end(list);
	client->output_buf_ready = 1;
}

void client_send(Client* client) {
	if(client->output_buf_ready ) {
		if(send(client->clientFD, client->buffer_out, BUFSIZE, 0) == -1) {
			perror("Cannot send infos to client");
		}
		client->output_buf_ready = 0;
	}
}

void client_answer(Client* client) {

}
