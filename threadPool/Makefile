CC:= g++
flags:=-Wall -Wextra -pedantic -std=c++11
dflags:=-ggdb3
cflags:=-c $(dflags)

default:main

main:test.o
	$(CC) test.o -lpthread -o main

test.o:test.cc
	$(CC) $(cflags) $(flags) test.cc

clean:
	rm *.o core main

