#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <commons/log.h>
#include <commons/config.h>
#include <commons/string.h>


typedef struct Alumno{
  int32_t id_mensaje; //4bytes
  int32_t legajo; //4bytes
  char* nombre; //1bytes por char
  char* apellido; //1byte por char
}  Alumno;


int main(int argc, char *argv[])
{
	Alumno * alu = malloc(sizeof(Alumno));
	alu->id_mensaje= 1;
	alu->legajo = 123;
	alu->nombre = malloc(sizeof(char)*10);
	strcpy(alu->nombre, "Juan");
	alu->apellido = malloc(sizeof(char)*10);
	strcpy(alu->apellido, "Perez");

	printf("Enviado: %s %s\n",alu->nombre,alu->apellido );



	void *bufferEnvio = malloc(28);
	memcpy(bufferEnvio, &(alu->id_mensaje), 4);
	memcpy(bufferEnvio + 4, &(alu->legajo), 4);
	memcpy(bufferEnvio + 4, &(alu->nombre), 10);
	memcpy(bufferEnvio + 10, &(alu->apellido), 10);

	
	void *bufferRecibo = malloc(28);
	//send() -> reciv() -> llena el bufferRecibo
	bufferRecibo = bufferEnvio;
	Alumno * aluRecibido = malloc(sizeof(Alumno));

	memcpy(&(aluRecibido->id_mensaje), bufferRecibo, 4);
	memcpy(&(aluRecibido->legajo), bufferRecibo + 4, 4);
	memcpy(&(aluRecibido->nombre), bufferRecibo + 4, 10);
	memcpy(&(aluRecibido->apellido), bufferRecibo + 10, 10);

	printf("Recibo: %s %s\n",aluRecibido->nombre,aluRecibido->apellido);

	free(alu->nombre);
	free(alu->apellido);
	free(alu);
	return 0;
}