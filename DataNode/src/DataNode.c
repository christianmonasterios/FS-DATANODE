/*
 ============================================================================
 Name        : DataNode.c
 Author      : Christian Monasterios
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "funcionesDataNode.h"

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <string.h>

//Variables Globales

int fdArchivo;
struct stat mystat;
char *pmapArchivo = NULL;
dataNode_block* BoquesDeDatos;

int cantidadDeBloques;
// Funciones

int levantarArchivo(char * archivoBinario);
char* mappearArchivo(int fdArchivoBinario, char * posArchivoBinario);
char *get_header(char *mensaje);

int main(int argc, char *argv[]) { //param la ruta del arch configuracion



	printf("%s\n",argv[1]);

	char* path = argv[1];
	crear_archivo_log("/home/utnso/Escritorio/DataNode-DEBUGGIN-LOG");

    leerArchivoConfig(path);

/*
    		printf("\n IP_FS: %s",data_DataNode->IP_FILESYSTEM);
			printf("\n PUERTO_FS: %d",data_DataNode->PUERTO_FILESYSTEM);
			printf("\n NOMBRE NODO: %s", data_DataNode->NOMBRE_NODO);
			printf("\n PUERTO WKR: %d", data_DataNode->PUERTO_WORKER);
			printf("\n DATA BIN: %s",data_DataNode->RUTA_DATABIN);
*/

    		fdArchivo = levantarArchivo(data_DataNode->RUTA_DATABIN);
    		pmapArchivo = mappearArchivo(fdArchivo, pmapArchivo);

    		fstat(fdArchivo, &mystat);

    		printf("\nTamanio Boque: %u", DATANODE_BLOCK_SIZE);
    		printf("\nTamanio Data.bin: %u", mystat.st_size);
    		cantidadDeBloques = mystat.st_size / DATANODE_BLOCK_SIZE;

			printf("\nCantBloques: %u", cantidadDeBloques);

//Funciona que Muestra todo el contenido del .bin
int ar;
			for (ar = 0; ar < cantidadDeBloques; ar++) {

					printf("\n %d-|%s| - ",ar, pmapArchivo+(1024*ar));

			}

// Mostrar todo el BIN

			conectarConFS();

			//FS

while (1) {

				char * solicitudFS = malloc(DATANODE_BLOCK_SIZE+17);
				memset(solicitudFS,'\0', DATANODE_BLOCK_SIZE+17);
				char *tipoArchivo=malloc(1);memset(tipoArchivo,'\0',1);
				char *operacion= malloc(1);memset(operacion,'\0',1);


				recibir(socketConexionFS,(void * )solicitudFS,DATANODE_BLOCK_SIZE+17);
				tipoArchivo = get_header(solicitudFS);
				operacion =string_substring(solicitudFS, 1, 1);

				puts(operacion);

				switch (atoi(operacion)) {
					case 0: //Lectura

						//getBloque()
						escribir_log(string_from_format("LEER:%d ",socketConexionFS));
						char* bloque1 = string_substring(solicitudFS, 2, 4);

						int Block1 = atoi(bloque1);

						if (strcmp(tipoArchivo,"T")==0) {
							printf("Es archivo de Texto");
							printf("\n Leer Bloque %d ", Block1);
							enviar(socketConexionFS,pmapArchivo+(DATANODE_BLOCK_SIZE*Block1),1024);

						}
						//getBloque()

						else {
							printf("Es archivo Binario");
						}
						break;

					case 1: //Escribir

						escribir_log(string_from_format("ESCRIBIR:%d ",socketConexionFS));
						puts("ESCRIBIR");

						char* bl1 = string_substring(solicitudFS, 2, 4);
						int Blocq1 = atoi(bl1);


						char* DATOS = malloc(1024);
						memset(DATOS,'\0',1024);

						memcpy(DATOS,solicitudFS+17,1024);

						printf("\nBloque %d - |%s|", Blocq1, DATOS);

						//setBloque()
						//Este memcopy ya le peca el .bin, el archivo esta mapeado en ese puntero.
						memcpy(pmapArchivo+(1024*Blocq1),DATOS,1024);
						// setBloque()



						printf("\n%s",pmapArchivo+(1024*Blocq1));

						enviar(socketConexionFS,DATOS,1024);

						free(DATOS);

						// Mostrar: Para ver si cargó bien o no.
						int ar;
						for (ar = 0; ar < cantidadDeBloques; ar++) {
						printf("\n %d-|%s| - ",ar, pmapArchivo+(1024*ar));
						}
						// Mostrar BIN


						break;

					}

					free(solicitudFS);
					free(operacion);
					free(tipoArchivo);

					//INICIO: Recibe Peticiones de FS para Lectura o Escritura



					//FIN: Recibe Peticiones de FS para Lectura o Escritura
}

			return 0;
}

int levantarArchivo(char * archivoBinario) {
	int fdArchivoBinario = open(archivoBinario, O_RDWR);
	if (fdArchivoBinario == 0) {
		perror("Error en Open");
		//escribir_log("error en open");
		close(fdArchivoBinario);
		exit(1);

	}
	//escribir_log("levantar archivo OK");
	return fdArchivoBinario;
}

char* mappearArchivo(int fdArchivoBinario, char * posArchivoBinario)
{
	fstat(fdArchivoBinario, &mystat);
	posArchivoBinario = mmap(0, mystat.st_size, PROT_READ | PROT_WRITE,MAP_SHARED, (int) fdArchivoBinario, 0);
	if (posArchivoBinario == MAP_FAILED) {
		perror("Error en mmap");
	//	escribir_log("error en mmap");
		close(fdArchivoBinario);
		exit(1);
	}
	//escribir_log("mmap OK");
	return posArchivoBinario;
}

char *get_header(char *mensaje)
{
	return string_substring(mensaje, 0, 1);
}


