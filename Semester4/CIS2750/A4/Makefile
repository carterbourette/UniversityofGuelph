all: A1 A2 A3 A4
CC = cc -ansi -Wall -g
FLAGS =
SRC =

# A1
A1: $(SRC)main.o $(SRC)LinkedList.o $(SRC)Translator.o
	$(CC) $(SRC)main.o $(SRC)LinkedList.o $(SRC)Translator.o -o a1

# A2
A2: stream addauthor post

stream: $(SRC)stream.o $(SRC)stringy.o
	ar cr libstream.a $(SRC)stream.o $(SRC)stringy.o

addauthor: stream $(SRC)addauthor.o
	$(CC) $(SRC)addauthor.o -L. -lstream -o addauthor

post: A1 stream $(SRC)post.cc
	./a1 $(SRC)post.cc
	$(CC) -c $(SRC)post.c $(FLAGS) -o $(SRC)post.o
	$(CC) $(SRC)post.o -L. -lstream -o post

#A3
A3: $(SRC)parse.o $(SRC)stringy.o
	$(CC) $(SRC)parse.o $(SRC)stringy.o -o a3

#A4
A4: $(SRC)db.o $(SRC)stringy.o
	#	For linux distrobution
	#gcc $(SRC)db.o $(SRC)stringy.o -o mydb -lmysqlclient -L/usr/lib/x86_64-linux-gnu/

	#	For mac
	gcc `mysql_config --include` $(SRC)db.o $(SRC)stringy.o `mysql_config --libs` -o db
	./db -create

#	Object Files
$(SRC)main.o: $(SRC)main.c
	$(CC) -c $(SRC)main.c $(FLAGS) -o $(SRC)main.o

$(SRC)LinkedList.o: $(SRC)LinkedList.c
	$(CC) -c $(SRC)LinkedList.c $(FLAGS) -o $(SRC)LinkedList.o

$(SRC)Translator.o: $(SRC)Translator.c
	$(CC) -c $(SRC)Translator.c $(FLAGS) -o $(SRC)Translator.o

$(SRC)addauthor.o: $(SRC)addauthor.c
	$(CC) -c $(SRC)addauthor.c $(FLAGS) -o $(SRC)addauthor.o

$(SRC)stream.o: $(SRC)stream.c
	$(CC) -c $(SRC)stream.c $(FLAGS) -o $(SRC)stream.o

$(SRC)db.o: $(SRC)db.c
	$(CC) -c $(SRC)db.c $(FLAGS) -o $(SRC)db.o

$(SRC)parse.o: $(SRC)parse.c
	$(CC) -c $(SRC)parse.c $(FLAGS) -o $(SRC)parse.o

$(SRC)stringy.o: $(SRC)stringy.c
	$(CC) -c $(SRC)stringy.c $(FLAGS) -o $(SRC)stringy.o

clean:
	rm $(SRC)*.o a1 a3 db addauthor post $(SRC)post.c libstream.a *.html a.out results.txt info.txt

purge:
	./db -reset
