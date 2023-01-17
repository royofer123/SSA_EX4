CC = gcc
AR = ar
FLAGS = -Wall -g 
OBJECTS = main.o nodes.o algo.o

algo.o: algo.c algo.h nodes.h
	$(CC) $(FLAGS) -c algo.c

nodes.o: nodes.c nodes.h 
	$(CC) $(FLAGS) -c nodes.c

main.o: main.c algo.h 
	$(CC) $(FLAGS) -c main.c

graph: $(OBJECTS) 
	$(CC) $(FLAGS) -o graph $(OBJECTS)

all: graph

.PHONY:
	all clean
clean:
	rm -f graph *.o