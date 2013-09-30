CC=g++
CFLAGS=-c -Wall
DBGFLAGS=-DDEBUG -g -Wall

all: LinkedList

default: LinkedList

LinkedList:

debug: LinkedList.hh test.o
	$(CC) $(DBGFLAGS) -o test test.cc

test.o: test.cc
	$(CC) $(CFLAGS) test.cc

clean:
	rm -f *.o test

