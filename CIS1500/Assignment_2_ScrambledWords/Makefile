all: WordScrambler
CC = gcc -std=c99 -Wall
FLAGS = -Iinclude
SRC = src/

WordScrambler: $(SRC)main.o $(SRC)Scram.o
	$(CC) $(SRC)main.o $(SRC)Scram.o -o bin/WordScrambler

$(SRC)main.o: $(SRC)main.c
	$(CC) -c $(SRC)main.c $(FLAGS) -o $(SRC)main.o

$(SRC)Scram.o: $(SRC)Scram.c
	$(CC) -c $(SRC)Scram.c $(FLAGS) -o $(SRC)Scram.o

clean:
	rm *.o WordScrambler
run:
	./bin/WordScrambler
