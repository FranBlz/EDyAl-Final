FLAGS = -Wall -Wextra -Werror -std=c99 -g

ESTRUCTURA1 = itree
ESTRUCTURA2 = tablahash
ESTRUCTURA3 = stack

SALIDA = salida

all: $(ESTRUCTURA1).o $(ESTRUCTURA2).o $(ESTRUCTURA3).o main

$(ESTRUCTURA3).o: $(ESTRUCTURA3).c $(ESTRUCTURA3).h $(ESTRUCTURA1).h
	gcc $(FLAGS) -c  $(ESTRUCTURA3).c

$(ESTRUCTURA1).o: $(ESTRUCTURA1).c $(ESTRUCTURA1).h $(ESTRUCTURA3).h
	gcc $(FLAGS) -c $(ESTRUCTURA1).c

$(ESTRUCTURA2).o: $(ESTRUCTURA2).c $(ESTRUCTURA2).h
	gcc $(FLAGS) -c  $(ESTRUCTURA2).c

main: interpreteSSCANF.c $(ESTRUCTURA1).o $(ESTRUCTURA2).o $(ESTRUCTURA3).o
	gcc $(FLAGS) -o $(SALIDA) interpreteSSCANF.c $(ESTRUCTURA1).o $(ESTRUCTURA2).o $(ESTRUCTURA3).o

clean: 
	rm *.o salida


