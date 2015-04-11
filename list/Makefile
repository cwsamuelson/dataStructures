CC:=g++
flags:=-Wall -Wextra -pedantic -std=c++11
dflags:=-ggdb3
cflags:=-c $(dflags)

name:= test

default:$(name)

$(name):main.o list.o
	$(CC) main.o list.o -o $(name)

list.o:list.cc
	$(CC) $(cflags) $(flags) list.cc

main.o:main.cc
	$(CC) $(cflags) $(flags) main.cc

clean:
	rm *.o core $(name)
