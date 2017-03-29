all: A1
CC = gcc -std=c99 -Wall
FLAGS = -Iinclude
SRC = src/

A1: $(SRC)main.o $(SRC)lex.yy.o
	#gcc -o msh $(SRC)main.o $(SRC)lex.yy.o -ll
	gcc -o msh $(SRC)main.o $(SRC)lex.yy.o -lfl

$(SRC)main.o: $(SRC)main.c
	$(CC) -c $(SRC)main.c $(FLAGS) -o $(SRC)main.o

$(SRC)lex.yy.o: $(SRC)lex.yy.c
	gcc -Wall -g -c $(SRC)lex.yy.c -o $(SRC)lex.yy.o

$(SRC)lex.yy.c: $(SRC)lex.c
	cd src && flex lex.c && cd ../

clean:
	rm -f $(SRC)*.o
	rm -f $(SRC)lex.yy.c
	rm -f msh
run:
	./msh
