all: A4
CC = gcc -std=c99 -Wall
FLAGS = -Iinclude
SRC = src/

A4: $(SRC)avltree.o
	$(CC) $(SRC)avltree.o -o A4

$(SRC)avltree.o: $(SRC)avltree.c
	$(CC) -c $(SRC)avltree.c $(FLAGS) -o $(SRC)avltree.o

$(SRC)Testing.o: $(SRC)Testing.c
	$(CC) -c $(SRC)Testing.c $(FLAGS) -o $(SRC)Testing.o

test:
	./A4Test

clean:
	rm src/*.o A4

run:
	./A4 
