/*
 * log.c
 *
 *  Created on: 29/11/2016
 *      Author: utnso
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <commons/log.h>
#include <commons/string.h>
#include "log.h"

t_log* logg;
pthread_mutex_t mutex_log;

void crear_archivo_log(char *file)
{
	logg = log_create(file,"DATANODE SERVIDOR",false, LOG_LEVEL_INFO);
	log_info(logg, "SERVIDOR - archivo de log creado");
	pthread_mutex_init(&mutex_log,NULL);
}

void escribir_log(char *mensaje)
{
	pthread_mutex_lock(&mutex_log);
	log_info(logg, mensaje);
	pthread_mutex_unlock(&mutex_log);
}

void liberar_log()
{
	log_destroy(logg);
}
