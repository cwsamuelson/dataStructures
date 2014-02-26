CC:= g++
flags:=-Wall
dflags:=-g -DDEBUG
cflags:=-c

default:main

main:test.o list.cc
	$(CC) test.o -L/usr/local/lib/Jing -lexcept -lstring -o main

test.o:test.cc
	$(CC) -c -Wall test.cc

clean:
	rm *.o main core

