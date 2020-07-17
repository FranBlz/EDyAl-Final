FLAGS = -Wall -Wextra -Werror -std=c99 -g

ESTRUCTURA1 = itree
ESTRUCTURA2 = tablahash

SALIDA = salida

all: $(ESTRUCTURA1).o $(ESTRUCTURA2).o main

$(ESTRUCTURA1).o: $(ESTRUCTURA1).c $(ESTRUCTURA1).h
	gcc $(FLAGS) -c $(ESTRUCTURA1).c

$(ESTRUCTURA2).o: $(ESTRUCTURA2).c $(ESTRUCTURA2).h
	gcc $(FLAGS) -c  $(ESTRUCTURA2).c

main: interprete.c $(ESTRUCTURA1).o $(ESTRUCTURA2).o
	gcc $(FLAGS) -o $(SALIDA) interprete.c $(ESTRUCTURA1).o $(ESTRUCTURA2).o

clean: 
	rm *.o vgcore*