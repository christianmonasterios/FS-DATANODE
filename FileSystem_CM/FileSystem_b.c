/*
 ============================================================================
 Name        : PokedexServidor.c
 Author      : Pokebanda CM - MM
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/sem.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <commons/bitarray.h>
#include <commons/string.h>
#include <string.h>
#include "socket.h"
#include <commons/collections/node.h>
#include <commons/collections/list.h>
#include "log.h"

// Variables Globales
int fdArchivo;
int cliente[20];
int *TablaAsig;
struct stat mystat;
char *pmapArchivo = NULL;
char *ContBitmap;
char *posBitMap;

// Programa Principal

int main(int argc, char *argv[]) {

	crear_archivo_log("/home/utnso/Escritorio/FileSystem-DEBUGGIN-LOG");

	int socketServer = iniciar_socket_server("127.0.0.1","5009");
	//escribir_log(string_from_format("inicio el servidor con numero de socket:%d ",socketServer));

	escribir_log(string_from_format("inicio el servidor con numero de socket:%d ",socketServer));

	int i = 0;

	while (1) {

		cliente[i] = escuchar_conexiones(socketServer); // Se van conectando los nodos
		escribir_log(string_from_format("Se conectó un nodo en: %d",cliente[i]));

		char * rutaArchivo = "/home/utnso/Escritorio/EjemploFS.txt";

		//FIN ENVIAR
		//Recibir Nodo

		printf("Se conectó un NODO \n");

		char *mensajeRecibido = malloc(50);
		memset(mensajeRecibido, '\0', 50);

		//FIN ENVIAR
		recibir(cliente[i],mensajeRecibido,50);

		//pthread_create(&hiloEsperarMensaje[i], NULL, (void*) esperar_mensaje, (void *) cliente[i]);

		printf("\nInfo Nodo Conectado: %s\n", mensajeRecibido );

		while (1) {

				char input[100]; // Pruebas: Ingresa por teclado para realizar
				scanf("%s", input);
				//printf("%s", input);
				//enviar(cliente[i],"T019890000017\0",17+1024);
				enviar(cliente[i],input,17+1024);
				//enviar(cliente[i],"T1198800040000028Hola soy un archivo de Texto",17+1024);
				escribir_log(string_from_format("El DataNode Conectado %d tiene hilo nro :%d ",cliente[i],i));

				char *mensajeRecibido2 = malloc(1024);
				memset(mensajeRecibido2, '\0',1024);
				recibir(cliente[i],mensajeRecibido2,1024);

				printf("\n%s\n",mensajeRecibido2);
				printf("\Se envió codigo a Cliente\n");


			}

		i++;
	}


	return 0;
}

