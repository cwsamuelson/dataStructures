CC:= g++
flags:=-Wall -std=c++11
dflags:=-g -DDEBUG
cflags:=-c
libraries:=-llist

default:main

static:liblist.a
dynamic:liblist.so.1.0
libs:static dynamic

main:liblist.a test.o character.o
	$(CC) character.o test.o -L/usr/local/lib/Jing/ $(libraries) -o main

list.o:list.cc
	$(CC) $(cflags) $(flags) list.cc

character.o:character.cc
	$(CC) $(cflags) $(flags) character.cc

test.o:test.cc
	$(CC) $(cflags) -DDEBUG $(flags) test.cc

liblist.a:list.o
	ar rcs liblist.a list.o

dynlist.o:list.cc
	$(CC) -fPIC $(cflags) $(flags) list.cc -o dynlist.o

liblist.so.1.0:dynlist.o
	$(CC) -shared -fPIC -Wl,-soname,liblist.so.1 -o liblist.so.1.0 dynlist.o -lc

clean:
	rm *.o core main liblist.a liblist.so.1.0

wipe:
	rm *.o main core

