/*
 ============================================================================
 Name        : moduloCliente.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "cliente.h"

int main(void) {
	puts("Hola, soy un modulo que levantare un cliente para conectar al servidor");
	levantarCliente();
	return EXIT_SUCCESS;
}
