all: A1
CC = gcc -std=c99 -Wall
FLAGS = -Iinclude
SRC =

A1: $(SRC)main.o $(SRC)carbon.o $(SRC)ackermann.o $(SRC)newton.o
	$(CC) $(SRC)main.o $(SRC)carbon.o $(SRC)ackermann.o $(SRC)newton.o -o A1

$(SRC)main.o: $(SRC)main.c
	$(CC) -c $(SRC)main.c $(FLAGS) -o $(SRC)main.o

$(SRC) carbon.o: $(SRC)carbon.c
	$(CC) -c $(SRC)carbon.c $(FLAGS) -o $(SRC)carbon.o

$(SRC)ackermann.o: $(SRC)ackermann.c
	$(CC) -c $(SRC)ackermann.c $(FLAGS) -o $(SRC)ackermann.o

$(SRC)newton.o: $(SRC)newton.c
	$(CC) -c $(SRC)newton.c $(FLAGS) -o $(SRC)newton.o

clean:
	rm *.o A1
run:
	./A1
