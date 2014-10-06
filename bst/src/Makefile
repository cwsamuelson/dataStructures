CC:= g++
flags:=-Wall -std=c++11
dflags:=-ggdb3
cflags:=-c $(dflags)

default:main

main:test.o
	$(CC) test.o -L/usr/local/lib/Jing/ -lcharacter -linteger -o main

test.o:test.hh test.cc
	$(CC) $(cflags) $(flags) test.cc

test.hh.gch:test.hh BST.cc
	$(CC) $(dflags) $(flags) test.hh

clean:
	rm *.o main core

