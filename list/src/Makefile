CC:= g++
flags:=-Wall
dflags:=-g -DDEBUG
cflags:=-c

default:main

lib:static
static:liblist.a
dynamic:liblist.so
dyn:dynamic

main:liblist.a test.o
	$(CC) testing.o test.o -L/usr/local/lib/Jing/ -lexcept -lstring -o main

list.o:list.cc
	$(CC) -c -Wall list.cc

test.o:test.cc
	$(CC) -c -Wall test.cc

liblist.a:list.o
	ar rcs liblist.a list.o

dynlist.o:list.cc
	$(CC) -fPIC -c list.cc -o dynlist.o

liblist.so:dynlist.o
	$(CC) -shared -fPIC -Wl,-soname,liblist.so.1 -o liblist.so.1.0 dynlist.o -lc

clean:
	rm *.o core main

cleanlib:
	rm liblist.a

