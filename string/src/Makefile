CC:=g++

default:main

lib:static

static:libstring.a
dynamic:libstring.so
dyn:dynamic
dynamic:libstring.so

main:libstring.a test.o
	$(CC) test.o -L/usr/local/lib/Jing/ -lstring -lexcept -o main

string.o:string.cc
	$(CC) -c -Wall string.cc

test.o:test.cc
	$(CC) -c -Wall test.cc

libstring.a:string.o
	ar rcs libstring.a string.o

dynstring.o:string.cc
	$(CC) -fPIC -c string.cc -o dynstring.o

libstring.so:dynstring.o
	$(CC) -shared -fPIC -Wl,-soname,libstring.so.1 -o libstring.so.1.0 dynstring.o -lc

clean:
	rm *.o core main

cleanlib:
	rm libstring.a

