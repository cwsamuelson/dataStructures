CC:= g++
flags:=-Wall -std=c++11
dflags:=-ggdb3
cflags:=-c $(dflags)

default:lib

lib:static

static:libinteger.a
dynamic:libinteger.so
dyn:dynamic

main:test.o
	$(CC) test.o -L/usr/local/lib/Jing/ -linteger -o main

Integer.o:Integer.cc
	$(CC) $(cflags) $(flags) Integer.cc

test.o:test.cc
	$(CC) $(cflags) $(flags) test.cc

#flags used for precompiled header must be the same as for compilation
test.hh.gch:test.hh
	$(CC) $(dflags) $(flags) test.hh

libinteger.a:Integer.o
	ar rcs libinteger.a Integer.o

dyninteger.o:Integer.cc
	$(CC) -fPIC -c Integer.cc -o dyninteger.o

libinteger.so:dyninteger.o
	$(CC) -shared -fPIC -Wl,-soname,libinteger.so.1 -o libinteger.so.1.0 dyninteger.o -lc

clean:
	rm *.o core main libinteger.a

