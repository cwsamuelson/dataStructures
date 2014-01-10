CC:= g++
flags:=-Wall
dflags:=-g -DDEBUG
cflags:=-c

default: all

all:main

list:list.o

main:test.o list.o
	$(CC) $(flags) -o main test.o list.o

test.o:test.cc
	$(CC) $(dflags) $(cflags) $(flags) test.cc

list.o:list.cc
	$(CC) $(dflags) $(cflags) $(flags) list.cc

clean:
	rm *.o main

