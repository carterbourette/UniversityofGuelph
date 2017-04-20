all: A2
CC = gcc -std=c99 -Wall
FLAGS = -Iinclude
SRC = src/

A2: $(SRC)p1.o $(SRC)Cars.o $(SRC)Parse.o $(SRC)LinkedList.o $(SRC)p2.o
	$(CC) $(SRC)p1.o $(SRC)Cars.o $(SRC)Parse.o $(SRC)LinkedList.o -o A2p1
	$(CC) $(SRC)p2.o $(SRC)LinkedList.o -o A2p2

$(SRC)p1.o: $(SRC)p1.c
	$(CC) -c $(SRC)p1.c $(FLAGS) -o $(SRC)p1.o

$(SRC)Cars.o: $(SRC)Cars.c
	$(CC) -c $(SRC)Cars.c $(FLAGS) -o $(SRC)Cars.o

$(SRC)Parse.o: $(SRC)Parse.c
	$(CC) -c $(SRC)Parse.c $(FLAGS) -o $(SRC)Parse.o

$(SRC)LinkedList.o: $(SRC)LinkedList.c
	$(CC) -c $(SRC)LinkedList.c $(FLAGS) -o $(SRC)LinkedList.o

$(SRC)p2.o: $(SRC)p2.c
	$(CC) -c $(SRC)p2.c $(FLAGS) -o $(SRC)p2.o

$(SRC)TestDriver.o: $(SRC)TestDriver.c
	$(CC) -c $(SRC)TestDriver.c $(FLAGS) -o $(SRC)TestDriver.o

$(SRC)Testing.o: $(SRC)Testing.c
	$(CC) -c $(SRC)Testing.c $(FLAGS) -o $(SRC)Testing.o


test: $(SRC)TestDriver.o $(SRC)Testing.o $(SRC)Cars.o $(SRC)LinkedList.o
	$(CC) $(SRC)TestDriver.o $(SRC)Testing.o $(SRC)Cars.o $(SRC)LinkedList.o -o A2test

clean:
	rm src/*.o A2
P1:
	./A2p1

P2:
	./A2p2 "12+53-*"
