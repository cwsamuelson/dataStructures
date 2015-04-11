CC:=g++
flags:=-Wall -Wextra -pedantic -std=c++11
dflags:=-ggdb3
cflags:=-c $(dflags)

name:= test

default:$(name)

$(name):main.o list.o node.o iterator.o
	$(CC) main.o list.o node.o iterator.o -o $(name)

node.o:node.cc
	$(CC) $(cflags) $(flags) node.cc

iterator.o:iterator.cc
	$(CC) $(cflags) $(flags) iterator.cc

list.o:list.cc
	$(CC) $(cflags) $(flags) list.cc

main.o:main.cc
	$(CC) $(cflags) $(flags) main.cc

clean:
	rm *.o core $(name)
