#Declaramos variables
CC := gcc

OBJS := funciones.o main.o

#Generamos el principal
all: ejecutableMain

ejecutableMain: $(OBJS)
	$(CC) -o ejecutableMain $(OBJS) 

funciones.o: funciones.c funciones.h
	$(CC) -c funciones.c

#Borramos todo
clearTodo: 
	rm ejecutableMain funciones.o


#-----------------------------------------------------------
#En el main van como dependecias todos los .o 
#de los .c de si mismo y de los que esten dentro 
#de los .h q use - y de ejecuta -o main y todos los puntos

#En los .o que 	quiero crear van como dependencia a si mismo .c y los .h 
#que use - y ejecuta -c de si mismmo.c


#se ejecuta la primera regla con make y las otras com
#make clearTodo