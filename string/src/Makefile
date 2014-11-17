CC:= g++
flags:=-Wall -std=c++11
dflags:=-ggdb3
cflags:=-c $(dflags)

default:lib

lib:static

static:libstring.a
dynamic:libstring.so
dyn:dynamic

main:test.o libstring.a
	$(CC) test.o -L/usr/local/lib/Jing/ -lcharacter -o main -lstring

string.o:string.cc
	$(CC) $(cflags) $(flags) string.cc

test.o:test.cc
	$(CC) $(cflags) $(flags) test.cc

test.hh.gch:test.hh
	$(CC) $(dflags) $(flags) test.hh

libstring.a:string.o
	ar rcs libstring.a string.o

dynstring.o:string.cc
	$(CC) -fPIC -c string.cc -o dynstring.o

libstring.so:dynstring.o
	$(CC) -shared -fPIC -Wl,-soname,libstring.so.1 -o libstring.so.1.0 dynstring.o -lc

clean:
	rm *.o core main libstring.a

