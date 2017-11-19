/*
 * socket.h
 *
 *  Created on: 10/10/2016
 *      Author: utnso
 */


#ifndef SOCKET_H_
#define SOCKET_H_

//Esta funcion genera un socket de tipo cliente (no puede aceptar conexiones, solo se conecta)
int iniciar_socket_cliente(char *ip, int puerto);
//Esta funcion envia mensajes a traves del socket conectado
//Devuelve un entero significativo de que si el mensaje fue enviado o no
int enviar(int socket_emisor, void *msg, int tamanio);

//Esta funcion recibe mensajes a traves de un socket
int recibir(int socket_receptor, void *buffer,int tamanio);
//Esta funcion envia un STRUCT a traves del socket conectado
//Devuelve un entero significativo de que si el mensaje fue enviado o no

int escuchar_conexiones(int socketServidor);

#endif /* SOCKET_H_ */
