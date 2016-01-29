all: A1
CC = gcc -std=c99 -Wall
FLAGS = -Iinclude
SRC = src/

A1: $(SRC)main.o $(SRC)storeval.o $(SRC)template.o
	$(CC) $(SRC)main.o $(SRC)storeval.o $(SRC)template.o -o bin/A1

$(SRC)main.o: $(SRC)main.c
	$(CC) -c $(SRC)main.c $(FLAGS) -o $(SRC)main.o

$(SRC)storeval.o: $(SRC)storeval.c
	$(CC) -c $(SRC)storeval.c $(FLAGS) -o $(SRC)storeval.o

$(SRC)template.o: $(SRC)template.c
	$(CC) -c $(SRC)template.c $(FLAGS) -o $(SRC)template.o

clean:
	rm *.o A1
run:
	./bin/A1 assets/template.txt assets/variables.txt assets/output.txt
