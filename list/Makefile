CC:=g++
flags:=-Wall -Wextra -pedantic -std=c++11
dflags:=-ggdb3
cflags:=-c $(dflags)

name:= test

default:$(name)

$(name):main.o
	$(CC) main.o -o $(name)

main.o:main.cc list.cc list_iterator.cc list_node.cc
	$(CC) $(cflags) $(flags) main.cc

clean:
	rm *.o core $(name)
