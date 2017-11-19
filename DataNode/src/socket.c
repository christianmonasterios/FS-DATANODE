/*
 * socket.c
 *
 *  Created on: 10/10/2016
 *      Author: utnso
 */

#include <stdio.h>
#include <string.h>    //strlen
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>    //write
#include <stdlib.h>
#include "socket.h"

//#define BACKLOG 3			// Define cuantas conexiones vamos a mantener pendientes al mismo tiempo
//#define PACKAGESIZE 1024
//#define IP_LOCAL "127.0.0.1"

int iniciar_socket_cliente(char *ip, int puerto)
{
	int connected_socket, puerto_conexion;
	struct sockaddr_in dest;

	//Creating socket
	if ((connected_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("error creating socket\n");
	}
	printf("created socket\n");

	puerto_conexion = puerto;

	dest.sin_family = AF_INET;
	dest.sin_port = htons( puerto_conexion );
	dest.sin_addr.s_addr = inet_addr( ip );

	//Connecting socket
	if (connect(connected_socket, (struct sockaddr*) &dest, sizeof(dest)) != 0) {
		perror("error connecting socket\n");
	}
	printf("connected socket to server %s:%d\n", ip, puerto_conexion);

	return connected_socket;
}
int enviar(int socket_emisor, void *mensaje_a_enviar, int tamanio)
{
	int ret;
	if ((ret = send(socket_emisor, mensaje_a_enviar, tamanio ,MSG_WAITALL)) < 0) {
		return -1;
	}
	return ret;
}


int recibir(int socket_receptor, void *buffer,int tamanio)
{
	int ret;

	if ((ret = recv(socket_receptor, buffer,tamanio,MSG_WAITALL)) <=0) {
		return -1;

	}
	return ret;
}

int escuchar_conexiones(int socketServidor)
{
	int client_sock_accepted;
	int c;
	struct sockaddr_in client;
	int BACKLOG = 20; //Cantidad de conexiones maximas

	//Listening socket
	if (listen(socketServidor, BACKLOG) != 0) {
		perror("error listening\n");
	}
	//printf("listening at port: %d\n", ntohs(my_addr.sin_port));

	//puts("Waiting for incoming connections...");
	c = sizeof(struct sockaddr_in);

	//accept connection from an incoming client
	client_sock_accepted = accept(socketServidor, (struct sockaddr *)&client, (socklen_t*)&c);
	if (client_sock_accepted < 0)
	{
		perror("error accepting failed\n");
	    return 1;
	}
	//printf("Connection accepted\n");

	return client_sock_accepted;
}

