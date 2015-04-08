CC:= g++
flags:=-Wall -Wextra -pedantic -std=c++11
dflags:=-ggdb3
cflags:=-c $(dflags)

default:main

main:test.o
	$(CC) test.o -o main

test.o:test.hh.gch test.cc
	$(CC) $(cflags) $(flags) test.cc

#flags used for precompiled header must be the same as for compilation
test.hh.gch:test.hh memoryPool.cc
	$(CC) $(cflags) $(flags) test.hh

clean:
	rm *.o core main test.hh.gch

