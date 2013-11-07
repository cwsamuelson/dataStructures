default: all

all:main

main:test.o bst.o
	g++ -g -o main -Wall test.o bst.o

bst.o:bst.cc
	g++ -g -c -Wall bst.cc

test.o:test.cc
	g++ -g -c -Wall test.cc

