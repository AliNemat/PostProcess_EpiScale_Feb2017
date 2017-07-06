CC=g++ -std=c++11

CFLAGS=-c -Wall

all: cell

cell: main.o area.o
		$(CC) main.o area.o -o cell

main.o: main.cpp
		$(CC) $(CFLAGS) main.cpp

area.o: area.cpp
		$(CC) $(CFLAGS) area.cpp

clean:
		rm -rf *o exec
