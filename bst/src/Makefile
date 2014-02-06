CC:= g++
flags:=-Wall
dflags:=-g -DDEBUG
cflags:=-c

default: all

all:main

main:test.o
	$(CC) $(dflags) -o main test.o

test.o:test.cc bst.hh bst.cc
	$(CC) $(dflags) $(cflags) $(flags) test.cc

bst.hh:bst.cc

clean:
	rm *.o main core

