CC:=g++

default: all

all:main

main:test.o bst.o
	$(CC) -g -o main -Wall test.o bst.o

bst.o:bst.cc
	$(CC) -g -c -Wall bst.cc

test.o:test.cc
	$(CC) -g -c -Wall test.cc

