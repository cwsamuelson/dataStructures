CC:= g++
flags:=-Wall -std=c++11
dflags:=-ggdb3
cflags:=-c $(dflags)

default:main

main:test.o
	$(CC) test.o -L/usr/local/lib/Jing/ -lcharacter -o main

test.o:List.cc test.cc
	$(CC) $(cflags) $(flags) test.cc

#flags used for precompiled header must be the same as for compilation
test.hh.gch:test.hh List.cc
	$(CC) $(dflags) $(flags) test.hh

clean:
	rm *.o core main test.hh.gch

