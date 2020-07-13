TEST1 = testing/hashTest
HASH = testing/tablahash.o
TEST2 = testing/itreeTest
ITREE = testing/itree.o

DEPENDENCIAS_TEST = $(TEST1).o $(TEST2).o $(ITREE) $(HASH)

SALIDA = salida

all: main tests

tests: testing/config.c $(DEPENDENCIAS_TEST)
	gcc -o config.out testing/config.c $(DEPENDENCIAS_TEST) -lcunit

$(TEST1): $(TEST1).c $(TEST1).h
	gcc -o $(TEST1).out $(TEST1).c

$(TEST2): $(TEST2).c $(TEST2).h
	gcc -o $(TEST2).out $(TEST2).c

main:
	cd ./src/ && make && mv ./*.o ../testing && cp ./*.h ../testing

clean:
	rm config.out testing/*.o testing/itree.h
