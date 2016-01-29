all: A1PIG
CC = gcc -std=c99 -Wall
FLAGS = -Iinclude
SRC = src/

A1PIG: $(SRC)a1PIG.o
	$(CC) $(SRC)a1PIG.o -o bin/A1PIG

$(SRC)a1PIG.o: $(SRC)a1PIG.c
	$(CC) -c $(SRC)a1PIG.c $(FLAGS) -o $(SRC)a1PIG.o
clean:
	rm *.o A1PIG
run:
	./bin/A1PIG
