/*
    ** server.c -- Ejemplo de servidor de sockets de flujo
    */


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

    #define MYPORT 8082    // Puerto al que conectarán los usuarios

    #define BACKLOG 10     // Cuántas conexiones pendientes se mantienen en cola

    void sigchld_handler(int s)
    {
        while(wait(NULL) > 0);
    }

    int main(void)
    {
        int sockfd, cliente;  // Escuchar sobre: sock_fd, nuevas conexiones sobre: cliente
        struct sockaddr_in my_addr;    // información sobre mi dirección
        struct sockaddr_in their_addr; // información sobre la dirección del cliente
        int sin_size;
        struct sigaction sa;
        int yes=1;

        //1° CREAMOS EL SOCKET
        //sockfd: numero o descriptor que identifica al socket que creo
        if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
            perror("socket");
            printf("Error al abrir el socket de escucha\n");
            exit(1);
        }
        printf("Se creo el socket %d\n",sockfd);

        if (setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int)) == -1) {
            perror("setsockopt");
            exit(1);
        }

        my_addr.sin_family = PF_INET;         // Ordenación de bytes de la máquina
        my_addr.sin_port = htons(MYPORT);     // short, Ordenación de bytes de la red
        my_addr.sin_addr.s_addr = inet_addr("192.168.0.12"); //INADDR_ANY (aleatoria) o 127.0.0.1 (local)
        memset(&(my_addr.sin_zero), '\0', 8); // Poner a cero el resto de la estructura

        //2° Relacionamos los datos de my_addr <=> socket
        if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1) {
            printf("Fallo el bind\n");
        	perror("bind");
            exit(1);
        }

        //3° Listen: se usa para dejar al socket escuchando las conexiones que se acumulan en una cola hasta que
        //la aceptamos
        if (listen(sockfd, BACKLOG) == -1) {
            perror("listen");
            printf("Fallo el listen\n");
            exit(1);
        }
        printf("Socket escuchando!!!\n");

        //-------
        sa.sa_handler = sigchld_handler; // Eliminar procesos muertos
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = SA_RESTART;
        if (sigaction(SIGCHLD, &sa, NULL) == -1) {
            perror("sigaction");
            exit(1);
        }
        //--------
        sin_size = sizeof(struct sockaddr_in);
		//4° Accept cliente: numero de socket del cliente que se acaba de conectar
        while(1){
		if ((cliente = accept(sockfd, (struct sockaddr *)&their_addr,
				&sin_size)) == -1) {
			perror("accept");
		}
		printf("Socket cliente %d de IP %s\n",cliente,inet_ntoa(their_addr.sin_addr));

		if (send(cliente, "Hola cliente, todo bien?\n", 25, 0) == -1){
			printf("No se pudo enviar saludo al cliente");
		}
       while(1){
            //Recibimos el mensaje
            //(lo que se puede hacer tambien es recibir un numero primero del tamaño del paquete y luego el paquete)
            char* buffer = malloc(5);
            int bytesRecibidos = recv(cliente,buffer,10,0);//10->4: como maximo 4 bytes
            if(bytesRecibidos <= 0){
            	printf("se fue el cliente\n");
            	break;
            }else{
            	if(strcmp ("exit", buffer) != 0){
            		printf("Llegaron %d bytes con mesaje %s\n",bytesRecibidos,buffer);
            		free(buffer);
            	}else{
            		printf("se fue el cliente\n");
            		break;
            	}

            }
       }
      }
        return 0;
    }