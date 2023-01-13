FLAGS = -Wall -g
CC = gcc

all: graph

nodes.o: nodes.c nodes.h
	$(CC) $(FLAGS) -c nodes.c -lm

edges.o: edges.c edges.h
	$(CC) $(FLAGS) -c edges.c -lm

main.o: main.c main.h
	$(CC) $(FLAGS) -c main.c -lm

graph: main.o edges.o nodes.o
	$(CC) $(FLAGS) -o graph main.o edges.o nodes.o -lm

.PHONY: clean all

clean:
	rm -f *.o graph
 
 