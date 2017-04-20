all: A3
CC = gcc -std=c99 -Wall
FLAGS = -Iinclude
SRC = src/

A3: $(SRC)p1.o $(SRC)p2.o $(SRC)Tree.o
	$(CC) $(SRC)p1.o $(SRC)Tree.o -o A3p1
	$(CC) $(SRC)p2.o -o A3p2

$(SRC)p1.o: $(SRC)p1.c
	$(CC) -c $(SRC)p1.c $(FLAGS) -o $(SRC)p1.o

$(SRC)p2.o: $(SRC)p2.c
	$(CC) -c $(SRC)p2.c $(FLAGS) -o $(SRC)p2.o

$(SRC)Tree.o: $(SRC)Tree.c
	$(CC) -c $(SRC)Tree.c $(FLAGS) -o $(SRC)Tree.o

$(SRC)Testing.o: $(SRC)Testing.c
	$(CC) -c $(SRC)Testing.c $(FLAGS) -o $(SRC)Testing.o

clean:
	rm src/*.o A3p1 A3p2

P1:
	./A3p1 "(((x1+5.12)*(x2-7.68))/x3)"

P2:
	./A3p2
