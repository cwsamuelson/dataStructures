CC:=g++

default:test

test:main

lib:static

main:string.o test.o
	$(CC) -L/usr/local/lib/Jing/ -lstring test.o -o main

string.o:string.cc
	$(CC) -c string.cc

test.o:test.cc
	$(CC) test.cc -c string.cc

static:string.o
	ar -cvq libstring.a string.o

dynstring.o:string.cc
	$(CC) -Wall -fPIC -c string.cc

dynamic:dynstring.o
	$(CC) -shared -fPIC -Wl,-soname,libstring.so.1 -o libstring.so.1.0 dynstring.o -lc

clean:
	rm *.o core main

