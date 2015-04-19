CC:= g++
flags:=-Wall -Wextra -pedantic -std=c++11
dflags:=-ggdb3
cflags:=-c $(dflags)

name:=main

default:$(name)

$(name):$(name).o
	$(CC) $(name).o -o $(name)

$(name).o:$(name).cc vector.cc vector_iterator.cc
	$(CC) $(cflags) $(flags) $(name).cc

clean:
	rm *.o core $(name)

