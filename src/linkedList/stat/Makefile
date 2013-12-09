CC:= g++
flags:=-Wall
dflags:=-g -DDEBUG
cflags:=-c

default: all

all:main

main:test.o LinkedList.o
	$(CC) $(flags) -o main test.o LinkedList.o

test.o:test.cc
	$(CC) $(dflags) $(cflags) $(flags) test.cc

LinkedList.o:LinkedList.cc
	$(CC) $(dflags) $(cflags) $(flags) LinkedList.cc

pch.hh.gch:pch.hh
	$(CC) pch.hh

clean:
	rm *.o main pch.hh.gch

