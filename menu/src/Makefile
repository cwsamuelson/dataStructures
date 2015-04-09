CC:=g++
flags:=-Wall -Wextra -pedantic -std=c++11
dflags:=-ggdb3
cflags:=-c

default:main

lib:static

static:libMenu.a
dynamic:libMenu.so
dyn:dynamic
dynamic:libMenu.so

main:libMenu.a test.o
	$(CC) test.o -L/usr/local/lib/Jing/ -lMenu -lexcept -lstring -o main

Menu.o:Menu.cc
	$(CC) $(cflags) $(flags) Menu.cc

test.o:test.cc
	$(CC) $(cflags) $(flags) test.cc

libMenu.a:Menu.o
	ar rcs libMenu.a Menu.o

dynMenu.o:Menu.cc
	$(CC) -fPIC -c Menu.cc -o dynMenu.o

libMenu.so:dynMenu.o
	$(CC) -shared -fPIC -Wl,-soname,libMenu.so.1 -o libMenu.so.1.0 dynMenu.o -lc

clean:
	rm *.o core main

cleanlib:
	rm libmenu.a

