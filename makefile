TEST1 = testing/hashTest
ESTRUCT1 = hash
TEST2 = testing/treeTest
ESTRUCT2 = tree
ITREE = testing/itree.o
TEST3 = testing/itreeTest
DEPENDENCIAS_TEST = $(TEST1).o $(TEST2).o $(TEST3).o $(ITREE)

SALIDA = salida

all: main tests

tests: testing/config.c $(DEPENDENCIAS_TEST)
	gcc -o config.out testing/config.c $(DEPENDENCIAS_TEST) -lcunit

$(TEST1): $(TEST1).c $(TEST1).h
	gcc -o $(TEST1).out $(TEST1).c

$(TEST3): $(TEST3).c $(TEST3).h
	gcc -c $(TEST3).c

$(TEST2): $(TEST2).c $(TEST2).h
	gcc -o $(TEST2).out $(TEST2).c

main:
	cd ./src/ && make && mv ./*.o ../testing && cp ./*.h ../testing

clean:
	rm config.out testing/*.o testing/itree.h
