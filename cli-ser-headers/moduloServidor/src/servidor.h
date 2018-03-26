/*
 * servidor.h
 *
 *  Created on: 25/3/2018
 *      Author: utnso
 */
#ifndef SERVIDORH
#define SERVIDORH

#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <signal.h>
#include <pthread.h>

void levantarServidor();

#define MYPORT 8082    // Puerto al que conectarán los usuarios

#define BACKLOG 10     // Cuántas conexiones pendientes se mantienen en cola

//#define MYIP "192.168.0.12"
#define MYIP "127.0.0.1"

typedef struct DatosCliente {
		   char*  ipCliente;
		   int   idSocketCliente;
} TipoDatosCliente;

pthread_mutex_t mutex;

#endif


