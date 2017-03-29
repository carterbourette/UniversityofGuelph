all: A2
CC = gcc -g -std=c99 -Wall
FLAGS = -Iinclude
SRC = src/

A2: $(SRC)main.o $(SRC)LinkedList.o $(SRC)interface.o
	$(CC) $(SRC)main.o $(SRC)LinkedList.o $(SRC)interface.o  -lncurses -o bin/A2

$(SRC)main.o: $(SRC)main.c
	$(CC) -c $(SRC)main.c $(FLAGS) -o $(SRC)main.o

$(SRC)LinkedList.o: $(SRC)LinkedList.c
	$(CC) -c $(SRC)LinkedList.c $(FLAGS) -o $(SRC)LinkedList.o

$(SRC)interface.o: $(SRC)interface.c
	$(CC) -c $(SRC)interface.c $(FLAGS) -lncurses -o $(SRC)interface.o

clean:
	rm src/*.o bin/A2
run:
	./bin/A2 assets/input.txt
