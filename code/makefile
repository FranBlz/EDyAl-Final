ESTRUCTURA = tablahash

all: $(ESTRUCTURA).o main

main: main2.c $(ESTRUCTURA).o
	gcc -o main main2.c $(ESTRUCTURA).o

$(ESTRUCTURA).o: $(ESTRUCTURA).c $(ESTRUCTURA).h
	gcc -c -Wall -Werror $(ESTRUCTURA).c

clean: 
	rm *.o vgcore*