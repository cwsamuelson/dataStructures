CC:= g++
flags:=-Wall -std=c++11
dflags:=-ggdb3
cflags:=-c $(dflags)

default:lib

lib:static

static:libcharacter.a
dynamic:libcharacter.so
dyn:dynamic

main:test.o
	$(CC) test.o -L/usr/local/lib/Jing/ -lcharacter -o main

character.o:character.cc
	$(CC) $(cflags) $(flags) character.cc

test.o:test.cc
	$(CC) $(cflags) $(flags) test.cc

#flags used for precompiled header must be the same as for compilation
test.hh.gch:test.hh
	$(CC) $(dflags) $(flags) test.hh

libcharacter.a:character.o
	ar rcs libcharacter.a character.o

dyncharacter.o:character.cc
	$(CC) -fPIC -c character.cc -o dyncharacter.o

libcharacter.so:dyncharacter.o
	$(CC) -shared -fPIC -Wl,-soname,libcharacter.so.1 -o libcharacter.so.1.0 dyncharacter.o -lc

clean:
	rm *.o core main test.hh.gch

