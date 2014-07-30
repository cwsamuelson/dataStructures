CC:= g++
flags:=-Wall -std=c++11
dflags:=-ggdb3
cflags:=-c $(dflags)

default:main

main:test.o character.o
	$(CC) character.o test.o -L/usr/local/lib/Jing/ -o main

character.o:character.cc
	$(CC) $(cflags) $(flags) character.cc

test.o:list.cc test.cc
	$(CC) $(cflags) $(flags) test.cc

clean:
	rm *.o core main

