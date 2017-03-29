all: A2
CC = gcc -std=c99 -Wall
FLAGS = -Iinclude
SRC = src/

A2: $(SRC)main.o $(SRC)Schedule.o $(SRC)LinkedList.o
	gcc -o simcpu $(SRC)main.o $(SRC)LinkedList.o $(SRC)Schedule.o

$(SRC)main.o: $(SRC)main.c
	$(CC) -c $(SRC)main.c $(FLAGS) -o $(SRC)main.o

$(SRC)Schedule.o: $(SRC)Schedule.c
	$(CC) -c $(SRC)Schedule.c $(FLAGS) -o $(SRC)Schedule.o

$(SRC)LinkedList.o: $(SRC)LinkedList.c
	$(CC) -c $(SRC)LinkedList.c $(FLAGS) -o $(SRC)LinkedList.o

clean:
	rm src/*.o simcpu
run:
	./simcpu -v -d -debug < assets/sample.txt
sample:
	./simcpu -v -d -debug -r 10  < assets/testcase1.txt
