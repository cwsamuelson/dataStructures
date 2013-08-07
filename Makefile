all: LinkedList

default: LinkedList

LinkedList: LinkedList.hh main.cc
	g++  -Wall -o main main.cc

debug: LinkedList.hh main.cc
	g++ -DDEBUG -g -Wall -o main main.cc

clean:
	rm -f main
