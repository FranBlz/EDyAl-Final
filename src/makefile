ESTRUCTURA1 = itree
ESTRUCTURA2 = tablahash

all: $(ESTRUCTURA1).o $(ESTRUCTURA2).o

$(ESTRUCTURA1).o: $(ESTRUCTURA1).c $(ESTRUCTURA1).h
	gcc -c -Wall -Werror $(ESTRUCTURA1).c

$(ESTRUCTURA2).o: $(ESTRUCTURA2).c $(ESTRUCTURA2).h
	gcc -c -Wall -Werror $(ESTRUCTURA2).c

clean: 
	rm *.o vgcore*