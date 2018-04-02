CC=g++ -std=c++11

CFLAGS=-c -Wall

all: cell

cell: main.o stat.o
		$(CC) main.o stat.o -o cell

main.o: main.cpp
		$(CC) $(CFLAGS) main.cpp

stat.o: stat.cpp
		$(CC) $(CFLAGS) stat.cpp

clean:
		rm -rf *o cell
