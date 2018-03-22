#Declaramos variables
CC := gcc

OBJS := funciones.o main.o

#Generamos el principal
all: ejecutableMain

ejecutableMain: $(OBJS)
	$(CC) -o ejecutableMain $(OBJS) 

main.o: main.c funciones.h
	$(CC) -c main.c 

funciones.o: funciones.c funciones.h
	$(CC) -c funciones.c

#Borramos todo
clearTodo: 
	rm ejecutableMain funciones.o main.o


#-----------------------------------------------------------
#En el principal (ejecutableMain) van como dependecias todos los .o 
#de los .c de si mismo y de los que esten dentro 
#de los .h q use Y de ejecuta -o principal y todos los .o

#En los .o que 	quiero crear van como dependencia a si mismo .c y los .h 
#que use Y ejecuta -c de si mismmo.c


#se ejecuta la primera regla con make y las otras com
#make clearTodo