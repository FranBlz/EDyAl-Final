FLAGS = -Wall -Wextra -Werror -std=c99 -g

ESTRUCTURA1 = itree
ESTRUCTURA2 = tablahash

SALIDA = salida

all: $(ESTRUCTURA1).o $(ESTRUCTURA2).o main

$(ESTRUCTURA1).o: $(ESTRUCTURA1).c $(ESTRUCTURA1).h
	gcc $(FLAGS) -c $(ESTRUCTURA1).c

$(ESTRUCTURA2).o: $(ESTRUCTURA2).c $(ESTRUCTURA2).h
	gcc $(FLAGS) -c  $(ESTRUCTURA2).c

main: interpreteSSCANF.c $(ESTRUCTURA1).o $(ESTRUCTURA2).o
	gcc $(FLAGS) -o $(SALIDA) interpreteSSCANF.c $(ESTRUCTURA1).o $(ESTRUCTURA2).o

clean: 
	rm *.o salida

# FLAGS = -Wall -Wextra -Werror -std=c99 -g

# ESTRUCTURA1 = itree
# ESTRUCTURA2 = tablahash

# all: $(ESTRUCTURA1).o $(ESTRUCTURA2).o

# $(ESTRUCTURA1).o: $(ESTRUCTURA1).c $(ESTRUCTURA1).h
# 	gcc $(FLAGS) -c $(ESTRUCTURA1).c

# $(ESTRUCTURA2).o: $(ESTRUCTURA2).c $(ESTRUCTURA2).h
# 	gcc $(FLAGS) -c  $(ESTRUCTURA2).c

# clean: 
# 	rm *.o vgcore*
