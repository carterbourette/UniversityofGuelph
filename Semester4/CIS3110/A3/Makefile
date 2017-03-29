all: holes dine
CC = gcc -std=c99 -Wall
FLAGS = -Iinclude
SRC = src/

dine: $(SRC)dine.o $(SRC)stringy.o
	gcc -o dine $(SRC)dine.o $(SRC)stringy.o -pthread
holes: $(SRC)holes.o $(SRC)LinkedList.o $(SRC)stringy.o
	gcc -o holes $(SRC)holes.o $(SRC)LinkedList.o $(SRC)stringy.o

$(SRC)dine.o: $(SRC)dine.c
	$(CC) -c $(SRC)dine.c $(FLAGS) -o $(SRC)dine.o

$(SRC)holes.o: $(SRC)holes.c
	$(CC) -c $(SRC)holes.c $(FLAGS) -o $(SRC)holes.o

$(SRC)LinkedList.o: $(SRC)LinkedList.c
	$(CC) -c $(SRC)LinkedList.c $(FLAGS) -o $(SRC)LinkedList.o

$(SRC)stringy.o: $(SRC)stringy.c
	$(CC) -c $(SRC)stringy.c $(FLAGS) -o $(SRC)stringy.o

clean:
	rm src/*.o dine holes

rdine:
	./dine 3 2

rholes:
	./holes testfile1
