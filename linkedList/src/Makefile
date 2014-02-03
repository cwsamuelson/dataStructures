CC:= g++
flags:=-Wall
dflags:=-g -DDEBUG
cflags:=-c

default: all

all:main

main:test.o list.h
	$(CC) $(dflags) -o main test.o

test.o:test.cc list.h
	$(CC) $(dflags) $(cflags) $(flags) test.cc

list.h:list.cc

clean:
	rm *.o main core

