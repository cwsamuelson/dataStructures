CC:= g++
flags:=-Wall
dflags:=-c -g -DDEBUG

default: all

all:main

main:test.o LinkedList.o
	$(CC) $(flags) -o main test.o LinkedList.o

test.o:test.cc
	$(CC) $(dflags) $(flags) test.cc

LinkedList.o:LinkedList.cc
	$(CC) $(dflags) $(flags) LinkedList.cc

clean:
	rm *.o main

